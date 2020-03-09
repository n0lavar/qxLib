@echo off
cls 
RD /S /Q %~dp0build
cmake ./build -DQX_DEBUG=1