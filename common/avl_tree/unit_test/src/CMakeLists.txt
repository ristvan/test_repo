include_directories(${GTEST_INCLUDE_DIR} ../../include)
link_directories(${GTEST_LIB_DIR})

add_executable(AVLTreeTest main.cc)
target_link_libraries(AVLTreeTest Common gtest pthread)
