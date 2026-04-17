@echo off
setlocal enabledelayedexpansion

::=============================================================================
:: OpenTemplate - Rebuild Script for Windows
::=============================================================================

set "PROJECT_NAME=OpenTemplate"
set "BUILD_DIR=build"
set "CMAKE_GENERATOR=Ninja"
set "CMAKE_ARCHITECTURE="

:: output colours
if defined COLOR (set "COLOR_ON=on") else (set "COLOR_ON=off")
if "%COLOR_ON%"=="on" (
    set "COLOR_RESET=[0m"
    set "COLOR_RED=[91m"
    set "COLOR_GREEN=[92m"
    set "COLOR_YELLOW=[93m"
    set "COLOR_BLUE=[94m"
    set "COLOR_CYAN=[96m"
) else (
    set "COLOR_RESET="
    set "COLOR_RED="
    set "COLOR_GREEN="
    set "COLOR_YELLOW="
    set "COLOR_BLUE="
    set "COLOR_CYAN="
)

::=============================================================================
:: message output function
::=============================================================================
call :print_header "OpenTemplate Build Script"
echo.

::=============================================================================
:: Check 1: CMake
::=============================================================================
call :print_step "Checking CMake..."
where cmake >nul 2>nul
if %errorlevel% neq 0 (
    call :print_error "CMake not found in PATH. Please install CMake and add it to PATH."
    pause
    exit /b 1
)

for /f "tokens=*" %%i in ('cmake --version ^| findstr /i "version"') do set "CMAKE_VERSION=%%i"
call :print_success "Found: %CMAKE_VERSION%"
echo.

::=============================================================================
:: Check 2: Ninja and GCC detection
::=============================================================================
call :print_step "Checking Ninja and GCC..."

:: Check Ninja
where ninja >nul 2>nul
if %errorlevel% neq 0 (
    call :print_error "Ninja not found in PATH. Please install Ninja and add it to PATH."
    call :print_info "Download from: https://github.com/ninja-build/ninja/releases"
    pause
    exit /b 1
)
call :print_success "Ninja found"

:: Check GCC (MinGW)
where g++ >nul 2>nul
if %errorlevel% neq 0 (
    call :print_error "GCC (MinGW) not found in PATH. Please install MinGW-w64 and add it to PATH."
    call :print_info "Download from: https://www.mingw-w64.org/"
    pause
    exit /b 1
)

for /f "tokens=*" %%i in ('g++ --version ^| findstr /i "g++"') do set "GCC_VERSION=%%i"
call :print_success "GCC found: !GCC_VERSION!"
echo.

::=============================================================================
:: Check 3: Check deps in external/
::=============================================================================
call :print_step "Checking external dependencies..."

set "MISSING_DEPS=0"

if not exist "%CD%\external\glfw\CMakeLists.txt" (
    call :print_error "GLFW not found in external/glfw/"
    set "MISSING_DEPS=1"
) else (
    call :print_success "GLFW found"
)

if not exist "%CD%\external\glad\CMakeLists.txt" (
    call :print_error "GLAD not found in external/glad/"
    set "MISSING_DEPS=1"
) else (
    call :print_success "GLAD found"
)

if not exist "%CD%\external\glm\CMakeLists.txt" (
    call :print_error "GLM not found in external/glm/"
    set "MISSING_DEPS=1"
) else (
    call :print_success "GLM found"
)

if "%MISSING_DEPS%"=="1" (
    call :print_error "Missing dependencies. Please ensure external libraries are in place."
    pause
    exit /b 1
)
echo.

::=============================================================================
:: Check 4: Internet connection (for FetchContent)
::=============================================================================
call :print_step "Checking internet connection for ImGui download..."

ping -n 1 github.com >nul 2>nul
if %errorlevel% equ 0 (
    call :print_success "Internet connection available"
) else (
    call :print_warning "No internet connection. ImGui download may fail."
)
echo.

::=============================================================================
:: Cleaning and rebuilding
::=============================================================================
call :print_step "Cleaning previous build..."

if exist "%BUILD_DIR%" (
    rmdir /s /q "%BUILD_DIR%" 2>nul
    if !errorlevel! equ 0 (
        call :print_success "Removed existing build directory"
    ) else (
        call :print_warning "Could not remove build directory (perhaps files are in use)"
        call :print_info "Trying to continue with existing directory..."
    )
) else (
    call :print_info "No existing build directory found"
)
echo.

::=============================================================================
:: Creating build directory
::=============================================================================
call :print_step "Creating build directory..."
mkdir "%BUILD_DIR%" 2>nul
if exist "%BUILD_DIR%" (
    call :print_success "Build directory created: %BUILD_DIR%"
) else (
    call :print_error "Failed to create build directory"
    pause
    exit /b 1
)
echo.

::=============================================================================
:: Configuring CMake with Ninja and GCC
::=============================================================================
cd "%BUILD_DIR%"

call :print_step "Configuring CMake (%CMAKE_GENERATOR%, GCC)..."

:: Defining build type (default - Release, can pass parameters)
set "BUILD_TYPE=%1"
if "%BUILD_TYPE%"=="" set "BUILD_TYPE=Release"

:: CMake command for Ninja (no -A flag needed)
set "CMAKE_CMD=cmake .. -G "%CMAKE_GENERATOR%" -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DBUILD_TESTS=OFF"

:: Force CMake to use GCC (MinGW) instead of MSVC
set "CMAKE_CMD=!CMAKE_CMD! -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++"

echo !CMAKE_CMD!
echo.

!CMAKE_CMD!

if %errorlevel% neq 0 (
    call :print_error "CMake configuration failed!"
    cd ..
    pause
    exit /b 1
)

call :print_success "CMake configuration completed"
echo.

::=============================================================================
:: project building with Ninja
::=============================================================================
call :print_step "Building project (%BUILD_TYPE%) with Ninja..."

:: Ninja build command
set "BUILD_CMD=ninja"

echo Running: %BUILD_CMD%
echo.

%BUILD_CMD%

if %errorlevel% neq 0 (
    call :print_error "Build failed!"
    cd ..
    pause
    exit /b 1
)

call :print_success "Build completed successfully"
cd ..
echo.

::=============================================================================
:: check exec availability
::=============================================================================
call :print_step "Verifying build output..."

set "EXE_PATH=%BUILD_DIR%\bin\%PROJECT_NAME%.exe"

if exist "!EXE_PATH!" (
    call :print_success "Executable found: !EXE_PATH!"
) else (
    call :print_warning "Executable not found at expected location"
    call :print_info "Searching for executable..."
    for /r "%BUILD_DIR%" %%f in (%PROJECT_NAME%.exe) do (
        call :print_success "Found at: %%f"
        set "EXE_PATH=%%f"
    )
)
echo.

::=============================================================================
:: check resources
::=============================================================================
call :print_step "Checking resources..."

if exist "%CD%\resources" (
    call :print_success "Resources directory found"

    dir /b "%CD%\resources" 2>nul | findstr . >nul
    if !errorlevel! equ 0 (
        call :print_success "Resources directory is not empty"
    ) else (
        call :print_warning "Resources directory is empty"
    )
) else (
    call :print_warning "No resources directory found in project root"
)
echo.

::=============================================================================
:: CLion integration hint
::=============================================================================
call :print_step "CLion integration"

call :print_info "To use this script with CLion:"
call :print_info "  File -> Settings -> Tools -> External Tools -> Add"
call :print_info "  Name: Rebuild with Ninja"
call :print_info "  Program: cmd.exe"
call :print_info "  Arguments: /c rebuild.bat"
call :print_info "  Working directory: $ProjectFileDir$"
echo.

::=============================================================================
:: final output
::=============================================================================
call :print_header "BUILD SUMMARY"
echo   %COLOR_CYAN%Project:%COLOR_RESET%   %PROJECT_NAME%
echo   %COLOR_CYAN%Build type:%COLOR_RESET% %BUILD_TYPE%
echo   %COLOR_CYAN%Generator:%COLOR_RESET%  Ninja + GCC
echo   %COLOR_CYAN%Compiler:%COLOR_RESET%   !GCC_VERSION!
echo   %COLOR_CYAN%Output:%COLOR_RESET%     %EXE_PATH%
echo.
call :print_success "Rebuild completed successfully!"
echo.

::=============================================================================
:: ask for execution
::=============================================================================
set "RUN_PROGRAM="
set /p "RUN_PROGRAM=Run the program now? (Y/N): "
if /i "%RUN_PROGRAM%"=="Y" (
    echo.
    call :print_step "Starting %PROJECT_NAME%..."
    echo.
    "%EXE_PATH%"
)

pause
exit /b 0

::=============================================================================
:: funcs for colored outputs
::=============================================================================

:print_step
echo %COLOR_BLUE%[STEP] %~1%COLOR_RESET%
exit /b

:print_success
echo %COLOR_GREEN%[OK]   %~1%COLOR_RESET%
exit /b

:print_error
echo %COLOR_RED%[ERROR] %~1%COLOR_RESET%
exit /b

:print_warning
echo %COLOR_YELLOW%[WARN]  %~1%COLOR_RESET%
exit /b

:print_info
echo %COLOR_CYAN%[INFO]  %~1%COLOR_RESET%
exit /b

:print_header
echo.
echo %COLOR_CYAN%========================================%COLOR_RESET%
echo %COLOR_CYAN%  %~1%COLOR_RESET%
echo %COLOR_CYAN%========================================%COLOR_RESET%
echo.
exit /b