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

#include "Graphics.h"

#include "WindowMgr.h"

struct Environment {
    GLFWwindow* window;
};

class LAakHandler {
private:
    lua_State* L;
    bool check_lua(int r);
    void register_mtables(lua_State* L);
    Environment env;

public:
    LAakHandler();
    ~LAakHandler();
    bool do_string(std::string input);
    bool do_string(char* input);
    std::string errmsg;
    std::string out;
};