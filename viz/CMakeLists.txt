
rock_find_qt5(OPTIONAL)
rock_find_qt4(OPTIONAL)

include(RockQt)

rock_qt_vizkit_plugin(
    TARGETPREFIX rock_tutorial-viz
    QT4_SUFFIX ""
    SOURCES RockVisualization.cpp
    MOC RockVisualization.hpp
    DEPS_PKGCONFIG base-types
    HEADERS RockVisualization.hpp)

install(FILES
    ${PROJECT_SOURCE_DIR}/resources/rock.osg
    ${PROJECT_SOURCE_DIR}/resources/rock.png
    DESTINATION share/vizkit3d
    )
