cmake_minimum_required (VERSION 2.6)

message( ${HOME} )
set (GTEST_LIB_DIR ${HOME}/apps/lib)
set (GTEST_INCLUDE_DIR ${HOME}/apps/include)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

enable_testing()
add_subdirectory(common)
add_subdirectory(TerraMystica)
