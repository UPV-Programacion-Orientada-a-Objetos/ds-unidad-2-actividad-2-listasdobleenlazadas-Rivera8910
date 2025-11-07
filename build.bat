@echo off
REM Script de compilación para Windows
REM Decodificador PRT-7

echo ========================================
echo   Compilando Decodificador PRT-7
echo ========================================
echo.

REM Verificar si existe la carpeta build
if exist build (
    echo Limpiando carpeta build existente...
    rmdir /s /q build
)

REM Crear carpeta build
echo Creando carpeta build...
mkdir build
cd build

echo.
echo Configurando proyecto con CMake...
cmake ..

if %errorlevel% neq 0 (
    echo.
    echo ERROR: Fallo en la configuracion de CMake
    echo Verifica que CMake este instalado y en el PATH
    pause
    exit /b 1
)

echo.
echo Compilando proyecto...
cmake --build . --config Release

if %errorlevel% neq 0 (
    echo.
    echo ERROR: Fallo en la compilacion
    pause
    exit /b 1
)

echo.
echo ========================================
echo   Compilacion exitosa!
echo ========================================
echo.
echo El ejecutable se encuentra en: build\Release\DecodificadorPRT7.exe
echo o en: build\DecodificadorPRT7.exe
echo.
echo Para ejecutar el programa:
echo   cd build
echo   DecodificadorPRT7.exe
echo.
pause