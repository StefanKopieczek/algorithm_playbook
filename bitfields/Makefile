include ../Makefile

bitfields_dir = ../bitfields

compile_bitfields: make_obj_dir
	cd ${obj_dir} && gcc -c ${bitfields_dir}/bitfields.c

package_bitfields: compile_bitfields make_obj_dir make_dist_dir
	ar -cvq ${dist_dir}/libbitfields.a ${obj_dir}/bitfields.o

compile_bitfields_tests: make_bin_dir
	gcc ${bitfields_dir}/*.c -o ${bin_dir}/bitfields_tests

test_bitfields: clean_obj_dir clean_bin_dir compile_bitfields_tests
	${bin_dir}/bitfields_tests
