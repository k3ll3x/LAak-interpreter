#ifndef GRAPHICS
#define GRAPHICS
#include <GL/glew.h>
#endif

#include "LAakTable.h"

class Graphics {
public:
    Graphics() = delete;
    ~Graphics() = delete;
    static void register_gl(lua_State* L);
private:
    inline static const char* gl_metatablename = "gl";

    //functions
    static int init_gl(lua_State* L);
    static int viewport_gl(lua_State* L);

    //functions
    inline static const luaL_Reg gl_methods[] = {
        { nullptr, nullptr }
    };

    //methods
    inline static const luaL_Reg gl_functions[] = {
        { "init", init_gl },
        { "viewport", viewport_gl },
        { nullptr, nullptr }
    };
};