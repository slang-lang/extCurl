# directories
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)   # binary root
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)      # library root

SET(CMAKE_CXX_FLAGS "-pedantic -fPIC -Wall -Werror -Wextra -Wunused -Wno-long-long -Wnon-virtual-dtor -Wno-undef -std=c++14 -Wno-type-limits")

if( "${BUILD}" STREQUAL "" OR "${BUILD}" MATCHES "Debug")

    # by default we build debug!
    # MESSAGE("Setting default build to: Debug")
    SET(CMAKE_BUILD_TYPE "Debug")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable -Wno-unused-value")

    # do more logging
    add_definitions(-DDEBUG)

    # suppress "veraltete Konvertierung von Zeichenkettenkonstante in »char*« [-Werror=write-strings]"
    add_definitions(-Wno-write-strings -Wno-unused-variable)

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -g")

elseif( "${BUILD}" MATCHES "Release")

    # MESSAGE("Setting default build to: Release")
    SET(CMAKE_BUILD_TYPE "Release")

    # suppress "veraltete Konvertierung von Zeichenkettenkonstante in »char*« [-Werror=write-strings]"
    add_definitions(-Wno-write-strings -Wno-unused-variable -Wno-unused-result -Wno-unused-value)

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing -O4")

else()

    MESSAGE(FATAL_ERROR "Specify a valid build type: cmake -DBUILD=Release|Debug")

endif()


# specify default includes for the project
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(CMAKE_SKIP_RPATH TRUE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
SET(CMAKE_INSTALL_RPATH "")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

# additional definitions
#add_definitions(-DLOG_LEVEL=3)

# common used functionality and functions
INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Common.cmake)

# now run the build that takes care of other arguments
INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Builder.cmake)

# include custom dependencies
INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Dependencies.cmake)
