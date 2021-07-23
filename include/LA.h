#include "Vector.h"

namespace LA {
    static void register_la(lua_State* L){
        Vector::register_vector(L);
    }
};
