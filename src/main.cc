#include "LuaHandler.h"

int main(int argc, char** argv){   
    auto lua_hndl = LuaHandler();

    std::string input;
    while(true){
        getline(std::cin, input);
        if(input == "quit")
            break;
        lua_hndl.do_string(input);
    }

    return 0;
}