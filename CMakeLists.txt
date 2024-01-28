cmake_minimum_required(VERSION 3.27)

project(YasashiiServer LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
        KawaiiMQ
        URL https://github.com/kagurazaka-ayano/KawaiiMq/releases/download/v1.0.0/KawaiiMQ-src.zip
)
FetchContent_MakeAvailable(KawaiiMQ)

include_directories(include/YasashiiServer)
file(GLOB SRC_SERVER src/server/*.cpp)
file(GLOB SRC_CLIENT src/client/*.cpp)

add_executable(YasashiiServer_server ${SRC_SERVER})
add_executable(YasashiiServer_client ${SRC_CLIENT})
