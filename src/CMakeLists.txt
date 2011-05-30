rock_library(rock_tutorial-viz
    SOURCES RockVisualization.cpp
    HEADERS RockVisualization.hpp
    DEPS_PKGCONFIG base-types vizkit
)

# install osg file
install(FILES
    ../resources/rock.osg
    ../resources/rock.png
    DESTINATION share/vizkit
    )

#rock_executable(rock_tutorial-viz_bin main.cpp
#    DEPS rock_tutorial-viz)

