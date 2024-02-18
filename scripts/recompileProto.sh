#!/usr/bin/env bash

proto_path="./proto"
proto_out="./proto/out"

# Remove old files
rm -rf "${proto_out:?}/"*

# Compile proto files
proto_files=$(find $proto_path -print | grep -e "\.proto$")
protoc -I=$proto_path --cpp_out=$proto_out $proto_files
echo "proto files compiled"
