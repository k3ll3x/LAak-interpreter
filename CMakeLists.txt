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
)

add_executable(laak ${SOURCES})

#libraries
# set (CMAKE_SHARED_LINKER_FLAGS "")
set(LUA ${CMAKE_CURRENT_SOURCE_DIR}/lua/lib/liblua.a)

target_link_libraries(laak ${LUA} ${EIGENLIB} ${CMAKE_DL_LIBS})

#threads
# set(THREADS_PREFER_PTHREAD_FLAG ON)
# find_package(Threads REQUIRED)

# target_link_libraries(cg_planet ${LIBS} Threads::Threads)