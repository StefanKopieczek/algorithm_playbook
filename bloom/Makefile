bloom_test:
	gcc -I../bitfield ../bitfield/bitfield.c murmur3.c bloom.c bloom_test.c -o bloom_test

run_test_script:
	./bloom_test

all: bloom_test.c

clean:
	@-rm bloom_test 2>/dev/null ||:

test: clean bloom_test run_test_script
