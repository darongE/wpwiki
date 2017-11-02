

set(MediaWiki_SRCS
    browsepage.cpp
    work.cpp
    WPMediaWiki.cpp
    query.cpp
    wikipage.cpp
    shield.cpp
    )



set(WPMediaWiki_INCLUDE_INSTALL_DIR ${CMAKECONFIG_INSTALL_DIR})

add_library(WPMediaWiki ${MediaWiki_SRCS})
generate_export_header(WPMediaWiki BASE_NAME MediaWiki)

add_library(WP::MediaWiki ALIAS WPMediaWiki)

target_include_directories(WPMediaWiki INTERFACE "$<INSTALL_INTERFACE:${WPMediaWiki_INCLUDE_INSTALL_DIR}/MediaWiki>")


target_link_libraries(WPMediaWiki
    PRIVATE
        Qt5::Core
        Qt5::Network
        KF5::CoreAddons
)

set_target_properties(WPMediaWiki
    PROPERTIES VERSION ${WPWIKI_VERSION_STRING}
    SOVERSION ${MediaWiki_SOVERSION}
    EXPORT_NAME "WPMediaWiki"
)

ecm_generate_headers(
                          WPMediaWiki_HEADERS
                          HEADER_NAMES
                          BrowsePage
                          work
                          WPMediaWiki
                          query
                          wikipage
                          shield
                          cookiehandler
                          REQUIRED_HEADERS MediaWiki_HEADERS
)

# Install files
install(TARGETS WPMediaWiki
        EXPORT WPMediaWikiTargets
        ${INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/MediaWiki_export.h
            ${MediaWiki_HEADERS}
            ${WPMediaWiki_HEADERS}
        DESTINATION ${WPMediaWiki_INCLUDE_INSTALL_DIR}/MediaWiki
        COMPONENT Devel)

include(ECMGeneratePriFile)

ecm_generate_pri_file(
    BASE_NAME MediaWiki
    LIB_NAME WPMediaWiki
    DEPS "core network"
    FILENAME_VAR PRI_FILENAME
)

install(FILES ${PRI_FILENAME}
        DESTINATION ${ECM_MKSPECS_INSTALL_DIR})
