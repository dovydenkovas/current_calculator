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
        src/main.cpp
        src/mainwindow.h
        src/mainwindow.cpp
        src/caltulate_circuit.h
        src/caltulate_circuit.cpp
        src/resources.rc
)


macro(copy_directory _src _dst)
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${_src} ${_dst}
        RESULT_VARIABLE _res
        OUTPUT_VARIABLE _out
        ERROR_VARIABLE  _err
    )
    if(_err)
        message(FATAL_ERROR "ERROR ---> could not be copied: ${_err}")
    endif()
endmacro()
copy_directory(${PROJECT_SOURCE_DIR}/images ${PROJECT_BINARY_DIR}/images)

add_executable(current_calculator WIN32 ${PROJECT_SOURCES})
target_link_libraries(current_calculator PRIVATE Qt5::Widgets Qt5::WebEngineWidgets)
