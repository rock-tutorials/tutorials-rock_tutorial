rock_vizkit_plugin(rock_tutorial-viz
    RockVisualization.cpp
    HEADERS RockVisualization.hpp)

# install osg file
install(FILES
    ../resources/rock.osg
    ../resources/rock.png
    DESTINATION share/vizkit
    )

#rock_executable(rock_tutorial-viz_bin main.cpp
#    DEPS rock_tutorial-viz)

