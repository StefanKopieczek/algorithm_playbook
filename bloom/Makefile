include ../bitfields/Makefile

compile_test_script: package_bitfields
	gcc -I../bitfields murmur3.c bloom.c bloom_test.c -L. -lbitfields -o bloom_test

test_bloom: compile_test_script
	./bloom_test

all: bloom_test.c

clean:
	@-rm bloom_test 2>/dev/null ||:

test: clean bloom_test run_test_script
