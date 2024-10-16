cmake_minimum_required(VERSION 3.29)
project(system_of_hotels)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/fedororlov/Qt/6.8.0/ios/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(system_of_hotels main.cpp
        host.cpp
        host.h
        host.ui
        Room.h)
target_link_libraries(system_of_hotels
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

