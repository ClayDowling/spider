check_CFLAGS = `pkg-config --cflags check`
wiring_CFLAGS = -I$(HOME)/workspace/wiringPi/wiringPi
CFLAGS = -std=c11 -I../src -I../mock $(wiring_CFLAGS) $(check_CFLAGS)
LIBS = `pkg-config --libs check`
VPATH=../src ../mock

TEST_OBJECTS = test_stepper.o
MOCKS = mockpi.o
SUT = stepper.o

all: test_stepper
	./test_stepper

test_stepper: $(SUT) $(TEST_OBJECTS) $(MOCKS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

memtest: test_stepper
	CK_FORK=no valgrind --leak-check=full ./test_stepper

clean:
	rm -f *.o
	rm -rf *.dSYM
	rm -f test_stepper
