INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
    Extension.cpp
    Types.cpp
)

SET(HEADERS
    CurlCleanup.h
    CurlInit.h
    CurlPerform.h
    CurlReadResult.h
    CurlReset.h
    CurlSetBearer.h
    CurlSetData.h
    CurlSetHeader.h
    CurlSetOptInt.h
    CurlSetOptStr.h
    CurlSetPassword.h
    CurlSetProgress.h
    CurlSetUrl.h
    CurlSetUsername.h
    CurlSetVerbose.h
    Extension.h
    Types.h
)

SET(DEPENDENCIES
    curl
)

SET(MODULES
    curl
    slang
)

add_include(Externals)

build_shared_lib(SlangCurl "${MODULES}")

