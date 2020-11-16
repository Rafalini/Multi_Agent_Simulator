#!/bin/sh
git clone httpsL//github.com/emscripten-core/emsdk.git
cd emsdk
git pull
./emsdk install sdk-1.39.8-64bit
./emsdk activate sdk-1.39.8-64bit
source ./emsdk_env.sh
