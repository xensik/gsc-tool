#!/usr/bin/env bash
set -euo pipefail

# Build macOS arm64 (debug)
CONFIG=debug_arm64
CORES=${MAKE_JOBS:-$(sysctl -n hw.ncpu 2>/dev/null || echo 1)}

echo "Assumes build files generated; run scripts/generate.sh if needed"

echo "Building config=${CONFIG} (jobs=${CORES})..."
make -C build config=${CONFIG} -j${CORES}

echo "Done."
