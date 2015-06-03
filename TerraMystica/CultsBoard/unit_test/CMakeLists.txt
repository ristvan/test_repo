include_directories(${GTEST_INCLUDE_DIR} ../include ../../Common/include ./mocks)
link_directories(${GTEST_LIB_DIR})

add_executable(CultsBoardTest CultsBoardTest.cc)
target_link_libraries(CultsBoardTest CultsBoard gmock pthread)
