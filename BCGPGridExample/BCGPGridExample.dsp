# Microsoft Developer Studio Project File - Name="BCGPGridExample" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BCGPGridExample - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BCGPGridExample.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BCGPGridExample.mak" CFG="BCGPGridExample - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BCGPGridExample - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BCGPGridExample - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "BCGPGridExample - Win32 ReleaseStatic" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BCGPGridExample - Win32 Release"

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

!ELSEIF  "$(CFG)" == "BCGPGridExample - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\Bin/BCGPGridExampleD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "BCGPGridExample - Win32 ReleaseStatic"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BCGPGridExample___Win32_ReleaseStatic"
# PROP BASE Intermediate_Dir "BCGPGridExample___Win32_ReleaseStatic"
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

# Name "BCGPGridExample - Win32 Release"
# Name "BCGPGridExample - Win32 Debug"
# Name "BCGPGridExample - Win32 ReleaseStatic"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BasicGridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPGridExample.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPGridExample.rc
# End Source File
# Begin Source File

SOURCE=.\BCGPGridExampleDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPGridExampleView.cpp
# End Source File
# Begin Source File

SOURCE=.\CellTypesGridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorGridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomCells.cpp
# End Source File
# Begin Source File

SOURCE=.\FilterGridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\FilterListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FilterStringDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MergeGridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\MergeGridItem.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportGridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TreeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VirtualGridCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\VirtualGridDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BasicGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\BCGPGridExample.h
# End Source File
# Begin Source File

SOURCE=.\BCGPGridExampleDoc.h
# End Source File
# Begin Source File

SOURCE=.\BCGPGridExampleView.h
# End Source File
# Begin Source File

SOURCE=.\CellTypesGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ColorGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\CustomCells.h
# End Source File
# Begin Source File

SOURCE=.\FilterGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\FilterListDlg.h
# End Source File
# Begin Source File

SOURCE=.\FilterStringDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MergeGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\MergeGridItem.h
# End Source File
# Begin Source File

SOURCE=.\ReportGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TreeDlg.h
# End Source File
# Begin Source File

SOURCE=.\VirtualGridCtrl.h
# End Source File
# Begin Source File

SOURCE=.\VirtualGridDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\BCGPGridExample.ico
# End Source File
# Begin Source File

SOURCE=.\res\BCGPGridExample.rc2
# End Source File
# Begin Source File

SOURCE=.\res\BCGPGridExampleDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\caption.bmp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\chart.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FilterIcons.png
# End Source File
# Begin Source File

SOURCE=.\res\Flags256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\header.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icons.bmp
# End Source File
# Begin Source File

SOURCE=.\res\list.bmp
# End Source File
# Begin Source File

SOURCE=.\res\propicons.bmp
# End Source File
# Begin Source File

SOURCE=.\res\shortcuts.bmp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\shortcuts32.png
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.png
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_color.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_report.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\xptheme.xml
# End Source File
# End Target
# End Project
