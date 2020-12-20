cmake_minimum_required(VERSION 3.5)

project(current_calculator LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt5 COMPONENTS Widgets Core Gui WebEngineWidgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets WebEngineWidgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.h
        mainwindow.cpp
        caltulate_circuit.h
        caltulate_circuit.cpp
)


add_executable(current_calculator  ${PROJECT_SOURCES})
target_link_libraries(current_calculator PRIVATE Qt5::Widgets Qt5::WebEngineWidgets)


