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
    static VectorXd** check_vector(lua_State* L, int idx=1);
    static int new_vector(lua_State* L);
    static int add_vectors(lua_State* L);
    static int sub_vectors(lua_State* L);
    static int mul_vector(lua_State* L);
    static int vector_tostring(lua_State* L);

    inline static const luaL_Reg vector_methods[] = {
        { "new", new_vector },
        { "__add", add_vectors },
        { "__sub", sub_vectors },
        { "__mul", mul_vector },
        { "__tostring", vector_tostring },
        { NULL, NULL }
    };
};
