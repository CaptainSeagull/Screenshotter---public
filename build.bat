@echo off

set BUILD_RELEASE=true
set SHOW_FPS_FLAG=true
set USE_OPENGL_WINDOW_FLAG=false

cd %~dp0

rem Require Visual Studio's cl
where cl >nul 2>nul
IF %ERRORLEVEL% NEQ 0 (
    echo "Error: cl is not in the path. Please setup Visual Studio to do cl builds by calling vcvarsall.bat"
    goto skipEverything
)

set WARNINGS=-wd4189 -wd4706 -wd4996 -wd4100 -wd4127 -wd4267 -wd4505 -wd4820 -wd4365 -wd4514 -wd4062 -wd4061 -wd4668 -wd4389 -wd4018 -wd4711 -wd4987 -wd4710 -wd4625 -wd4626 -wd4350 -wd4826 -wd4640 -wd4571 -wd4986 -wd4388 -wd4129 -wd4201 -wd4577 -wd4191 -wd4464 -wd5045 -wd5220 -wd5219 -wd4244

if "%ALLOW_TESTS_FLAG%"=="true" (
    set ALLOW_TESTS=-DALLOW_TESTS=1
) else (
    set ALLOW_TESTS=-DALLOW_TESTS=0
)

if "%USE_OPENGL_WINDOW_FLAG%"=="true" (
    set USE_OPENGL_WINDOW=-DUSE_OPENGL_WINDOW=1
) else (
    set USE_OPENGL_WINDOW=-DUSE_OPENGL_WINDOW=0
)

if "%SHOW_FPS_FLAG%"=="true" (
    set SHOW_FPS=-DSHOW_FPS=1
) else (
    set SHOW_FPS=-DSHOW_FPS=0
)

set COMMON_COMPILER_FLAGS=-nologo -Gm- -GR- %WARNINGS% -FC -Zi -Oi -GS- -Gs9999999 -Wall %USE_OPENGL_WINDOW% %SHOW_FPS%
set DEBUG_COMPILER_FLAGS=%COMMON_COMPILER_FLAGS% -DINTERNAL=1 -DALLOW_ASSERTS=1 -MTd -EHa- -Od
set RELEASE_COMPILER_FLAGS=%COMMON_COMPILER_FLAGS% -DINTERNAL=0 -DALLOW_ASSERTS=0 -MT -fp:fast -EHa- -O2

pushd "tools"
del "../src/main_generated*"
del "../src/platform_win32_generated*"
mirror.exe ../src/main.cpp ../src/platform_win32.cpp
popd

IF NOT EXIST "build" mkdir "build"
pushd "build"

set BUILD_SCREENSHOTTER=-FeScreenshotter "../../src/main.cpp" -FmScreenshotter.map -link kernel32.lib -stack:0x100000,0x100000 -EXPORT:init_platform_settings -EXPORT:handle_input_and_render -PDB:%random%_screenshotter.pdb -stack:0x100000,0x100000 -subsystem:windows,5.2
set BUILD_WIN32=-FeWin32 "../../src/platform_win32.cpp" -FmWin32.map -link -nodefaultlib kernel32.lib -stack:0x100000,0x100000 -subsystem:windows,5.2

echo ----
echo Building debug

IF NOT EXIST "debug" mkdir "debug"
pushd "debug"

del *_screenshotter.pdb > NUL > NUL

cl -LD %DEBUG_COMPILER_FLAGS% %BUILD_SCREENSHOTTER%
cl %DEBUG_COMPILER_FLAGS% %BUILD_WIN32%

popd rem debug

if "%BUILD_RELEASE%"=="true" (
    echo ----
    echo Building release

    IF NOT EXIST "release" mkdir "release"
    pushd "release"

    del *_screenshotter.pdb > NUL > NUL

    cl -LD %RELEASE_COMPILER_FLAGS% %BUILD_SCREENSHOTTER%
    cl %RELEASE_COMPILER_FLAGS% %BUILD_WIN32%

    popd rem release
)

popd rem build

:skipEverything