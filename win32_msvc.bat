@echo off

set RELEASE_FLAG=false
set INTERNAL_FLAG=true
set ALLOW_ASSERTS_FLAG=true

cd %~dp0

rem Require Visual Studio's cl
where cl >nul 2>nul
IF %ERRORLEVEL% NEQ 0 (
    echo "Error: cl is not in the path. Please setup Visual Studio to do cl builds by calling vcvarsall.bat"
    goto skipEverything
)

set WARNINGS=-wd4189 -wd4706 -wd4996 -wd4100 -wd4127 -wd4267 -wd4505 -wd4820 -wd4365 -wd4514 -wd4062 -wd4061 -wd4668 -wd4389 -wd4018 -wd4711 -wd4987 -wd4710 -wd4625 -wd4626 -wd4350 -wd4826 -wd4640 -wd4571 -wd4986 -wd4388 -wd4129 -wd4201 -wd4577 -wd4244 -wd4623 -wd4204 -wd4101 -wd4255 -wd4191 -wd4477 -wd4242 -wd4464 -wd5045

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

set COMPILER_FLAGS=-nologo -Gm- -GR- %WARNINGS% -FC -Zi -Oi -GS- -Gs9999999 -Wall %INTERNAL% %ALLOW_ASSERTS% %ALLOW_TESTS%
if "%RELEASE_FLAG%"=="true" (
    set COMPILER_FLAGS=%COMPILER_FLAGS% -MT -fp:fast -EHa- -O2
) else (
    set COMPILER_FLAGS=%COMPILER_FLAGS% -MTd -EHa- -Od
)

set LINKER_FLAGS=-link kernel32.lib -stack:0x100000,0x100000

IF NOT EXIST "build" mkdir "build"

echo Running Mirror
pushd "tools"
mirror.exe ../src/main.cpp
popd

echo Building Screenshotter
pushd "build"
cl -Fescreenshotter %COMPILER_FLAGS% "../src/main.cpp" -FmScreenshotter.map user32.lib gdi32.lib %LINKER_FLAGS% -subsystem:console,5.2
popd