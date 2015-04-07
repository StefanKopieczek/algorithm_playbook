compile_bitfields:
	gcc -c ../bitfields/bitfields.c

package_bitfields: compile_bitfields
	ar -cvq libbitfields.a bitfields.o

compile_bitfields_tests:
	gcc ../bitfields/*.c -o bitfields_tests

test_bitfields: clean_bitfields compile_bitfields_tests
	./bitfields_tests

clean_bitfields_objects:
	@-rm ../bitfields/*.o 2> /dev/null ||:

clean_bitfields_libraries:
	@-rm libbitfields.a 2> /dev/null ||:

clean_bitfields_binaries:
	@rm ../bitfields/bitfield_test 2>/dev/null ||:

clean_bitfields: clean_bitfields_objects clean_bitfields_libraries clean_bitfields_binaries


