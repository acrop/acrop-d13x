@rem !!! Do not change this file in-place, change its copy instead !!!
@rem !!!  Otherwise you will lose your settings after next update  !!!

@echo off

set PATH=%SystemRoot%\system32;%PATH%
set PATH=C:\WINDOWS\system32;%PATH%

rem Simple "ver" prints empty line before Windows version
rem Use this construction to print just a version info
cmd /d /c ver | "%windir%\system32\find.exe" "Windows"

rem Now we form the command prompt

rem This will start prompt with `User@PC `
set ConEmuPrompt0=$E[m$E[32m$E]9;8;"USERNAME"$E\@$E]9;8;"COMPUTERNAME"$E\$S

rem Followed by colored `Path`
set ConEmuPrompt1=%ConEmuPrompt0%$E[92m$P$E[90m
if NOT "%PROCESSOR_ARCHITECTURE%" == "AMD64" (
  if "%PROCESSOR_ARCHITEW6432%" == "AMD64" if "%PROCESSOR_ARCHITECTURE%" == "x86" (
    rem Use another text color if cmd was run from SysWow64
    set ConEmuPrompt1=%ConEmuPrompt0%$E[93m$P$E[90m
  )
)

rem Carriage return and `$` or `>`
rem Spare `$E[90m` was specially added because of GitShowBranch.cmd
if "%ConEmuIsAdmin%" == "ADMIN" (
  set ConEmuPrompt2=$_$E[90m$$
) else (
  set ConEmuPrompt2=$_$E[90m$G
)

rem Finally reset color and add space
set ConEmuPrompt3=$E[m$S$E]9;12$E\

:: ============= RT-Thread ENV Path ==================

set ENV_ROOT=%~dp0..\..\..

SET RTT_EXEC_PATH=%~dp0\..\..\..\..\..\toolchain\bin
set RTT_CC=gcc
set PKGS_ROOT=%ENV_ROOT%\packages
set SCONS=%ENV_ROOT%\tools\Python27\Scripts
set PATH=%ENV_ROOT%\tools\MinGit-2.25.1-32-bit\cmd;%PATH%
set PATH=%ENV_ROOT%\tools\bin;%PATH%
set PATH=%RTT_EXEC_PATH%;%PATH%
set PATH=%ENV_ROOT%\tools\Python27;%PATH%
set PATH=%ENV_ROOT%\tools\Python38;%PATH%
set PATH=%SCONS%;%PATH%
set PATH=%ENV_ROOT%\tools\qemu\qemu32;%PATH%

start /b python %~dp0..\..\scripts\init_env.py

:: ====== RT-Thread ENV Change Code Page ================

rem OneStep command
set SDK_PRJ_TOP_DIR=%CD%
set PATH=%PATH%;%SDK_PRJ_TOP_DIR%\tools\scripts\onestep
doskey list=scons --list-noboot -C %SDK_PRJ_TOP_DIR%
doskey bm=boot_menuconfig
doskey km=app_menuconfig
doskey m=make_boot_and_app
doskey mb=make_boot_and_app
:: make uboot
doskey mu=make_boot
:: make spl
doskey ms=make_boot
doskey ma=make_app
doskey c=clean_boot_and_app
doskey mc=make_boot_and_app clean
doskey i=scons --info -C %SDK_PRJ_TOP_DIR%
doskey aicupg=scons --aicupg -C %SDK_PRJ_TOP_DIR%
doskey croot=cd /d %SDK_PRJ_TOP_DIR%
doskey cr=cd /d %SDK_PRJ_TOP_DIR%
doskey cb=cbuild
doskey co=cout
doskey ct=ctarget
doskey update=sdk_update

chcp 65001 > nul
echo Luban-Lite Env Tool for Windows (V1.3.5)
echo.
echo      _         _   ___        ___ _     _
echo     / \   _ __^| ^|_^|_ _^|_ __  / __^| ^|__ (_)_ __
echo    / _ \ ^| '__^| __^|^| ^|^| '_ \^| ^|  ^| '_ \^| ^| '_ \
echo   / ___ \^| ^|  ^| ^|_ ^| ^|^| ^| ^| ^| ^|__^| ^| ^| ^| ^| ^|_) ^|
echo  /_/   \_\_^|   \__^|___^|_^| ^|_^|\___^|_^| ^|_^|_^| .__/
echo                                          ^|_^|

Setlocal ENABLEDELAYEDEXPANSION
::启用命令扩展，参加setlocal /?命令
set str1=%~dp0
set str=%str1%
set env_root=%~dp0

:next
if not "%str%"=="" (
set /a num+=1
if "!str:~0,1!"==" " (
    echo.
    echo *******************************************************************
    echo Env 工具所在路径如下：
    echo %env_root:~0,-21%
    echo 警告：以上路径不能包含中文或空格，请将 Env 移动到符合要求的路径中。
    echo *******************************************************************
    endlocal
    goto break_str
)
set "str=%str:~1%"
goto next
)
endlocal

set "str=%~dp0"
>"%tmp%\t.t" echo;WSH.Echo(/[\u4E00-\u9FFF]/.test(WSH.Arguments(0)))
for /f %%a in ('cscript -nologo -e:jscript "%tmp%\t.t" "%str%"') do if %%a neq 0 (goto not_support_chinese) else goto break_str

:not_support_chinese
echo.
echo *******************************************************************
echo Env 工具所在路径如下：
echo %env_root:~0,-29%
echo 警告：以上路径不能包含中文或空格，请将 Env 移动到符合要求的路径中。
echo *******************************************************************

:break_str

chcp 437 > nul

:: ======================================================
if /I "%~1" == "/git" goto git
if /I "%~1" == "-git" goto git
goto no_git

:git
call "%~dp0GitShowBranch.cmd" /i
goto :EOF

:no_git
rem Set new prompt
PROMPT %ConEmuPrompt1%%ConEmuPrompt2%%ConEmuPrompt3%
