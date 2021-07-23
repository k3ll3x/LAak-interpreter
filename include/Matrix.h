#ifndef LUA
#define LUA
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#endif

#ifndef ALGORITHM
#define ALGORITHM
#include <algorithm>
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#include "Vector.h"

class Matrix {
public:
    static void register_matrix(lua_State* L);
private:
    inline static const char* metatablename = "matrix";
    inline static const char* identity = "i";

    static MatrixXd** check_matrix(lua_State* L, int idx=1);
    static int new_matrix(lua_State* L);
    static int ij_matrix(lua_State* L);
    static int get_matsize(lua_State* L);
    static int free_matrix(lua_State* L);
    static int matrix_tostring(lua_State* L);

    static void register_methods(lua_State* L, luaL_Reg const* methods);

    inline static const luaL_Reg matrix_methods[] = {
        { "ij", ij_matrix },
        { "rc", ij_matrix },
        { "size", get_matsize },
        { nullptr, nullptr }
    };

    inline static const luaL_Reg matrix_functions[] = {
        { "new", new_matrix },
        { "__gc", free_matrix },
        { "__tostring", matrix_tostring },
        { nullptr, nullptr }
    };
};