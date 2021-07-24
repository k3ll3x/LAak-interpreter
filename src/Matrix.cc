#include "Matrix.h"

void Matrix::register_methods(lua_State* L, luaL_Reg const* methods){
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);
    lua_settable(L, -3);
    for(int i = 0; (methods+i)->name != nullptr; ++i){
        lua_pushcfunction(L, (methods+i)->func);
        lua_setfield(L, -2, (methods+i)->name);
    }
}

void Matrix::register_matrix(lua_State* L){
    luaL_newmetatable(L, mat_metatablename);

    register_methods(L, matrix_methods);

    luaL_setfuncs(L, matrix_functions, 0);
    lua_setglobal(L, mat_metatablename);
}

bool Matrix::ismatrix(lua_State* L, int idx){
    void* ud = luaL_checkudata(L, idx, mat_metatablename);
    return (ud != NULL);
}

MatrixXd** Matrix::check_matrix(lua_State* L, int idx){
    void* ud = luaL_checkudata(L, idx, mat_metatablename);
    luaL_argcheck(L, ud != NULL, idx, "matrix expected");
    return (MatrixXd**)ud;
}

int Matrix::new_matrix(lua_State* L){
    int n = lua_gettop(L);
    MatrixXd** m = (MatrixXd**)lua_newuserdata(L, sizeof(MatrixXd*));
    if(n >= 2){
        int rows = luaL_checkinteger(L, 1);
        int cols = luaL_checkinteger(L, 2);
        *m = new MatrixXd(rows, cols);
        if(n == 3){
            if(lua_isnumber(L, 3)){
                auto val = luaL_checknumber(L, 3);
                for(int r = 0; r < rows; r++){
                    for(int c = 0; c < cols; c++){
                        (*(*m))(r,c) = val;
                    }
                }
            }else if(lua_isstring(L, 3)){
                if(strcmp(luaL_checkstring(L, 3), identity) == 0 && rows == cols){
                    for(int i = 0; i < cols; i++){
                        (*(*m))(i,i) = 1.0;
                    }
                }else{
                    delete *m;
                    return luaL_error(L, "Must be a square matrix and 3rd argument to \"i\"");
                }
            }else{
                return luaL_error(L, "3rd argument can only be a number or \"i\" for identity matrix");
            }
        }
    }else{
        return luaL_error(L, "Expected 2 arguments, rows and cols");
    }
    luaL_getmetatable(L, mat_metatablename);
    lua_setmetatable(L, -2);
    return 1;
}

int Matrix::free_matrix(lua_State* L){
    MatrixXd** m = check_matrix(L);
    std::cout << *m << '\t' << "matrix freed" << '\n';
    delete *m;
    return 0;
}

int Matrix::ij_matrix(lua_State* L){
    int n = lua_gettop(L);
    MatrixXd** m = check_matrix(L);
    int i = luaL_checkinteger(L, 2);
    int j = luaL_checkinteger(L, 3);
    if(i >= 0 && i < (*(*m)).rows() && j >= 0 && j < (*(*m)).cols()){
        if(n > 3){
            (*(*m))(i,j) = luaL_checknumber(L, 4);
            return 0;
        }
        lua_pushnumber(L, (*(*m))(i,j));
    }else{
        return luaL_error(L, "index out of range");
    }
    return 1;
}

int Matrix::get_matsize(lua_State* L){
    MatrixXd** m = check_matrix(L);
    lua_pushinteger(L, (*(*m)).size());
    return 1;
}

int Matrix::add_matrix(lua_State* L){
    MatrixXd** a = check_matrix(L);
    MatrixXd** b = check_matrix(L, 2);

    if((*(*a)).size() != (*(*b)).size())
        return luaL_error(L, "Matrices sizes are not the same");

    MatrixXd** m = (MatrixXd**)lua_newuserdata(L, sizeof(MatrixXd*));
    *m = new MatrixXd((*(*a)) + (*(*b)));

    luaL_getmetatable(L, mat_metatablename);
    lua_setmetatable(L, -2);

    return 1;
}

int Matrix::sub_matrix(lua_State* L){
    MatrixXd** a = check_matrix(L);
    MatrixXd** b = check_matrix(L, 2);
    if((*(*a)).size() != (*(*b)).size())
        return luaL_error(L, "Matrices sizes are not the same");

    MatrixXd** m = (MatrixXd**)lua_newuserdata(L, sizeof(MatrixXd*));

    *m = new MatrixXd((*(*a)) - (*(*b)));
    luaL_getmetatable(L, mat_metatablename);
    lua_setmetatable(L, -2);
    return 1;
}

int Matrix::mul_matrix(lua_State* L){
    double s;
    MatrixXd** a;
    MatrixXd** b;
    VectorXd** v;
    std::cout << "WTF\n";
    if(lua_isnumber(L,1)){
        std::cout << "number 1\n";
        s = luaL_checknumber(L, 1);
        a = check_matrix(L, 2);
        MatrixXd** r = (MatrixXd**)lua_newuserdata(L, sizeof(MatrixXd*));
        *r = new MatrixXd(s * (*(*a)));
        luaL_getmetatable(L, mat_metatablename);
        lua_setmetatable(L, -2);
        return 1;
    }else if(ismatrix(L)){
        std::cout << "matrix 1\n";
        a = check_matrix(L);
        if(ismatrix(L, 2)){
            std::cout << "matrix 2\n";
            b = check_matrix(L, 2);
            if((*(*a)).cols() == (*(*b)).rows()){
                MatrixXd** r = (MatrixXd**)lua_newuserdata(L, sizeof(MatrixXd*));
                *r = new MatrixXd((*(*a)) * (*(*b)));
                luaL_getmetatable(L, mat_metatablename);
                lua_setmetatable(L, -2);
                return 1;
            }else{
                return luaL_error(L, "Matrices columns and rows are not the same");
            }
        }else if(Vector::isvector(L, 2)){
            std::cout << "vector 2\n";
            v = Vector::check_vector(L, 2);
            if((*(*a)).cols() == (*(*v)).rows()){
                VectorXd** r = (VectorXd**)lua_newuserdata(L, sizeof(VectorXd*));
                *r = new VectorXd((*(*a)) * (*(*v)));
                luaL_getmetatable(L, Vector::vec_metatablename);
                lua_setmetatable(L, -2);
                return 1;
            }else{
                return luaL_error(L, "Matrix columns and Vector rows are not the same");
            }
        }else{
            std::cout << "number 2\n";
            s = luaL_checknumber(L, 2);
            MatrixXd** r = (MatrixXd**)lua_newuserdata(L, sizeof(MatrixXd*));
            *r = new MatrixXd((*(*a)) * s);
            luaL_getmetatable(L, mat_metatablename);
            lua_setmetatable(L, -2);
            return 1;
        }
    }else{
        std::cout << "vector 1\n";
        v = Vector::check_vector(L, 1);
        a = check_matrix(L, 2);
        if((*(*v)).cols() == (*(*a)).rows()){
            VectorXd** r = (VectorXd**)lua_newuserdata(L, sizeof(VectorXd*));
            *r = new VectorXd((*(*v)) * (*(*a)));
            luaL_getmetatable(L, Vector::vec_metatablename);
            lua_setmetatable(L, -2);
            return 1;
        }else{
            return luaL_error(L, "Matrix columns and Vector rows are not the same");
        }
    }
    return 1;
}

int Matrix::matrix_tostring(lua_State* L){
    MatrixXd** m = check_matrix(L);
    std::ostringstream mosb;
    mosb << (*(*m));
    std::string mstr = mosb.str();
    // std::replace(mstr.begin(), mstr.end(), '\n', ',');
    lua_pushfstring(L, "%s", mstr.c_str());
    return 1;
}