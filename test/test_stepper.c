#include "stepper.h"
#include "mockpi.h"
#include <check.h>

struct stepper *s = NULL;

#define PIN_A 1
#define PIN_B 2
#define PIN_C 3
#define PIN_D 4

int pin_ptr;

void setup(void)
{
	init_mocks();
	s = stepper_create(PIN_A,PIN_B,PIN_C,PIN_D);
	pin_ptr = 0;
}

void teardown(void)
{
	stepper_destroy(s);
}

void validate_step(int pinA, int pinB, int pinC, int pinD)
{
	struct pin_setting hist;
	int idx;

	for(idx = 0; idx < 4; ++idx) {
		hist = digital_write_history(pin_ptr);
		switch(hist.pin) {
			case PIN_A:
				ck_assert_int_eq(pinA, hist.value);
				break;
			case PIN_B:
				ck_assert_int_eq(pinB, hist.value);
				break;
			case PIN_C:
				ck_assert_int_eq(pinC, hist.value);
				break;
			case PIN_D:
				ck_assert_int_eq(pinD, hist.value);
				break;
		}
		++pin_ptr;
	}
}

START_TEST(stepper_create_does_not_fire_pins)
{
	ck_assert_int_eq(digital_write_count(), 0);
}
END_TEST

START_TEST(stepper_create_returns_stepper_ptr)
{
	ck_assert_ptr_ne(s, NULL);
}
END_TEST

START_TEST(stepper_create_sets_pins_for_write)
{
	struct pin_setting hist;

	ck_assert_int_eq(pin_mode_count(), 4);

	hist = pin_mode_history(0);
	ck_assert_int_eq(hist.pin, PIN_A);
	ck_assert_int_eq(hist.value, OUTPUT);

	hist = pin_mode_history(1);
	ck_assert_int_eq(hist.pin, PIN_B);
	ck_assert_int_eq(hist.value, OUTPUT);

	hist = pin_mode_history(2);
	ck_assert_int_eq(hist.pin, PIN_C);
	ck_assert_int_eq(hist.value, OUTPUT);

	hist = pin_mode_history(3);
	ck_assert_int_eq(hist.pin, PIN_D);
	ck_assert_int_eq(hist.value, OUTPUT);
}
END_TEST

START_TEST(stepper_step_sets_pins_a_and_c_high)
{
	struct pin_setting hist;
	stepper_step(s, 1, 100);

	validate_step(HIGH, 555, HIGH, LOW);
}
END_TEST

TCase *tcase_stepper(void)
{
	TCase *tc;

	tc = tcase_create("stepper");
	tcase_add_test(tc, stepper_create_does_not_fire_pins);
	tcase_add_test(tc, stepper_create_returns_stepper_ptr);
	tcase_add_test(tc, stepper_create_sets_pins_for_write);
	tcase_add_test(tc, stepper_step_sets_pins_a_and_c_high);
	tcase_add_checked_fixture(tc, setup, teardown);

	return tc;
}

Suite *suite_spider(void)
{
	Suite *s;

	s = suite_create("spider");

	suite_add_tcase(s, tcase_stepper());

	return s;
}

int main(int argc, char **argv)
{
	Suite *s;
	SRunner *runner;
	int number_fails;

	s = suite_spider();
	runner = srunner_create(s);
	srunner_run_all(runner, CK_NORMAL);
	number_fails = srunner_ntests_failed(runner);
	srunner_free(runner);

	return number_fails;
}
