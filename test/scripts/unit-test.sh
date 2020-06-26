#!/usr/bin/env bash

# Configure, build and run all unit tests

set -euo pipefail

NUM_CPUS=${NUM_CPUS:-$(nproc)}
PROJECT_DIR=$(
  cd "$(dirname "$0")"/../..
  pwd
)

"${PROJECT_DIR}/test/scripts/bits/config.sh" \
  -DCMAKE_PROJECT_cdsp_INCLUDE:FILEPATH="$(pwd)"/conan_paths.cmake \
  "$@"

"${PROJECT_DIR}/test/scripts/bits/build.sh" test-all

ctest \
  --output-on-failure \
  --parallel "${NUM_CPUS}" \
  --tests-regex ^test-unit-
