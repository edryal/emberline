cmake_minimum_required(VERSION 3.16)
project(emberline)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (WIN32)
    message(STATUS "Building on Windows, using local libs/raylib")
    add_subdirectory(libs/raylib)
else()
    # Depending on how your system raylib was packaged, it might or might not
    # have Wayland support baked in. Building from source guarantees Wayland
    # (and X11 still works either way). If you don't know or don't care, leave
    # this off - X11/XWayland also works.
    option(USE_SYSTEM_RAYLIB "Use system raylib instead of building from source"
           OFF)
    if (USE_SYSTEM_RAYLIB)
        message(STATUS "USE_SYSTEM_RAYLIB=ON, looking for system raylib install")
        find_package(raylib REQUIRED)
        message(STATUS "Using system raylib ${raylib_VERSION}")
    else()
        message(STATUS "Building raylib from source with Wayland support")
        # Flags to build raylib with Wayland support
        set(GLFW_BUILD_WAYLAND ON CACHE BOOL "" FORCE)
        include(FetchContent)
        FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 6.0
        )
        FetchContent_MakeAvailable(raylib)
    endif()
endif()

# Using `main` instead of ${PROJECT_NAME} for now, since it's quicker to
# type and read while the project's still this small. Change it later.
add_executable(main src/main.cpp)
target_link_libraries(main raylib)
