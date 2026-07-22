#!/usr/bin/env bash
set -euo pipefail

PROGNAME="$(basename "$0")"

usage() {
  cat <<EOF
Usage: $PROGNAME [--fix|-f] [-h|--help]

Runs clang-tidy over all \`src/**/*.cpp\` and \`test/**/*.cpp\` files, excluding any path
containing \`/engine/\` (generated tables), using the checks in \`.clang-tidy\`.

Warnings are reported for headers under \`include/\`, \`src/\` and \`test/\` only;
\`deps/\` and \`engine/\` are never diagnosed.

Use \`--fix\` to apply the suggested fixes in-place.

Requires:
 - \`clang-tidy\` on PATH
 - \`compile_commands.json\` in repo root. Generate it with:
     bear --output compile_commands.json -- make -C build -j8
EOF
}

FIX=()
while [[ $# -gt 0 ]]; do
  case "$1" in
    -f|--fix) FIX=(--fix --fix-errors); shift ;;
    -h|--help) usage; exit 0 ;;
    *) echo "Unknown option: $1"; usage; exit 2 ;;
  esac
done

if ! command -v clang-tidy >/dev/null 2>&1; then
  echo "clang-tidy not found in PATH. Install it (e.g. 'brew install llvm')."
  exit 2
fi

if [[ ! -f compile_commands.json ]]; then
  echo "compile_commands.json not found. Generate it with:"
  echo "  bear --output compile_commands.json -- make -C build -j8"
  exit 2
fi

EXTRA=()
# homebrew clang-tidy pairs its own libc++ with the macOS SDK C headers
# and fails to parse without an explicit sysroot.
if [[ "$(uname)" == "Darwin" ]]; then
  EXTRA=(--extra-arg=-isysroot"$(xcrun --show-sdk-path)")
fi

files=()
while IFS= read -r -d '' f; do files+=("$f"); done < <(find src test -type f -name '*.cpp' ! -path '*/engine/*' -print0 2>/dev/null || true)

if [[ ${#files[@]} -eq 0 ]]; then
  echo "No files found to check"
  exit 0
fi

echo "Checking ${#files[@]} files..."
clang-tidy -p . -quiet "${EXTRA[@]}" "${FIX[@]+"${FIX[@]}"}" "${files[@]}"
