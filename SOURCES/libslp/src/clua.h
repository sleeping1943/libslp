/************************************
*
*This header is used to help C/C++ call the function that in lua;
*filename : src/lua_base.h
*author   : sleeping
*date     : 六  3/17 12:01:12 2018
*
************************************/
#ifndef _SLP_SRC_CLUA_BASE_H
#define _SLP_SRC_CLUA_BASE_H

#include "lua_base.h"
#include <vector>
#include <map>
#include <string>
#include <exception>

#include <boost/any.hpp>

using std::string;
using std::vector;
using std::map;
using std::exception;

using boost::any;
using boost::any_cast;


/* C++调用lua出错异常 */
class lua_call_exception {
	public:
		lua_call_exception(string errstr) {
			err_str_ = "LUA:";
			err_str_ += errstr;
		};

		virtual const char* what() const {
			return err_str_.data();	
		};
	private:
		string err_str_;
};

/*  通用压栈函数 */
template<typename T>
void _push_value(lua_State* L,const T& value) {
}

template<typename T>
void _push_value(lua_State* L,T* value) {
	lua_pushstring(L,value);
}

template<>
void _push_value(lua_State* L,const int& value);

template<>
void _push_value(lua_State* L,const bool& value);

template<>
void _push_value(lua_State* L,const string& value);

template<>
void _push_value(lua_State* L,char* value);

template<>
void _push_value(lua_State* L,const any& value);

template<typename T>
void get_value(lua_State* L, T& t) {
	char errbuf[1024];
	sprintf(errbuf,"%s:Line[%d]:The type t is not supported!",__FILE__,__LINE__);
	throw lua_call_exception(errbuf);
};

template<>
void get_value(lua_State* L, int& t);

template<>
void get_value(lua_State* L, bool& t);

template<>
void get_value(lua_State* L, string& t);

template<>
void get_value(lua_State* L,vector<any>& vec);

/* 简单的单一输入参数和输出参数 */
template <typename T,typename C>
void call_luaf(lua_State* L, C& c, const string& func_name, const T& t) {
	lua_getglobal(L,func_name.c_str());
	_push_value(L,t);
	if (lua_pcall(L,1,1,0) != 0) {
		string err_str = __FILE__;
		err_str += ":";
		err_str += std::to_string(__LINE__);
		err_str += ":";
		err_str += lua_tostring(L,-1);
		lua_remove(L,-1);
		throw lua_call_exception(err_str);
	}
	get_value(L,c);
}

/* table数组做输入参数和一个输出参数 */
template <typename C>
void call_luaf(lua_State* L, C& c, const string& func_name, const vector<any>& v) {
	if (!L)
		return;
	lua_getglobal(L,func_name.data());
	lua_newtable(L);
	for (int i=0; i<v.size();) {
		_push_value(L,v[i]);	
		lua_rawseti(L,-2,++i);
	}
	if (lua_pcall(L,1,1,0)) {
		stack_dump(L);
		string err_str = __FILE__;
		err_str += ":";
		err_str += std::to_string(__LINE__);
		err_str += ":";
		err_str += lua_tostring(L,-1);
		lua_remove(L,-1);
		throw lua_call_exception(err_str);
		return;
	}
	
	get_value(L,c);
}

/* table当map做输入参数和一个输出参数 */
template <typename C>
void call_luaf(lua_State* L, C& c, const string& func_name, const map<string,any>& m) {
	if (!L)
		return;
	lua_getglobal(L,func_name.data());
	lua_newtable(L);
	for (const auto& iter : m) {
		_push_value(L,iter.first);	
		_push_value(L,iter.second);	
		lua_settable(L,-3);
	}
	if (lua_pcall(L,1,1,0)) {
		stack_dump(L);
		string err_str = __FILE__;
		err_str += ":";
		err_str += std::to_string(__LINE__);
		err_str += ":";
		err_str += lua_tostring(L,-1);
		lua_remove(L,-1);
		throw lua_call_exception(err_str);
		return;
	}
	get_value(L,c);
}

#endif /*_SLP_SRC_CLUA_BASE_H*/
