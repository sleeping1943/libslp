
all:
	@sh ./script/chg_rpm_home.sh
	@rpmbuild -bb ./SPECS/libslp.spec

clean_rpms:
	@rm -fr ./RPMS/x86_64/*

clean:clean_rpms
	@rm -fr ./BUILDROOT/*
