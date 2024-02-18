cmake_minimum_required(VERSION 3.27)

project(YasashiiServer LANGUAGES CXX)
include(FetchContent)
include(FindProtobuf)
set(CMAKE_CXX_STANDARD 23)


file(GLOB SRC_SERVER src/server/*.cpp)
file(GLOB SRC_CLIENT src/client/*.cpp)
file(GLOB SRC_COMMON src/common/*.cpp)
file(GLOB PROTO_SRCS ${CMAKE_SOURCE_DIR}/proto/out/*.cc)
file(GLOB TYPE_SRCS ${CMAKE_SOURCE_DIR}/proto/out/Types/*.cc)
set(INCLUDE_COMMON include/YasashiiServer/Common)
set(INCLUDE_SERVER include/YasashiiServer/Server)
set(INCLUDE_CLIENT include/YasashiiServer/Client)
set(INCLUDE_PROTO ${CMAKE_SOURCE_DIR}/proto/out)
set(protobuf_BUILD_TESTS OFF)
set(KawaiiMQ_BUILD_TESTS OFF)
set(ABSL_PROPAGATE_CXX_STD ON)
set(SKIP_PERFORMANCE_COMPARISON ON)

include(FetchContent)

list(APPEND INCLUDE_COMMON ${INCLUDE_PROTO})

list(APPEND INCLUDE ${Protobuf_INCLUDE_DIRS})
link_libraries(protobuf::libprotobuf)

execute_process(
        COMMAND "./scripts/recompileProto.sh"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

FetchContent_Declare(
        KawaiiMQ
        GIT_REPOSITORY https://github.com/kagurazaka-ayano/KawaiiMq.git
        GIT_TAG        main
)
FetchContent_MakeAvailable(KawaiiMQ)
list(APPEND INCLUDE_COMMON ${KawaiiMQ_SOURCE_DIR}/include)
link_libraries(KawaiiMQ)

FetchContent_Declare(
        httplib
        GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(httplib)
list(APPEND INCLUDE_COMMON ${httplib_SOURCE_DIR})

include_directories(${INCLUDE_COMMON})
list(APPEND SRC_COMMON ${PROTO_SRCS})

add_executable(YasashiiServer_server ${SRC_SERVER} ${SRC_COMMON})
add_executable(YasashiiServer_client ${SRC_CLIENT} ${SRC_COMMON})

target_include_directories(YasashiiServer_server PRIVATE ${INCLUDE_SERVER})
target_include_directories(YasashiiServer_client PRIVATE ${INCLUDE_CLIENT})
