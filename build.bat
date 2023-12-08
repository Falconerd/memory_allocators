@echo off
SETLOCAL

SET COMPILER_FLAGS=-Zi -TC
::SET COMPILER_FLAGS=-O2 -TC
SET LINKER_FLAGS=kernel32.lib shell32.lib -subsystem:console

IF NOT EXIST .\build\ mkdir .\build\

cl %COMPILER_FLAGS% main.c -Fe.\build\run.exe -link %LINKER_FLAGS%

IF %ERRORLEVEL% NEQ 0 (
    echo Compilation failed!
    EXIT /B %ERRORLEVEL%
)

del main.obj

echo Compilation successful!

ENDLOCAL
