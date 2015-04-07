# Utilities and variables to be used by other Makefiles.
# All paths are prepended with ../ so that they can be used by the
# individual Makefiles in each component folder.

dist_dir = ../dist
obj_dir = ../obj
bin_dir = ../bin

clean: clean_dist_dir clean_bin_dir clean_obj_dir

clean_dist_dir:
	@-rm -rf ${dist_dir} 2> /dev/null ||:

make_dist_dir:
	@-mkdir -p ${dist_dir} 2> /dev/null ||:

clean_obj_dir:
	@-rm -rf ${obj_dir} 2> /dev/null ||:

make_obj_dir:
	@-mkdir -p ${obj_dir} 2> /dev/null ||:

clean_bin_dir:
	@-rm -rf ${bin_dir} 2> /dev/null ||:

make_bin_dir:
	@-mkdir -p ${bin_dir} 2> /dev/null ||:
