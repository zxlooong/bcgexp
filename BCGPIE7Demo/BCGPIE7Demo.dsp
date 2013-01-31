# Microsoft Developer Studio Project File - Name="BCGPIE7Demo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BCGPIE7Demo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BCGPIE7Demo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BCGPIE7Demo.mak" CFG="BCGPIE7Demo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BCGPIE7Demo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BCGPIE7Demo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "BCGPIE7Demo - Win32 ReleaseStatic" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BCGPIE7Demo - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
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

!ELSEIF  "$(CFG)" == "BCGPIE7Demo - Win32 Debug"

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
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\Bin/BCGPIE7DemoD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "BCGPIE7Demo - Win32 ReleaseStatic"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BCGPIE7Demo___Win32_ReleaseStatic"
# PROP BASE Intermediate_Dir "BCGPIE7Demo___Win32_ReleaseStatic"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\BinStatic"
# PROP Intermediate_Dir "ReleaseStatic"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_BCGCBPRO_STATIC_" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL" /d "_BCGCBPRO_STATIC_"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "BCGPIE7Demo - Win32 Release"
# Name "BCGPIE7Demo - Win32 Debug"
# Name "BCGPIE7Demo - Win32 ReleaseStatic"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BCGPIE7Demo.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPIE7Demo.rc
# End Source File
# Begin Source File

SOURCE=.\BCGPIE7DemoDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPIE7DemoView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ExplorerBar.cpp
# End Source File
# Begin Source File

SOURCE=.\FavoritesManager.cpp
# End Source File
# Begin Source File

SOURCE=.\HistoryObj.cpp
# End Source File
# Begin Source File

SOURCE=.\LinkButton.cpp
# End Source File
# Begin Source File

SOURCE=.\LinksBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MyDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\RebarDC.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TabBar.cpp
# End Source File
# Begin Source File

SOURCE=.\TabWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\TrackMouse.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualManager.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BCGPIE7Demo.h
# End Source File
# Begin Source File

SOURCE=.\BCGPIE7DemoDoc.h
# End Source File
# Begin Source File

SOURCE=.\BCGPIE7DemoView.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ExplorerBar.h
# End Source File
# Begin Source File

SOURCE=.\FavoritesManager.h
# End Source File
# Begin Source File

SOURCE=.\HistoryObj.h
# End Source File
# Begin Source File

SOURCE=.\LinkButton.h
# End Source File
# Begin Source File

SOURCE=.\LinksBar.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MenuBar.h
# End Source File
# Begin Source File

SOURCE=.\MyDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\RebarDC.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TabBar.h
# End Source File
# Begin Source File

SOURCE=.\TabWnd.h
# End Source File
# Begin Source File

SOURCE=.\TrackMouse.h
# End Source File
# Begin Source File

SOURCE=.\VisualManager.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Group "Controls"

# PROP Default_Filter ""
# Begin Group "Style_1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\Controls\Style_1\Tab.png
# End Source File
# End Group
# Begin Group "Style_2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\Controls\Style_2\Tab.png
# End Source File
# End Group
# Begin Group "Tab"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\Controls\Tab\Corners.PNG
# End Source File
# Begin Source File

SOURCE=.\res\Controls\Tab\iconsD.png
# End Source File
# Begin Source File

SOURCE=.\res\Controls\Tab\iconsH.png
# End Source File
# Begin Source File

SOURCE=.\res\Controls\Tab\iconsN.png
# End Source File
# Begin Source File

SOURCE=.\res\Controls\Tab\Sides.png
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Controls\btnPin.PNG
# End Source File
# Begin Source File

SOURCE=.\res\Controls\btnSmClose.png
# End Source File
# Begin Source File

SOURCE=.\res\Controls\style_1.xml
# End Source File
# Begin Source File

SOURCE=.\res\Controls\style_2.xml
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\address_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\addressbar.png
# End Source File
# Begin Source File

SOURCE=.\res\addressbar_120.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGPIE7Demo.ico
# End Source File
# Begin Source File

SOURCE=.\res\BCGPIE7Demo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\BCGPIE7DemoDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\btnAddressBar.png
# End Source File
# Begin Source File

SOURCE=.\res\btnAddressBar_120.png
# End Source File
# Begin Source File

SOURCE=.\res\btnMenuAddressBar.png
# End Source File
# Begin Source File

SOURCE=.\res\btnMenuAddressBar_120.png
# End Source File
# Begin Source File

SOURCE=.\res\explorer16.BMP
# End Source File
# Begin Source File

SOURCE=.\res\explorer256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\explorer32.png
# End Source File
# Begin Source File

SOURCE=.\res\explorerbar16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\explorerbar256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\explorerbar32.PNG
# End Source File
# Begin Source File

SOURCE=.\res\explorericons16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\explorericons256.BMP
# End Source File
# Begin Source File

SOURCE=.\res\favorites32.png
# End Source File
# Begin Source File

SOURCE=.\res\favorites32_120.png
# End Source File
# Begin Source File

SOURCE=.\res\menu_images.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tab_dummy.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbaric16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbaric256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbaric32.png
# End Source File
# Begin Source File

SOURCE=.\xptheme.xml
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
