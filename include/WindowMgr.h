#include "LAakTable.h"

#ifndef WINDOWMGR
#define WINDOWMGR
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#endif

struct fw_window {
    char name[20];
    GLFWwindow* window;
    int width;
    int height;
};

class WindowMgr {
public:
    WindowMgr() = delete;
    ~WindowMgr() = delete;
    static void register_window(lua_State* L);

    //main window
    inline static GLFWwindow* window;
private:
    //main window width & height
    inline static int width, height;

    inline static const char* win_metatablename = "window";
    inline static const char* win_create_err = "could not create window";

    static fw_window* check_fw_window(lua_State* L, int idx = 1);
    static bool is_fw_window(lua_State* L, int idx = 1);

    //functions
    static int init(lua_State* L);
    static int create(lua_State* L);
    static int get_height(lua_State* L);
    static int get_width(lua_State* L);

    static int free_window(lua_State* L);

    //functions
    inline static const luaL_Reg window_methods[] = {
        { "init", init },
        { "create", create },
        { "get_height", get_height },
        { "get_width", get_width },
        { "__gc", free_window },
        { nullptr, nullptr }
    };

    //methods
    inline static const luaL_Reg window_functions[] = {
        { nullptr, nullptr }
    };
};