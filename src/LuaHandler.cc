#include "LuaHandler.h"

LuaHandler::LuaHandler(){
    this->L = luaL_newstate();
    luaL_openlibs(this->L);

    //register vector methods
    LA::register_vector(L);
}

LuaHandler::~LuaHandler(){
    lua_close(this->L);
}

bool LuaHandler::check_lua(int r){
    if(r != LUA_OK){
        std::string errormsg = lua_tostring(L, -1);
        std::cout << errormsg << '\n';
        return false;
    }
    return true;
}

void LuaHandler::do_string(std::string input){
    int r = luaL_dostring(this->L, input.c_str());
    LuaHandler::check_lua(r);
}