cmake_minimum_required(VERSION 2.8.12)

project(WikiSearch)

find_package(Qt5 ${REQUIRED_QT_VERSION} NO_MODULE REQUIRED Core Network Widgets)
find_package(KF5MediaWiki ${KF5_VERSION} REQUIRED)
find_package(KF5CoreAddons ${KF5_VERSION} REQUIRED NO_MODULE)

set (WikiSearch_src ${PROJECT_SOURCE_DIR}/wikiform.cpp)
set (WikiSearch_hdr ${PROJECT_SOURCE_DIR}/wikiform.h)
set (WikiSearch_ui  ${PROJECT_SOURCE_DIR}/wikiform.ui)
set (WikiSearchBin_src ${PROJECT_SOURCE_DIR}/main.cpp)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)

qt5_wrap_cpp(WikiSearchLib_hdr_moc ${WikiSearchLib_hdr})
qt5_wrap_ui (WikiSearchLib_ui_moc  ${WikiSearchLib_ui})

add_executable(WikiSearch
              ${WikiSearchBin_src}
              ${WikiSearch_hdr}
              ${WikiSearch_ui}
              ${WikiSearch_src})




target_link_libraries(WikiSearch

    PRIVATE
        Qt5::Core
        Qt5::Network
        Qt5::Widgets
        KF5::MediaWiki
        KF5::CoreAddons
)

set_target_properties(WikiSearch PROPERTIES COMPILE_FLAGS "-std=c++11")
