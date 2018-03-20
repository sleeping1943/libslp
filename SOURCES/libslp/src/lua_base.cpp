#include "lua_base.h"

using std::cout;
using std::string;
using std::endl;
void stack_dump(lua_State* L, int frame_index) {
	int frame_count = lua_gettop(L);	
	for (int i = frame_count; i > 0; --i) {
		int t = lua_type(L,i);	
		cout << "frame[" << i << "] ";
		switch (t) {
			case LUA_TSTRING:
				cout << "string:" << lua_tostring(L,i) << endl;
				break;
			case LUA_TNIL:
				cout << "nil:nil" << endl;
				break;
			case LUA_TNUMBER:
				cout << "number:" << lua_tonumber(L,i) << endl;
				break;
			case LUA_TBOOLEAN:
				cout << "boolean:" << lua_toboolean(L,i) << endl;
				break;
			case LUA_TTABLE:
				cout << "table:{}" << endl;
				break;
			case LUA_TFUNCTION:
				cout << "function:{}" << endl;
				break;
			case LUA_TUSERDATA:
				cout << "userdata:{}" << endl;
				break;
			case LUA_TTHREAD:
				cout << "thread:{}" << endl;
				break;
			case LUA_TLIGHTUSERDATA:
				cout << "lightuserdata:{}" << endl;
				break;
			default:
				cout << "Unknown type!" << endl;
				break;
		}
	}
};

bool check_empty(lua_State* L) {
	if (lua_gettop(L) < 1) {
		string err_str = __FILE__;
		err_str += ":";
		err_str += std::to_string(__LINE__);
		err_str += "not enough args in the stack!";
		throw lua_call_exception(err_str);
		return true;
	}
	return false;
};