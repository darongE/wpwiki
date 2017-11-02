

set(wpwiki_SRCS
    browsepage.cpp
    work.cpp
    WPMediaWiki.cpp
    query.cpp
    wikipage.cpp
    shield.cpp
    )



add_library(WPMediaWiki ${wpwiki_SRCS})
generate_export_header(WPMediaWiki BASE_NAME WPWiki)

add_library(WP::WPWiki ALIAS WPMediaWiki)

target_include_directories(WPMediaWiki INTERFACE "$<INSTALL_INTERFACE:${WP_INCLUDE_INSTALL_DIR}/MediaWiki>")


target_link_libraries(WPMediaWiki
    PRIVATE
        Qt5::Core
        Qt5::Network
        KF5::CoreAddons
)

set_target_properties(WPMediaWiki
    PROPERTIES VERSION ${WPWIKI_VERSION_STRING}
    SOVERSION ${WPWIKI_SOVERSION}
    EXPORT_NAME "WPWiki"
)

ecm_generate_headers(
                          WPWiki_CamelCase_HEADERS
                          HEADER_NAMES
                          BrowsePage
                          work
                          WPMediaWiki
                          query
                          wikipage
                          shield
                          cookiehandler
                          REQUIRED_HEADERS WPWiki_HEADERS
)



#set(WPMEDIAWIKI_INCLUDE_INSTALL_DIR ${CMAKECONFIG_INSTALL_DIR})

# Install files
install(TARGETS WPMediaWiki
        EXPORT WPMediaWikiTargets
        ${INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/mediawiki_export.h
            ${WPWiki_HEADERS}
            ${WPWiki_CamelCase_HEADERS}
        DESTINATION ${CMAKECONFIG_INSTALL_DIR}/WPWiki
        COMPONENT Devel)

include(ECMGeneratePriFile)

ecm_generate_pri_file(
    BASE_NAME WPWiki
    LIB_NAME WPMediaWiki
    DEPS "core network"
    FILENAME_VAR PRI_FILENAME
)

install(FILES ${PRI_FILENAME}
        DESTINATION ${ECM_MKSPECS_INSTALL_DIR})
