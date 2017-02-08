#
#
#此头文件用于构建目标程序
#filename : makefile
#author   : sleeping
#email    : csleeping@163.com
#date     : 2017年02月07日 星期二 15时16分58秒
#
#

out?=$(PWD)
CXX:=g++
target:=test_config
suffix:=
cpps:=$(wildcard ./src/*.cpp)
hpps:=$(wildcard ./src/*.hpp)
objs:=$(cpps:%.cpp=%.o)
CFLGAS:= -c -o 
LDFLAGS:= -o
ERR:=

ifeq ($(cpps),)
	ERR:=$(error $(shell echo -e "\033[31mno cpp files are found!\033[m"))
endif

ifeq ($(dbg),1)
	suffix:=_debug
	target:=$(target)$(suffix)
	CFLGAS:= -c -g -o  
	LDFLAGS:= -g -o 
else
	suffix:=
	target:=$(target)$(suffix)
	CFLGAS:= -c -o 
	LDFLAGS:= -o 
endif

.PHONY: show

$(out)/$(target):$(objs)
	$(CXX) $(LDFLAGS) $@ $^ -lshelper -llua 

$(objs):%.o:%.cpp $(ERR)
	$(CXX) $(CFLGAS)$@ $< -std=c++11

test:$(target)
	@echo -e "\033[32m执行$(out)/$^\033[m"
	@$(out)/$^ ./isdlp.conf

show:
	@echo -e "\033[32mout=$(out)"
	@echo target=$(target)
	@echo suffix=$(suffix)
	@echo cpps=$(cpps)
	@echo objs=$(objs)
	@echo CFLGAS=$(CFLGAS)
	@echo -e "LDFLAGS=$(LDFLAGS)\033[m"

clean:
	@echo -e "\033[31m清除$(target)\033[m"
	@$(RM)  $(target)
	@echo -e "\033[31m清除$(objs)\033[m"
	@$(RM)  $(objs)

