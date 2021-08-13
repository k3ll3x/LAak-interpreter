#include "LAakHandler.h"

int main(int argc, char** argv){
    auto laak_hndl = LAakHandler();

    if(argc > 1){
        if(laak_hndl.do_string("dofile(\"" + std::string(argv[1]) + "\")"))
            std::cout << laak_hndl.errmsg << '\n';
    }

    std::string input;
    while(true){
        getline(std::cin, input);
        if(input == "quit")
            break;
        if(!laak_hndl.do_string(input)){
            std::cout << laak_hndl.errmsg << '\n';
        }else{
            std::cout << laak_hndl.out;
        }
    }

    return 0;
}