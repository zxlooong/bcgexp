# Microsoft Developer Studio Project File - Name="BCGPMediaPlayer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BCGPMediaPlayer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BCGPMediaPlayer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BCGPMediaPlayer.mak" CFG="BCGPMediaPlayer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BCGPMediaPlayer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BCGPMediaPlayer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "BCGPMediaPlayer - Win32 ReleaseStatic" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BCGPMediaPlayer - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\bin"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 vfw32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "BCGPMediaPlayer - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\bin"
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
# ADD LINK32 vfw32.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\bin/BCGPMediaPlayerD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "BCGPMediaPlayer - Win32 ReleaseStatic"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BCGPMediaPlayer___Win32_ReleaseStatic"
# PROP BASE Intermediate_Dir "BCGPMediaPlayer___Win32_ReleaseStatic"
# PROP BASE Ignore_Export_Lib 0
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
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL" /d "_BCGCBPRO_STATIC_"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 vfw32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 vfw32.lib /nologo /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "BCGPMediaPlayer - Win32 Release"
# Name "BCGPMediaPlayer - Win32 Debug"
# Name "BCGPMediaPlayer - Win32 ReleaseStatic"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BCGPMediaPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMediaPlayer.rc
# End Source File
# Begin Source File

SOURCE=.\BCGPMediaPlayerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPMediaPlayerView.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorChooserBar.cpp
# End Source File
# Begin Source File

SOURCE=.\EqualizerBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ExplorerBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MCIControl.cpp
# End Source File
# Begin Source File

SOURCE=.\NavigationBar.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
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

SOURCE=.\BCGPMediaPlayer.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMediaPlayerDoc.h
# End Source File
# Begin Source File

SOURCE=.\BCGPMediaPlayerView.h
# End Source File
# Begin Source File

SOURCE=.\ColorChooserBar.h
# End Source File
# Begin Source File

SOURCE=.\EqualizerBar.h
# End Source File
# Begin Source File

SOURCE=.\ExplorerBar.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MCIControl.h
# End Source File
# Begin Source File

SOURCE=.\NavigationBar.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
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
# Begin Source File

SOURCE=.\res\backExplorer.png
# End Source File
# Begin Source File

SOURCE=.\res\backNavi1.png
# End Source File
# Begin Source File

SOURCE=.\res\backNavi1Ctrl.png
# End Source File
# Begin Source File

SOURCE=.\res\backNavi1CtrlA.png
# End Source File
# Begin Source File

SOURCE=.\res\backNavi2.png
# End Source File
# Begin Source File

SOURCE=.\res\backNavi2Ctrl.png
# End Source File
# Begin Source File

SOURCE=.\res\backNavi2CtrlA.png
# End Source File
# Begin Source File

SOURCE=.\res\backProgress.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGPMediaPlayer.ico
# End Source File
# Begin Source File

SOURCE=.\res\BCGPMediaPlayer.rc2
# End Source File
# Begin Source File

SOURCE=.\res\BCGPMediaPlayerDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\borderCaption.png
# End Source File
# Begin Source File

SOURCE=.\res\borderCaptionB.png
# End Source File
# Begin Source File

SOURCE=.\res\borderCaptionM.png
# End Source File
# Begin Source File

SOURCE=.\res\borderCaptionMB.png
# End Source File
# Begin Source File

SOURCE=.\res\borderExplorerL.png
# End Source File
# Begin Source File

SOURCE=.\res\borderExplorerR.png
# End Source File
# Begin Source File

SOURCE=.\res\borderL.png
# End Source File
# Begin Source File

SOURCE=.\res\borderM.png
# End Source File
# Begin Source File

SOURCE=.\res\borderNavi1B.png
# End Source File
# Begin Source File

SOURCE=.\res\borderNavi1L.png
# End Source File
# Begin Source File

SOURCE=.\res\borderNavi1R.png
# End Source File
# Begin Source File

SOURCE=.\res\borderNavi2B.png
# End Source File
# Begin Source File

SOURCE=.\res\borderNavi2BCtrl.png
# End Source File
# Begin Source File

SOURCE=.\res\borderNavi2L.png
# End Source File
# Begin Source File

SOURCE=.\res\borderNavi2R.png
# End Source File
# Begin Source File

SOURCE=.\res\borderR.png
# End Source File
# Begin Source File

SOURCE=.\res\btnBarNext.png
# End Source File
# Begin Source File

SOURCE=.\res\btnBarPrev.png
# End Source File
# Begin Source File

SOURCE=.\res\btnCaptionClose.png
# End Source File
# Begin Source File

SOURCE=.\res\btnExplorer.png
# End Source File
# Begin Source File

SOURCE=.\res\btnExplorerBF.png
# End Source File
# Begin Source File

SOURCE=.\res\btnExplorerFrameBF.png
# End Source File
# Begin Source File

SOURCE=.\res\btnExplorerLogo.png
# End Source File
# Begin Source File

SOURCE=.\res\btnExplorerSep.png
# End Source File
# Begin Source File

SOURCE=.\res\btnNext.png
# End Source File
# Begin Source File

SOURCE=.\res\btnNormal.png
# End Source File
# Begin Source File

SOURCE=.\res\btnPlay.png
# End Source File
# Begin Source File

SOURCE=.\res\btnPrev.png
# End Source File
# Begin Source File

SOURCE=.\res\btnSplit.png
# End Source File
# Begin Source File

SOURCE=.\res\btnSplitM.png
# End Source File
# Begin Source File

SOURCE=.\res\btnSys.png
# End Source File
# Begin Source File

SOURCE=.\res\btnSys1.png
# End Source File
# Begin Source File

SOURCE=.\res\btnSys2.png
# End Source File
# Begin Source File

SOURCE=.\res\btnSys3.png
# End Source File
# Begin Source File

SOURCE=.\res\channelEqV.png
# End Source File
# Begin Source File

SOURCE=.\res\iconArrowDown.png
# End Source File
# Begin Source File

SOURCE=.\res\iconClose.png
# End Source File
# Begin Source File

SOURCE=.\res\iconMaximize.png
# End Source File
# Begin Source File

SOURCE=.\res\iconMinimize.png
# End Source File
# Begin Source File

SOURCE=.\res\iconNext.png
# End Source File
# Begin Source File

SOURCE=.\res\iconPlay.png
# End Source File
# Begin Source File

SOURCE=.\res\iconPlayH.png
# End Source File
# Begin Source File

SOURCE=.\res\iconPrev.png
# End Source File
# Begin Source File

SOURCE=.\res\iconProgress.png
# End Source File
# Begin Source File

SOURCE=.\res\iconProgressR.png
# End Source File
# Begin Source File

SOURCE=.\res\iconRestore.png
# End Source File
# Begin Source File

SOURCE=.\res\iconSound.png
# End Source File
# Begin Source File

SOURCE=.\res\iconStop.png
# End Source File
# Begin Source File

SOURCE=.\res\thumbB.png
# End Source File
# Begin Source File

SOURCE=.\res\thumbV.png
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
