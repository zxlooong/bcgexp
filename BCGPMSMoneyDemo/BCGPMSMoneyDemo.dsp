# Microsoft Developer Studio Project File - Name="BCGPMSMoneyDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BCGPMSMoneyDemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BCGPMSMoneyDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BCGPMSMoneyDemo.mak" CFG="BCGPMSMoneyDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BCGPMSMoneyDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BCGPMSMoneyDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "BCGPMSMoneyDemo - Win32 ReleaseStatic" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BCGPMSMoneyDemo - Win32 Release"

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
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /incremental:yes

!ELSEIF  "$(CFG)" == "BCGPMSMoneyDemo - Win32 Debug"

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
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\bin/BCGPMSMoneyDemoD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "BCGPMSMoneyDemo - Win32 ReleaseStatic"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BCGPMSMoneyDemo___Win32_ReleaseStatic"
# PROP BASE Intermediate_Dir "BCGPMSMoneyDemo___Win32_ReleaseStatic"
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
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /i "..\..\BCGCBPro\Styles" /d "NDEBUG" /d "_AFXDLL" /d "_BCGCBPRO_STATIC_"
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

# Name "BCGPMSMoneyDemo - Win32 Release"
# Name "BCGPMSMoneyDemo - Win32 Debug"
# Name "BCGPMSMoneyDemo - Win32 ReleaseStatic"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BCGPMSMCaptionBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMCaptionBarButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMCategorieBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMCategorieBar.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMCategorieBarButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMCategorieBarButton.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMLinksBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMLinksBarButton.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMMenuBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMoneyDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMoneyDemo.rc
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMoneyDemoDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMoneyDemoView.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMTasksPane.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMVisualManager.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BCGPMSMCaptionBar.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMCaptionBarButton.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMDialog.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMLinksBar.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMLinksBarButton.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMMenuBar.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMoneyDemo.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMoneyDemoDoc.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMoneyDemoView.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMTasksPane.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMToolBar.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMSMVisualManager.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
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

SOURCE=.\res\BCGPMSMoneyDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\BCGPMSMoneyDemo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\BCGPMSMoneyDemoDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\CaptionBtns.BMP
# End Source File
# Begin Source File

SOURCE=.\res\coldtool.bmp
# End Source File
# Begin Source File

SOURCE=.\res\distool.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FrameBkgnd.BMP
# End Source File
# Begin Source File

SOURCE=.\res\hottoolb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\menu_images_16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\menu_img.bmp
# End Source File
# Begin Source File

SOURCE=.\res\prestool.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ViewBkgnd.BMP
# End Source File
# Begin Source File

SOURCE=.\xptheme.bin
# End Source File
# End Group
# End Target
# End Project
