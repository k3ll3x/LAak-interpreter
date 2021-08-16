#include "WindowMgr.h"

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

void WindowMgr::register_window(lua_State* L){
    LAakTable::register_table(L, win_metatablename, window_methods, window_functions);
}

// int WindowMgr::new_window(lua_State* L){
//     auto context = ImGui::GetCurrentContext();
//     ImGui::ImGuiWindow win;
//     strcpy(win.name, "yeah");
//     context->Windows.push_back(&win);
//     return 1;
// }

fw_window* WindowMgr::check_fw_window(lua_State* L, int idx){
    void* ud = luaL_checkudata(L, idx, win_metatablename);
    luaL_argcheck(L, ud != NULL, idx, "window expected");
    return (fw_window*)ud;
}

int WindowMgr::init(lua_State* L){
    if (!glfwInit()){
        //clean up
		return luaL_error(L, win_create_err);
	}
    int n = lua_gettop(L);
    if(n == 2){
        int mayor = luaL_checkinteger(L, 1);
        int minor = luaL_checkinteger(L, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mayor);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    }else{
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    }
    return 0;
}

int WindowMgr::create(lua_State* L){
    const char* name = luaL_checkstring(L, 1);
    int w = luaL_checkinteger(L, 2);
    int h = luaL_checkinteger(L, 3);
    fw_window* fw_winp = (fw_window*)lua_newuserdata(L, sizeof(fw_window));
    strcpy(fw_winp->name, name);
    fw_winp->width = w;
    fw_winp->height = h;
    fw_winp->window = glfwCreateWindow(fw_winp->width, fw_winp->height, fw_winp->name, nullptr, nullptr);
    if(fw_winp->window == nullptr)
        return luaL_error(L, win_create_err);
    luaL_getmetatable(L, win_metatablename);
    lua_setmetatable(L, -2);
    return 1;
}

int WindowMgr::get_height(lua_State* L){
    if(!window){
        return luaL_error(L, "no window");
    }
    int height;
    glfwGetWindowSize(window, nullptr, &height);
    if(lua_checkstack(L, 1)){
        lua_pushinteger(L, height);
    }else{
        luaL_error(L, LAakTable::nospacestack);
    }
    return 1;
}

int WindowMgr::get_width(lua_State* L){
    if(!window){
        return luaL_error(L, "no window");
    }
    int width;
    glfwGetWindowSize(window, &width, nullptr);
    if(lua_checkstack(L, 1)){
        lua_pushinteger(L, width);
    }else{
        luaL_error(L, LAakTable::nospacestack);
    }
    return 1;
}

int WindowMgr::free_window(lua_State* L){
    fw_window* fw_win = check_fw_window(L);
    glfwDestroyWindow(fw_win->window);
	// glfwTerminate();
    return 0;
}