#include "LuaHandler.h"

LuaHandler::LuaHandler(){
    L = luaL_newstate();
    luaL_openlibs(L);

    //custom print to redirect output
    LuaUtilLib::register_luautillib(L);

    //register vector methods
    LA::register_la(L);

    //register window methods
    WindowMgr::register_window(L);
}

LuaHandler::~LuaHandler(){
    lua_close(L);
}

bool LuaHandler::check_lua(int r){
    if(r != LUA_OK){
        errmsg = lua_tostring(L, -1);
        return false;
    }else{
        out = LuaUtilLib::out;
        LuaUtilLib::out = "";
    }
    return true;
}

bool LuaHandler::do_string(std::string input){
    int r = luaL_dostring(L, input.c_str());
    return LuaHandler::check_lua(r);
}