# Microsoft Developer Studio Project File - Name="BCGPOutlookDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BCGPOutlookDemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BCGPOutlookDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BCGPOutlookDemo.mak" CFG="BCGPOutlookDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BCGPOutlookDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BCGPOutlookDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "BCGPOutlookDemo - Win32 ReleaseStatic" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BCGPOutlookDemo - Win32 Release"

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

!ELSEIF  "$(CFG)" == "BCGPOutlookDemo - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\Bin/BCGPOutlookDemoD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "BCGPOutlookDemo - Win32 ReleaseStatic"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BCGPOutlookDemo___Win32_ReleaseStatic"
# PROP BASE Intermediate_Dir "BCGPOutlookDemo___Win32_ReleaseStatic"
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

# Name "BCGPOutlookDemo - Win32 Release"
# Name "BCGPOutlookDemo - Win32 Debug"
# Name "BCGPOutlookDemo - Win32 ReleaseStatic"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AppLookDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPOutlookDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPOutlookDemo.rc
# End Source File
# Begin Source File

SOURCE=.\BCGPOutlookDemoDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPOutlookDemoView.cpp
# End Source File
# Begin Source File

SOURCE=.\CalendarBar.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderListBar.cpp
# End Source File
# Begin Source File

SOURCE=.\FolderListPopupWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\FoldersTree.cpp
# End Source File
# Begin Source File

SOURCE=.\MailBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MailFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\MailView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\PreviewPane.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WorkspaceObj.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AppLookDlg.h
# End Source File
# Begin Source File

SOURCE=.\BCGPOutlookDemo.h
# End Source File
# Begin Source File

SOURCE=.\BCGPOutlookDemoDoc.h
# End Source File
# Begin Source File

SOURCE=.\BCGPOutlookDemoView.h
# End Source File
# Begin Source File

SOURCE=.\CalendarBar.h
# End Source File
# Begin Source File

SOURCE=.\FolderListBar.h
# End Source File
# Begin Source File

SOURCE=.\FolderListPopupWnd.h
# End Source File
# Begin Source File

SOURCE=.\FoldersTree.h
# End Source File
# Begin Source File

SOURCE=.\MailBar.h
# End Source File
# Begin Source File

SOURCE=.\MailFrame.h
# End Source File
# Begin Source File

SOURCE=.\MailView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PreviewPane.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WorkspaceObj.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\adnanced.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\advanced_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\animation.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\animation_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BCGPOutlookDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\BCGPOutlookDemo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\BCGPOutlookDemoDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\header.bmp
# End Source File
# Begin Source File

SOURCE=.\res\list.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mail.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mail.ico
# End Source File
# Begin Source File

SOURCE=.\Res\mail_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\menu_image.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\menu_image_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\outlookl.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\outlookl_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\outlooks.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\outlooks_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pages.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pages1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pages_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\pages_small_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pin.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\toolbar_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\UserImages.bmp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\web.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\web_hc.bmp
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
