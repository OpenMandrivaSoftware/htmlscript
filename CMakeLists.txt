cmake_minimum_required(VERSION 3.20)
project(htmlscript)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 23)

set(QT_VERSION 6 CACHE STRING "Major version of Qt to use (5 and 6 will work, anything else may or may not work)")

find_package(Qt${QT_VERSION} COMPONENTS Core Gui Widgets WebEngineWidgets REQUIRED)
add_executable(htmlscript main.cpp Page.cpp)
target_link_libraries(htmlscript Qt${QT_VERSION}::Core Qt${QT_VERSION}::Gui Qt${QT_VERSION}::Widgets Qt${QT_VERSION}::WebEngineWidgets)

install(TARGETS htmlscript DESTINATION bin)
