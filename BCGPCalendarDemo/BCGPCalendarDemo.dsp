# Microsoft Developer Studio Project File - Name="BCGPCalendarDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BCGPCalendarDemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BCGPCalendarDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BCGPCalendarDemo.mak" CFG="BCGPCalendarDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BCGPCalendarDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BCGPCalendarDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "BCGPCalendarDemo - Win32 ReleaseStatic" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BCGPCalendarDemo - Win32 Release"

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

!ELSEIF  "$(CFG)" == "BCGPCalendarDemo - Win32 Debug"

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
# ADD LINK32 /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\Bin/BCGPCalendarDemoD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "BCGPCalendarDemo - Win32 ReleaseStatic"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BCGPCalendarDemo___Win32_ReleaseStatic"
# PROP BASE Intermediate_Dir "BCGPCalendarDemo___Win32_ReleaseStatic"
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

# Name "BCGPCalendarDemo - Win32 Release"
# Name "BCGPCalendarDemo - Win32 Debug"
# Name "BCGPCalendarDemo - Win32 ReleaseStatic"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AppointmentDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPAppointmentDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPCalendarDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPCalendarDemo.rc
# End Source File
# Begin Source File

SOURCE=.\BCGPCalendarDemoDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPCalendarDemoView.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPPlannerClockIconsDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\CalendarBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GotoDayDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\PlannerTooltipCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintTypeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyBar.cpp
# End Source File
# Begin Source File

SOURCE=.\RecurrenceConfirmDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RecurrenceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RecurrenceRuleDailyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RecurrenceRuleDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RecurrenceRuleMonthlyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RecurrenceRuleWeeklyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RecurrenceRuleYearlyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ResourceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AppointmentDlg.h
# End Source File
# Begin Source File

SOURCE=.\BCGPAppointmentDemo.h
# End Source File
# Begin Source File

SOURCE=.\BCGPCalendarDemo.h
# End Source File
# Begin Source File

SOURCE=.\BCGPCalendarDemoDoc.h
# End Source File
# Begin Source File

SOURCE=.\BCGPCalendarDemoView.h
# End Source File
# Begin Source File

SOURCE=.\BCGPPlannerClockIconsDemo.h
# End Source File
# Begin Source File

SOURCE=.\CalendarBar.h
# End Source File
# Begin Source File

SOURCE=.\ColorComboBox.h
# End Source File
# Begin Source File

SOURCE=.\GotoDayDialog.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PlannerTooltipCtrl.h
# End Source File
# Begin Source File

SOURCE=.\PrintTypeDlg.h
# End Source File
# Begin Source File

SOURCE=.\PropertyBar.h
# End Source File
# Begin Source File

SOURCE=.\RecurrenceConfirmDlg.h
# End Source File
# Begin Source File

SOURCE=.\RecurrenceDlg.h
# End Source File
# Begin Source File

SOURCE=.\RecurrenceRuleDailyDlg.h
# End Source File
# Begin Source File

SOURCE=.\RecurrenceRuleDlg.h
# End Source File
# Begin Source File

SOURCE=.\RecurrenceRuleMonthlyDlg.h
# End Source File
# Begin Source File

SOURCE=.\RecurrenceRuleWeeklyDlg.h
# End Source File
# Begin Source File

SOURCE=.\RecurrenceRuleYearlyDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ResourceDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\BCGPCalendarDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\BCGPCalendarDemo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\BCGPCalendarDemoDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\calendar_icons.BMP
# End Source File
# Begin Source File

SOURCE=.\res\caption.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Clock_Clock.png
# End Source File
# Begin Source File

SOURCE=.\res\Clock_Hours.PNG
# End Source File
# Begin Source File

SOURCE=.\res\Clock_Minutes.png
# End Source File
# Begin Source File

SOURCE=.\res\plan_d_tb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\plan_d_tb256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\plan_tb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\plan_tb256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\planmulti_tb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\planmulti_tb256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\prntype_1.ico
# End Source File
# Begin Source File

SOURCE=.\res\prntype_2.ico
# End Source File
# Begin Source File

SOURCE=.\res\prntype_3.ico
# End Source File
# Begin Source File

SOURCE=.\res\prntype_4.ico
# End Source File
# Begin Source File

SOURCE=.\res\security.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\users.ico
# End Source File
# Begin Source File

SOURCE=.\res\workspace.bmp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
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
