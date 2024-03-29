#include "LAakHandler.h"

void LAakHandler::register_mtables(lua_State* L){
    //custom print to redirect output and other utils
    LuaUtilLib::register_luautillib(L);

    //register matrix and vector metatable
    LA::register_la(L);

    //register graphics metatable
    Graphics::register_gl(L);

    //register window metatable
    WindowMgr::register_window(L);
}

LAakHandler::LAakHandler(){
    L = luaL_newstate();
    luaL_openlibs(L);
    register_mtables(L);
}

LAakHandler::~LAakHandler(){
    lua_close(L);
}

bool LAakHandler::check_lua(int r){
    if(r != LUA_OK){
        errmsg = lua_tostring(L, -1);
        return false;
    }else{
        out = LuaUtilLib::out;
        LuaUtilLib::out = "";
    }
    return true;
}

bool LAakHandler::do_string(std::string input){
    int r = luaL_dostring(L, input.c_str());
    return LAakHandler::check_lua(r);
}

bool LAakHandler::do_string(char* input){
    int r = luaL_dostring(L, input);
    return LAakHandler::check_lua(r);
}