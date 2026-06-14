@echo off
echo Compilando BitQuest

echo [1/2] Compilando rutinas.asm con NASM
nasm -f win64 rutinas.asm -o rutinas.obj
if errorlevel 1 (
    echo.
    echo Error al compilar el codigo en NASM
    pause
    exit /b 1
)

echo [2/2] Enlazando main.c y juego.c
gcc main.c juego.c rutinas.obj -o BitQuest.exe
if errorlevel 1 (
    echo.
    echo Error al enlazar con GCC
    pause
    exit /b 1
)

echo.
echo Ejecutando juego...
echo.
BitQuest.exe