@echo off
setlocal
cd /d "%~dp0"
where gcc >nul 2>&1
if errorlevel 1 (
    echo ERROR: GCC is not installed or not in PATH.
    echo Install MinGW-w64 GCC and restart VS Code or this terminal.
    pause
    exit /b 1
)
echo Compiling Personal Fitness Record Manager...
gcc -std=c11 -Wall -Wextra -pedantic personal_fitness_manager.c -o fitness_manager.exe
if errorlevel 1 (
    echo Compilation failed. Check the errors shown above.
    pause
    exit /b 1
)
echo.
echo Starting program...
echo.
fitness_manager.exe
echo.
pause
