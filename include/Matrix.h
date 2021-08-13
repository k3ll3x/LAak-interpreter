#include "MatVec.h"

class Matrix {
public:
    Matrix() = delete;
    ~Matrix() = delete;
    static void register_matrix(lua_State* L);
private:
    inline static const char* identity = "i";
    inline static const char* random = "rand";

    // inline static const std::map<std::string, std::string> doc_list = {};

    // static int doc_matrix(lua_State* L);

    static int new_matrix(lua_State* L);
    static int rand_matrix(lua_State* L);
    static int ij_matrix(lua_State* L);
    static int row_matrix(lua_State* L);
    static int col_matrix(lua_State* L);
    static int get_matsize(lua_State* L);
    static int cols_matrix(lua_State* L);
    static int rows_matrix(lua_State* L);
    static int add_matrix(lua_State* L);
    static int sub_matrix(lua_State* L);
    static int mul_matrix(lua_State* L);
    static int cos_matrix(lua_State* L);
    static int sin_matrix(lua_State* L);
    static int T_matrix(lua_State* L);
    static int Td_matrix(lua_State* L);
    static int inverse_matrix(lua_State* L);
    static int det_matrix(lua_State* L);
    static int conj_matrix(lua_State* L);
    static int adj_matrix(lua_State* L);
    static int adjd_matrix(lua_State* L);
    static int trilow_matrix(lua_State* L);
    static int triup_matrix(lua_State* L);
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
        { "row", row_matrix },
        { "col", col_matrix },
        { "size", get_matsize },
        { "cols", cols_matrix },
        { "rows", rows_matrix },
        { "cos", cos_matrix },
        { "sin", sin_matrix },
        { "transpose", T_matrix },
        { "t", T_matrix },
        { "T", T_matrix },
        { "transposed", Td_matrix },
        { "td", Td_matrix },
        { "inverse", inverse_matrix },
        { "inv", inverse_matrix },
        { "determinant", det_matrix },
        { "det", det_matrix },
        { "conjugate", conj_matrix },
        { "conj", conj_matrix },
        { "adjoint", adj_matrix },
        { "adj", adj_matrix },
        { "adjointed", adjd_matrix },
        { "adjd", adjd_matrix },
        { "triangularLower", trilow_matrix },
        { "triLow", trilow_matrix },
        { "triangularUpper", triup_matrix },
        { "triUp", triup_matrix },
        { "sum", sum_matrix },
        { "prod", prod_matrix },
        { "mean", mean_matrix },
        { "minCoeff", mincoeff_matrix },
        { "min", mincoeff_matrix },
        { "maxCoeff", maxcoeff_matrix },
        { "max", maxcoeff_matrix },
        { "trace", trace_matrix },
        { nullptr, nullptr }
    };

    inline static const luaL_Reg matrix_functions[] = {
        // { "doc", doc_matrix },
        { "new", new_matrix },
        { "rand", rand_matrix },
        { "random", rand_matrix },
        { "__gc", free_matrix },
        { "__add", add_matrix },
        { "__sub", sub_matrix },
        { "__mul", mul_matrix },
        { "__eq", eq_matrix },
        { "__tostring", matrix_tostring },
        { nullptr, nullptr }
    };
};
