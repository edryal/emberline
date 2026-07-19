## First time opening the project
Configure everything by running:
```bash
cmake -B build
```
This generates `compile_commands.json` (for clangd) and the `build/` directory.

Compile and link the application:
```bash
cmake --build build
```

Run the application:
```bash
./build/main
```

> [!TIP]
> One-liner if you like to write stuff manually:
> ```bash
> cmake --build build && ./build/main
> ```

Or just use the run script to configure (if needed), build, and then run:
```bash
./run-linux.sh
```

## Build

By default, `CMakeLists.txt` builds raylib from source (via `FetchContent`) with Wayland support enabled. X11 support is also built in alongside it, so nothing extra is needed on X11-only setups either.

If you'd rather link against a system-installed raylib instead of building from source, configure with:
```bash
cmake -B build -DUSE_SYSTEM_RAYLIB=ON
```
Note: Wayland support then depends entirely on how your system's raylib package was built - not guaranteed.

If you switch `USE_SYSTEM_RAYLIB` after already having a `build/` folder, wipe it first so the change actually takes effect:
```bash
rm -rf build
```
