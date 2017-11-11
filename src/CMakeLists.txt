
set(mediawiki_SRCS
    browsepage.cpp

    image.cpp
    imageinfo.cpp

    login.cpp
    logout.cpp

    queryimageinfo.cpp
    queryimages.cpp
    querysiteinfogeneral.cpp
    generalinfo.cpp
    querysiteinfousergroups.cpp
    queryrevision.cpp

    usergroup.cpp
    revision.cpp

    parse.cpp
    upload.cpp
    work.cpp
    WPMediaWiki.cpp
    query.cpp
    wikipage.cpp
    shield.cpp  )


add_library(WPMediaWiki ${mediawiki_SRCS})
generate_export_header(WPMediaWiki BASE_NAME WPWiki)

add_library(WP::MediaWiki ALIAS WPMediaWiki)

#target_include_directories(WPMediaWiki PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..;${CMAKE_CURRENT_BINARY_DIR}>")

#set(WPMediaWiki_INCLUDE_INSTALL_DIR ${CMAKECONFIG_INSTALL_DIR})

target_include_directories(WPMediaWiki INTERFACE "$<INSTALL_INTERFACE:${KF5_INCLUDE_INSTALL_DIR}/MediaWiki>")


target_link_libraries(WPMediaWiki
    PRIVATE
        Qt5::Core
        Qt5::Network
        KF5::CoreAddons
)

set_target_properties(WPMediaWiki
    PROPERTIES VERSION ${MEDIAWIKI_VERSION_STRING}
    SOVERSION ${MEDIAWIKI_VERSION}
    EXPORT_NAME "MediaWiki"
)
ecm_generate_headers( MediaWiki_CamelCase_HEADERS

                      HEADER_NAMES
                      BrowsePage
                      work
                      WPMediaWiki
                      query
                      wikipage
                      shield
                      image
                      imageinfo
                      login
                      logout

                      queryimageinfo
                      queryimages
                      querysiteinfogeneral
                      generalinfo
                      querysiteinfousergroups
                      queryrevision

                      usergroup
                      revision

                      parse
                      upload


                      REQUIRED_HEADERS MediaWiki_HEADERS)

# Install files
install(TARGETS WPMediaWiki
        EXPORT WPMediaWikiTargets
        ${INSTALL_TARGETS_DEFAULT_ARGS})


install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/mediawiki_export.h
            ${MediaWiki_HEADERS}
            ${MediaWiki_CamelCase_HEADERS}
            DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/MediaWiki
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
