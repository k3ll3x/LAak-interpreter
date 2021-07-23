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

#ifndef EIGEN
#define EIGEN
#include "Eigen/Dense"
typedef Eigen::Vector<double, Eigen::Dynamic> VectorXd;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixXd;
#endif

class Vector {
public:
    static void register_vector(lua_State* L);
    static VectorXd** check_vector(lua_State* L, int idx=1);
private:
    inline static const char* metatablename = "vector";

    static double* get_element(lua_State* L);
    static int new_vector(lua_State* L);
    static int norm_vector(lua_State* l);
    static int normc_vector(lua_State* l);
    static int mag_vector(lua_State* l);
    static int get_vecsize(lua_State* L);
    static int free_vector(lua_State* L);
    static int get_vecelem(lua_State* L);
    static int set_vecelem(lua_State* L);
    static int add_vectors(lua_State* L);
    static int sub_vectors(lua_State* L);
    static int mul_vector(lua_State* L);
    static int div_vector(lua_State* L);
    static int eq_vectors(lua_State* L);
    static int unm_vectors(lua_State* L);
    static int vector_tostring(lua_State* L);

    static void register_methods(lua_State* L, luaL_Reg const* methods);

    inline static const luaL_Reg vector_methods[] = {
        // { "__index", get_vecelem },
        { "k", get_vecelem },
        { "__newindex", set_vecelem },
        { "normalize", norm_vector },
        { "normalized", normc_vector },
        { "magnitude", mag_vector },
        { "size", get_vecsize },
        { nullptr, nullptr }
    };

    inline static const luaL_Reg vector_functions[] = {
        { "new", new_vector },
        { "__gc", free_vector },
        { "__add", add_vectors },
        { "__sub", sub_vectors },
        { "__mul", mul_vector },
        { "__div", div_vector },
        { "__eq", eq_vectors },
        { "__unm", unm_vectors },
        { "__tostring", vector_tostring },
        { nullptr, nullptr }
    };
};
