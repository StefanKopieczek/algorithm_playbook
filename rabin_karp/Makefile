include ../bloom/Makefile

rabin_karp_dir = ../rabin_karp

compile_rabin_karp: make_obj_dir package_bloom
	cd ${obj_dir} && gcc -c -I${bloom_dir} -I${bitfields_dir} ${rabin_karp_dir}/rabin_karp.c -lbloom

package_rabin_karp: compile_rabin_karp make_obj_dir make_dist_dir
	ar -cvq ${dist_dir}/librabinkarp.a ${obj_dir}/rabin)karp.o

compile_rabin_karp_tests: package_bloom make_dist_dir make_bin_dir
	cd ${rabin_karp_dir} && gcc -I${bloom_dir} -I${bitfields_dir} rabin_karp.c rabin_karp_test.c -L${dist_dir} -lbloom -o ${bin_dir}/rabin_karp_tests

test_rabin_karp: clean_dist_dir clean_obj_dir clean_bin_dir compile_rabin_karp_tests
	${bin_dir}/rabin_karp_tests
