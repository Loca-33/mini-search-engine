cmake_minimum_required(VERSION 3.5)

project(MiniSearchEngine VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(MiniSearchEngine
    main.cpp
    mainwindow.cpp
    searchengine.cpp
    mainwindow.h
    searchengine.h
)

target_link_libraries(MiniSearchEngine PRIVATE Qt6::Widgets)

set_target_properties(MiniSearchEngine PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
