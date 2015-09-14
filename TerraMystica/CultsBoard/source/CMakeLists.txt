include_directories(
    ../include 
    ../../Common/include
)

add_library(
    CultsBoard
    CultsBoardImpl.cc
    CultsLane.cc
    KeyCounter.cc
)
