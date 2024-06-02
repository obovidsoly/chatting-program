#!/bin/bash

exclude_list="\
$(basename $0)\|\
build.sh
"

set -e

ls $(pwd) | grep -vx ${exclude_list} | xargs -I ARG rm -rf ARG

rm -rf "$(pwd)/../install"

echo "clean done!"

set +e
