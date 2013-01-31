# Microsoft Developer Studio Project File - Name="WordPad" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=WordPad - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wordpad.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wordpad.mak" CFG="WordPad - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WordPad - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WordPad - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "WordPad - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "WordPad - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "WordPad - Win32 ReleaseStatic" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WordPad - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
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

!ELSEIF  "$(CFG)" == "WordPad - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W4 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\bin/wordpadd.exe"

!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\WordPad_"
# PROP BASE Intermediate_Dir ".\WordPad_"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin"
# PROP Intermediate_Dir ".\UniRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /out:"..\..\bin/wordpadU.exe"
# SUBTRACT LINK32 /incremental:yes

!ELSEIF  "$(CFG)" == "WordPad - Win32 Unicode Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\WordPad0"
# PROP BASE Intermediate_Dir ".\WordPad0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin"
# PROP Intermediate_Dir ".\UniDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\bin\wordpadUD.exe"

!ELSEIF  "$(CFG)" == "WordPad - Win32 ReleaseStatic"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WordPad___Win32_ReleaseStatic"
# PROP BASE Intermediate_Dir "WordPad___Win32_ReleaseStatic"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\BinStatic"
# PROP Intermediate_Dir "ReleaseStatic"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_BCGCBPRO_STATIC_" /FR /Yu"stdafx.h" /FD /c
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

# Name "WordPad - Win32 Release"
# Name "WordPad - Win32 Debug"
# Name "WordPad - Win32 Unicode Release"
# Name "WordPad - Win32 Unicode Debug"
# Name "WordPad - Win32 ReleaseStatic"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\AppLookDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\buttondi.cpp
# End Source File
# Begin Source File

SOURCE=.\chicdial.cpp
# End Source File
# Begin Source File

SOURCE=.\cntritem.cpp
# End Source File
# Begin Source File

SOURCE=.\datedial.cpp
# End Source File
# Begin Source File

SOURCE=.\ddxm.cpp
# End Source File
# Begin Source File

SOURCE=.\docopt.cpp
# End Source File
# Begin Source File

SOURCE=.\doctype.cpp
# End Source File
# Begin Source File

SOURCE=.\filenewd.cpp
# End Source File
# Begin Source File

SOURCE=.\formatba.cpp
# End Source File
# Begin Source File

SOURCE=.\formatpa.cpp
# End Source File
# Begin Source File

SOURCE=.\formatta.cpp
# End Source File
# Begin Source File

SOURCE=.\ipframe.cpp
# End Source File
# Begin Source File

SOURCE=.\key.cpp
# End Source File
# Begin Source File

SOURCE=.\listdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\mainfrm.cpp
# End Source File
# Begin Source File

SOURCE=.\multconv.cpp
# End Source File
# Begin Source File

SOURCE=.\options.cpp
# End Source File
# Begin Source File

SOURCE=.\optionsh.cpp
# End Source File
# Begin Source File

SOURCE=.\pageset.cpp
# End Source File
# Begin Source File

SOURCE=.\ruler.cpp
# End Source File
# Begin Source File

SOURCE=.\splash.cpp
# End Source File
# Begin Source File

SOURCE=.\srvritem.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\strings.cpp
# End Source File
# Begin Source File

SOURCE=.\TaskPane.cpp
# End Source File
# Begin Source File

SOURCE=.\unitspag.cpp
# End Source File
# Begin Source File

SOURCE=.\wordpad.cpp
# End Source File
# Begin Source File

SOURCE=.\wordpad.rc
# End Source File
# Begin Source File

SOURCE=.\wordpdoc.cpp
# End Source File
# Begin Source File

SOURCE=.\wordpvw.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;inl;fi;fd"
# Begin Source File

SOURCE=.\AppLookDlg.h
# End Source File
# Begin Source File

SOURCE=.\buttondi.h
# End Source File
# Begin Source File

SOURCE=.\chicdial.h
# End Source File
# Begin Source File

SOURCE=.\cntritem.h
# End Source File
# Begin Source File

SOURCE=.\datedial.h
# End Source File
# Begin Source File

SOURCE=.\ddxm.h
# End Source File
# Begin Source File

SOURCE=.\docopt.h
# End Source File
# Begin Source File

SOURCE=.\doctype.h
# End Source File
# Begin Source File

SOURCE=.\filenewd.h
# End Source File
# Begin Source File

SOURCE=.\formatba.h
# End Source File
# Begin Source File

SOURCE=.\formatpa.h
# End Source File
# Begin Source File

SOURCE=.\formatta.h
# End Source File
# Begin Source File

SOURCE=.\helpids.h
# End Source File
# Begin Source File

SOURCE=.\ipframe.h
# End Source File
# Begin Source File

SOURCE=.\key.h
# End Source File
# Begin Source File

SOURCE=.\listdlg.h
# End Source File
# Begin Source File

SOURCE=.\mainfrm.h
# End Source File
# Begin Source File

SOURCE=.\mswd6_32.h
# End Source File
# Begin Source File

SOURCE=.\multconv.h
# End Source File
# Begin Source File

SOURCE=.\options.h
# End Source File
# Begin Source File

SOURCE=.\optionsh.h
# End Source File
# Begin Source File

SOURCE=.\pageset.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\ruler.h
# End Source File
# Begin Source File

SOURCE=.\splash.h
# End Source File
# Begin Source File

SOURCE=.\srvritem.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\strings.h
# End Source File
# Begin Source File

SOURCE=.\TaskPane.h
# End Source File
# Begin Source File

SOURCE=.\unitspag.h
# End Source File
# Begin Source File

SOURCE=.\wordpad.h
# End Source File
# Begin Source File

SOURCE=.\wordpdoc.h
# End Source File
# Begin Source File

SOURCE=.\wordpvw.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\border_type.bmp
# End Source File
# Begin Source File

SOURCE=.\res\font.bmp
# End Source File
# Begin Source File

SOURCE=.\res\formatba.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\full_scr.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\iconnote.ico
# End Source File
# Begin Source File

SOURCE=.\Res\logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\main1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\mainfram_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rtfdoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\rulerbl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rulerblm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rulerdo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rulerdom.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rulerta.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rulertam.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rulerup.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rulerupm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\srvr.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\tasks.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\tasks_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\taskspanetoolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\textdoc.ico
# End Source File
# Begin Source File

SOURCE=.\RES\toolbar_images.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\toolbar_images_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wordp48.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wordpad.ico
# End Source File
# Begin Source File

SOURCE=.\res\wordpad.rc2
# End Source File
# Begin Source File

SOURCE=.\res\write.ico
# End Source File
# Begin Source File

SOURCE=.\xptheme.bin
# End Source File
# End Group
# End Target
# End Project
