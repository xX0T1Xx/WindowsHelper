@echo off
g++ source\*.cpp -Iinclude -o bin\main.exe -lUxTheme -lComctl32 -lGdi32 -w
bin\main.exe