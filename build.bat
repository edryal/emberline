@echo off
REM Windows dev loop: configure -> build -> run.
REM Mirrors run-linux.sh but for the Windows/MSVC toolchain.
REM (clangd completion in WSL is handled separately by compile_flags.txt.)

setlocal
cd /d "%~dp0"

REM Separate from the Linux build dir on purpose - see run-linux.sh. An MSVC
REM CMakeCache.txt and a gcc one can't share a directory, and WSL often builds
REM from this same checkout.
set BUILD_DIR=build-win

REM Only configure when the build dir doesn't exist yet; re-running is fast
REM anyway, but this keeps a plain build quick.
if not exist "%BUILD_DIR%" (
    echo No build directory found, configuring...
    cmake -B "%BUILD_DIR%"
    if errorlevel 1 (
        echo Configure failed.
        exit /b 1
    )
)

cmake --build "%BUILD_DIR%" --config Debug
if errorlevel 1 (
    echo Build failed.
    exit /b 1
)

echo Launching...
"%BUILD_DIR%\Debug\main.exe"
