cmake_minimum_required(VERSION 3.19)

# laak interpreter
project(laak VERSION 1.0)

# C++ standard
set(CMAKE_CXX_STANDARD 20)

#add Eigen library
add_subdirectory(eigen)
set(EIGENLIB eigen)

#wildcard additions sources
file(GLOB SOURCES "src/*.cc")

# includes
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lua/include
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)

#imgui
set(IMGUI_SRC
    ${IMGUI_SRC}
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

set (CMAKE_SHARED_LINKER_FLAGS "-DIMGUI_IMPL_OPENGL_LOADER_GLEW,`pkg-config --static --libs glfw3`,`pkg-config --cflags glfw3`")
set(WINLIB GL glfw GLEW)

#LUA
# set (CMAKE_SHARED_LINKER_FLAGS "")
set(LUA ${CMAKE_CURRENT_SOURCE_DIR}/lua/lib/liblua.a)
set(EXECLIBS edit ${WINLIB})

add_executable(ilaak ${SOURCES} ${IMGUI_SRC})
target_link_libraries(ilaak ${LUA} ${EIGENLIB} ${CMAKE_DL_LIBS} ${EXECLIBS})

#laaklib
add_library(laak STATIC ${SOURCES})
target_link_libraries(laak PUBLIC ${LUA} ${EIGENLIB} ${CMAKE_DL_LIBS} )
target_include_directories(laak PUBLIC include PRIVATE src)
target_include_directories(laak PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lua/include)

#threads
# set(THREADS_PREFER_PTHREAD_FLAG ON)
# find_package(Threads REQUIRED)

# target_link_libraries(cg_planet ${LIBS} Threads::Threads)
