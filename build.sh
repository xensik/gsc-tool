#!/bin/bash

arch=${1:-x64}
config=${2:-debug}

if [[ "$(uname)" == "Linux" ]]; then
  cores="-j$(nproc)"
elif [[ "$(uname)" == "Darwin" ]]; then
  cores="-j$(sysctl -n hw.logicalcpu)"
fi

premake5 gmake2
pushd build
make config=${config}_${arch} $cores
popd
