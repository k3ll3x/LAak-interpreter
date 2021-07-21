#include "LuaHandler.h"

int main(int argc, char** argv){   
    auto lua_hndl = LuaHandler();

    std::string input;
    while(input != "quit"){
        getline(std::cin, input);
        lua_hndl.do_string(input);
        input = "";
    }

    return 0;
}