cmake_minimum_required(VERSION 3.16)

project(Counter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Sql)


qt_standard_project_setup()

qt_add_executable(appCounter
    main.cpp
)

qt_add_qml_module(appCounter
    URI Counter
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES mycounter.h mycounter.cpp
    RESOURCES assets/background1.jpg assets/background3.jpg assets/background4.jpg assets/background5.jpg assets/background6.jpg assets/background7.jpg assets/background8.jpg
    SOURCES randomnumbergenerator.h randomnumbergenerator.cpp
    SOURCES filehandler.h filehandler.cpp
    SOURCES databasemanager.h databasemanager.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appCounter PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appCounter
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appCounter
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Core Qt6::Gui Qt6::Sql
)

include(GNUInstallDirs)
install(TARGETS appCounter
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
