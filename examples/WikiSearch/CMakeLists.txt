cmake_minimum_required(VERSION 2.8.12)

project(WikiSearch)

find_package(Qt5 ${REQUIRED_QT_VERSION} NO_MODULE REQUIRED Core Network Widgets)
find_package(WPMediaWiki ${KF5_VERSION} REQUIRED)
find_package(KF5CoreAddons ${KF5_VERSION} REQUIRED NO_MODULE)

set(CMAKE_AUTOMOC ON)

add_executable(
    WikiSearch
    mainwindow.cpp
)

target_link_libraries(WikiSearch
    PRIVATE
        Qt5::Core
        Qt5::Network
        Qt5::Widgets
        WP::Mediawiki
        KF5::CoreAddons
)
set_target_properties(WikiSearch PROPERTIES COMPILE_FLAGS "-std=c++11")
