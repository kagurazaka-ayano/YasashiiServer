cmake_minimum_required(VERSION 3.27)

project(YasashiiServer LANGUAGES CXX)
include(FetchContent)
set(CMAKE_CXX_STANDARD 23)

file(GLOB SRC_SERVER src/server/*.cpp)
file(GLOB SRC_CLIENT src/client/*.cpp)
set(INCLUDE_COMMON include/YasashiiServer/common)
set(INCLUDE_SERVER include/YasashiiServer/server)
set(INCLUDE_CLIENT include/YasashiiServer/client)
file(GLOB COMMON src/common/*.cpp)
list(APPEND SRC_COMMON ${COMMON})

include(FetchContent)
set(INCLUDE ${INCLUDE_COMMON})

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(fmt)
list(APPEND INCLUDE ${fmt_SOURCE_DIR}/include)
link_libraries(fmt::fmt)

FetchContent_Declare(
        KawaiiMQ
        GIT_REPOSITORY https://github.com/kagurazaka-ayano/KawaiiMq.git
        GIT_TAG        main
)
FetchContent_MakeAvailable(KawaiiMQ)
list(APPEND INCLUDE ${KawaiiMQ_SOURCE_DIR}/include)
link_libraries(KawaiiMQ)

FetchContent_Declare(
        httplib
        GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(httplib)
list(APPEND INCLUDE ${httplib_SOURCE_DIR})

FetchContent_Declare(cereal
        GIT_REPOSITORY https://github.com/USCiLab/cereal.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(cereal)
list(APPEND INCLUDE ${cereal_SOURCE_DIR}/include)

include_directories(${INCLUDE})

add_executable(YasashiiServer_server ${SRC_SERVER} ${SRC_COMMON})
add_executable(YasashiiServer_client ${SRC_CLIENT} ${SRC_COMMON})

target_include_directories(YasashiiServer_server PRIVATE ${INCLUDE_SERVER})
target_include_directories(YasashiiServer_client PRIVATE ${INCLUDE_CLIENT})
