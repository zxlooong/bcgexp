# Microsoft Developer Studio Project File - Name="DrawCli" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DrawCli - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DrawCli.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DrawCli.mak" CFG="DrawCli - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DrawCli - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DrawCli - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "DrawCli - Win32 ReleaseStatic" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DrawCli - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "DrawCli - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\Bin/DrawCliD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "DrawCli - Win32 ReleaseStatic"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "DrawCli___Win32_ReleaseStatic"
# PROP BASE Intermediate_Dir "DrawCli___Win32_ReleaseStatic"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
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
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "DrawCli - Win32 Release"
# Name "DrawCli - Win32 Debug"
# Name "DrawCli - Win32 ReleaseStatic"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\cntritem.cpp
# End Source File
# Begin Source File

SOURCE=.\drawcli.cpp
# End Source File
# Begin Source File

SOURCE=.\drawcli.rc
# End Source File
# Begin Source File

SOURCE=.\drawdoc.cpp
# End Source File
# Begin Source File

SOURCE=.\drawobj.cpp
# End Source File
# Begin Source File

SOURCE=.\drawtool.cpp
# End Source File
# Begin Source File

SOURCE=.\drawvw.cpp
# End Source File
# Begin Source File

SOURCE=.\LineWeightDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\mainfrm.cpp
# End Source File
# Begin Source File

SOURCE=.\propset.cpp
# End Source File
# Begin Source File

SOURCE=.\rectdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RibbonListButton.cpp
# End Source File
# Begin Source File

SOURCE=.\splitfrm.cpp
# End Source File
# Begin Source File

SOURCE=.\statpage.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\summinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\summpage.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\cntritem.h
# End Source File
# Begin Source File

SOURCE=.\DrawCli.h
# End Source File
# Begin Source File

SOURCE=.\drawdoc.h
# End Source File
# Begin Source File

SOURCE=.\drawobj.h
# End Source File
# Begin Source File

SOURCE=.\drawtool.h
# End Source File
# Begin Source File

SOURCE=.\drawvw.h
# End Source File
# Begin Source File

SOURCE=.\LineWeightDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\propset.h
# End Source File
# Begin Source File

SOURCE=.\rectdlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RibbonListButton.h
# End Source File
# Begin Source File

SOURCE=.\splitfrm.h
# End Source File
# Begin Source File

SOURCE=.\statpage.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\summinfo.h
# End Source File
# Begin Source File

SOURCE=.\summpage.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\DrawCli.ico
# End Source File
# Begin Source File

SOURCE=.\res\DrawCli.rc2
# End Source File
# Begin Source File

SOURCE=.\res\drawdoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\filelarge.png
# End Source File
# Begin Source File

SOURCE=.\res\filesmall.png
# End Source File
# Begin Source File

SOURCE=.\res\formatlarge.PNG
# End Source File
# Begin Source File

SOURCE=.\res\formatsmall.PNG
# End Source File
# Begin Source File

SOURCE=.\res\homelarge.png
# End Source File
# Begin Source File

SOURCE=.\res\homesmall.png
# End Source File
# Begin Source File

SOURCE=.\res\lineweight.png
# End Source File
# Begin Source File

SOURCE=.\res\main.png
# End Source File
# Begin Source File

SOURCE=.\res\pencil.cur
# End Source File
# Begin Source File

SOURCE=.\res\prop24.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ribbonicons.png
# End Source File
# Begin Source File

SOURCE=.\res\sb_1.png
# End Source File
# Begin Source File

SOURCE=.\res\sb_2.png
# End Source File
# Begin Source File

SOURCE=.\res\styles.png
# End Source File
# Begin Source File

SOURCE=.\res\viewlarge.png
# End Source File
# Begin Source File

SOURCE=.\res\viewsmall.png
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.htm
# End Source File
# Begin Source File

SOURCE=.\setup.rul
# End Source File
# Begin Source File

SOURCE=.\xptheme.xml
# End Source File
# End Target
# End Project
