include_directories(${GTEST_INCLUDE_DIR} ../include ../../Common/include ./mocks ./stubs)
link_directories(${GTEST_LIB_DIR})

add_executable(CultsBoardTest CultsBoardTest.cc TestMain.cc)
target_link_libraries(CultsBoardTest CultsBoard gmock pthread)

add_test(NAME cults_board_unit_test COMMAND CultsBoardTest)
