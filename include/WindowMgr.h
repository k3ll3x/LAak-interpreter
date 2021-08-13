#ifndef WINDOWMGR
#define WINDOWMGR
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#endif

#ifndef LUA
#define LUA
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#endif

class WindowMgr {
public:
    WindowMgr() = delete;
    ~WindowMgr() = delete;
    static void register_window(lua_State* L);
private:
    inline static const char* win_metatablename = "window";

    static void register_methods(lua_State* L, luaL_Reg const* methods);

    //methods

    //functions
    
    inline static const luaL_Reg window_methods[] = {
        { nullptr, nullptr }
    };

    inline static const luaL_Reg window_functions[] = {
        { nullptr, nullptr }
    };
};