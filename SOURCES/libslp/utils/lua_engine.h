/************************************
*
*此头文件...
*filename : src/lua_engine.h
*author   : sleeping
*email    : csleeping@163.com
*date     : 2016年09月08日 星期四 11时32分13秒
*
************************************/
#ifndef _SLP_SRC_LUA_ENGINE_H
#define _SLP_SRC_LUA_ENGINE_H
#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#ifdef __cplusplus
}
#endif

#define BEGIN_DEFINE_ITEM(itemname)\
static const struct luaL_Reg itemname [] = {
#define ITEM(name,func)\
    {name,func},
#define END_DEFINE_ITEM\
    {NULL,NULL} \
};

#define REGIST(name,moudle) extern "C" int luaopen_##moudle (lua_State *L) {\
    luaL_register(L,name,moudle);\
    return 1;\
}

class lua_engine {
    public:
        lua_engine(){};
        ~lua_engine(){};
        bool init(char* fname,lua_State* l=NULL);
        void c_invoking_lua(const char*func,const char* fmt,...);
    private:
        lua_State *L;
};


#endif /*_SLP_SRC_LUA_ENGINE_H*/

