#!/usr/bin/env bash

# stops the script if any command fails
set -e

# Separate from the Windows build dir on purpose. A CMakeCache.txt records the
# compiler that generated it, so an MSVC cache and a gcc cache can't share a
# directory - and on WSL this repo is often the same checkout Windows builds
# from. Splitting them lets both toolchains coexist without wiping each other.
BUILD_DIR="build-linux"

# -d : does this file exist and is it a directory
# ! : negation, so we check if the directory doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    echo "No build directory found, configuring..."
    cmake -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Debug
fi

cmake --build "$BUILD_DIR" --parallel

# Under WSL, Mesa doesn't autodetect the GPU and silently falls back to
# llvmpipe - software rendering on the CPU, which is unusable for a 3D game.
# /dev/dxg is the WSL GPU passthrough device, so its presence means we're on
# WSL with a GPU available and should use Mesa's d3d12 backend to reach it.
# Both vars are only set if you haven't set them yourself, and neither is
# touched on a real Linux box, where autodetection works fine.
if [ -e /dev/dxg ]; then
    export GALLIUM_DRIVER="${GALLIUM_DRIVER:-d3d12}"
    # Pick the discrete GPU. Without this, d3d12 grabs whichever adapter
    # Windows lists first, which tends to be the integrated one.
    export MESA_D3D12_DEFAULT_ADAPTER_NAME="${MESA_D3D12_DEFAULT_ADAPTER_NAME:-NVIDIA}"
fi

echo "Launching..."
"$BUILD_DIR/main"
