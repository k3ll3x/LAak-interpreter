#include "MatVec.h"

class Matrix {
public:
    Matrix() = delete;
    ~Matrix() = delete;
    static void reg(lua_State* L);
private:
    inline static const char* identity = "i";
    inline static const char* random = "rand";
    inline static const char* metatable_name = MatVec::mat_metatablename;

    static int doc(lua_State* L);
    static int _new(lua_State* L);
    static int rand(lua_State* L);
    static int ij(lua_State* L);
    static int row(lua_State* L);
    static int col(lua_State* L);
    static int get_matsize(lua_State* L);
    static int cols(lua_State* L);
    static int rows(lua_State* L);
    static int add(lua_State* L);
    static int sub(lua_State* L);
    static int mul(lua_State* L);
    static int cos(lua_State* L);
    static int sin(lua_State* L);
    static int T(lua_State* L);
    static int Td(lua_State* L);
    static int inverse(lua_State* L);
    static int det(lua_State* L);
    static int conj(lua_State* L);
    static int adj(lua_State* L);
    static int adjd(lua_State* L);
    static int trilow(lua_State* L);
    static int triup(lua_State* L);
    static int sum(lua_State* L);
    static int prod(lua_State* L);
    static int mean(lua_State* L);
    static int mincoeff(lua_State* L);
    static int maxcoeff(lua_State* L);
    static int trace(lua_State* L);
    static int free(lua_State* L);
    static int eq(lua_State* L);
    static int tostring(lua_State* L);

    // get from file at doc folder or generated with RtApi scripts
    /*  filename:
            metatable_name
        contents:
            function/method_name [documentation]
        regex:
            .+\[.*\]
    */
    inline static std::map<std::string, const std::string> docs = {
        { "doc", 
            "\t\tMatrix:\n\n"
            "new, ij, rc, row, col, size, cols, rows, cos, sin, transpose, t, T, transposed, td, inverse, inv, determinant, det, conjugate, conj, adjoint, adj, adjointed, adjd, triangularLower, triLow, triangularUpper, triUp, sum, prod, mean, minCoeff, min, maxCoeff, max, trace, rand, random" },
        { "new", "Create new Matrix" },
        { "ij", "Return value at i, j" },
        { "rc", "Return value at r, c" },
        { "row", "Return row" },
        { "col", "Return column" },
        { "size", "Return size" },
        { "cols", "Return columns" },
        { "rows", "Return rows" },
        { "cos", "Return Matrix with applyed cosine function" },
        { "sin", "" },
        { "transpose", "" },
        { "t", "" },
        { "T", "" },
        { "transposed", "" },
        { "td", "" },
        { "inverse", "" },
        { "inv", "" },
        { "determinant", "" },
        { "det", "" },
        { "conjugate", "" },
        { "conj", "" },
        { "adjoint", "" },
        { "adj", "" },
        { "adjointed", "" },
        { "adjd", "" },
        { "triangularLower", "" },
        { "triLow", "" },
        { "triangularUpper", "" },
        { "triUp", "" },
        { "sum", "" },
        { "prod", "" },
        { "mean", "" },
        { "minCoeff", "" },
        { "min", "" },
        { "maxCoeff", "" },
        { "max", "" },
        { "trace", "" },
        { "rand", "" },
        { "random", "" }
    };

    inline static const luaL_Reg methods[] = {
        { "ij", ij },
        { "rc", ij },
        { "row", row },
        { "col", col },
        { "size", get_matsize },
        { "cols", cols },
        { "rows", rows },
        { "cos", cos },
        { "sin", sin },
        { "transpose", T },
        { "t", T },
        { "T", T },
        { "transposed", Td },
        { "td", Td },
        { "inverse", inverse },
        { "inv", inverse },
        { "determinant", det },
        { "det", det },
        { "conjugate", conj },
        { "conj", conj },
        { "adjoint", adj },
        { "adj", adj },
        { "adjointed", adjd },
        { "adjd", adjd },
        { "triangularLower", trilow },
        { "triLow", trilow },
        { "triangularUpper", triup },
        { "triUp", triup },
        { "sum", sum },
        { "prod", prod },
        { "mean", mean },
        { "minCoeff", mincoeff },
        { "min", mincoeff },
        { "maxCoeff", maxcoeff },
        { "max", maxcoeff },
        { "trace", trace },
        { nullptr, nullptr }
    };

    inline static const luaL_Reg functions[] = {
        { "doc", doc },
        { "new", _new },
        { "rand", rand },
        { "random", rand },
        { "__gc", free },
        { "__add", add },
        { "__sub", sub },
        { "__mul", mul },
        { "__eq", eq },
        { "__tostring", tostring },
        { nullptr, nullptr }
    };
};
