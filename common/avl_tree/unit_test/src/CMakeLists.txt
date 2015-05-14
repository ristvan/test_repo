include_directories(${GTEST_DIR}/include ../../include)

add_executable(AVLTreeTest main.cc)
target_link_libraries(AVLTreeTest Common gtest)
