#include "Vector.h"

void print_stack(lua_State* L){
    int n = lua_gettop(L);
    std::cout << "\t\tStack:\n";
    for(int i = 1; i <= n; i++){
        std::cout << "\t" << luaL_typename(L, lua_type(L, i)) << '\n';
    }
}

void Vector::register_methods(lua_State* L, luaL_Reg const* methods){
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);
    lua_settable(L, -3);
    for(int i = 0; (methods+i)->name != nullptr; ++i){
        lua_pushcfunction(L, (methods+i)->func);
        lua_setfield(L, -2, (methods+i)->name);
    }
}

void Vector::register_vector(lua_State* L){
    //Column Vectors
    luaL_newmetatable(L, MatVec::vec_metatablename);
    register_methods(L, vector_methods);
    luaL_setfuncs(L, vector_functions, 0);
    lua_setglobal(L, MatVec::vec_metatablename);

    //Row Vectors
    luaL_newmetatable(L, MatVec::rowvec_metatablename);
    register_methods(L, vector_methods);
    luaL_setfuncs(L, vector_functions, 0);
    lua_setglobal(L, MatVec::rowvec_metatablename);
}

double* Vector::get_element(lua_State* L, const char* name){
    print_stack(L);
    if(strcmp(name, MatVec::vec_metatablename) == 0){
        VectorXd** v = (VectorXd**)MatVec::check_vector(L);
        int index = luaL_checkinteger(L, 2);
        luaL_argcheck(L, 0 <= index && index < (*(*v)).size(), 2, "index out of range");
        return &(*(*v))[index];
    }else{
        RowVectorXd** v = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename);
        int index = luaL_checkinteger(L, 2);
        luaL_argcheck(L, 0 <= index && index < (*(*v)).size(), 2, "index out of range");
        return &(*(*v))[index];
    }
    std::cout << "none\n";
    return nullptr;
}

int Vector::get_vecelem(lua_State* L){
    print_stack(L);
    if(MatVec::isvector(L)){
        if(lua_checkstack(L, 1)){
            lua_pushnumber(L, *get_element(L));
        }else{
            return luaL_error(L, "no more space in stack");
        }
    }else{
        if(lua_checkstack(L, 1)){
            lua_pushnumber(L, *get_element(L, MatVec::rowvec_metatablename));
        }else{
            return luaL_error(L, "no more space in stack");
        }
    }
    return 1;
}

int Vector::set_vecelem(lua_State* L){
    print_stack(L);
    double newval = luaL_checknumber(L, 3);
    if(MatVec::isvector(L)){
        *get_element(L) = newval;
    }else{
        *get_element(L, MatVec::rowvec_metatablename) = newval;
    }
    return 0;
}

int Vector::new_vector(lua_State* L){
    int n = lua_gettop(L);
    if(n >= 1){
        VectorXd** v = (VectorXd**)lua_newuserdata(L, sizeof(VectorXd*));
        if(n == 1){
            //create vector with argument as size
            if(lua_isnumber(L,1)){
                int size = luaL_checkinteger(L, 1);
                *v = new VectorXd(size);
            //create vector with contents of table
            }else if(lua_istable(L,1)){
                *v = new VectorXd(lua_rawlen(L, 1));
                if(lua_checkstack(L, 1)){
                    lua_pushnil(L);
                }else{
                    return luaL_error(L, "no more space in stack");
                }
                int idx = 0;
                while (lua_next(L, 1) != 0) {
                    (*(*v))[idx] = luaL_checknumber(L, -1);
                    idx++;
                    lua_pop(L, 1);
                }
            }else{
                return luaL_error(L, "Expected number or table/list");
            }
        }
        else{
            //create vector with multiple arguments
            *v = new VectorXd(n);
            for(int i = 1; i <= n; i++){
                (*(*v))[i-1] = luaL_checknumber(L, i);
            }
        }
    }else{
        return luaL_error(L, "Expected more arguments");
    }
    luaL_getmetatable(L, MatVec::vec_metatablename);
    lua_setmetatable(L, -2);
    return 1;
}

int Vector::free_vector(lua_State* L){
    print_stack(L);
    if(MatVec::isvector(L)){
        VectorXd** v = (VectorXd**)MatVec::check_vector(L);
        std::cout << *v << '\t' << "colum vector freed" << '\n';
        delete *v;
    }else{
        RowVectorXd** v = (RowVectorXd**)MatVec::check_vector(L);
        std::cout << *v << '\t' << "row vector freed" << '\n';
        delete *v;
    }
    return 0;
}

int Vector::add_vectors(lua_State* L){
    if(MatVec::isvector(L, MatVec::vec_metatablename, 2)){
        VectorXd** a = (VectorXd**)MatVec::check_vector(L);
        VectorXd** b = (VectorXd**)MatVec::check_vector(L, MatVec::vec_metatablename, 2);
        
        if((*(*a)).size() != (*(*b)).size())
            return luaL_error(L, "Vector sizes are not the same");
        
        auto r = VectorXd((*(*a)) + (*(*b)));
        MatVec::alloc_vector(L, &r);
    }else{
        RowVectorXd** a = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename);
        RowVectorXd** b = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename, 2);
        
        if((*(*a)).size() != (*(*b)).size())
            return luaL_error(L, "Vector sizes are not the same");
        
        auto r = RowVectorXd((*(*a)) + (*(*b)));
        MatVec::alloc_vector(L, &r, MatVec::rowvec_metatablename);
    }
    return 1;
}

int Vector::sub_vectors(lua_State* L){
    if(MatVec::isvector(L, MatVec::vec_metatablename, 2)){
        VectorXd** a = (VectorXd**)MatVec::check_vector(L);
        VectorXd** b = (VectorXd**)MatVec::check_vector(L, MatVec::vec_metatablename, 2);
        
        if((*(*a)).size() != (*(*b)).size())
            return luaL_error(L, "Vector sizes are not the same");
        
        auto r = VectorXd((*(*a)) - (*(*b)));
        MatVec::alloc_vector(L, &r);
    }else{
        RowVectorXd** a = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename);
        RowVectorXd** b = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename, 2);
        
        if((*(*a)).size() != (*(*b)).size())
            return luaL_error(L, "Vector sizes are not the same");
        
        auto r = RowVectorXd((*(*a)) - (*(*b)));
        MatVec::alloc_vector(L, &r, MatVec::rowvec_metatablename);
    }
    return 1;
}

int Vector::mul_vector(lua_State* L){
    print_stack(L);
    if(lua_isnumber(L,1)){
        //number * vector = vector
        std::cout << "number * vector = vector\n";
        double a = luaL_checknumber(L, 1);
        if(MatVec::isvector(L, MatVec::vec_metatablename, 2)){
            std::cout << "column vector\n";
            VectorXd** v = (VectorXd**)MatVec::check_vector(L, MatVec::vec_metatablename, 2);
            auto res = VectorXd(a * (*(*v)));
            MatVec::alloc_vector(L, &res);
        }else{
            std::cout << "row vector\n";
            RowVectorXd** v = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename, 2);
            auto res = RowVectorXd(a * (*(*v)));
            MatVec::alloc_vector(L, &res, MatVec::rowvec_metatablename);
        }
        return 1;
    }else if(lua_isnumber(L, 2)){
        //vector * number = vector
        double a = luaL_checknumber(L, 2);
        std::cout << "vector * number = vector\n";
        if(MatVec::isvector(L)){//???
            std::cout << "cv*s\n";
            VectorXd** v = (VectorXd**)MatVec::check_vector(L);
            auto res = VectorXd(a * (*(*v)));
            MatVec::alloc_vector(L, &res);
        }else{
            std::cout << "rv*s\n";
            RowVectorXd** v = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename);
            auto res = RowVectorXd(a * (*(*v)));
            MatVec::alloc_vector(L, &res, MatVec::rowvec_metatablename);
        }
        return 1;
    }else if(MatVec::ismatrix(L, 2)){
        //rowvector * matrix = rowvector
        std::cout << "rowvector * matrix = rowvector\n";
        RowVectorXd** rv = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename);
        MatrixXd** m = MatVec::check_matrix(L, 2);
        if((*(*rv)).cols() == (*(*m)).rows()){
            auto res = RowVectorXd((*(*rv)) * (*(*m)));
            MatVec::alloc_vector(L, &res, MatVec::rowvec_metatablename);
            return 1;
        }else{
            return luaL_error(L, "Matrix columns and Vector rows are not the same");
        }
    }else if(MatVec::isvector(L, MatVec::rowvec_metatablename)){//???
        //row vector * column vector = scalar
        std::cout << "row vector * column vector = scalar\n";
        RowVectorXd** a = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename);
        VectorXd** b = (VectorXd**)MatVec::check_vector(L, MatVec::vec_metatablename, 2);
        if((*(*a)).cols() != (*(*b)).rows())
            return luaL_error(L, "Vector rows and cols are not the same");
        auto res = (*(*a)) * (*(*b));
        if(lua_checkstack(L, 1)){
            lua_pushnumber(L, res);
        }else{
            return luaL_error(L, "no more space in stack");
        }
        return 1;
    }else{
        //column vector * row vector = matrix
        std::cout << "column vector * row vector = matrix\n";
        VectorXd** a = (VectorXd**)MatVec::check_vector(L, MatVec::vec_metatablename);
        RowVectorXd** b = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename, 2);
        if((*(*a)).rows() != (*(*b)).cols())
            return luaL_error(L, "Vector rows and cols are not the same");
        MatrixXd res = (*(*a)) * (*(*b));
        MatVec::alloc_matrix(L, res);
        return 1;
    }
    return 1;
}

int Vector::norm_vector(lua_State* L){
    if(MatVec::isvector(L)){
        VectorXd** v = (VectorXd**)MatVec::check_vector(L);
        (*(*v)).normalize();
    }else{
        RowVectorXd** v = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename);
        (*(*v)).normalize();
    }
    return 0;
}

int Vector::normc_vector(lua_State* L){
    if(MatVec::isvector(L)){
        VectorXd** v = (VectorXd**)MatVec::check_vector(L);
        auto r = (*(*v)).normalized();
        MatVec::alloc_vector(L, &r);
    }else{
        RowVectorXd** v = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename);
        auto r = (*(*v)).normalized();
        MatVec::alloc_vector(L, &r, MatVec::rowvec_metatablename);
    }
    return 0;
}

int Vector::mag_vector(lua_State* L){
    if(MatVec::isvector(L)){
        VectorXd** v = (VectorXd**)MatVec::check_vector(L);
        if(lua_checkstack(L, 1)){
            lua_pushnumber(L, (*(*v)).norm());
        }else{
            return luaL_error(L, "no more space in stack");
        }
    }else{
        RowVectorXd** v = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename);
        if(lua_checkstack(L, 1)){
            lua_pushnumber(L, (*(*v)).norm());
        }else{
            return luaL_error(L, "no more space in stack");
        }
    }
    return 1;
}

// bad argument #-2 to 'dot' (string expected, got nil)
int Vector::dot_vectors(lua_State* L){
    print_stack(L);
    if(MatVec::isvector(L)){
        VectorXd** a = (VectorXd**)MatVec::check_vector(L);
        VectorXd** b = (VectorXd**)MatVec::check_vector(L, MatVec::vec_metatablename, 2);
        if((*(*a)).size() != (*(*b)).size())
            return luaL_error(L, "Vector sizes are not the same");
        auto d = (*(*a)).dot(*(*b));
        if(lua_checkstack(L, 1)){
            lua_pushnumber(L, d);
        }else{
            return luaL_error(L, "no more space in stack");
        }
    }else{
        RowVectorXd** a = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename);
        RowVectorXd** b = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename, 2);
        if((*(*a)).size() != (*(*b)).size())
            return luaL_error(L, "Vector sizes are not the same");
        auto d = (*(*a)).dot(*(*b));
        if(lua_checkstack(L, 1)){
            lua_pushnumber(L, d);
        }else{
            return luaL_error(L, "no more space in stack");
        }
    }
    return 1;
}

// bad argument #-2 to 'cross' (string expected, got nil)
int Vector::cross_vectors(lua_State* L){
    print_stack(L);
    if(MatVec::isvector(L)){
        VectorXd** a = (VectorXd**)MatVec::check_vector(L);
        VectorXd** b = (VectorXd**)MatVec::check_vector(L, MatVec::vec_metatablename, 2);
        if((*(*a)).size() != (*(*b)).size() || (*(*a)).size() != 3)
            return luaL_error(L, "Vector sizes are not the same and they should be 3 dimensions");
        Eigen::Vector<double, 3> aa, bb;
        aa = (*(*a));
        bb = (*(*b));
        auto v = aa.cross(bb);
        MatVec::alloc_vector(L, &v);
    }else{
        RowVectorXd** a = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename);
        RowVectorXd** b = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename, 2);
        if((*(*a)).size() != (*(*b)).size() || (*(*a)).size() != 3)
            return luaL_error(L, "Vector sizes are not the same and they should be 3 dimensions");
        Eigen::Vector<double, 3> aa, bb;
        aa = (*(*a));
        bb = (*(*b));
        auto v = aa.cross(bb);
        MatVec::alloc_vector(L, &v, MatVec::rowvec_metatablename);
    }
    return 1;
}

int Vector::T_vector(lua_State* L){
    if(MatVec::isvector(L)){
        VectorXd** a = (VectorXd**)MatVec::check_vector(L);
        auto r = RowVectorXd((*(*a)).transpose());
        MatVec::alloc_vector(L, &r, MatVec::rowvec_metatablename);
    }else{
        RowVectorXd** a = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename);
        auto r = VectorXd((*(*a)).transpose());
        MatVec::alloc_vector(L, &r, MatVec::vec_metatablename);
    }
    return 1;
}

int Vector::type_vector(lua_State* L){
    if(MatVec::isvector(L)){
        if(lua_checkstack(L, 1)){
            lua_pushstring(L, "column vector");
        }else{
            return luaL_error(L, "no more space in stack");
        }
    }else{
        if(lua_checkstack(L, 1)){
            lua_pushstring(L, "row vector");
        }else{
            return luaL_error(L, "no more space in stack");
        }
    }
    return 1;
}

int Vector::get_vecsize(lua_State* L){
    if(MatVec::isvector(L)){
        VectorXd** v = (VectorXd**)MatVec::check_vector(L);
        if(lua_checkstack(L, 1)){
            lua_pushinteger(L, (*(*v)).size());
        }else{
            return luaL_error(L, "no more space in stack");
        }
    }else{
        RowVectorXd** v = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename);
        if(lua_checkstack(L, 1)){
            lua_pushinteger(L, (*(*v)).size());
        }else{
            return luaL_error(L, "no more space in stack");
        }
    }
    return 1;
}

// bad argument #-1 to 'eq' (string expected, got nil)
int Vector::eq_vectors(lua_State* L){
    print_stack(L);
    if(MatVec::isvector(L)){
        VectorXd** a = (VectorXd**)MatVec::check_vector(L);
        VectorXd** b = (VectorXd**)MatVec::check_vector(L, MatVec::vec_metatablename, 2);
        if(lua_checkstack(L, 1)){
            lua_pushboolean(L, (*(*a)) == (*(*b)));
        }else{
            return luaL_error(L, "no more space in stack");
        }
    }else{
        RowVectorXd** a = (RowVectorXd**)MatVec::check_vector(L);
        RowVectorXd** b = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename, 2);
        if(lua_checkstack(L, 1)){
            lua_pushboolean(L, (*(*a)) == (*(*b)));
        }else{
            return luaL_error(L, "no more space in stack");
        }
    }
    return 1;
}

int Vector::unm_vector(lua_State* L){
    //I dont know why should be index 2 but works
    if(MatVec::isvector(L, MatVec::vec_metatablename, 2)){
    // if(MatVec::isvector(L)){
        VectorXd** a = (VectorXd**)MatVec::check_vector(L);
        VectorXd res = -(*(*a));
        MatVec::alloc_vector(L, &res, MatVec::vec_metatablename);
    }else{
        RowVectorXd** a = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename);
        RowVectorXd res = -(*(*a));
        MatVec::alloc_vector(L, &res, MatVec::rowvec_metatablename);
    }
    return 1;
}

int Vector::vector_tostring(lua_State* L){
    if(MatVec::isvector(L)){
        VectorXd** v = (VectorXd**)MatVec::check_vector(L);
        std::ostringstream vosb;
        vosb << (*(*v));
        std::string vstr = vosb.str();
        if(lua_checkstack(L, 1)){
            lua_pushfstring(L, "[\n%s\n]", vstr.c_str());
        }else{
            return luaL_error(L, "no more space in stack");
        }
        // lua_pushfstring(L, "%s", vstr.c_str());
    }else{
        RowVectorXd** v = (RowVectorXd**)MatVec::check_vector(L, MatVec::rowvec_metatablename);
        std::ostringstream vosb;
        vosb << (*(*v));
        std::string vstr = vosb.str();
        // std::replace(vstr.begin(), vstr.end(), '\n', ',');
        if(lua_checkstack(L, 1)){
            lua_pushfstring(L, "[ %s ]", vstr.c_str());
        }else{
            return luaL_error(L, "no more space in stack");
        }
        // lua_pushfstring(L, "%s", vstr.c_str());
    }
    return 1;
}