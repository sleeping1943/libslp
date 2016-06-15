CXX:=g++
target:=libslp_utils
cpps:=$(wildcard ./utils/*.cpp)
objs:=$(cpps:%.cpp=%.o)
suffix:=.so
CFALGS:= -c -fPIC -o
LDFALGS:=  -shared -o

ifeq (${dbg},1) 
	CFALGS:= -c -g -fPIC -o
	LDFALGS:= -g -shared -o
	suffix:=_debug.so
endif

${target}${suffix}:${objs}
	${CXX} ${LDFALGS} $@ $^

${objs}:%.o:%.cpp
	${CXX} ${CFALGS} $@ $<
show:
	@echo -e "target:\033[31m${target}${suffix}\033[m"
	@echo -e "suffix:\033[31m${suffix}\033[m"
	@echo -e "CFALGS:\033[31m${CFALGS}\033[m"
	@echo -e "LDFALGS:\033[31m${LDFALGS}\033[m"
	@echo -e "cpps:\033[31m${cpps}\033[m"
	@echo -e "objs:\033[31m${objs}\033[m"

clean:
	$(RM) $(objs)
	${RM} ${target}${suffix}
