#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <string.h>
#include "lua_engine.h"
#include "log.h"

using slp::log::log;
using slp::log::level;

bool lua_engine::init(char* fname,lua_State* l) 
{
    if (!l) L = luaL_newstate();
    else L = l;
    int ret = luaL_loadfile(L,fname);
    switch (ret) {
        case LUA_ERRSYNTAX:
            log::trace(time(NULL),__FUNCTION__,"systax error during pre-compilation!",level::error);            
            return false;
            break;
        case LUA_ERRMEM:
            log::trace(time(NULL),__FUNCTION__,"memory allocation error!",level::error);            
            return false;
            break;
        default:
            break;
    }
    luaL_openlibs(L);
    lua_pcall(L,0,0,0);
    return true;
}

void lua_engine::c_invoking_lua(const char*func,const char* fmt,...) 
{
    va_list vl;
    int narg=0,nres=0;  
    
    va_start(vl,fmt);
    lua_getglobal(L,func);

    /* push args into stack */
    for (narg = 0; *fmt; ++narg) {
        luaL_checkstack(L,1,"too many arguments");
        switch (*fmt++) {
            case 'd':  
                lua_pushnumber(L,va_arg(vl,double)); 
                break;
            case 'i': 
                lua_pushinteger(L,va_arg(vl,int));
                break;
            case 's':
                lua_pushstring(L,va_arg(vl,char*));
                break;
            case '>':
                goto endargs;
                break;
            default:
                luaL_error(L,"invalid option (%c)",*(fmt-1));
        }
    }
endargs:

    nres = strlen(fmt);
    /* invoking lua function */
    if (lua_pcall(L,narg,nres,0) != 0)
        luaL_error(L,"error calling '%s':%s",func,lua_tostring(L,-1));

    /* the index of first result */
    nres = -nres;
    while (*fmt) {
        switch (*fmt++) {
            case 'd':   /* result of double */
                if (!lua_isnumber(L,nres))
                    luaL_error(L,"wrong result type");
                *va_arg(vl,double*) = lua_tonumber(L,nres);
                break;
            case 'i':   /* result of int */ 
                if (!lua_isnumber(L,nres))
                   luaL_error(L,"wrong result type");
                *va_arg(vl,int*) = lua_tointeger(L,nres);
                break;
            case 's':   /* result of string */
                if (!lua_isstring(L,nres))
                    luaL_error(L,"wrong result type");
                *va_arg(vl,const char**) = lua_tostring(L,nres);
                break;
            default:
                luaL_error(L,"invalid option (%c)",*(fmt-1));
        }
       ++nres;
    }

    va_end(vl);
}
