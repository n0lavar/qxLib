@echo off
cls 
rd /S /Q %~dp0build
md %~dp0build
cd build
cmake ..
cd ..