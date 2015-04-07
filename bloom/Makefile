include ../bitfields/Makefile

bloom_dir = ../bloom

compile_bloom: make_obj_dir package_bitfields
	cd ${obj_dir} && gcc -c -I${bitfields_dir} ${bloom_dir}/bloom.c ${bloom_dir}/murmur3.c -L${dist_dir} -lbitfields

package_bloom: compile_bloom make_obj_dir make_dist_dir
	ar -cvq ${dist_dir}/libbloom.a ${obj_dir}/bloom.o ${obj_dir}/murmur3.o

compile_test_script: package_bitfields make_dist_dir make_bin_dir
	cd ${bloom_dir} && gcc -I${bitfields_dir} murmur3.c bloom.c bloom_test.c -L${dist_dir} -lbitfields -o ${bin_dir}/bloom_tests

test_bloom: clean_dist_dir clean_obj_dir clean_bin_dir compile_test_script
	${bin_dir}/bloom_tests
