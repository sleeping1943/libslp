version_file:=$(shell pwd)/SPECS/libshelper.version

export version_file
.PHONY:show show_build clean clean_rpms

all:
	@sh ./script/chg_rpm_home.sh
	@rpmbuild -bb ./SPECS/libslp.spec

show:
	@make show -C ./SOURCES/libslp

show_build:
	@tree ./BUILD
	@tree ./BUILDROOT
	@tree ./RPMS

clean_rpms:
	@rm -fr ./RPMS/x86_64/*

clean:clean_rpms
	@rm -fr ./BUILDROOT/*
	@make clean -C ./SOURCES/libslp
