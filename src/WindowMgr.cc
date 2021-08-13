#include "WindowMgr.h"

void WindowMgr::register_methods(lua_State* L, luaL_Reg const* methods){
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);
    lua_settable(L, -3);
    for(int i = 0; (methods+i)->name != nullptr; ++i){
        lua_pushcfunction(L, (methods+i)->func);
        lua_setfield(L, -2, (methods+i)->name);
    }
}

void WindowMgr::register_window(lua_State* L){
    luaL_newmetatable(L, win_metatablename);

    register_methods(L, window_methods);

    luaL_setfuncs(L, window_functions, 0);
    lua_setglobal(L, window_metatablename);
}