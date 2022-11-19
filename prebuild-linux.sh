#!/bin/bash
git submodule update --init --recursive
./tools/linux/premake5 gmake2
