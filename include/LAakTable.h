//Virtual class for LAak Metatables
#ifndef LUA
#define LUA
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#endif

#ifndef LAAKTBL
#define LAAKTBL
namespace LAakTable {
    inline static const char* nospacestack = "no space left in stack";
    inline static const char* nomemory = "no memory left";
    inline static const char* index_out_range = "index out of range";

    static void register_methods(lua_State* L, luaL_Reg const* methods){
        lua_pushstring(L, "__index");
        lua_pushvalue(L, -2);
        lua_settable(L, -3);
        for(int i = 0; (methods+i)->name != nullptr; ++i){
            lua_pushcfunction(L, (methods+i)->func);
            lua_setfield(L, -2, (methods+i)->name);
        }
    }

    static void register_table(lua_State* L, const char* metatablename, const luaL_Reg* methods, const luaL_Reg* functions){
        luaL_newmetatable(L, metatablename);
        register_methods(L, methods);
        luaL_setfuncs(L, functions, 0);
        lua_setglobal(L, metatablename);
    }
}
#endif