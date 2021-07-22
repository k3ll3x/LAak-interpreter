#include "LA.h"

void LA::register_vector(lua_State* L){
    luaL_newmetatable(L, "vector");
    lua_pushcfunction(L, get_vecelem);
    lua_setfield(L, -2, "__index");
    lua_pushcfunction(L, set_vecelem);
    lua_setfield(L, -2, "__newindex");
    luaL_setfuncs(L, vector_methods, 0);
    lua_setglobal(L, "vector");
}

VectorXd** LA::check_vector(lua_State* L, int idx){
    void* ud = luaL_checkudata(L, idx, "vector");
    luaL_argcheck(L, ud != NULL, idx, "vector expected");
    return (VectorXd**)ud;
}

double* LA::get_element(lua_State* L){
    VectorXd** v = check_vector(L);
    int index = luaL_checkinteger(L, 2);
    luaL_argcheck(L, 0 <= index && index < (*(*v)).size(), 2, "index out of range");
    return &(*(*v))[index];
}

int LA::get_vecelem(lua_State* L){
    lua_pushnumber(L, *get_element(L));
    return 1;
}

int LA::set_vecelem(lua_State* L){
    double newval = luaL_checknumber(L, 3);
    *get_element(L) = newval;
    return 0;
}

int LA::new_vector(lua_State* L){
    int n = lua_gettop(L);
    if(n >= 1){
        VectorXd** v = (VectorXd**)lua_newuserdata(L, sizeof(VectorXd*));
        if(n == 1){
            //create vector with size as argument
            if(lua_isnumber(L,1)){
                int size = luaL_checkinteger(L, 1);
                *v = new VectorXd(size);
            //create vector with contents of table
            }else if(lua_istable(L,1)){
                *v = new VectorXd(lua_rawlen(L, 1));
                lua_pushnil(L);
                int idx = 0;
                while (lua_next(L, 1) != 0) {
                    (*(*v))[idx] = luaL_checknumber(L, -1);
                    idx++;
                    lua_pop(L, 1);
                }
            }else{
                return luaL_error(L, "Expected number or table/list");
            }
        }else{
            //create vector with multiple arguments
            *v = new VectorXd(n);
            for(int i = 1; i <= n; i++){
                (*(*v))[i-1] = luaL_checknumber(L, i);
            }
        }
        // lua_getglobal(L, "vector");
        luaL_getmetatable(L, "vector");
        lua_setmetatable(L, -2);
    }else{
        return luaL_error(L, "Expected more arguments");
    }
    return 1;
}

int LA::add_vectors(lua_State* L){
    VectorXd** a = check_vector(L);
    VectorXd** b = check_vector(L, 2);

    if((*(*a)).size() != (*(*b)).size())
        return luaL_error(L, "Vector sizes are not the same");

    VectorXd** v = (VectorXd**)lua_newuserdata(L, sizeof(VectorXd*));

    *v = new VectorXd((*(*a)) + (*(*b)));

    luaL_getmetatable(L, "vector");
    lua_setmetatable(L, -2);
    return 1;
}

int LA::sub_vectors(lua_State* L){
    VectorXd** a = check_vector(L);
    VectorXd** b = check_vector(L, 2);

    if((*(*a)).size() != (*(*b)).size())
            return luaL_error(L, "Vector sizes are not the same");

    VectorXd** v = (VectorXd**)lua_newuserdata(L, sizeof(VectorXd*));

    *v = new VectorXd((*(*a)) - (*(*b)));
    luaL_getmetatable(L, "vector");
    lua_setmetatable(L, -2);
    return 1;
}

int LA::mul_vector(lua_State* L){
    double a;
    VectorXd** v;
    if(lua_isnumber(L,1)){
        a = luaL_checknumber(L, 1);
        v = check_vector(L, 2);
    }else{
        a = luaL_checknumber(L, 2);
        v = check_vector(L);
    }
    VectorXd** r = (VectorXd**)lua_newuserdata(L, sizeof(VectorXd*));
    *r = new VectorXd(a * (*(*v)));
    luaL_getmetatable(L, "vector");
    lua_setmetatable(L, -2);
    return 1;
}

int LA::vector_tostring(lua_State* L){
    VectorXd** v = check_vector(L);
    std::ostringstream vosb;
    vosb << (*(*v));
    std::string vstr = vosb.str();
    std::replace(vstr.begin(), vstr.end(), '\n', ',');
    lua_pushfstring(L, "{ %s }", vstr.c_str());
    return 1;
}