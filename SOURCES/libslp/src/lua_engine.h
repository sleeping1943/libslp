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
 *TODO 类中的函数若包含成员，则调用失败，段错误
 */

/**
 * @brief 定义lua调用的C函数
 * @param itemname C/C++模块名
 */
#define BEGIN_DEFINE_ITEM(itemname)\
static const struct luaL_Reg itemname [] = {
#define ITEM(name,func)\
    {name,func},
#define END_DEFINE_ITEM\
    {NULL,NULL} \
};


/**
 * @brief 定义C++类并压入栈,定义回收垃圾的函数
 *
 * @param CLASSNAME C++类名
 * @param METANAME 元表名
 * @param INITMOUDLE 用于绑定的结构块
 *
 * @return 入栈参数个数
 */
#define DEFINE_CLASS(CLASSNAME,METANAME,INITMOUDLE)\
int _new_func(lua_State* L) {\
    CLASSNAME** p = (CLASSNAME**)lua_newuserdata(L,sizeof(void*));\
    *p = new CLASSNAME;\
    luaL_getmetatable(L,METANAME);\
    lua_setmetatable(L,-2);\
    return 1;\
}\
\
int _destroy(lua_State* L) {\
    CLASSNAME** pclass = (CLASSNAME**)luaL_checkudata(L,1,METANAME);\
    if (*pclass) {\
       delete *pclass;\
       *pclass = NULL;\
    }\
    return 0;\
}\
\
\
BEGIN_DEFINE_ITEM(INITMOUDLE)\
    ITEM("new",_new_func)\
END_DEFINE_ITEM\


/**
 * @brief 注册C函数模块
 *
 * @param name lua中变量名
 * @param moudle C/C++模块名
 *
 * @return 
 */
#define REGIST(name,moudle)\
extern "C" int luaopen_##moudle (lua_State *L) {\
    luaL_register(L,name,moudle);\
    return 1;\
}


/**
 * @brief 注册带元表和垃圾回收的C/C++函数模块
 *
 * @param name lua脚本中使用的模块名
 * @param moudle lua中require的模块名
 * @param initmoudle C++类的函数定义块
 * @param metaname 创建类的函数定义块
 *
 * @return 无意义 
 */
#define REGIST_WITH_META(name,moudle,initmoudle,metaname)\
extern "C" int luaopen_##moudle (lua_State *L) {\
    luaL_newmetatable(L,metaname);\
    lua_pushstring(L,"__gc");\
    lua_pushcfunction(L,_destroy);\
    lua_settable(L,-3);\
\
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

