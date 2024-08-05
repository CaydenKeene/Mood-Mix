cmake_minimum_required(VERSION 3.16)

project(Mood-Mix VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appMood-Mix
    main.cpp
)

qt_add_qml_module(appMood-Mix
    URI Mood-Mix
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES songmanager.cpp songmanager.h
        SOURCES tsl/array-hash/array_growth_policy.h tsl/array-hash/array_hash.h tsl/array-hash/array_map.h tsl/array-hash/array_set.h tsl/htrie_hash.h tsl/htrie_map.h tsl/htrie_set.h
        SOURCES DataAccess.cpp DataAccess.h
        QML_FILES Components/Attribute.qml
        QML_FILES Components/Search.qml
        QML_FILES Components/TimeCompare.qml
        QML_FILES Components/Info.qml
        RESOURCES Icons/spotify.svg
        RESOURCES Icons/spotify.png
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appMood-Mix PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appMood-Mix
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appMood-Mix
    PRIVATE Qt6::Quick
    #PRIVATE tsl::hat_trie
)

include(GNUInstallDirs)
install(TARGETS appMood-Mix
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
