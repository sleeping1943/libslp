#ifndef _LOGICSERVER_LUA_BASE_H
#define _LOGICSERVER_LUA_BASE_H
#include <iostream>
#include <string>

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

using std::cout;
using std::string;
using std::endl;
void stack_dump(lua_State* L, int frame_index=0);
bool check_empty(lua_State* L);

#endif	//_LOGICSERVER_LUA_BASE_H