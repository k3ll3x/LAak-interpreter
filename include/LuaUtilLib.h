#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef LUA
#define LUA
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#endif

namespace LuaUtilLib {
    static std::string out;

    static int r_print(lua_State* L){
        int n = lua_gettop(L);
        out = "";
        for(int i = 1; i <= n; i++){
            out += luaL_tolstring(L, i, 0);
        }
        if(out != "")
            out += "\n";
        return 0;
    }

    static int pgt(lua_State* L){
        lua_pushglobaltable(L);             // Get global table
        lua_pushnil(L);                     // put a nil key on stack
        out = "";
        while (lua_next(L,-2) != 0) {       // key(-1) is replaced by the next key(-1) in table(-2)
            // out += lua_typename(L, -2);
            // out += "\t";
            out += lua_tostring(L, -2);      // Get key(-2) name
            out += "\n";
            lua_pop(L,1);                   // remove value(-1), now key on top at(-1)
        }
        lua_pop(L,1);                       // remove global table(-1)

        if(out != "")
            out += "\n";
        return 0;
    }

    static const luaL_Reg r_print_lib [] = {
        { "print", r_print },
        { "pgt", pgt },
        { nullptr, nullptr }
    };

    static void register_luautillib(lua_State* L){
        lua_getglobal(L, "_G");
        luaL_setfuncs(L, r_print_lib, 0);
        lua_pop(L, 1);
    }
}