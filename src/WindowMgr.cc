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

bool WindowMgr::is_fw_window(lua_State* L, int idx){
    if(lua_checkstack(L, 2) && lua_getmetatable(L, idx)){
        lua_pushstring(L, "__name");
        lua_rawget(L, -2);
        if(lua_isstring(L, -1)){
            return (strcmp(luaL_checkstring(L, -1), win_metatablename) == 0);
        }
    }//stack overflow or no metatable
    return false;
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
    GLFWwindow* win;
    int h;
    if(is_fw_window(L)){
        fw_window* fw_win = check_fw_window(L);
        win = fw_win->window;
    }else{
        if(!window){
            return luaL_error(L, "no window");
        }
        win = window;
    }

    glfwGetWindowSize(win, nullptr, &h);
    
    if(lua_checkstack(L, 1)){
        lua_pushinteger(L, h);
    }else{
        luaL_error(L, LAakTable::nospacestack);
    }
    return 1;
}

int WindowMgr::get_width(lua_State* L){
    GLFWwindow* win;
    int w;
    if(is_fw_window(L)){
        fw_window* fw_win = check_fw_window(L);
        win = fw_win->window;
    }else{
        if(!window){
            return luaL_error(L, "no window");
        }
        win = window;
    }

    glfwGetWindowSize(win, &w, nullptr);
    
    if(lua_checkstack(L, 1)){
        lua_pushinteger(L, w);
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