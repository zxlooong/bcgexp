# Microsoft Developer Studio Project File - Name="BCGPControls" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BCGPControls - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BCGPControls.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BCGPControls.mak" CFG="BCGPControls - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BCGPControls - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BCGPControls - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "BCGPControls - Win32 ReleaseStatic" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BCGPControls - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /incremental:yes

!ELSEIF  "$(CFG)" == "BCGPControls - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /GX /Zi /Od /I "." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\Bin/BCGPControlsD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "BCGPControls - Win32 ReleaseStatic"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BCGPControls___Win32_ReleaseStatic"
# PROP BASE Intermediate_Dir "BCGPControls___Win32_ReleaseStatic"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\BinStatic"
# PROP Intermediate_Dir "ReleaseStatic"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_BCGCBPRO_STATIC_" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\BCGCBPro\Styles" /d "NDEBUG" /d "_AFXDLL" /d "_BCGCBPRO_STATIC_"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT BASE LINK32 /incremental:yes
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /incremental:yes

!ENDIF 

# Begin Target

# Name "BCGPControls - Win32 Release"
# Name "BCGPControls - Win32 Debug"
# Name "BCGPControls - Win32 ReleaseStatic"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BCGControlsPropSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPControls.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPControls.rc
# End Source File
# Begin Source File

SOURCE=.\CustomProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\Page1.cpp
# End Source File
# Begin Source File

SOURCE=.\Page2.cpp
# End Source File
# Begin Source File

SOURCE=.\Page3.cpp
# End Source File
# Begin Source File

SOURCE=.\Page4.cpp
# End Source File
# Begin Source File

SOURCE=.\Page5.cpp
# End Source File
# Begin Source File

SOURCE=.\Page6.cpp
# End Source File
# Begin Source File

SOURCE=.\Page7.cpp
# End Source File
# Begin Source File

SOURCE=.\Page8.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BCGControlsPropSheet.h
# End Source File
# Begin Source File

SOURCE=.\BCGPControls.h
# End Source File
# Begin Source File

SOURCE=.\CustomProperties.h
# End Source File
# Begin Source File

SOURCE=.\Page1.h
# End Source File
# Begin Source File

SOURCE=.\Page2.h
# End Source File
# Begin Source File

SOURCE=.\Page3.h
# End Source File
# Begin Source File

SOURCE=.\Page4.h
# End Source File
# Begin Source File

SOURCE=.\Page5.h
# End Source File
# Begin Source File

SOURCE=.\Page6.h
# End Source File
# Begin Source File

SOURCE=.\Page7.h
# End Source File
# Begin Source File

SOURCE=.\Page8.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\BCGPControls.ico
# End Source File
# Begin Source File

SOURCE=.\res\BCGPControls.ico
# End Source File
# Begin Source File

SOURCE=.\BCGPControls.rc2
# End Source File
# Begin Source File

SOURCE=.\Res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Btn.cur
# End Source File
# Begin Source File

SOURCE=.\Res\btn1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\btn1_hot.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\button32.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\button32hot.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\buttons.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\check32.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\checkno.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\checkno32.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\globe.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\icons.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\icons32.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\image.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\play.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\play_hot.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\propicons.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\radio_of.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\radio_of32.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\radio_on.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\radio_on32.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\stop.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\stop_hot.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\test_bit.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\xptheme.bin
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
