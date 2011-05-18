rock_library(rocktutorial-viz
    SOURCES RockVisualization.cpp
    HEADERS RockVisualization.hpp
    DEPS_PKGCONFIG base-types vizkit
)

#rock_executable(rock_tutorial-viz_bin main.cpp
#    DEPS rocktutorial-viz)

