#include "Vector.h"
#include "Matrix.h"

namespace LA {
    static void register_la(lua_State* L){
        Vector::register_vector(L);
        Matrix::register_matrix(L);
    }
};
