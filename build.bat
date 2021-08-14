@echo off

set RELEASE_FLAG=false
set INTERNAL_FLAG=true
set ALLOW_ASSERTS_FLAG=true
set SHOW_FPS_FLAG=true
set USE_OPENGL_WINDOW_FLAG=false
set RUN_SCREENSHOTTING_ON_THREAD_FLAG=false

cd %~dp0

rem Require Visual Studio's cl
where cl >nul 2>nul
IF %ERRORLEVEL% NEQ 0 (
    echo "Error: cl is not in the path. Please setup Visual Studio to do cl builds by calling vcvarsall.bat"
    goto skipEverything
)

set WARNINGS=-wd4189 -wd4706 -wd4996 -wd4100 -wd4127 -wd4267 -wd4505 -wd4820 -wd4365 -wd4514 -wd4062 -wd4061 -wd4668 -wd4389 -wd4018 -wd4711 -wd4987 -wd4710 -wd4625 -wd4626 -wd4350 -wd4826 -wd4640 -wd4571 -wd4986 -wd4388 -wd4129 -wd4201 -wd4577 -wd4244 -wd4623 -wd4204 -wd4101 -wd4255 -wd4191 -wd4477 -wd4242 -wd4464 -wd4917 -wd5045 -wd5220 -wd5219

if "%INTERNAL_FLAG%"=="true" (
    set INTERNAL=-DINTERNAL=1
) else (
    set INTERNAL=-DINTERNAL=0
)

if "%ALLOW_ASSERTS_FLAG%"=="true" (
    set ALLOW_ASSERTS=-DALLOW_ASSERTS=1
) else (
    set ALLOW_ASSERTS=-DALLOW_ASSERTS=0
)

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

if "%RUN_SCREENSHOTTING_ON_THREAD_FLAG%"=="true" (
    set RUN_SCREENSHOTTING_ON_THREAD=-DRUN_SCREENSHOTTING_ON_THREAD=1
) else (
    set RUN_SCREENSHOTTING_ON_THREAD=-DRUN_SCREENSHOTTING_ON_THREAD=0
)

set COMPILER_FLAGS=-nologo -Gm- -GR- %WARNINGS% -FC -Zi -Oi -GS- -Gs9999999 -Wall %INTERNAL% %ALLOW_ASSERTS% %ALLOW_TESTS% %USE_OPENGL_WINDOW% %RUN_SCREENSHOTTING_ON_THREAD% %SHOW_FPS%
if "%RELEASE_FLAG%"=="true" (
    set COMPILER_FLAGS=%COMPILER_FLAGS% -MT -fp:fast -EHa- -O2
) else (
    set COMPILER_FLAGS=%COMPILER_FLAGS% -MTd -EHa- -Od
)

IF NOT EXIST "build" mkdir "build"

pushd "tools"
del "../src/main_generated*"
del "../src/platform_win32_generated*"
mirror.exe ../src/main.cpp ../src/platform_win32.cpp
popd

echo Building Screenshotter
pushd "build"

del *_screenshotter.pdb > NUL > NUL

cl -LD -FeScreenshotter %COMPILER_FLAGS% "../src/main.cpp" -FmScreenshotter.map -link kernel32.lib -stack:0x100000,0x100000 -EXPORT:init_platform_settings -EXPORT:handle_input_and_render -PDB:%random%_screenshotter.pdb -stack:0x100000,0x100000 -subsystem:windows,5.2
cl -FeWin32 %COMPILER_FLAGS% "../src/platform_win32.cpp" -FmWin32.map -link -nodefaultlib kernel32.lib -stack:0x100000,0x100000 -subsystem:windows,5.2
popd

:skipEverything