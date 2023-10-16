@echo off
@set REVISION=V7.0 BETA5
@set REVDATE=2007-01-03
@set OSR_DEBUG=off
@if "%OS%"=="Windows_NT" goto :MAIN
@echo This script requires Windows NT 4.0 or later to run properly!
goto :EOF
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::
::    This software is supplied for instructional purposes only.
::
::    OSR Open Systems Resources, Inc. (OSR) expressly disclaims any warranty
::    for this software.  THIS SOFTWARE IS PROVIDED  "AS IS" WITHOUT WARRANTY
::    OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING, WITHOUT LIMITATION,
::    THE IMPLIED WARRANTIES OF MECHANTABILITY OR FITNESS FOR A PARTICULAR
::    PURPOSE.  THE ENTIRE RISK ARISING FROM THE USE OF THIS SOFTWARE REMAINS
::    WITH YOU.  OSR's entire liability and your exclusive remedy shall not
::    exceed the price paid for this material.  In no event shall OSR or its
::    suppliers be liable for any damages whatsoever (including, without
::    limitation, damages for loss of business profit, business interruption,
::    loss of business information, or any other pecuniary loss) arising out
::    of the use or inability to use this software, even if OSR has been
::    advised of the possibility of such damages.  Because some states/
::    jurisdictions do not allow the exclusion or limitation of liability for
::    consequential or incidental damages, the above limitation may not apply
::    to you.
::
::    OSR Open Systems Resources, Inc.
::    105 Route 101A Suite 19
::    Amherst, NH 03031  (603) 595-6500 FAX: (603) 595-6503
::    email bugs to: bugs@osr.com
::
::
::    MODULE:
::
::      ddkbuild.cmd
::
::    ABSTRACT:
::
::      This file allows drivers to be build with visual studio and visual studio.net
::
::    AUTHOR(S):
::
::      - OSR Open Systems Resources, Inc.
::      - Oliver Schneider (ddkwizard.assarbad.net)
::
::    REQUIREMENTS:  Environment variables that must be set.
::
::      %NT4BASE%  - Set this up for "-NT4" builds
::      %W2KBASE%  - Set this up for "-W2K*" builds
::      %WXPBASE%  - Set this up for "-WXP*" builds
::      %WNETBASE% - Set this up for "-WNET*" builds
::      %WLHBASE% - Set this up for "-WLH*" builds
::
::      %WDF_ROOT% must be set if attempting to do a WDF Build.
::
::      Examples:
::        NT4BASE : could be "D:\NT4DDK"
::        W2KBASE : could be "D:\Nt50DDK"
::        WXPBASE : could be "D:\WINDDK\2600"
::        WNETBASE: could be "D:\WINDDK\3790.1830" or "C:\WINDDK\3790"
::
::    COMMAND FORMAT (taken from the script's output):
::
::      ddkbuild <platform> <build type> <directory> [flags] [-WDF] [-PREFAST]
::
::      Platform values:
::            -W2K       to indicate W2K        build using %W2KBASE%
::            -W2K64     to indicate W2K  IA64  build using %W2KBASE%
::            -WXP       to indicate WXP        build using %WXPBASE%
::            -WXP64     to indicate WXP  IA64  build using %WXPBASE%
::            -WXP2K     to indicate W2K        build using %WXPBASE%
::            -WNET      to indicate WNET       build using %WNETBASE%
::            -WNET64    to indicate WNET IA64  build using %WNETBASE% (= -WNETI64)
::            -WNETXP    to indicate WXP        build using %WNETBASE%
::            -WNETXP64  to indicate WXP  IA64  build using %WNETBASE%
::            -WNETAMD64 to indicate WNET AMD64 build using %WNETBASE% (= -WNETX64)
::            -WNET2K    to indicate W2K        build using %WNETBASE%
::            -WLH       to indicate WLH        build using %WLHBASE%
::            -WLH2K     to indicate W2K        build using %WLHBASE%
::            -WLHXP     to indicate WXP        build using %WLHBASE%
::            -WLHNET    to indicate WNET       build using %WLHBASE%
::            -WLHNETI64 to indicate WNET IA64  build using %WLHBASE%
::            -WLHNETX64 to indicate WNET AMD64 build using %WLHBASE%
::            -WLHI64    to indicate WLH IA64   build using %WLHBASE%
::            -WLHX64    to indicate WLH AMD64  build using %WLHBASE%
::            -NT4       to indicate NT4        build using %NT4BASE%
::
::      Build types:
::             checked
::             chk       indicates a checked build
::             free
::             fre       indicates a free build
::
::      Remaining parameters:
::             directory path to build directory, try . (cwd)
::             flags     any random flags you think should be passed to build (try /a
::                       for clean)
::            -WDF       performs a WDF build
::            -PREFAST   performs a PREFAST build
::
::      Note: "-WDF" has been tested with the 01.00.5054 version of the framework
::
::    RETURN CODES AND THEIR MEANING:
::
::       001 == Unknown build type. Check the <platform> parameter
::       002 == No WDF_ROOT given using WDF build type.
::       003 == The DDK-specific base directory variable (NT4BASE, W2KBASE, WXPBASE,
::              WNETBASE) is not set at all and could not be auto-detected!
::       004 == BASEDIR variable is empty. Check to see that the DDK-specific
::              variable is set correctly (i.e. NT4BASE, W2KBASE, WXPBASE, WNETBASE)
::       005 == No mode (checked/free) was given. Check the respective parameter!
::       006 == No DIR or SOURCES file found in the given target directory.
::       007 == No target directory given.
::       008 == Given target directory does not exist.
::
::       Note: If %OSR_ERRCODE% and %ERRORLEVEL% are equal, the return code stems
::             from one of the tools being called during the build process.
::
::    BROWSE FILES:
::
::       This procedure supports the building of BROWSE files to be used by
::       Visual Studio 6 and by Visual Studio.Net  However, the BSCfiles created
::       by bscmake for the 2 studios are not compatible. When this command procedure
::       runs, it selects the first bscmake.exe found in the path.   So, make
::       sure that the correct bscmake.exe is in the path....
::
::       Note that if using Visual Studio.NET the .BSC must be added to the project
::       in order for the project to be browsed.
::       Another alternative is the VS addon named "Visual Assist X" which will
::       parse the header files - no more need for browse files.
::
::    COMPILERS:
::
::        If you are building NT4 you should really
::        be using the VC 6 compiler.   Later versions of the DDK now contain the
::        compiler and the linker.  This procedure should use the correct compiler.
::
::    GENERAL COMMENTS:
::
::        This procedure has been cleaned up to be modular and easy to
::        understand.
::
::        As of the Server 2003 SP1 DDK ddkbuild now clears the
::        NO_BROWSE_FILE and NO_BINPLACE environment variables so that users
::        can use these features.
::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: / MAIN function of the script
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:MAIN
:: Building "stack frame"
setlocal ENABLEEXTENSIONS & pushd

:: Init some special variables
set OSR_VERSTR=OSR DDKBUILD.CMD %REVISION% (%REVDATE%) - OSR, Open Systems Resources, Inc.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Set error messages
:: Possible codes: 1
set ERR_UnknownBuildType=Unknown type of build. Please recheck parameters.
:: Possible codes: 2
set ERR_NoWdfRoot=WDF_ROOT is not defined, are you using 00.01.5054 or later?
:: Possible codes: 3
set ERR_BaseDirNotSet=To build using type %%OSR_TARGET%% you need to set the %%%%%%BASEDIRVAR%%%%%% environment variable to point to the %%BASEDIROS%% DDK base directory!
:: Possible codes: 4
set ERR_NoBASEDIR=NT4BASE, W2KBASE, WXPBASE and/or WNETBASE environment variable(s) not set. Environment variable(s) must be set by user according to DDK version(s) installed.
:: Possible codes: 5
set ERR_BadMode=^<build type^> must be 'checked', 'free', 'chk' or 'fre' (case-insensitive).
:: Possible codes: 6
set ERR_NoTarget=Target directory must contain a SOURCES or DIRS file.
:: Possible codes: 7, 8
set ERR_NoDir=The ^<directory^> parameter must be a valid directory.

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Clear the error code variable
set OSR_ERRCODE=0
set prefast_build=0

:: Turn on tracing, use %OSR_TRACE% instead of ECHO
if /i {%OSR_DEBUG%} == {on} (set OSR_TRACE=@echo) else (set OSR_TRACE=rem)

:: Turn on echoing of current line if %OSR_DEBUG% is set to "on"
@echo %OSR_DEBUG%

:: Output version string
@echo %OSR_VERSTR%
%OSR_TRACE% ^(Current module: ^"%~f0^"^)

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Set the target platform variable
set OSR_TARGET=%1
:: Remove any dashes in the variable
if not {%OSR_TARGET%} == {} set OSR_TARGET=%OSR_TARGET:-=%
:: Show help if the target parameter is empty after removal of the dashes
if {%OSR_TARGET%} == {} goto :USAGE

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Additional error handling for better usability
:: These subroutines will also attempt to locate the requested DDK!!!
set OSR_ERRCODE=3
%OSR_TRACE% Checking whether the environment variable for the build type was set
:: Calling as a subroutine has 2 advantages:
:: 1. the script does not quit if the label was not found
:: 2. we return to the line after the call and can check variables there
call :%OSR_TARGET%Check
:: If the BASEDIROS/BASEDIRVAR variable is not defined, it means the subroutine did not exist!
if not DEFINED BASEDIROS call :ShowErrorMsg 1 "%ERR_UnknownBuildType% (BASEDIROS)" & goto :USAGE
if not DEFINED BASEDIRVAR call :ShowErrorMsg 1 "%ERR_UnknownBuildType% (BASEDIRVAR)" & goto :USAGE
if not {%OSR_ERRCODE%} == {0} call :ShowErrorMsg %OSR_ERRCODE% "%ERR_BaseDirNotSet%" & goto :USAGE

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
set BASEDIR=%%%BASEDIRVAR%%%
call :ResolveVar BASEDIR
:: Check for existing %BASEDIR%
if {%BASEDIR%}=={} call :ShowErrorMsg 4 "%ERR_NoBASEDIR%" & goto :USAGE
set PATH=%BASEDIR%\bin;%PATH%
%OSR_TRACE% Now jump to the initialization of the commandline
:: Calling as a subroutine has 2 advantages:
:: 1. the script does not quit if the label was not found
:: 2. we return to the line after the call and can check variables there
call :%OSR_TARGET%Build

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
%OSR_TRACE% We returned from the variable initialization
if not DEFINED OSR_CMDLINE call :ShowErrorMsg 1 "%ERR_UnknownBuildType% (OSR_CMDLINE)" & goto :USAGE

%OSR_TRACE% Hurrah, all the variables have been initialized, continuing
:: Proceed with common build steps
goto :CommonBuild

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Check whether the parameter makes sense and try to
:: correct it if possible
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:WLHCheck
:WLHX64Check
:WLHI64Check
:WLHNETX64Check
:WLHNETI64Check
:WLHXPCheck
:WLH2KCheck
:WLHNETCheck
set BASEDIROS=Windows Vista/Longhorn Server
set BASEDIRVAR=WLHBASE
:: Compatibility between BUILD and VS ... prevent pipes from being used
echo Clearing %%VS_UNICODE_OUTPUT%% ...
set VS_UNICODE_OUTPUT=
:: Return to caller
if DEFINED %BASEDIRVAR% goto :CommonCheckNoErrorWithReturn
call :CommonCheckMsg1
:: Try all the possible "default" locations
set BASEDIRTEMP=%SystemDrive%\WINDDK\6000
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
set BASEDIRTEMP=%ProgramFiles%\WINDDK\6000
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
:: Try some "odd" locations
set BASEDIRTEMP=%SystemDrive%\DDK\6000
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
set BASEDIRTEMP=%ProgramFiles%\DDK\6000
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
goto :CommonCheckErrorNotSupportedWithReturn

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:WNET2KCheck
:WNETXPCheck
:WNETXP64Check
:WNET64Check
:WNETI64Check
:WNETAMD64Check
:WNETX64Check
:WNETCheck

set BASEDIROS=Windows 2003 Server
set BASEDIRVAR=WNETBASE
:: Return to caller
if DEFINED %BASEDIRVAR% goto :CommonCheckNoErrorWithReturn
call :CommonCheckMsg1
:: Try all the possible "default" locations
set BASEDIRTEMP=%SystemDrive%\WINDDK\3790.1830
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
set BASEDIRTEMP=%SystemDrive%\WINDDK\3790.1218
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
set BASEDIRTEMP=%SystemDrive%\WINDDK\3790
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
set BASEDIRTEMP=%ProgramFiles%\WINDDK\3790.1830
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
set BASEDIRTEMP=%ProgramFiles%\WINDDK\3790.1218
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
set BASEDIRTEMP=%%ProgramFiles%\WINDDK\3790
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
:: Try some "odd" locations
set BASEDIRTEMP=%SystemDrive%\DDK\3790.1830
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
set BASEDIRTEMP=%SystemDrive%\DDK\3790.1218
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
set BASEDIRTEMP=%SystemDrive%\DDK\3790
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
set BASEDIRTEMP=%ProgramFiles%\DDK\3790.1830
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
set BASEDIRTEMP=%ProgramFiles%\DDK\3790.1218
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
set BASEDIRTEMP=%ProgramFiles%\DDK\3790
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
goto :CommonCheckErrorNotDetectedWithReturn

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:WXP64Check
:WXPCheck
:WXP2KCheck
set BASEDIROS=Windows XP
set BASEDIRVAR=WXPBASE
:: Return to caller
if DEFINED %BASEDIRVAR% goto :CommonCheckNoErrorWithReturn
call :CommonCheckMsg1
:: Try all the possible "default" locations
set BASEDIRTEMP=%SystemDrive%\WINDDK\2600
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
set BASEDIRTEMP=%ProgramFiles%\WINDDK\2600
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
:: Try some "odd" locations
set BASEDIRTEMP=%SystemDrive%\DDK\2600
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
set BASEDIRTEMP=%ProgramFiles%\DDK\2600
echo Trying %BASEDIRTEMP% ...
if exist "%BASEDIRTEMP%" goto :CommonCheckSetVarWithReturn
goto :CommonCheckErrorNotDetectedWithReturn

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:W2K64Check
:W2KCheck
set BASEDIROS=Windows 2000
set BASEDIRVAR=W2KBASE
:: Return to caller
if DEFINED %BASEDIRVAR% goto :CommonCheckNoErrorWithReturn
call :CommonCheckMsg2
goto :CommonCheckErrorNotSupportedWithReturn

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:NT4Check
set BASEDIROS=Windows NT4
set BASEDIRVAR=NT4BASE
:: Return to caller
if DEFINED %BASEDIRVAR% goto :CommonCheckNoErrorWithReturn
call :CommonCheckMsg2
goto :CommonCheckErrorNotSupportedWithReturn

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:CommonCheckMsg1
echo.
echo WARNING: %%%BASEDIRVAR%%% NOT SET!
echo   Attempting to auto-detect the installation folder and set %%%BASEDIRVAR%%%.
echo   (If this fails *you* will have to set it!)
echo.
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:CommonCheckMsg2
echo.
echo WARNING:
echo   Auto-detection of the folder settings is not supported for the requested DDK.
echo   Please set %%%BASEDIRVAR%%% yourself!
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:CommonCheckSetVarWithReturn
echo Found!
echo.
set %BASEDIRVAR%=%BASEDIRTEMP%
set BASEDIRTEMP=
:: Tell the caller it was successful
:CommonCheckNoErrorWithReturn
set OSR_ERRCODE=0
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:CommonCheckErrorNotDetectedWithReturn
echo.
echo None of the usual default paths works. Set %%%BASEDIRVAR%%% manually!
:CommonCheckErrorNotSupportedWithReturn
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Initialize variables specific to the respective platform
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: NT 4.0 build using NT4 DDK
:NT4Build
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv.bat %%BASEDIR%% %%BuildMode%% "%%MSDEVDIR%%"
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: W2K build for 32bit using WXP DDK
:WXP2KBuild
set OSR_CMDLINE=%%BASEDIR%%\bin\w2k\set2k.bat %%BASEDIR%% %%BuildMode%%
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: W2K build for 64bit (Intel) using W2K DDK
:W2K64Build
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv64.bat %%BASEDIR%% %%BuildMode%%
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: W2K build for 32bit using W2K DDK
:W2KBuild
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv.bat %%BASEDIR%% %%BuildMode%%
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: WXP build for 64bit (Intel) using WXP DDK
:WXP64Build
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv.bat %%BASEDIR%% %%BuildMode%% 64
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: WXP build for 32bit using WXP DDK
:WXPBuild
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv.bat %%BASEDIR%% %%BuildMode%%
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: W2K build for 32bit using WNET DDK
:WNET2KBuild
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv.bat %%BASEDIR%% W2K %%BuildMode%%
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: WXP build for 32bit using WNET DDK
:WNETXPBuild
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv.bat %%BASEDIR%% %%BuildMode%% WXP
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: WXP build for 64bit using WNET DDK
:WNETXP64Build
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv.bat %%BASEDIR%% %%BuildMode%% 64 WXP
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: WNET build for 64bit (Intel) using WNET DDK
:WNET64Build
:WNETI64Build
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv.bat %%BASEDIR%% %%BuildMode%% 64 WNET
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: WNET build for 64bit (AMD) using WNET DDK
:WNETAMD64Build
:WNETX64Build
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv.bat %%BASEDIR%% %%BuildMode%% AMD64 WNET
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: WNET build for 32bit using WNET DDK
:WNETBuild
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv.bat %%BASEDIR%% %%BuildMode%%
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: WLH build for 32bit using WLH DDK
:WLHBuild
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv.bat %%BASEDIR%% %%BuildMode%% WLH
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: WLH build for 64bit (AMD) using WLH DDK
:WLHX64Build
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv.bat %%BASEDIR%% %%BuildMode%% AMD64 WLH
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: WLH build for 64bit (Intel) using WLH DDK
:WLHI64Build
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv.bat %%BASEDIR%% %%BuildMode%% 64 WLH
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: WNET build for 64bit (AMD) using WLH DDK
:WLHNETX64Build
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv.bat %%BASEDIR%% %%BuildMode%% AMD64 WNET
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: WNET build for 64bit (Intel) using WLH DDK
:WLHNETI64Build
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv.bat %%BASEDIR%% %%BuildMode%% 64 WNET
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: WXP build for 32bit using WLH DDK
:WLHXPBuild
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv.bat %%BASEDIR%% %%BuildMode%% WXP
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: W2K build for 32bit using WLH DDK
:WLH2KBuild
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv.bat %%BASEDIR%% %%BuildMode%% W2K
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: WNET build for 32bit using WLH DDK
:WLHNETBuild
set OSR_CMDLINE=%%BASEDIR%%\bin\setenv.bat %%BASEDIR%% %%BuildMode%% WNET
goto :EOF

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: All builds go here for the rest of the procedure. Now,
:: we are getting ready to call build. The big problem
:: here is to figure our the name of the buildxxx files
:: being generated for the different platforms.
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:CommonBuild
:: Remove first command line arg
shift
call :SetMode %1
if not {%OSR_ERRCODE%} == {0} call :ShowErrorMsg %OSR_ERRCODE% "%ERR_BadMode%" & goto :USAGE
:: Resolve unresolved variable
set OSR_BUILDNAME=%OSR_TARGET% (%BuildMode%) build using the %BASEDIROS% DDK and %%%BASEDIRVAR%%%
::call :ResolveVar OSR_BUILDNAME
::set OSR_BUILDNAME=%OSR_BUILDNAME%

call :CheckTargets %2
if {%OSR_ERRCODE%} == {6} call :ShowErrorMsg %OSR_ERRCODE% "%ERR_NoTarget%" & goto :USAGE
if not {%OSR_ERRCODE%} == {0} call :ShowErrorMsg %OSR_ERRCODE% "%ERR_NoDir%" & goto :USAGE

:: Resolve any variables in the command line string
set OSR_CMDLINE=%OSR_CMDLINE%

pushd .
:: This external script prepares the build environment (e.g. setenv.bat)
call %OSR_CMDLINE%
popd

:: ----------------------------------------------------------------------------
:: Setting global variables for the scope of this CMD session
set NO_BROWSER_FILE=
set NO_BINPLACE=
set buildDirectory=%2

set mpFlag=-M
if {%BUILD_ALT_DIR%}=={} goto :NT4

:: W2K sets this!
set W2kEXT=%BUILD_ALT_DIR%
set mpFlag=-MI

:NT4
if {%NUMBER_OF_PROCESSORS%}=={} set mpFlag=
if {%NUMBER_OF_PROCESSORS%}=={1} set mpFlag=

:: Set additional variables at this point or do whatever you please
@if exist "%buildDirectory%\ddkprebld.cmd" @(
  echo Performing pre-build steps ...
  call %buildDirectory%\ddkprebld.cmd
)

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Determine the settings of flags, WDF and PREFAST in
:: other words what was set for %3 and beyond....
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
@echo Doing a %OSR_BUILDNAME%
set OSR_ARGS= + argument(s):
if not {%3} == {} set OSR_ARGS=%OSR_ARGS% %3
if not {%4} == {} set OSR_ARGS=%OSR_ARGS% %4
if not {%5} == {} set OSR_ARGS=%OSR_ARGS% %5
if /i "%OSR_ARGS%" == " + argument(s):" set OSR_ARGS=
@echo Directory: %buildDirectory%%OSR_ARGS% (%BASEDIRVAR% == %BASEDIR%)

cd /D %~s2
set bflags=-Ze
set bscFlags=

:ContinueParsing
if {%3} == {} goto :DONE
if {%3} == {/a} goto :RebuildallFound
if /i {%3} == {-WDF} goto :WDFFound
if /i {%3} == {-PREFAST} goto :PrefastFound
set bscFlags=/n
:: Old line: set bflags=%bflags% %3 -e
set bflags=%bflags% %3 -e
:: Remove first arg
shift
goto :ContinueParsing

:WDFFound
shift
if /i {%BASEDIRVAR%} == {WLHBASE} goto :WDFOkay
if {%WDF_ROOT%} == {} call :ShowErrorMsg 2 "%ERR_NoWdfRoot%" & goto :USAGE
pushd .
call %WDF_ROOT%\set_wdf_env.cmd
popd
:WDFOkay
:: set OSR_DEBUG=on We don't need that here
goto :ContinueParsing

:PrefastFound
shift
set prefast_build=1
goto :ContinueParsing

:RebuildallFound
shift
set bscFlags=/n
set bflags=-cfeZ
goto :ContinueParsing

:DONE

if exist "build%W2kEXT%.err"   erase /f /q "build%W2kEXT%.err"
if exist "build%W2kEXT%.wrn2"   erase /f /q "build%W2kEXT%.wrn"
if exist "build%W2kEXT%.log"   erase /f /q "build%W2kEXT%.log"
if exist "prefast%W2kEXT%.log" erase /f /q "prefast%W2kEXT%.log"

if not {%prefast_build%} == {0} goto :RunPrefastBuild
@echo Run build %bflags% %mpFlag% for %BuildMode% version in %buildDirectory%
pushd .
build  %bflags% %mpFlag%
goto :BuildComplete

:RunPrefastBuild
@echo Run prefast build %bflags% %mpFlag% for %BuildMode% version in %buildDirectory%
pushd .
setlocal
set PREFASTLOG=PREfast_defects_%W2kEXT%.xml
prefast /log=%PREFASTLOG% /reset build  %bflags% %mpFlag% > NUL
if "%errorlevel%" GTR "0" set OSR_ERRCODE=%errorlevel%
prefast /log=%PREFASTLOG% list > prefast%W2kEXT%.log
echo The PREfast logfile is ^"%prefastlog%^"!
endlocal

:BuildComplete
if not {%errorlevel%} == {0} set OSR_ERRCODE=%errorlevel%
popd

@echo %OSR_DEBUG%

:: Assume that the onscreen errors are complete!
setlocal
set WARNING_FILE_COUNT=0
set WARNING_OUTPUT=0
if exist "build%W2kEXT%.wrn" set /a WARNING_FILE_COUNT=%WARNING_FILE_COUNT%+1
if exist "build%W2kEXT%.log" set /a WARNING_FILE_COUNT=%WARNING_FILE_COUNT%+1
if not {%WARNING_FILE_COUNT%} == {0} (
  @echo ================ Build warnings =======================
  if exist "build%W2kEXT%.wrn" findstr "warning[^.][DRCLU][0-9]*" "build%W2kEXT%.log"
  if exist "build%W2kEXT%.log" findstr "error[^.][DRCLU][0-9]*" "build%W2kEXT%.log"
  set /a WARNING_OUTPUT=%WARNING_OUTPUT%+1
)
set WARNING_FILE_COUNT=0
if exist "prefast%W2kEXT%.log" set /a WARNING_FILE_COUNT=%WARNING_FILE_COUNT%+1
:: Reset if this is no PREfast build
if {%prefast_build%} == {0} set WARNING_FILE_COUNT=0
if not {%WARNING_FILE_COUNT%} == {0} (
  @echo =============== PREfast warnings ======================
  if exist "prefast%W2kEXT%.log" findstr "warning[^.][CLU]*" "prefast%W2kEXT%.log"
  set /a WARNING_OUTPUT=%WARNING_OUTPUT%+1
)
if not {%WARNING_OUTPUT%} == {0} (
  @echo =======================================================
)
endlocal
@echo.
@echo.
@echo Build complete
@echo Building browse information files
if exist "buildbrowse.cmd" call "buildbrowse.cmd" & goto :postBuildSteps
set sbrlist=sbrList.txt
if not exist sbrList%CPU%.txt goto :sbrDefault
set sbrlist=sbrList%CPU%.txt

:sbrDefault
if not exist %sbrlist% goto :postBuildSteps
:: Prepend blank space
if not {%bscFlags%} == {} set bscFlags= %bscFlags%
:: bscmake%bscFlags% prevents a double blank space ...
bscmake%bscFlags% @%sbrlist%

:: Perform whatever post-build steps
:postBuildSteps
@if exist %buildDirectory%\ddkpostbld.cmd @(
  echo Performing post build steps ...
  call %buildDirectory%\ddkpostbld.cmd
)
goto :END
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: \ MAIN function of the script
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::  / SetMode
::    Subroutine to validate the mode of the build passed in. It must be free,
::    FREE, fre, FRE or checked, CHECKED, chk, CHK. Anything else is an error.
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:SetMode
set BuildMode=
if /i {%OSR_TARGET%} == {WLH2K} goto :SetModeWLH2K
for %%f in (free fre) do if /i {%%f} == {%1} set BuildMode=free
for %%f in (checked chk) do if /i {%%f} == {%1} set BuildMode=checked
goto :SetModeCommonEnd
:SetModeWLH2K
for %%f in (free fre) do if /i {%%f} == {%1} set BuildMode=f
for %%f in (checked chk) do if /i {%%f} == {%1} set BuildMode=c
:SetModeCommonEnd
%OSR_TRACE% Mode set to ^"%BuildMode%^"
if {%BuildMode%} == {} set OSR_ERRCODE=5
goto :EOF
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::  \ SetMode
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: / CheckTargets subroutine
::   Subroutine to validate that the target directory exists and that there is
::   either a DIRS or SOURCES and MakeFile in it.
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:CheckTargets
:: Building "stack frame"
setlocal & pushd & set OSR_ERRCODE=0
if not {%1} == {} goto :CheckTargets1
set OSR_ERRCODE=7
goto :CheckTargets_ret
:CheckTargets1
if exist "%1" goto :CheckTargets2
set OSR_ERRCODE=8
goto :CheckTargets_ret
:CheckTargets2
if not exist "%1\DIRS" goto :CheckTargets3
set OSR_ERRCODE=0
goto :CheckTargets_ret
:CheckTargets3
if exist "%1\SOURCES" goto :CheckTargets4
set OSR_ERRCODE=6
goto :CheckTargets_ret
:CheckTargets4
if exist "%1\MAKEFILE" goto :CheckTargets5
set OSR_ERRCODE=6
goto :CheckTargets_ret
:CheckTargets5
set OSR_ERRCODE=0
:CheckTargets_ret
:: Cleaning "stack frame" and returning error code into global scope
popd & endlocal & set OSR_ERRCODE=%OSR_ERRCODE%
goto :EOF
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: \ CheckTargets subroutine
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: / ResolveVar subroutine
::   There is only one parameter, the name of the variable to be resolved!
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:ResolveVar
set OSR_TEMP=%1
set OSR_TEMPRET2=%%%OSR_TEMP%%%
:ResolveVarLoop
set OSR_TEMPRET1=%OSR_TEMPRET2%
set OSR_TEMPRET2=%OSR_TEMPRET1%
for /f "tokens=*" %%i in ('echo %OSR_TEMPRET1%') do (
  set %OSR_TEMP%=%%i
  set OSR_TEMPRET2=%%i
)
if not {%OSR_TEMPRET1%} == {%OSR_TEMPRET2%} goto :ResolveVarLoop
set OSR_TEMP=
set OSR_TEMPRET1=
set OSR_TEMPRET2=
goto :EOF
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: / ResolveVar subroutine
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: / ErrorWithUsage subroutine
::   This one will take the passed in parameters and build a nice error
::   message which is returned to the user along with the usage hints.
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:ShowErrorMsg
@set OSR_ERRCODE=%1
@set OSR_ERRMSG=%2
@set OSR_ERRMSG=%OSR_ERRMSG:"=%
@set OSR_ERRMSG=%OSR_ERRMSG:'="%
@set OSR_ERRMSG=ERROR #%OSR_ERRCODE%: %OSR_ERRMSG%
@echo.
@echo %OSR_ERRMSG%
goto :EOF
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: \ ErrorWithUsage subroutine
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Usage output
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:USAGE
@echo.
@echo Syntax:
@echo ddkbuild ^<platform^> ^<build type^> ^<directory^> [flags] [-WDF] [-PREFAST]
@echo.
@echo Platform values:
@echo       -W2K       to indicate W2K        build using %%W2KBASE%%
@echo       -W2K64     to indicate W2K  IA64  build using %%W2KBASE%%
@echo       -WXP       to indicate WXP        build using %%WXPBASE%%
@echo       -WXP64     to indicate WXP  IA64  build using %%WXPBASE%%
@echo       -WXP2K     to indicate W2K        build using %%WXPBASE%%
@echo       -WNET      to indicate WNET       build using %%WNETBASE%%
@echo       -WNET64    to indicate WNET IA64  build using %%WNETBASE%% (= -WNETI64)
@echo       -WNETXP    to indicate WXP        build using %%WNETBASE%%
@echo       -WNETXP64  to indicate WXP  IA64  build using %%WNETBASE%%
@echo       -WNETAMD64 to indicate WNET AMD64 build using %%WNETBASE%% (= -WNETX64)
@echo       -WNET2K    to indicate W2K        build using %%WNETBASE%%
@echo       -WLH       to indicate WLH        build using %%WLHBASE%%
@echo       -WLH2K     to indicate W2K        build using %%WLHBASE%%
@echo       -WLHXP     to indicate WXP        build using %%WLHBASE%%
@echo       -WLHNET    to indicate WNET       build using %%WLHBASE%%
@echo       -WLHNETI64 to indicate WNET IA64  build using %%WLHBASE%%
@echo       -WLHNETX64 to indicate WNET AMD64 build using %%WLHBASE%%
@echo       -WLHI64    to indicate WLH IA64   build using %%WLHBASE%%
@echo       -WLHX64    to indicate WLH AMD64  build using %%WLHBASE%%
@echo       -NT4       to indicate NT4        build using %%NT4BASE%%
@echo.
@echo Build types:
@echo        checked
@echo        chk       indicates a checked build
@echo        free
@echo        fre       indicates a free build
@echo.
@echo Remaining parameters:
@echo        directory path to build directory, try . (cwd)
@echo        flags     any random flags you think should be passed to build (try /a
@echo                  for clean)
@echo       -WDF       performs a WDF build
@echo       -PREFAST   performs a PREFAST build
@echo.
@echo Examples:
@echo       ^"ddkbuild -NT4 checked .^" (for NT4 BUILD)
@echo       ^"ddkbuild -WXP64 chk .^"
@echo       ^"ddkbuild -WXP chk c:\projects\myproject^"
@echo       ^"ddkbuild -WNET64 chk .^"      (IA64 bit build)
@echo       ^"ddkbuild -WNETAMD64 chk .^"   (AMD64/EM64T bit build)
@echo       ^"ddkbuild -WNETXP chk . -cZ -WDF^"
@echo       ^"ddkbuild -WNETXP chk . -cZ -PREFAST^"
@echo.
@echo       In order for this procedure to work correctly for each platform, it
@echo       requires an environment variable to be set up for certain platforms.
@echo       The environment variables are as follows:
@echo.
@echo       %%NT4BASE%%  - Set this up for ^"-NT4^" builds
@echo       %%W2KBASE%%  - Set this up for ^"-W2K^" and ^"-W2K64^" builds
@echo       %%WXPBASE%%  - Set this up for ^"-WXP^", ^"-WXP64^", ^"-WXP2K^" builds
@echo       %%WNETBASE%% - Set this up for ^"-WNET*^" builds
@echo       %%WLHBASE%%  - Set this up for ^"-WLH*^" builds
@echo.
@echo       %%WDF_ROOT%% must be set if attempting to do a WDF Build.
@echo.
@echo.
@echo   %OSR_VERSTR%
@echo   -^> report any problems found to info@osr.com or assarbad.net/contact
@echo.

:END
popd & endlocal
exit /b %OSR_ERRCODE%
@echo ddkbuild complete
