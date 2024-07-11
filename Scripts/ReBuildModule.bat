@echo off

rmdir Bin-Obj/Engine/Source/%1 /s /q
call Build.bat
