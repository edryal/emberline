cmake_minimum_required(VERSION 3.16)
project(emberline)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# On linux depending on the package you have installed, raylib might or
# might not come with wayland support. So build it from source to be sure
# that it will use wayland and not xwayland. If you don't know or don't care,
# just leave this be, since raylib works with X11 by default.
option(USE_SYSTEM_RAYLIB "Use system raylib instead of building from source"
       OFF)

if (USE_SYSTEM_RAYLIB)
    message(STATUS "USE_SYSTEM_RAYLIB=ON, looking for system raylib install")
    find_package(raylib REQUIRED)
    message(STATUS "Using system raylib ${raylib_VERSION}")
else()
    message(STATUS "Building raylib from source with Wayland support")

    # Flags to build raylib with wayland support
    set(GLFW_BUILD_WAYLAND ON CACHE BOOL "" FORCE)
    set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE)

    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 6.0
    )
    FetchContent_MakeAvailable(raylib)
endif()

# Replace `main` with ${PROJECT_NAME} later on,
# but for now it's faster to type and understand `main`
add_executable(main src/main.cpp)
target_link_libraries(main raylib)
