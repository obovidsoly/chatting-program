#!/bin/bash

build_path=$(pwd)
tool_chain_path="${build_path}/tool-chain"

set -e

mkdir ${tool_chain_path} -p -m 755

cd ${tool_chain_path}

cmake ${build_path}/..
cmake --build ${tool_chain_path} -v
cmake --install ${tool_chain_path} -v

set +e

echo "#############################################################################################"
echo "####################################### Build Success #######################################"
echo "#############################################################################################"


