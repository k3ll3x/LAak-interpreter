#include "LuaHandler.h"

int main(int argc, char** argv){
    auto lua_hndl = LuaHandler();

    if(argc > 1){
        if(lua_hndl.do_string("dofile(\"" + std::string(argv[1]) + "\")"))
            std::cout << lua_hndl.errmsg << '\n';
    }

    std::string input;
    while(true){
        getline(std::cin, input);
        if(input == "quit")
            break;
        if(!lua_hndl.do_string(input)){
            std::cout << lua_hndl.errmsg << '\n';
        }else{
            std::cout << lua_hndl.out;
        }
    }

    return 0;
}