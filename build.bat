@echo off
cls 
RD /S /Q %~dp0build
cmake ./build