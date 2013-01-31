# Microsoft Developer Studio Project File - Name="BCGPMSOffice2007Demo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BCGPMSOffice2007Demo - Win32 DebugStatic
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BCGPMSOffice2007Demo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BCGPMSOffice2007Demo.mak" CFG="BCGPMSOffice2007Demo - Win32 DebugStatic"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BCGPMSOffice2007Demo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BCGPMSOffice2007Demo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "BCGPMSOffice2007Demo - Win32 ReleaseStatic" (based on "Win32 (x86) Application")
!MESSAGE "BCGPMSOffice2007Demo - Win32 DebugStatic" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BCGPMSOffice2007Demo - Win32 Release"

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

!ELSEIF  "$(CFG)" == "BCGPMSOffice2007Demo - Win32 Debug"

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
# ADD LINK32 /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\bin/BCGPMSOffice2007DemoD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "BCGPMSOffice2007Demo - Win32 ReleaseStatic"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BCGPMSOffice2007Demo___Win32_ReleaseStatic"
# PROP BASE Intermediate_Dir "BCGPMSOffice2007Demo___Win32_ReleaseStatic"
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
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "BCGPMSOffice2007Demo - Win32 DebugStatic"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BCGPMSOffice2007Demo___Win32_DebugStatic"
# PROP BASE Intermediate_Dir "BCGPMSOffice2007Demo___Win32_DebugStatic"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\BinStatic"
# PROP Intermediate_Dir "ReleaseStatic"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_BCGCBPRO_STATIC_" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /i "..\..\BCGCBPro\Styles" /d "_DEBUG" /d "_AFXDLL" /d "_BCGCBPRO_STATIC_"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\bin/BCGPMSOffice2007DemoD.exe" /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\BinStatic/BCGPMSOffice2007DemoD.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "BCGPMSOffice2007Demo - Win32 Release"
# Name "BCGPMSOffice2007Demo - Win32 Debug"
# Name "BCGPMSOffice2007Demo - Win32 ReleaseStatic"
# Name "BCGPMSOffice2007Demo - Win32 DebugStatic"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BCGPMSOffice2007Demo.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMSOffice2007Demo.rc
# End Source File
# Begin Source File

SOURCE=.\BCGPMSOffice2007DemoDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMSOffice2007DemoView.cpp
# End Source File
# Begin Source File

SOURCE=.\ClipboardPane.cpp
# End Source File
# Begin Source File

SOURCE=.\CntrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBanner.cpp
# End Source File
# Begin Source File

SOURCE=.\keys.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ResourcePage.cpp
# End Source File
# Begin Source File

SOURCE=.\RibbonListButton.cpp
# End Source File
# Begin Source File

SOURCE=.\RibbonTableButton.cpp
# End Source File
# Begin Source File

SOURCE=.\RibbonTooltipCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BCGPMSOffice2007Demo.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMSOffice2007DemoDoc.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMSOffice2007DemoView.h
# End Source File
# Begin Source File

SOURCE=.\ClipboardPane.h
# End Source File
# Begin Source File

SOURCE=.\CntrItem.h
# End Source File
# Begin Source File

SOURCE=.\DlgBanner.h
# End Source File
# Begin Source File

SOURCE=.\keys.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\OptionsPage.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ResourcePage.h
# End Source File
# Begin Source File

SOURCE=.\RibbonListButton.h
# End Source File
# Begin Source File

SOURCE=.\RibbonTableButton.h
# End Source File
# Begin Source File

SOURCE=.\RibbonTooltipCtrl.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\BCGPMSOffice2007Demo.ico
# End Source File
# Begin Source File

SOURCE=.\res\BCGPMSOffice2007Demo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\BCGPMSOffice2007DemoDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\bullets.png
# End Source File
# Begin Source File

SOURCE=.\res\Buttons.png
# End Source File
# Begin Source File

SOURCE=.\res\chart.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ChartDesign.png
# End Source File
# Begin Source File

SOURCE=.\res\ChartDesignLarge.png
# End Source File
# Begin Source File

SOURCE=.\res\ChartFormat.png
# End Source File
# Begin Source File

SOURCE=.\res\ChartFormatLarge.png
# End Source File
# Begin Source File

SOURCE=.\res\ChartLayout.png
# End Source File
# Begin Source File

SOURCE=.\res\ChartLayoutLarge.png
# End Source File
# Begin Source File

SOURCE=.\res\clearall.png
# End Source File
# Begin Source File

SOURCE=.\res\filelarge.png
# End Source File
# Begin Source File

SOURCE=.\res\filesmall.png
# End Source File
# Begin Source File

SOURCE=.\res\HeaderPat_1.png
# End Source File
# Begin Source File

SOURCE=.\res\HeaderPat_2.png
# End Source File
# Begin Source File

SOURCE=.\res\HeaderPat_3.png
# End Source File
# Begin Source File

SOURCE=.\res\HeaderPat_4.png
# End Source File
# Begin Source File

SOURCE=.\res\info.png
# End Source File
# Begin Source File

SOURCE=.\res\Insert.png
# End Source File
# Begin Source File

SOURCE=.\res\InsertLarge.png
# End Source File
# Begin Source File

SOURCE=.\res\layout.png
# End Source File
# Begin Source File

SOURCE=.\res\Mailings.png
# End Source File
# Begin Source File

SOURCE=.\res\MailingsLarge.png
# End Source File
# Begin Source File

SOURCE=.\res\main.png
# End Source File
# Begin Source File

SOURCE=.\res\multi.png
# End Source File
# Begin Source File

SOURCE=.\res\num.png
# End Source File
# Begin Source File

SOURCE=.\res\options.png
# End Source File
# Begin Source File

SOURCE=.\res\PageLayout.png
# End Source File
# Begin Source File

SOURCE=.\res\PageLayoutLarge.png
# End Source File
# Begin Source File

SOURCE=.\res\pasteall.png
# End Source File
# Begin Source File

SOURCE=.\res\picture.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PictureFormat.png
# End Source File
# Begin Source File

SOURCE=.\res\PictureFormatLarge.png
# End Source File
# Begin Source File

SOURCE=.\res\position1.png
# End Source File
# Begin Source File

SOURCE=.\res\position2.png
# End Source File
# Begin Source File

SOURCE=.\res\References.png
# End Source File
# Begin Source File

SOURCE=.\res\ReferencesLarge.png
# End Source File
# Begin Source File

SOURCE=.\res\refresh.ico
# End Source File
# Begin Source File

SOURCE=.\res\Review.png
# End Source File
# Begin Source File

SOURCE=.\res\ReviewLarge.png
# End Source File
# Begin Source File

SOURCE=.\res\shape1.png
# End Source File
# Begin Source File

SOURCE=.\res\Shape2.png
# End Source File
# Begin Source File

SOURCE=.\res\Shape3.png
# End Source File
# Begin Source File

SOURCE=.\res\Shape4.png
# End Source File
# Begin Source File

SOURCE=.\res\Shape5.png
# End Source File
# Begin Source File

SOURCE=.\res\Shape6.png
# End Source File
# Begin Source File

SOURCE=.\res\Shape7.png
# End Source File
# Begin Source File

SOURCE=.\res\spell.ico
# End Source File
# Begin Source File

SOURCE=.\res\spell.png
# End Source File
# Begin Source File

SOURCE=.\res\styles.png
# End Source File
# Begin Source File

SOURCE=.\res\table.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ThemeColors.png
# End Source File
# Begin Source File

SOURCE=.\res\ThemeEffects.png
# End Source File
# Begin Source File

SOURCE=.\res\ThemeFonts.png
# End Source File
# Begin Source File

SOURCE=.\res\ThemeThemes.png
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.png
# End Source File
# Begin Source File

SOURCE=".\res\tooltip-clipboard.png"
# End Source File
# Begin Source File

SOURCE=".\res\tooltip-fontdlg.png"
# End Source File
# Begin Source File

SOURCE=".\res\tooltip-main.png"
# End Source File
# Begin Source File

SOURCE=".\res\tooltip-paragraph.png"
# End Source File
# Begin Source File

SOURCE=.\res\View.png
# End Source File
# Begin Source File

SOURCE=.\res\ViewLarge.png
# End Source File
# Begin Source File

SOURCE=.\res\ViewPat_1.png
# End Source File
# Begin Source File

SOURCE=.\res\ViewPat_2.png
# End Source File
# Begin Source File

SOURCE=.\res\ViewPat_3.png
# End Source File
# Begin Source File

SOURCE=.\res\ViewPat_4.png
# End Source File
# Begin Source File

SOURCE=.\res\Write.png
# End Source File
# Begin Source File

SOURCE=.\res\WriteFont.png
# End Source File
# Begin Source File

SOURCE=.\res\WriteLarge.png
# End Source File
# Begin Source File

SOURCE=.\res\WriteParagraph.png
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
