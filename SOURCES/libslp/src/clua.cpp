#include "clua.h"

template<>
void _push_value(lua_State* L,const int& value) {
	std::cout << "push int[" << value << "] into lua stack" << std::endl;
	lua_pushinteger(L,value);
}

template<>
void _push_value(lua_State* L,const bool& value) {
	lua_pushboolean(L,value);
}

template<>
void _push_value(lua_State* L,const string& value) {
	lua_pushstring(L,value.c_str());
}

template<>
void _push_value(lua_State* L,char* value) {
	lua_pushstring(L,value);
}

template<>
void _push_value(lua_State* L,const any& value) {
	if (value.type() == typeid(int)) {
		_push_value(L,any_cast<int>(value));
	} else if (value.type() == typeid(bool)) {
		_push_value(L,any_cast<bool>(value));
	} else {
		_push_value(L,any_cast<string>(value));
	} 
}

template<>
void get_value(lua_State* L, int& t) {
	if (check_empty(L)) return;
	if (LUA_TNUMBER == lua_type(L,-1)) {
		t = lua_tointeger(L,-1);
		lua_remove(L,-1);
		stack_dump(L);
	} else {
		throw lua_call_exception("the retuan value is not number!");	
	}
};

template<>
void get_value(lua_State* L, bool& t) {
	if (check_empty(L)) return;
	if (LUA_TBOOLEAN == lua_type(L,-1)) {
		t = lua_toboolean(L,-1);
		lua_remove(L,-1);
	} else {
		throw lua_call_exception("the retuan value is not boolean!");	
	}
};

template<>
void get_value(lua_State* L, string& t) {
	if (check_empty(L)) return;
	if (LUA_TSTRING == lua_type(L,-1)) {
		t = lua_tostring(L,-1);
		lua_remove(L,-1);
	} else {
		throw lua_call_exception("the retuan value is not string!");	
	}
};


template<>
void get_value(lua_State* L,vector<any>& vec) {
	if (lua_type(L,-1) != LUA_TTABLE) {
		string err_str = __FILE__;
		err_str += ":";
		err_str += std::to_string(__LINE__);
		err_str += "return value is not table!";
		throw lua_call_exception(err_str);
		return;
	}
	/* 默认返回单一值 */
	size_t ret_count = lua_objlen(L,-1);
	any a;
	stack_dump(L);
	for (size_t i = 1; i <= ret_count; ++i) {
		std::cout << "ret_count:" << ret_count << " i=" << i << std::endl;
		lua_pushnumber(L,i);
		lua_gettable(L,-2);
		switch(lua_type(L,-1)) {
			case LUA_TNUMBER:
				a = lua_tointeger(L,-1);
				lua_remove(L,-1);
				break;
			case LUA_TBOOLEAN:
				a = lua_toboolean(L,-1);
				lua_remove(L,-1);
				break;
			case LUA_TSTRING:
				a = lua_tostring(L,-1);
				lua_remove(L,-1);
				break;
			case LUA_TNIL:
				lua_call_exception("return a nil value!");
				break;
			default:
				break;
		}
		vec.push_back(a);
	}
	lua_settop(L,0);
	return;

}