#include "LAakHandler.h"
// libedit-dev
#include <editline/readline.h>
// #include <editline/history.h>

int main(int argc, char** argv){
    auto laak_hndl = LAakHandler();

    if(argc > 1){
        if(laak_hndl.do_string("dofile(\"" + std::string(argv[1]) + "\")"))
            std::cout << laak_hndl.errmsg << '\n';
    }

    while(true){
        /* Output our prompt and get input */        
        char* input = readline("&> ");

        if(input == nullptr || strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0){
            free(input);
            break;
        }
        if(!laak_hndl.do_string(std::string(input))){
            std::cout << laak_hndl.errmsg << '\n';
        }else{
            std::cout << laak_hndl.out;
        }
        add_history(input);
        if(input)
            free(input);
    }

    return 0;
}