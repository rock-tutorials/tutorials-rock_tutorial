rock_library(rock_tutorial_viz
    SOURCES dummy.cpp)

rock_executable(rock_tutorial_viz_bin main.cpp
    DEPS rock_tutorial_viz)

