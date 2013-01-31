# Microsoft Developer Studio Project File - Name="BCGPVisualStudioGUIDemoStatic" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BCGPVisualStudioGUIDemoStatic - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BCGPVisualStudioGUIDemoStatic.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BCGPVisualStudioGUIDemoStatic.mak" CFG="BCGPVisualStudioGUIDemoStatic - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BCGPVisualStudioGUIDemoStatic - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BCGPVisualStudioGUIDemoStatic - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BCGPVisualStudioGUIDemoStatic - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "ReleaseStatic"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_BCGCBPRO_STATIC_" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\BCGCBPro\Styles\Office 2007 (luna - blue)\\" /i "..\..\BCGCBPro\Styles" /d "NDEBUG" /d "_AFXDLL" /d "_BCGCBPRO_STATIC_"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /pdb:"..\..\bin/BCGPVisualStudioGUIDemoS.pdb" /machine:I386 /out:"..\..\bin/BCGPVisualStudioGUIDemoS.exe"

!ELSEIF  "$(CFG)" == "BCGPVisualStudioGUIDemoStatic - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\bin"
# PROP Intermediate_Dir "DebugStatic"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_BCGCBPRO_STATIC_" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\BCGCBPro\Styles" /d "_DEBUG" /d "_AFXDLL" /d "_BCGCBPRO_STATIC_"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /pdb:"..\..\bin/BCGPVisualStudioGUIDemoSD.pdb" /debug /machine:I386 /out:"..\..\bin/BCGPVisualStudioGUIDemoSD.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "BCGPVisualStudioGUIDemoStatic - Win32 Release"
# Name "BCGPVisualStudioGUIDemoStatic - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AppLookDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPVisualStudioGUIDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPVisualStudioGUIDemo.rc
# End Source File
# Begin Source File

SOURCE=.\BCGPVisualStudioGUIDemoDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPVisualStudioGUIDemoView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassTreeWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ClassViewBar.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DynamicHelpView.cpp
# End Source File
# Begin Source File

SOURCE=.\FileViewBar.cpp
# End Source File
# Begin Source File

SOURCE=.\FindComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GotoLineDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsPages.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputView.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertiesViewBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ResourceView.cpp
# End Source File
# Begin Source File

SOURCE=.\StartView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ToolBox.cpp
# End Source File
# Begin Source File

SOURCE=.\UndoBar.cpp
# End Source File
# Begin Source File

SOURCE=.\UndoListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\WatchBar.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AppLookDlg.h
# End Source File
# Begin Source File

SOURCE=.\BCGPVisualStudioGUIDemo.h
# End Source File
# Begin Source File

SOURCE=.\BCGPVisualStudioGUIDemoDoc.h
# End Source File
# Begin Source File

SOURCE=.\BCGPVisualStudioGUIDemoView.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ClassTreeWnd.h
# End Source File
# Begin Source File

SOURCE=.\ClassViewBar.h
# End Source File
# Begin Source File

SOURCE=.\CustomEditCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DynamicHelpView.h
# End Source File
# Begin Source File

SOURCE=.\FileViewBar.h
# End Source File
# Begin Source File

SOURCE=.\FindComboBox.h
# End Source File
# Begin Source File

SOURCE=.\GotoLineDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\OptionsDlg.h
# End Source File
# Begin Source File

SOURCE=.\OptionsPages.h
# End Source File
# Begin Source File

SOURCE=.\OutputView.h
# End Source File
# Begin Source File

SOURCE=.\PropertiesViewBar.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ResourceView.h
# End Source File
# Begin Source File

SOURCE=.\StartView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ToolBox.h
# End Source File
# Begin Source File

SOURCE=.\UndoBar.h
# End Source File
# Begin Source File

SOURCE=.\UndoListBox.h
# End Source File
# Begin Source File

SOURCE=.\WatchBar.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Group "Examples"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\res\Examples\bcgpedit-cpp.xml"
# End Source File
# Begin Source File

SOURCE=".\res\Examples\bcgpedit-web.xml"
# End Source File
# Begin Source File

SOURCE=.\res\Examples\example.asp
# End Source File
# Begin Source File

SOURCE=.\res\Examples\Example.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\BCGPVisualStudioGUIDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\BCGPVisualStudioGUIDemo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\BCGPVisualStudioGUIDemoDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\break.bmp
# End Source File
# Begin Source File

SOURCE=.\res\build.bmp
# End Source File
# Begin Source File

SOURCE=.\res\build_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\class_view.bmp
# End Source File
# Begin Source File

SOURCE=.\res\class_view.ico
# End Source File
# Begin Source File

SOURCE=.\res\class_view_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\class_view_hc.ico
# End Source File
# Begin Source File

SOURCE=.\res\cpp.ico
# End Source File
# Begin Source File

SOURCE=.\res\current.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dynamichelp_bar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dynamichelp_bar_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dynamichelp_view.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dynamichelp_view.ico
# End Source File
# Begin Source File

SOURCE=.\res\dynamichelp_view_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dynamichelp_view_hc.ico
# End Source File
# Begin Source File

SOURCE=.\res\edit.bmp
# End Source File
# Begin Source File

SOURCE=.\res\edit_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\file_view.bmp
# End Source File
# Begin Source File

SOURCE=.\res\file_view.ico
# End Source File
# Begin Source File

SOURCE=.\res\file_view_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\file_view_hc.ico
# End Source File
# Begin Source File

SOURCE=.\res\intellisense.bmp
# End Source File
# Begin Source File

SOURCE=.\res\intellisense_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\menuimages.bmp
# End Source File
# Begin Source File

SOURCE=.\res\menuimages_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\optionsimages.bmp
# End Source File
# Begin Source File

SOURCE=.\res\output_bar.ico
# End Source File
# Begin Source File

SOURCE=.\res\output_bar_hc.ico
# End Source File
# Begin Source File

SOURCE=.\res\properties_bar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\properties_bar.ico
# End Source File
# Begin Source File

SOURCE=.\res\properties_bar_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\properties_bar_hc.ico
# End Source File
# Begin Source File

SOURCE=.\res\resource_view.bmp
# End Source File
# Begin Source File

SOURCE=.\res\resource_view.ico
# End Source File
# Begin Source File

SOURCE=.\res\resource_view_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\resource_view_hc.ico
# End Source File
# Begin Source File

SOURCE=.\res\solution_bar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\solution_bar_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sort.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sort_hc.bmp
# End Source File
# Begin Source File

SOURCE=".\res\start-hot.psd"
# End Source File
# Begin Source File

SOURCE=.\res\start.bmp
# End Source File
# Begin Source File

SOURCE=.\res\start.psd
# End Source File
# Begin Source File

SOURCE=.\res\start_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_res.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_res_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbox.ico
# End Source File
# Begin Source File

SOURCE=.\res\toolbox_hc.ico
# End Source File
# Begin Source File

SOURCE=.\res\tools_page1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tools_page1_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tools_page2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tools_page2_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tools_page3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tools_page3_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\watch_bar.ico
# End Source File
# Begin Source File

SOURCE=.\res\watch_bar_hc.ico
# End Source File
# Begin Source File

SOURCE=.\res\web.ico
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
