#!/bin/sh
git submodule update --init --recursive
./tools/macos/premake5 gmake2
