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
};