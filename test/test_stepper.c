#include "stepper.h"
#include "mockpi.h"
#include <check.h>

void setup(void)
{
	init_mocks();
}

void teardown(void)
{
	// Do nothing
}

START_TEST(stepper_create_does_not_fire_pins)
{
	struct stepper *s = stepper_create(1,2,3,4);
	ck_assert_int_eq(digital_write_count(), 0);
	stepper_destroy(s);
}
END_TEST

START_TEST(stepper_create_returns_stepper_ptr)
{
	struct stepper *s = stepper_create(1, 2, 3, 4);
	ck_assert_ptr_ne(s, NULL);
	stepper_destroy(s);
}
END_TEST

TCase *tcase_stepper(void)
{
	TCase *tc;

	tc = tcase_create("stepper");
	tcase_add_test(tc, stepper_create_does_not_fire_pins);
	tcase_add_test(tc, stepper_create_returns_stepper_ptr);

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
