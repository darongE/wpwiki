
#project name
project(WikiSearch)

#
cmake_minimum_required(VERSION 2.8.12)


find_package(Qt5 ${REQUIRED_QT_VERSION} NO_MODULE REQUIRED Core Network Widgets)
find_package(WPMediaWiki ${KF5_VERSION} REQUIRED)
find_package(KF5CoreAddons ${KF5_VERSION} REQUIRED NO_MODULE)

qt5_wrap_ui(WikiSearch UI_FILES mainwindow.ui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_executable(
    WikiSearch
    mainwindow.cpp
   ${UI_FILES}
   mainwindow.ui
)


target_link_libraries(WikiSearch
    PRIVATE
        Qt5::Core
        Qt5::Network
        Qt5::Widgets
        WP::WPWiki
        KF5::CoreAddons
)

set_target_properties(WikiSearch PROPERTIES COMPILE_FLAGS "-std=c++11")


#target_link_libraries(ThreadWeaver_ThumbNailer KF5::ThreadWeaver)
