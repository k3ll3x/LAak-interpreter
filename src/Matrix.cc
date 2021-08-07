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
    luaL_newmetatable(L, MatVec::mat_metatablename);

    register_methods(L, matrix_methods);

    luaL_setfuncs(L, matrix_functions, 0);
    lua_setglobal(L, MatVec::mat_metatablename);
}

int Matrix::new_matrix(lua_State* L){
    int n = lua_gettop(L);
    MatrixXd** m;
    if(lua_checkstack(L, 1)){
        m = (MatrixXd**)lua_newuserdata(L, sizeof(MatrixXd*));
    }else{
        return luaL_error(L, MatVec::nospacestack);
    }
    if(n >= 2){
        int rows = luaL_checkinteger(L, 1);
        int cols = luaL_checkinteger(L, 2);
        *m = new MatrixXd(rows, cols);
        if(*m == nullptr)
            return luaL_error(L, MatVec::nomemory);
        if(n == 3){
            if(lua_isnumber(L, 3)){
                auto val = luaL_checknumber(L, 3);
                (*(*m)).fill(val);
            }else if(lua_isstring(L, 3)){
                if(strcmp(luaL_checkstring(L, 3), identity) == 0 && rows == cols){
                    (*(*m)).fill(0.0);
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
        }else if(n > 3){
            return luaL_error(L, "Expected 3 arguments, rows, cols and \"i\" for identity or number");
        }else{
            (*(*m)).fill(0);
        }
    }else{
        return luaL_error(L, "Expected 2 arguments, rows and cols");
    }
    luaL_getmetatable(L, MatVec::mat_metatablename);
    lua_setmetatable(L, -2);
    return 1;
}

int Matrix::free_matrix(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    std::cout << *m << '\t' << "matrix freed" << '\n';
    delete *m;
    return 0;
}

int Matrix::ij_matrix(lua_State* L){
    int n = lua_gettop(L);
    MatrixXd** m = MatVec::check_matrix(L);
    int i = luaL_checkinteger(L, 2);
    int j = luaL_checkinteger(L, 3);
    if(i >= 0 && i < (*(*m)).rows() && j >= 0 && j < (*(*m)).cols()){
        if(n > 3){
            (*(*m))(i,j) = luaL_checknumber(L, 4);
            return 0;
        }
        if(lua_checkstack(L, 1)){
            lua_pushnumber(L, (*(*m))(i,j));
        }else{
            return luaL_error(L, MatVec::nospacestack);
        }
    }else{
        return luaL_error(L, "index out of range");
    }
    return 1;
}

int Matrix::get_matsize(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    if(lua_checkstack(L, 1)){
        lua_pushinteger(L, (*(*m)).size());
    }else{
        return luaL_error(L, MatVec::nospacestack);
    }
    return 1;
}

int Matrix::cols_matrix(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    if(lua_checkstack(L, 1)){
        lua_pushinteger(L, (*(*m)).cols());
    }else{
        return luaL_error(L, MatVec::nospacestack);
    }
    return 1;
}

int Matrix::rows_matrix(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    if(lua_checkstack(L, 1)){
        lua_pushinteger(L, (*(*m)).rows());
    }else{
        return luaL_error(L, MatVec::nospacestack);
    }
    return 1;
}

int Matrix::T_matrix(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    MatVec::alloc_matrix(L, (*(*m)).transpose());
    return 1;
}

int Matrix::Td_matrix(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    (*(*m)).transposeInPlace();
    return 1;
}

int Matrix::inverse_matrix(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    MatVec::alloc_matrix(L ,(*(*m)).inverse());
    return 1;
}

int Matrix::det_matrix(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    lua_pushnumber(L, (*(*m)).determinant());
    return 1;
}

int Matrix::conj_matrix(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    MatVec::alloc_matrix(L, (*(*m)).conjugate());
    return 1;
}

int Matrix::adj_matrix(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    MatVec::alloc_matrix(L, (*(*m)).adjoint());
    return 1;
}

int Matrix::adjd_matrix(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    (*(*m)).adjointInPlace();
    return 1;
}

int Matrix::trilow_matrix(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    MatVec::alloc_matrix(L, (*(*m)).triangularView<Eigen::Lower>());
    return 1;
}

int Matrix::triup_matrix(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    MatVec::alloc_matrix(L, (*(*m)).triangularView<Eigen::Upper>());
    return 1;
}

int Matrix::sum_matrix(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    if(lua_checkstack(L, 1)){
        lua_pushnumber(L, (*(*m)).sum());
    }else{
        return luaL_error(L, MatVec::nospacestack);
    }
    return 1;
}

int Matrix::prod_matrix(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    if(lua_checkstack(L, 1)){
        lua_pushnumber(L, (*(*m)).prod());
    }else{
        return luaL_error(L, MatVec::nospacestack);
    }
    return 1;
}

int Matrix::mean_matrix(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    if(lua_checkstack(L, 1)){
        lua_pushnumber(L, (*(*m)).mean());
    }else{
        return luaL_error(L, MatVec::nospacestack);
    }
    return 1;
}

int Matrix::mincoeff_matrix(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    if(lua_checkstack(L, 1)){
        lua_pushnumber(L, (*(*m)).minCoeff());
    }else{
        return luaL_error(L, MatVec::nospacestack);
    }
    return 1;
}

int Matrix::maxcoeff_matrix(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    if(lua_checkstack(L, 1)){
        lua_pushnumber(L, (*(*m)).maxCoeff());
    }else{
        return luaL_error(L, MatVec::nospacestack);
    }
    return 1;
}

int Matrix::trace_matrix(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    if(lua_checkstack(L, 1)){
        lua_pushnumber(L, (*(*m)).trace());
    }else{
        return luaL_error(L, MatVec::nospacestack);
    }
    return 1;
}

int Matrix::add_matrix(lua_State* L){
    MatrixXd** a = MatVec::check_matrix(L);
    MatrixXd** b = MatVec::check_matrix(L, 2);

    if((*(*a)).size() != (*(*b)).size())
        return luaL_error(L, "Matrices sizes are not the same");

    MatVec::alloc_matrix(L, (*(*a)) + (*(*b)));

    return 1;
}

int Matrix::sub_matrix(lua_State* L){
    MatrixXd** a = MatVec::check_matrix(L);
    MatrixXd** b = MatVec::check_matrix(L, 2);
    if((*(*a)).size() != (*(*b)).size())
        return luaL_error(L, "Matrices sizes are not the same");

    MatVec::alloc_matrix(L, (*(*a)) - (*(*b)));

    return 1;
}

int Matrix::mul_matrix(lua_State* L){
    double s;
    MatrixXd** a;
    MatrixXd** b;
    VectorXd** v;
    if(lua_isnumber(L,1)){
        s = luaL_checknumber(L, 1);
        a = MatVec::check_matrix(L, 2);
        MatVec::alloc_matrix(L, s * (*(*a)));
        return 1;
    }else if(lua_isnumber(L, 2)){
        a = MatVec::check_matrix(L);
        s = luaL_checknumber(L, 2);
        MatVec::alloc_matrix(L, (*(*a)) * s);
        return 1;
    }else if(MatVec::ismatrix(L, 2)){
        a = MatVec::check_matrix(L);
        b = MatVec::check_matrix(L, 2);
        if((*(*a)).cols() == (*(*b)).rows()){
            MatVec::alloc_matrix(L, (*(*a)) * (*(*b)));
            return 1;
        }else{
            return luaL_error(L, "Matrices columns and rows are not the same");
        }
    }else{
        a = MatVec::check_matrix(L);
        v = (VectorXd**)MatVec::check_vector(L, MatVec::vec_metatablename, 2);
        if((*(*a)).cols() == (*(*v)).rows()){
            auto r = VectorXd((*(*a)) * (*(*v)));
            MatVec::alloc_vector(L, &r);
            return 1;
        }else{
            return luaL_error(L, "Matrix columns and Vector rows are not the same");
        }
    }
    return 1;
}

int Matrix::eq_matrix(lua_State* L){
    MatrixXd** a = MatVec::check_matrix(L);
    MatrixXd** b = MatVec::check_matrix(L, 2);
    if(lua_checkstack(L, 1)){
        lua_pushboolean(L, (*(*a)) == (*(*b)));
    }else{
        return luaL_error(L, MatVec::nospacestack);
    }
    return 1;
}

int Matrix::matrix_tostring(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    std::ostringstream mosb;
    mosb << (*(*m));
    std::string mstr = mosb.str();
    // std::replace(mstr.begin(), mstr.end(), '\n', ',');
    if(lua_checkstack(L, 1)){
        lua_pushfstring(L, "%s", mstr.c_str());
    }else{
        return luaL_error(L, MatVec::nospacestack);
    }
    return 1;
}