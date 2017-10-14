project(wpwiki)

message(STATUS "----------------------------------------------------------------------------------")
message(STATUS "Starting CMake configuration for: ${PROJECT_NAME}")

set(CMAKE_MIN_VERSION   "2.8.12")
set(ECM_MIN_VERSION     "1.5.0")
set(KF5_VERSION         "5.5.0")
set(REQUIRED_QT_VERSION "5.2.0")

# Used to set library's SONAME, change first digit on API/ABI break
set(LIBMEDIAWIKI_LIBVERSION         "1.0.0")
set(WPMEDIAWIKI_INCLUDE_INSTALL_DIR ${CMAKECONFIG_INSTALL_DIR})

cmake_minimum_required(VERSION ${CMAKE_MIN_VERSION})

############## ECM setup #################################################################################################################

find_package(ECM ${ECM_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(ECMGenerateHeaders)
include(ECMGeneratePriFile)
include(ECMSetupVersion)
include(ECMMarkNonGuiExecutable)
include(ECMOptionalAddSubdirectory)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings)
include(ECMPackageConfigHelpers)
include(GenerateExportHeader)
include(FeatureSummary)


ecm_setup_version(${LIBMEDIAWIKI_LIBVERSION}
    VARIABLE_PREFIX MEDIAWIKI
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/wpwiki_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/WPMediaWikiConfigVersion.cmake"
)

# Required Qt5 components to build this framework
find_package(Qt5 ${REQUIRED_QT_VERSION} NO_MODULE REQUIRED Core Network)
find_package(KF5CoreAddons ${KF5_VERSION} REQUIRED)

# Subdirectories
add_subdirectory(src)

# Create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/WPMediaWiki")

ecm_configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/WPMediaWikiConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/WPMediaWikiConfig.cmake"
    INSTALL_DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
)

install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/WPMediaWikiConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/WPMediaWikiConfigVersion.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel)

install(EXPORT WPMediaWikiTargets
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        FILE WPMediaWikiTargets.cmake
        NAMESPACE WP::)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/wpwiki_version.h"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel)


feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)











