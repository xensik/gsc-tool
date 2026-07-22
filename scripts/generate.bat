@echo off
setlocal
pushd %~dp0\.. || (echo Failed to change directory & exit /b 1)

echo Updating git submodules...
git submodule update --init --recursive

where premake5 >nul 2>&1
if errorlevel 1 (
  echo premake5 not found on PATH. Please install premake5 and retry.
  exit /b 2
)

echo Generating Visual Studio solution via premake5...
premake5 vs2022

popd
echo Generation complete.
