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

#include "LA.h"
#include "LuaUtilLib.h"

#include "WindowMgr.h"

class LuaHandler {
private:
    lua_State* L;
    bool check_lua(int r);
    void register_mtables(lua_State* L);

public:
    LuaHandler();
    ~LuaHandler();
    bool do_string(std::string input);
    std::string errmsg;
    std::string out;
};