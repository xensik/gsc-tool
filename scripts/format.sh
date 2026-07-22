#!/usr/bin/env bash
set -euo pipefail

PROGNAME="$(basename "$0")"

usage() {
  cat <<EOF
Usage: $PROGNAME [--apply|-a] [--check|-c] [-h|--help]

By default runs a dry-run check using clang-format's `--dry-run --Werror`.
Use `--apply` to rewrite files in-place (`-i`).

This script targets:
 - all `src/**/*.cpp` files excluding any path containing `/engine/`
 - all `include/**/*.hpp` files

Requires: `clang-format` available on PATH and a `.clang-format` in repo root (or style configured).
EOF
}

MODE="check"
while [[ $# -gt 0 ]]; do
  case "$1" in
    -a|--apply) MODE="apply"; shift ;;
    -c|--check) MODE="check"; shift ;;
    -h|--help) usage; exit 0 ;;
    *) echo "Unknown option: $1"; usage; exit 2 ;;
  esac
done

if ! command -v clang-format >/dev/null 2>&1; then
  echo "clang-format not found in PATH. Install it (e.g. 'brew install clang-format')."
  exit 2
fi

# Collect files: src/**/*.cpp excluding any path with /engine/, and include/**/*.hpp
files=()
while IFS= read -r -d '' f; do files+=("$f"); done < <(find src -type f -name '*.cpp' ! -path '*/engine/*' -print0 2>/dev/null || true)
while IFS= read -r -d '' f; do files+=("$f"); done < <(find include -type f -name '*.hpp' -print0 2>/dev/null || true)

if [[ ${#files[@]} -eq 0 ]]; then
  echo "No files found to format"
  exit 0
fi

echo "Processing ${#files[@]} files (mode=${MODE})..."

if [[ "$MODE" == "apply" ]]; then
  # Apply formatting in-place
  printf '%s\0' "${files[@]}" | xargs -0 -n 1000 clang-format -style=file -i
  echo "Formatting applied to ${#files[@]} files."
else
  # Check formatting (dry-run) and exit non-zero if any file needs formatting
  printf '%s\0' "${files[@]}" | xargs -0 -n 1000 clang-format -style=file --dry-run --Werror
  echo "Format check passed."
fi

exit 0
