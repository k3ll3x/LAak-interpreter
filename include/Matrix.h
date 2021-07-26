#include "MatVec.h"

class Matrix {
public:
    static void register_matrix(lua_State* L);
private:
    inline static const char* identity = "i";

    static int new_matrix(lua_State* L);
    static int ij_matrix(lua_State* L);
    static int get_matsize(lua_State* L);
    static int cols_matrix(lua_State* L);
    static int rows_matrix(lua_State* L);
    static int add_matrix(lua_State* L);
    static int sub_matrix(lua_State* L);
    static int mul_matrix(lua_State* L);
    static int T_matrix(lua_State* L);
    static int Td_matrix(lua_State* L);
    static int conj_matrix(lua_State* L);
    static int adj_matrix(lua_State* L);
    static int adjd_matrix(lua_State* L);
    static int sum_matrix(lua_State* L);
    static int prod_matrix(lua_State* L);
    static int mean_matrix(lua_State* L);
    static int mincoeff_matrix(lua_State* L);
    static int maxcoeff_matrix(lua_State* L);
    static int trace_matrix(lua_State* L);
    static int free_matrix(lua_State* L);
    static int eq_matrix(lua_State* L);
    static int matrix_tostring(lua_State* L);

    static void register_methods(lua_State* L, luaL_Reg const* methods);

    inline static const luaL_Reg matrix_methods[] = {
        { "ij", ij_matrix },
        { "rc", ij_matrix },
        { "size", get_matsize },
        { "cols", cols_matrix },
        { "rows", rows_matrix },
        { "transpose", T_matrix },
        { "t", T_matrix },
        { "transposed", Td_matrix },
        { "td", Td_matrix },
        { "conjugate", conj_matrix },
        { "conj", conj_matrix },
        { "adjoint", adj_matrix },
        { "adj", adj_matrix },
        { "adjointed", adjd_matrix },
        { "adjd", adjd_matrix },
        { "sum", sum_matrix },
        { "prod", prod_matrix },
        { "mean", mean_matrix },
        { "minCoeff", mincoeff_matrix },
        { "minc", mincoeff_matrix },
        { "maxCoeff", maxcoeff_matrix },
        { "maxc", maxcoeff_matrix },
        { "trace", trace_matrix },
        { nullptr, nullptr }
    };

    inline static const luaL_Reg matrix_functions[] = {
        { "new", new_matrix },
        { "__gc", free_matrix },
        { "__add", add_matrix },
        { "__sub", sub_matrix },
        { "__mul", mul_matrix },
        { "__eq", eq_matrix },
        { "__tostring", matrix_tostring },
        { nullptr, nullptr }
    };
};