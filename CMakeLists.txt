cmake_minimum_required(VERSION 3.16)
project(emberline)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# raylib is always built from source, on every platform. One code path means
# Windows, WSL and Linux all get the exact same pinned version, and a fresh
# clone needs nothing but CMake and a compiler - no submodule init, no distro
# package. The first configure downloads it; later ones reuse build/_deps.
include(FetchContent)

# On Linux/WSL, build GLFW with Wayland support - but only when the toolchain
# to do so is actually present. Wayland needs wayland-scanner plus the client
# and protocol dev packages, and GLFW hard-errors at configure time if we ask
# for Wayland without them (a bare WSL install has none of it). Detecting
# instead of forcing means the same configure command works on a full Linux
# desktop and on a stock WSL box. X11 is built either way, so falling back
# costs nothing under XWayland/WSLg.
if (UNIX AND NOT APPLE)
    find_program(WAYLAND_SCANNER_EXE wayland-scanner)
    find_package(PkgConfig QUIET)
    if (PkgConfig_FOUND)
        pkg_check_modules(WAYLAND_CLIENT QUIET wayland-client)
    endif()

    # GLFW needs at least one windowing backend's headers. A stock WSL install
    # has neither, and GLFW's own failure surfaces several layers deep inside
    # FetchContent, so check up front and say what to install.
    find_package(X11 QUIET)
    if (NOT X11_FOUND AND NOT WAYLAND_CLIENT_FOUND)
        message(FATAL_ERROR
            "No windowing backend found - raylib needs X11 or Wayland dev "
            "packages to build.\n"
            "Fedora:\n"
            "  sudo dnf install gcc-c++ libX11-devel libXrandr-devel "
            "libXi-devel libXcursor-devel libXinerama-devel mesa-libGL-devel "
            "alsa-lib-devel wayland-devel libxkbcommon-devel "
            "wayland-protocols-devel\n"
            "Debian/Ubuntu:\n"
            "  sudo apt install build-essential libx11-dev libxrandr-dev "
            "libxi-dev libxcursor-dev libxinerama-dev libgl1-mesa-dev "
            "libasound2-dev libwayland-dev libxkbcommon-dev wayland-protocols")
    endif()

    if (WAYLAND_SCANNER_EXE AND WAYLAND_CLIENT_FOUND)
        message(STATUS "Wayland dev packages found, building raylib with Wayland support")
        set(GLFW_BUILD_WAYLAND ON CACHE BOOL "" FORCE)
    else()
        message(STATUS "Wayland dev packages not found, building X11-only "
                       "(install wayland-protocols, libwayland-dev and "
                       "libxkbcommon-dev for native Wayland)")
        set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
    endif()
endif()

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.0
)
FetchContent_MakeAvailable(raylib)

# Using `main` instead of ${PROJECT_NAME} for now, since it's quicker to
# type and read while the project's still this small. Change it later.
add_executable(main src/main.cpp)
target_link_libraries(main raylib)
