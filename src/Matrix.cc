#include "Matrix.h"

void Matrix::reg(lua_State* L){
    LAakTable::register_table(L, MatVec::mat_metatablename, methods, functions);
}

int Matrix::doc(lua_State* L){
    std::string who = "doc";
    if(lua_isstring(L, 1)){
        who = luaL_checkstring(L, 1);
    }
    if(!docs.contains(who)){
        return luaL_error(L, "No documentation available");
    }
    if(lua_checkstack(L, 1)){
        lua_pushfstring(L, "%s", docs[who].c_str());
    }else{
        return luaL_error(L, LAakTable::nospacestack);
    }
    return 1;
}

int Matrix::_new(lua_State* L){
    int n = lua_gettop(L);
    MatrixXd** m;
    if(lua_checkstack(L, 1)){
        m = (MatrixXd**)lua_newuserdata(L, sizeof(MatrixXd*));
    }else{
        return luaL_error(L, LAakTable::nospacestack);
    }
    if(n == 1){
        if(lua_istable(L, 1)){
            int rows = lua_rawlen(L, 1);
            int cols;
            bool once = true;
            if(lua_checkstack(L, 1)){
                lua_pushnil(L);
            }else{
                return luaL_error(L, LAakTable::nospacestack);
            }
            int row = 0;
            int col = 0;
            while (lua_next(L, 1) != 0) {
                if(lua_istable(L, -1)){
                    if(once){
                        once = false;
                        cols = lua_rawlen(L, -1);
                        *m = new MatrixXd(rows, cols);
                        (*(*m)).fill(0);
                    }
                    if(lua_checkstack(L, 1)){
                        lua_pushnil(L);
                    }else{
                        return luaL_error(L, LAakTable::nospacestack);
                    }
                    while (lua_next(L, -2) != 0) {
                        if(col >= cols){
                            return luaL_error(L, LAakTable::index_out_range);
                        }
                        (*(*m))(row, col) = luaL_checknumber(L, -1);
                        col++;
                        lua_pop(L, 1);
                    }                    
                    row++;
                    col = 0;
                }else{
                    return luaL_error(L, "table of table expected");
                }
                lua_pop(L, 1);
            }
        }else{
            return luaL_error(L, "table expected");
        }
    }else if(n >= 2){
        int rows = luaL_checkinteger(L, 1);
        int cols = luaL_checkinteger(L, 2);
        *m = new MatrixXd(rows, cols);
        if(*m == nullptr)
            return luaL_error(L, LAakTable::nomemory);
        if(n == 3){
            if(lua_isnumber(L, 3)){
                auto val = luaL_checknumber(L, 3);
                (*(*m)).fill(val);
            }else if(lua_isstring(L, 3)){
                if(strcmp(luaL_checkstring(L, 3), identity) == 0 && rows == cols){
                    (*(*m)) = MatrixXd::Identity(rows, cols);
                }else if(strcmp(luaL_checkstring(L, 3), random) == 0){
                    (*(*m)) = MatrixXd::Random(rows, cols);
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

int Matrix::rand(lua_State* L){
    int r = luaL_checkinteger(L, 1);
    int c = luaL_checkinteger(L, 2);
    MatVec::alloc_matrix(L, MatrixXd::Random(r, c));
    return 1;
}

//need to remove reference -> Address boundary error
int Matrix::free(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    // std::cout << *m << '\t' << "matrix freed" << '\n';
    delete *m;
    m = nullptr;
    return 0;
}

int Matrix::ij(lua_State* L){
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
            return luaL_error(L, LAakTable::nospacestack);
        }
    }else{
        return luaL_error(L, LAakTable::index_out_range);
    }
    return 1;
}

int Matrix::row(lua_State* L){
    int n = lua_gettop(L);
    MatrixXd** m = MatVec::check_matrix(L);
    int r = luaL_checkinteger(L, 2);
    if(r >= 0 && r < (*(*m)).rows()){
        if(n > 2){
            if(lua_istable(L, 3)){
                unsigned int size = lua_rawlen(L, 3);
                auto v = RowVectorXd(size);
                int idx = 0;
                if(lua_checkstack(L, 1))
                    lua_pushnil(L);
                while (lua_next(L, 3) != 0) {
                    if(idx >= size)
                        return luaL_error(L, LAakTable::index_out_range);
                    v[idx] = luaL_checknumber(L, -1);
                    idx++;
                    lua_pop(L, 1);
                }
                if(v.size() == (*(*m)).cols()){
                    (*(*m)).row(r) = v;
                }else{
                    return luaL_error(L, "Vector size and Matrix columns are not the same");
                }
            }else{
                RowVectorXd** v = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename, 3);
                if((*(*v)).size() == (*(*m)).cols()){
                    (*(*m)).row(r) = (*(*v));
                }else{
                    return luaL_error(L, "Vector size and Matrix columns are not the same");
                }
            }
            return 0;
        }
        if(lua_checkstack(L, 1)){
            auto mr = RowVectorXd((*(*m)).row(r));
            MatVec::alloc_vector(L, &mr, MatVec::rowvec_metatablename);
        }else{
            return luaL_error(L, LAakTable::nospacestack);
        }
    }else{
        return luaL_error(L, LAakTable::index_out_range);
    }
    return 1;
}

int Matrix::col(lua_State* L){
    int n = lua_gettop(L);
    MatrixXd** m = MatVec::check_matrix(L);
    int c = luaL_checkinteger(L, 2);
    if(c >= 0 && c < (*(*m)).cols()){
        if(n > 2){
            if(lua_istable(L, 3)){
                unsigned int size = lua_rawlen(L, 3);
                auto v = VectorXd(size);
                int idx = 0;
                if(lua_checkstack(L, 1))
                    lua_pushnil(L);
                while (lua_next(L, 3) != 0) {
                    if(idx >= size)
                        return luaL_error(L, LAakTable::index_out_range);
                    v[idx] = luaL_checknumber(L, -1);
                    idx++;
                    lua_pop(L, 1);
                }
                if(v.size() == (*(*m)).rows()){
                    (*(*m)).col(c) = v;
                }else{
                    return luaL_error(L, "Vector size and Matrix rows are not the same");
                }
            }else{
                VectorXd** v = (VectorXd**)MatVec::check_vector(L, MatVec::vec_metatablename, 3);
                if((*(*v)).size() == (*(*m)).rows()){
                    (*(*m)).col(c) = (*(*v));
                }else{
                    return luaL_error(L, "Vector size and Matrix rows are not the same");
                }
            }
            return 0;
        }
        if(lua_checkstack(L, 1)){
            auto mc = VectorXd((*(*m)).col(c));
            MatVec::alloc_vector(L, &mc, MatVec::vec_metatablename);
        }else{
            return luaL_error(L, LAakTable::nospacestack);
        }
    }else{
        return luaL_error(L, LAakTable::index_out_range);
    }
    return 1;
}

int Matrix::get_matsize(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    if(lua_checkstack(L, 1)){
        lua_pushinteger(L, (*(*m)).size());
    }else{
        return luaL_error(L, LAakTable::nospacestack);
    }
    return 1;
}

int Matrix::cols(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    if(lua_checkstack(L, 1)){
        lua_pushinteger(L, (*(*m)).cols());
    }else{
        return luaL_error(L, LAakTable::nospacestack);
    }
    return 1;
}

int Matrix::rows(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    if(lua_checkstack(L, 1)){
        lua_pushinteger(L, (*(*m)).rows());
    }else{
        return luaL_error(L, LAakTable::nospacestack);
    }
    return 1;
}

int Matrix::cos(lua_State* L){
    MatrixXd** m = (MatrixXd**)MatVec::check_matrix(L);
    MatrixXd nm = (*(*m)).array().cos();
    MatVec::alloc_matrix(L, nm);
    return 1;
}

int Matrix::sin(lua_State* L){
    MatrixXd** m = (MatrixXd**)MatVec::check_matrix(L);
    MatrixXd nm = (*(*m)).array().sin();
    MatVec::alloc_matrix(L, nm);
    return 1;
}

int Matrix::T(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    MatVec::alloc_matrix(L, (*(*m)).transpose());
    return 1;
}

int Matrix::Td(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    (*(*m)).transposeInPlace();
    return 1;
}

int Matrix::inverse(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    MatVec::alloc_matrix(L ,(*(*m)).inverse());
    return 1;
}

int Matrix::det(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    lua_pushnumber(L, (*(*m)).determinant());
    return 1;
}

int Matrix::conj(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    MatVec::alloc_matrix(L, (*(*m)).conjugate());
    return 1;
}

int Matrix::adj(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    MatVec::alloc_matrix(L, (*(*m)).adjoint());
    return 1;
}

int Matrix::adjd(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    (*(*m)).adjointInPlace();
    return 1;
}

int Matrix::trilow(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    MatVec::alloc_matrix(L, (*(*m)).triangularView<Eigen::Lower>());
    return 1;
}

int Matrix::triup(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    MatVec::alloc_matrix(L, (*(*m)).triangularView<Eigen::Upper>());
    return 1;
}

int Matrix::sum(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    if(lua_checkstack(L, 1)){
        lua_pushnumber(L, (*(*m)).sum());
    }else{
        return luaL_error(L, LAakTable::nospacestack);
    }
    return 1;
}

int Matrix::prod(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    if(lua_checkstack(L, 1)){
        lua_pushnumber(L, (*(*m)).prod());
    }else{
        return luaL_error(L, LAakTable::nospacestack);
    }
    return 1;
}

int Matrix::mean(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    if(lua_checkstack(L, 1)){
        lua_pushnumber(L, (*(*m)).mean());
    }else{
        return luaL_error(L, LAakTable::nospacestack);
    }
    return 1;
}

int Matrix::mincoeff(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    if(lua_checkstack(L, 1)){
        lua_pushnumber(L, (*(*m)).minCoeff());
    }else{
        return luaL_error(L, LAakTable::nospacestack);
    }
    return 1;
}

int Matrix::maxcoeff(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    if(lua_checkstack(L, 1)){
        lua_pushnumber(L, (*(*m)).maxCoeff());
    }else{
        return luaL_error(L, LAakTable::nospacestack);
    }
    return 1;
}

int Matrix::trace(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    if(lua_checkstack(L, 1)){
        lua_pushnumber(L, (*(*m)).trace());
    }else{
        return luaL_error(L, LAakTable::nospacestack);
    }
    return 1;
}

int Matrix::add(lua_State* L){
    MatrixXd** a = MatVec::check_matrix(L);

    if(MatVec::isvector(L, MatVec::vec_metatablename, 2)){
        VectorXd** v = (VectorXd**)MatVec::check_vector(L, MatVec::vec_metatablename, 2);
        if((*(*a)).rows() != (*(*v)).size())
            return luaL_error(L, "Matrix rows and Vector size are not the same");
        auto nmat = MatrixXd((*(*a)).rows(), (*(*a)).cols());
        for(int c = 0; c < (*(*a)).cols(); c++){
            nmat.col(c) = (*(*a)).col(c) + (*(*v));
        }
        MatVec::alloc_matrix(L, nmat);
    }else if(MatVec::isvector(L, MatVec::rowvec_metatablename, 2)){
        RowVectorXd** v = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename, 2);
        if((*(*a)).cols() != (*(*v)).size())
            return luaL_error(L, "Matrix columns and Vector size are not the same");
        auto nmat = MatrixXd((*(*a)).rows(), (*(*a)).cols());
        for(int r = 0; r < (*(*a)).rows(); r++){
            nmat.row(r) = (*(*a)).row(r) + (*(*v));
        }
        MatVec::alloc_matrix(L, nmat);
    }else{
        MatrixXd** b = MatVec::check_matrix(L, 2);

        if((*(*a)).size() != (*(*b)).size())
            return luaL_error(L, "Matrices sizes are not the same");

        MatVec::alloc_matrix(L, (*(*a)) + (*(*b)));
    }
    return 1;
}

int Matrix::sub(lua_State* L){
    MatrixXd** a = MatVec::check_matrix(L);

    if(MatVec::isvector(L, MatVec::vec_metatablename, 2)){
        VectorXd** v = (VectorXd**)MatVec::check_vector(L, MatVec::vec_metatablename, 2);
        if((*(*a)).rows() != (*(*v)).size())
            return luaL_error(L, "Matrix rows and Vector size are not the same");
        auto nmat = MatrixXd((*(*a)).rows(), (*(*a)).cols());
        for(int c = 0; c < (*(*a)).cols(); c++){
            nmat.col(c) = (*(*a)).col(c) - (*(*v));
        }
        MatVec::alloc_matrix(L, nmat);
    }else if(MatVec::isvector(L, MatVec::rowvec_metatablename, 2)){
        RowVectorXd** v = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename, 2);
        if((*(*a)).cols() != (*(*v)).size())
            return luaL_error(L, "Matrix columns and Vector size are not the same");
        auto nmat = MatrixXd((*(*a)).rows(), (*(*a)).cols());
        for(int r = 0; r < (*(*a)).rows(); r++){
            nmat.row(r) = (*(*a)).row(r) - (*(*v));
        }
        MatVec::alloc_matrix(L, nmat);
    }else{
        MatrixXd** b = MatVec::check_matrix(L, 2);

        if((*(*a)).size() != (*(*b)).size())
            return luaL_error(L, "Matrices sizes are not the same");

        MatVec::alloc_matrix(L, (*(*a)) - (*(*b)));
    }
    return 1;
}

int Matrix::mul(lua_State* L){
    double s;
    MatrixXd** a;
    MatrixXd** b;
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
        VectorXd** v = (VectorXd**)MatVec::check_vector(L, MatVec::vec_metatablename, 2);
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

int Matrix::eq(lua_State* L){
    MatrixXd** a = MatVec::check_matrix(L);
    MatrixXd** b = MatVec::check_matrix(L, 2);
    if((*(*a)).rows() == (*(*b)).rows() && (*(*a)).cols() == (*(*b)).cols()){
        if(lua_checkstack(L, 1)){
            lua_pushboolean(L, (*(*a)) == (*(*b)));
        }else{
            return luaL_error(L, LAakTable::nospacestack);
        }
    }else{
        return luaL_error(L, "Matrices Dimensions are not the same");
    }
    return 1;
}

int Matrix::tostring(lua_State* L){
    MatrixXd** m = MatVec::check_matrix(L);
    std::ostringstream mosb;
    mosb << (*(*m));
    std::string mstr = mosb.str();
    // std::replace(mstr.begin(), mstr.end(), '\n', ',');
    if(lua_checkstack(L, 1)){
        lua_pushfstring(L, "%s", mstr.c_str());
    }else{
        return luaL_error(L, LAakTable::nospacestack);
    }
    return 1;
}