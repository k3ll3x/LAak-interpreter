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

//----------Linear Algebra------------
#include "Eigen/Dense"

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixXd;
typedef Eigen::Vector<double, Eigen::Dynamic> VectorXd;
//------------------------------------

class LA {
public:
    static void register_vector(lua_State* L);
private:
    //-------------vector----------------
    static VectorXd** check_vector(lua_State* L, int idx=1);
    static double* get_element(lua_State* L);
    static int new_vector(lua_State* L);
    static int free_vector(lua_State* L);
    static int get_vecelem(lua_State* L);
    static int set_vecelem(lua_State* L);
    static int add_vectors(lua_State* L);
    static int sub_vectors(lua_State* L);
    static int mul_vector(lua_State* L);
    static int norm_vector(lua_State* l);
    static int vector_tostring(lua_State* L);

    // static void register_methods(lua_State* L, luaL_Reg const* methods);

    // inline static const luaL_Reg vector_methods[] = {
    //     { NULL, NULL }
    // };

    inline static const luaL_Reg vector_functions[] = {
        { "new", new_vector },
        { "__gc", free_vector },
        { "__index", get_vecelem },
        { "__newindex", set_vecelem },
        { "__add", add_vectors },
        { "__sub", sub_vectors },
        { "__mul", mul_vector },
        { "__tostring", vector_tostring },
        { "normalize", norm_vector },
        { nullptr, nullptr }
    };
    //-----------------------------------
};
