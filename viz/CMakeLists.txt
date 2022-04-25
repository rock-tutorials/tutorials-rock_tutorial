rock_find_qt5(Core)

rock_vizkit_plugin(rock_tutorial-viz
    RockVisualization.cpp
    MOC RockVisualization.hpp
    DEPS_PKGCONFIG base-types
    HEADERS RockVisualization.hpp)

install(FILES
    ${PROJECT_SOURCE_DIR}/resources/rock.osg
    ${PROJECT_SOURCE_DIR}/resources/rock.png
    DESTINATION share/vizkit3d
    )
