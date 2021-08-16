#include "Graphics.h"

void Graphics::register_gl(lua_State* L){
    LAakTable::register_table(L, gl_metatablename, gl_methods, gl_functions);
}

int Graphics::init_gl(lua_State* L){
    if (GLEW_OK != glewInit()){
        //cleanup();
		return luaL_error(L, "Error init glew");
	}

    // OpenGL init
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
    // GL version
    if(lua_checkstack(L, 1)){
        lua_pushstring(L, (char*)glGetString(GL_VERSION));
    }else{
        return luaL_error(L, LAakTable::nospacestack);
    }
    return 1;
}

int Graphics::viewport_gl(lua_State* L){
    int n = lua_gettop(L);
    if(n != 4)
        return luaL_error(L, "4 parameters expected, x, y, width, height");
    int vp[4];
    for(int i = 1; i <= n; i++){
        vp[i-1] = luaL_checkinteger(L, i);
    }
    glViewport(vp[0], vp[1], vp[2], vp[3]);
    return 0;
}