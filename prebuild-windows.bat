@echo off
git submodule update --init --recursive
tools\windows\premake5.exe vs2019
