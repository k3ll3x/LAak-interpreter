//Virtual class for LAak Metatables
#ifndef LUA
#define LUA
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#endif

#ifndef STRING
#include <string>
#include <cstring>
#endif

#ifndef MAP
#include <map>
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

class Metatable {
public:
    Metatable() = delete;
    ~Metatable() = delete;
    std::string metatable_name;
    void reg(lua_State* L){
        LAakTable::register_table(L, metatable_name.c_str(), methods, functions);
    }
private:
    static std::map<std::string, const std::string> docs;
    const luaL_Reg* methods;
    const luaL_Reg* functions;
    int tostring(lua_State* L);
    int free(lua_State* L);
    int add(lua_State* L);
    int sub(lua_State* L);
    int mul(lua_State* L);
    int eq(lua_State* L);
    static int doc(lua_State* L){
        std::string who = "doc";
        if(lua_isstring(L, 1)){
            who = luaL_checkstring(L, 1);
        }
        if(!docs.contains(who)){
            return luaL_error(L, "No documentation available");
        }
        if(lua_checkstack(L, 1)){
            lua_pushfstring(L, "%s", docs[who].c_str());
        }else{
            return luaL_error(L, LAakTable::nospacestack);
        }
        return 1;
    }
};
#endif