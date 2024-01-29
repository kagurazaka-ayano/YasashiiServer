cmake_minimum_required(VERSION 3.27)

project(YasashiiServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
set(INCLUDE include/YasashiiServer)
FetchContent_Declare(
        KawaiiMQ
        URL https://github.com/kagurazaka-ayano/KawaiiMq/releases/latest/download/KawaiiMQ-src.zip
)
FetchContent_MakeAvailable(KawaiiMQ)
list(APPEND INCLUDE ${KawaiiMQ_SOURCE_DIR}/include)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(fmt)
list(APPEND INCLUDE ${fmt_SOURCE_DIR}/include)
link_libraries(fmt::fmt)
FetchContent_Declare(
        httplib
        GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(httplib)
list(APPEND INCLUDE ${httplib_SOURCE_DIR})

include_directories(${INCLUDE})
file(GLOB SRC_SERVER src/server/*.cpp)
file(GLOB SRC_CLIENT src/client/*.cpp)
file(GLOB SRC_COMMON src/common/*.cpp)

add_executable(YasashiiServer_server ${SRC_SERVER} ${SRC_COMMON})
add_executable(YasashiiServer_client ${SRC_CLIENT} ${SRC_COMMON})
