@echo off
REM Windows dev loop: configure -> build -> run.
REM Mirrors run-linux.sh but for the Windows/MSVC toolchain.
REM (clangd completion in WSL is handled separately by compile_flags.txt.)

setlocal
cd /d "%~dp0"

set BUILD_DIR=build

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
