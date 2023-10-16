@echo off
for %%d in (.) do set CurrentFolder=%%~nd
if exist excfile.txt set ExcFileSwitch=-x@excfile.txt
"%ProgramFiles%\winrar\winrar.exe" a -o+ -r -ed %ExcFileSwitch% %CurrentFolder%.rar *.*
if exist incfile.txt "%ProgramFiles%\winrar\winrar.exe" a -o+ -r -ed %CurrentFolder%.rar @incfile.txt
set CurrentFolder=

