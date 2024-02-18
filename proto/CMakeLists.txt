# protobuf generation

include(FindProtobuf)

file(GLOB PROTO_BASE "${CMAKE_SOURCE_DIR}/proto/*.proto")
file(GLOB PROTO_TYPES "${CMAKE_SOURCE_DIR}/proto/Types/*.proto")

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_BASE} ${PROTO_TYPES})
