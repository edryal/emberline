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

`CMakeLists.txt` builds raylib from source via `FetchContent`, pinned to tag `6.0`, on every platform - Windows, WSL and Linux alike. There's nothing to install and no submodule to initialise: the first `cmake -B build` clones raylib into `build/_deps`, and later configures reuse it.

### Linux / WSL prerequisites

Because raylib is compiled here rather than installed as a package, you need the windowing and audio dev headers once per machine.

Fedora (including Fedora on WSL):
```bash
sudo dnf install gcc-c++ libX11-devel libXrandr-devel libXi-devel \
    libXcursor-devel libXinerama-devel mesa-libGL-devel alsa-lib-devel \
    wayland-devel libxkbcommon-devel wayland-protocols-devel
```

Debian/Ubuntu:
```bash
sudo apt install build-essential libx11-dev libxrandr-dev libxi-dev \
    libxcursor-dev libxinerama-dev libgl1-mesa-dev libasound2-dev \
    libwayland-dev libxkbcommon-dev wayland-protocols
```

Wayland support is enabled automatically when `wayland-scanner` and the Wayland dev packages are present, and skipped when they aren't - X11 is built either way, so it works under XWayland and WSLg regardless. If none of the backends are installed, the configure step stops with the install command above rather than failing deep inside GLFW.

### Running the GUI from WSL

On WSL2 with WSLg (Windows 11), the game window opens on the Windows desktop with no extra setup - no X server, no `DISPLAY` export. WSLg provides both `DISPLAY=:0` and `WAYLAND_DISPLAY=wayland-0`, so whichever backend raylib was built against will work. Just run `./run-linux.sh` from inside WSL.

**GPU acceleration.** Mesa doesn't autodetect the GPU under WSL and quietly falls back to `llvmpipe` - software rendering on the CPU, which is far too slow for a 3D game. `run-linux.sh` detects WSL (via `/dev/dxg`) and sets `GALLIUM_DRIVER=d3d12` to route through the real GPU, plus `MESA_D3D12_DEFAULT_ADAPTER_NAME=NVIDIA` to pick the discrete card over the integrated one. Both respect values you set yourself, and neither is set on a real Linux machine.

If you launch the binary directly instead of through the script, you'll get software rendering. Check which you're on by looking for the `Renderer:` line in raylib's startup log - `llvmpipe` means CPU, `D3D12 (...)` means GPU. On a non-NVIDIA machine, change or drop `MESA_D3D12_DEFAULT_ADAPTER_NAME`.

Windows needs no equivalent step; the Win32 backend ships with the toolchain.

Use `run-linux.sh` on Linux/WSL and `build.bat` on Windows; both configure (if needed), build, and run.
