include_directories(${GTEST_DIR}/include ../../include)
link_directories(${GTEST_DIR})

add_executable(AVLTreeTest main.cc)
target_link_libraries(AVLTreeTest Common gtest pthread)
