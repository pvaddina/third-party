cmake_minimum_required(VERSION 3.5.1)
project(g3log-wrapper)

set(CMAKE_PREFIX_PATH "../install/g3log/static/${CMAKE_BUILD_TYPE}")
set(CMAKE_INSTALL_PREFIX "../../install/g3log-wrapper/static/${CMAKE_BUILD_TYPE}")

find_package(g3log CONFIG REQUIRED)
message(
"g3log package:
    found: ${G3LOG_FOUND}
    include dir: ${G3LOG_INCLUDE_DIRS}
    libraries: ${G3LOG_LIBRARIES}"
)

set (SRCS inc/g3log-wrapper.h src/g3log-wrapper.cpp)

add_library(g3log-wrapper STATIC ${SRCS})

target_include_directories(g3log-wrapper
PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
PUBLIC
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(g3log-wrapper
PRIVATE
  ${G3LOG_LIBRARIES}
)

#############################################################################################
# Installing the library and the include headers
#############################################################################################

# Install target files of the project and define an export configuration called 'g3log-wrapperExport'.
# Note that the export file itself is not generated and installed in this command
install(TARGETS g3log-wrapper
        EXPORT g3log-wrapperExport
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

# Specify install rules to install the include files
install(DIRECTORY inc/
        DESTINATION include 
        FILES_MATCHING 
        PATTERN "*.h")


# Install the export configuration as 'g3log-wrapper.cmake' with the given namespae and at the given destination
install(EXPORT g3log-wrapperExport
        FILE g3log-wrapper.cmake 
        DESTINATION cmake)

#############################################################################################
# Steps to generate the g3log-wrapperConfig.cmake which is required for find_package to discover the lib
#############################################################################################
include(CMakePackageConfigHelpers)

# generate the config file that includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/g3log-wrapperConfig.cmake"
                              INSTALL_DESTINATION "cmake"
                              NO_SET_AND_CHECK_MACRO
                              NO_CHECK_REQUIRED_COMPONENTS_MACRO
                             )

# generate the version file for the config file
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/g3log-wrapperConfigVersion.cmake
                                  VERSION 1.1.10
                                  COMPATIBILITY SameMajorVersion
                                  )
# Install the generated configuration files
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/g3log-wrapperConfigVersion.cmake ${CMAKE_CURRENT_BINARY_DIR}/g3log-wrapperConfig.cmake 
        DESTINATION cmake
        )

# At this point, we have generated a relocatable CMake Configuration for our project that 
# can be used after the project has been installed or packaged. If we want our project to 
# also be used from a build directory we only have to add the following to the bottom of the 
#top level CMakeLists.txt
export(EXPORT g3log-wrapperExport
  FILE "${CMAKE_CURRENT_BINARY_DIR}/g3log-wrapper.cmake"
)


