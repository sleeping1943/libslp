CXX:=g++
target:=libshelper
cpps:=$(wildcard ./src/*.cpp)
objs:=$(cpps:%.cpp=%.o)
CFALGS:= -c -fPIC -o
LDFALGS:=  -shared -o

ifeq ($(version_file),)
	version_file:=../../SPECS/libshelper.version
endif
VERSION:=$(shell awk -F ':' '{if ($$1 == "version") print $$2}' $(version_file))

suffix:=.${VERSION}.so
ifeq (${dbg},1) 
	CFALGS:= -c -g -fPIC -o
	LDFALGS:= -g -shared -o
	suffix:=_debug.${VERSION}.so
endif


${target}${suffix}:${objs}
	${CXX} ${LDFALGS} $@ $^ -pthread -lhiredis
	@echo -e "\033[32m生成动态库:$@\033[m"

${objs}:%.o:%.cpp
	${CXX} ${CFALGS} $@ $< -std=c++11
show:
	@echo -e "target:\033[31m${target}${suffix}\033[m"
	@echo -e "suffix:\033[31m${suffix}\033[m"
	@echo -e "CFALGS:\033[31m${CFALGS}\033[m"
	@echo -e "LDFALGS:\033[31m${LDFALGS}\033[m"
	@echo -e "cpps:\033[31m${cpps}\033[m"
	@echo -e "objs:\033[31m${objs}\033[m"
	@echo -e "VERSION:\033[31m${VERSION}\033[m"
	@echo -e "version_file:\033[31m${version_file}\033[m"
	

clean:
	$(RM) $(objs)
	${RM} ${target}${suffix}
	@make clean -C ./test
