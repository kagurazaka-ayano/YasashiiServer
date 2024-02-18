cmake_minimum_required(VERSION 3.27)

project(YasashiiServer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
include(FetchContent)
include(FindProtobuf)


file(GLOB SRC_SERVER src/server/*.cpp)
file(GLOB SRC_CLIENT src/client/*.cpp)
file(GLOB SRC_COMMON src/common/*.cpp)
set(INCLUDE_COMMON include/YasashiiServer/Common)
set(INCLUDE_SERVER include/YasashiiServer/Server)
set(INCLUDE_CLIENT include/YasashiiServer/Client)
set(protobuf_BUILD_TESTS OFF)
set(KawaiiMQ_BUILD_TESTS OFF)
set(ABSL_PROPAGATE_CXX_STD ON)
set(SKIP_PERFORMANCE_COMPARISON ON)


set(INCLUDE ${INCLUDE_COMMON})
list(APPEND INCLUDE ${Protobuf_INCLUDE_DIRS})
link_libraries(protobuf::libprotobuf)

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

add_subdirectory(proto "${CMAKE_SOURCE_DIR}/protoOutput")

include_directories(${INCLUDE})

add_executable(YasashiiServer_server ${SRC_SERVER} ${SRC_COMMON})
add_executable(YasashiiServer_client ${SRC_CLIENT} ${SRC_COMMON})

target_include_directories(YasashiiServer_server PRIVATE ${INCLUDE_SERVER})
target_include_directories(YasashiiServer_client PRIVATE ${INCLUDE_CLIENT})
