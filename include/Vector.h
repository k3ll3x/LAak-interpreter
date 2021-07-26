#include "MatVec.h"

class Vector {
public:
    static void register_vector(lua_State* L);
private:
    static double* get_element(lua_State* L, const char* name = MatVec::vec_metatablename);
    static int new_vector(lua_State* L);
    static int norm_vector(lua_State* l);
    static int normc_vector(lua_State* l);
    static int mag_vector(lua_State* l);
    static int dot_vectors(lua_State* l);
    static int cross_vectors(lua_State* l);
    static int T_vector(lua_State* l);
    static int type_vector(lua_State* l);
    static int get_vecsize(lua_State* L);
    static int free_vector(lua_State* L);
    static int get_vecelem(lua_State* L);
    static int set_vecelem(lua_State* L);
    static int add_vectors(lua_State* L);
    static int sub_vectors(lua_State* L);
    static int mul_vector(lua_State* L);
    static int eq_vectors(lua_State* L);
    static int unm_vector(lua_State* L);
    static int vector_tostring(lua_State* L);

    static void register_methods(lua_State* L, luaL_Reg const* methods);

    inline static const luaL_Reg vector_methods[] = {
        // { "__index", get_vecelem },
        { "k", get_vecelem },
        { "__newindex", set_vecelem },
        { "normalize", norm_vector },
        { "n", norm_vector },
        { "normalized", normc_vector },
        { "nd", normc_vector },
        { "magnitude", mag_vector },
        { "mag", mag_vector },
        { "dot", dot_vectors },
        { "cross", cross_vectors },
        { "transpose", T_vector },
        { "t", T_vector },
        { "type", type_vector },
        { "size", get_vecsize },
        { nullptr, nullptr }
    };

    inline static const luaL_Reg vector_functions[] = {
        { "new", new_vector },
        { "__gc", free_vector },
        { "__add", add_vectors },
        { "__sub", sub_vectors },
        { "__mul", mul_vector },
        { "__eq", eq_vectors },
        { "__unm", unm_vector },
        { "__tostring", vector_tostring },
        { nullptr, nullptr }
    };
};
