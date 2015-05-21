include_directories(${GTEST_DIR}/include ../include)
link_directories(${GTEST_DIR})

add_executable(CultsBoardTest CultsBoardTest.cc)
target_link_libraries(CultsBoardTest CultsBoard gtest pthread)
