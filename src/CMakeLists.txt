

set(MediaWiki_SRCS
    browsepage.cpp
    Work.cpp
    MediaWiki.cpp
    Query.cpp
    WikiPage.cpp
    )



set(WPMEDIAWIKI_INCLUDE_INSTALL_DIR ${CMAKECONFIG_INSTALL_DIR})

add_library(WPMediaWiki ${MediaWiki_SRCS})
generate_export_header(WPMediaWiki BASE_NAME MediaWiki)

add_library(WP::MediaWiki ALIAS WPMediaWiki)

target_include_directories(WPMediaWiki INTERFACE "$<INSTALL_INTERFACE:${WPMEDIAWIKI_INCLUDE_INSTALL_DIR}/MediaWiki>")


target_link_libraries(WPMediaWiki
    PRIVATE
        Qt5::Core
        Qt5::Network
        KF5::CoreAddons
)

set_target_properties(WPMediaWiki
    PROPERTIES VERSION ${MediaWiki_VERSION_STRING}
    SOVERSION ${MediaWiki_SOVERSION}
    EXPORT_NAME "MediaWiki"
)

ecm_generate_headers(
                          WPMediaWiki_HEADERS
                          HEADER_NAMES
                          BrowsePage
                          Work
                          MediaWiki
                          Query
                          WikiPage
                          REQUIRED_HEADERS MediaWiki_HEADERS
)

# Install files
install(TARGETS WPMediaWiki
        EXPORT WPMediaWikiTargets
        ${INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/mediawiki_export.h
            ${MediaWiki_HEADERS}
            ${WPMediaWiki_HEADERS}
        DESTINATION ${WPMEDIAWIKI_INCLUDE_INSTALL_DIR}/MediaWiki
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
