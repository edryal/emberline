# First time opening the project

Configure everything by running:
```bash
cmake -B build
```
This will generate the `compile_commands.json` and the `build/` directory.

Compile and link the application:
```bash
cmake --build build
```

Run the application:
```bash
./build/main
```
> [!TIP]
> One-liner:
> ```bash
> cmake --build build && ./build/main
> ```

Or use the run script to configure, build and run:
```bash
.run-linux.sh
```

# Build

By default `CMakeLists.txt` will build raylib from source with wayland flags. <br>
Raylib is built with X11 support by default so you don't have to change anything. <br>
Unless you want to use your own system raylib package, then set `USE_SYSTEM_RAYLIB` to `ON` in `CMakeLists.txt`.
