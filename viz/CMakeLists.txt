
rock_vizkit_plugin(rock_tutorial-viz
    RockVisualization.cpp 
    HEADERS RockVisualization.hpp)

install(FILES
    ${PROJECT_SOURCE_DIR}/resources/rock.osg
    ${PROJECT_SOURCE_DIR}/resources/rock.png
    DESTINATION share/vizkit
    )
