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

class LuaHandler {
private:
    lua_State* L;
    bool check_lua(int r);

public:
    LuaHandler();
    ~LuaHandler();
    void do_string(std::string input);
};