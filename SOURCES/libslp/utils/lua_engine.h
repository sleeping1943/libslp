/************************************
*
*此头文件定义了lua与C/C++通信的帮助函数和宏
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

/*
 *定义lua调用的C函数
 */
#define BEGIN_DEFINE_ITEM(itemname)\
static const struct luaL_Reg itemname [] = {
#define ITEM(name,func)\
    {name,func},
#define END_DEFINE_ITEM\
    {NULL,NULL} \
};

#define DEFINE_CLASS(CLASSNAME,METANAME)\
int _new_func(lua_State* L) {\
    CLASSNAME* p = (CLASSNAME*)lua_newuserdata(L,sizeof(void*));\
    p = new CLASSNAME;\
    luaL_getmetatable(L,METANAME);\
    lua_setmetatable(L,-2);\
    return 1;\
}\
\
BEGIN_DEFINE_ITEM(initmoudle)\
    ITEM("new",_new_func)\
END_DEFINE_ITEM\


/*
 *注册C函数模块
 */
#define REGIST(name,moudle)\
extern "C" int luaopen_##moudle (lua_State *L) {\
    luaL_register(L,name,moudle);\
    return 1;\
}

/*
 *注册带元表的C函数模块
 */
#define REGIST_WITH_META(name,moudle,initmoudle,metaname)\
extern "C" int luaopen_##moudle (lua_State *L) {\
    luaL_newmetatable(L,metaname);\
    lua_pushvalue(L,-1);\
    lua_setfield(L,-2,"__index");\
    luaL_register(L,NULL,moudle);\
    luaL_register(L,name,initmoudle);\
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

