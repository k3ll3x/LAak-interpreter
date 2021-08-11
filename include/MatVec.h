#ifndef LUA
#define LUA
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef EIGEN
#define EIGEN
#include "Eigen/Dense"
#include "Eigen/Geometry"
typedef Eigen::Vector<double, Eigen::Dynamic> VectorXd;
typedef Eigen::RowVector<double, Eigen::Dynamic> RowVectorXd;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixXd;
#endif

#ifndef MAP
#define MAP
#include <map>
#endif

#ifndef MATVEC
#define MATVEC
// namespace for the shared functions between Matrix and Vector
namespace MatVec {
    inline static const char* mat_metatablename = "matrix";
    inline static const char* vec_metatablename = "vector";
    inline static const char* rowvec_metatablename = "rowvector";
    inline static const char* nospacestack = "no space left in stack";
    inline static const char* nomemory = "no memory left";
    inline static const char* index_out_range = "index out of range";

    static MatrixXd** check_matrix(lua_State* L, int idx = 1){
        void* ud = luaL_checkudata(L, idx, mat_metatablename);
        luaL_argcheck(L, ud != NULL, idx, "matrix expected");
        return (MatrixXd**)ud;
    }

    static bool ismatrix(lua_State* L, int idx = 1){
        if(lua_checkstack(L, 2) && lua_getmetatable(L, idx)){
            lua_pushstring(L, "__name");
            lua_rawget(L, -2);
            if(lua_isstring(L, -1)){
                return (strcmp(luaL_checkstring(L, -1), mat_metatablename) == 0);
            }
        }//stack overflow or no metatable
        return false;
    }

    static bool alloc_matrix(lua_State* L, MatrixXd mv){
        if(lua_checkstack(L, 1)){
            MatrixXd** m = (MatrixXd**)lua_newuserdata(L, sizeof(MatrixXd*));
            *m = new MatrixXd(mv);
            if(*m == nullptr)
                return luaL_error(L, nomemory);
            luaL_getmetatable(L, mat_metatablename);
            lua_setmetatable(L, -2);
        }else{
            return luaL_error(L, nospacestack);
        }
        return true;
    }

    static void** check_vector(lua_State* L, const char* name = vec_metatablename, int idx = 1){
        void* ud = luaL_checkudata(L, idx, name);
        luaL_argcheck(L, ud != NULL, idx, "vector expected");
        return (void**)ud;
    }

    static bool isvector(lua_State* L, const char* name = vec_metatablename, int idx = 1){
        if(lua_checkstack(L, 2) && lua_getmetatable(L, idx)){
            lua_pushstring(L, "__name");
            lua_rawget(L, -2);
            if(lua_isstring(L, -1)){
                return (strcmp(luaL_checkstring(L, -1), name) == 0);
            }
        }
        return false;
    }

    static int alloc_vector(lua_State* L, void* vv, const char* name = vec_metatablename){
        if(strcmp(name, vec_metatablename) == 0){
            if(lua_checkstack(L, 1)){
                VectorXd** v = (VectorXd**)lua_newuserdata(L, sizeof(VectorXd*));
                *v = new VectorXd(*((VectorXd*)vv));
                if(*v == nullptr)
                    return luaL_error(L, nomemory);
                luaL_getmetatable(L, name);
                lua_setmetatable(L, -2);
            }else{
                return luaL_error(L, nospacestack);
            }
        }else{
            if(lua_checkstack(L, 1)){
                RowVectorXd** v = (RowVectorXd**)lua_newuserdata(L, sizeof(RowVectorXd*));
                *v = new RowVectorXd(*((RowVectorXd*)vv));
                if(*v == nullptr)
                    return luaL_error(L, nomemory);
                luaL_getmetatable(L, name);
                lua_setmetatable(L, -2);
            }else{
                return luaL_error(L, nospacestack);
            }
        }
        return 1;
    }
}
#endif