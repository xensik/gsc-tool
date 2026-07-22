#!/usr/bin/env bash
set -euo pipefail

# Initialize and update submodules, then run premake to generate build files.
REPO_ROOT=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
cd "$REPO_ROOT"

echo "Updating git submodules..."
git submodule update --init --recursive

if ! command -v premake5 >/dev/null 2>&1; then
  echo "premake5 not found on PATH. Please install premake5 and retry."
  exit 2
fi

echo "Running premake5 gmake2 to generate build files..."
premake5 gmake2

echo "Generation complete. You can now run scripts/build_*.sh to build."
