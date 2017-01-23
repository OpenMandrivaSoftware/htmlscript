cmake_minimum_required(VERSION 3.5)
project(htmlscript)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_definitions(-std=gnu++14)

find_package(Qt5 COMPONENTS Core Gui Widgets WebEngineWidgets REQUIRED)
add_executable(htmlscript main.cpp Page.cpp)
qt5_use_modules(htmlscript Core Gui Widgets WebEngineWidgets)

install(TARGETS htmlscript DESTINATION bin)
