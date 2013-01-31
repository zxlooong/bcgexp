# Microsoft Developer Studio Project File - Name="BCGPShopDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BCGPShopDemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BCGPShopDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BCGPShopDemo.mak" CFG="BCGPShopDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BCGPShopDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BCGPShopDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "BCGPShopDemo - Win32 ReleaseStatic" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BCGPShopDemo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin"
# PROP Intermediate_Dir "Release"
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

!ELSEIF  "$(CFG)" == "BCGPShopDemo - Win32 Debug"

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
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\Bin/BCGPShopDemoD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "BCGPShopDemo - Win32 ReleaseStatic"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BCGPShopDemo___Win32_ReleaseStatic"
# PROP BASE Intermediate_Dir "BCGPShopDemo___Win32_ReleaseStatic"
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
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL" /d "_BCGCBPRO_STATIC_"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "BCGPShopDemo - Win32 Release"
# Name "BCGPShopDemo - Win32 Debug"
# Name "BCGPShopDemo - Win32 ReleaseStatic"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BCGPShopDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPShopDemo.rc
# End Source File
# Begin Source File

SOURCE=.\BCGPShopDemoDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPShopDemoView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorPicker.cpp
# End Source File
# Begin Source File

SOURCE=.\ContextToolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Palette.cpp
# End Source File
# Begin Source File

SOURCE=.\PaletteMiniFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\ShadowWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\SharedBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\ShopTabWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ShopToolBase.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TabbedBar.cpp
# End Source File
# Begin Source File

SOURCE=.\TabHeaderLayout.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualManager.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BCGPShopDemo.h
# End Source File
# Begin Source File

SOURCE=.\BCGPShopDemoDoc.h
# End Source File
# Begin Source File

SOURCE=.\BCGPShopDemoView.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ColorPicker.h
# End Source File
# Begin Source File

SOURCE=.\ContextToolbar.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Palette.h
# End Source File
# Begin Source File

SOURCE=.\PaletteMiniFrame.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ShadowWnd.h
# End Source File
# Begin Source File

SOURCE=.\SharedBitmap.h
# End Source File
# Begin Source File

SOURCE=.\ShopTabWnd.h
# End Source File
# Begin Source File

SOURCE=.\ShopToolBase.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TabbedBar.h
# End Source File
# Begin Source File

SOURCE=.\TabHeaderLayout.h
# End Source File
# Begin Source File

SOURCE=.\ToolPalette.h
# End Source File
# Begin Source File

SOURCE=.\VisualManager.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\BCGPShopDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\BCGPShopDemo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\BCGPShopDemoDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\BtnsSwapReset.png
# End Source File
# Begin Source File

SOURCE=.\res\ContextToolbar.png
# End Source File
# Begin Source File

SOURCE=.\res\HrzToolBar.png
# End Source File
# Begin Source File

SOURCE=.\res\HrzToolBarClr.png
# End Source File
# Begin Source File

SOURCE=.\res\MiniFrameBtn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Tab_CloseBtn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Tab_Headers.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TabbedBarCtrl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ToolBarCaption.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbarm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ToolBtns.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ToolLasso.png
# End Source File
# Begin Source File

SOURCE=.\res\ToolLassoClr.png
# End Source File
# Begin Source File

SOURCE=.\res\ToolSelect.png
# End Source File
# Begin Source File

SOURCE=.\res\ToolSelectClr.PNG
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
