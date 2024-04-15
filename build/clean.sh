#!/bin/bash

ls $(pwd) | grep -v "build.sh\\|clean.sh" | xargs --verbose rm -rf;
rm -rf $(pwd)/../install
