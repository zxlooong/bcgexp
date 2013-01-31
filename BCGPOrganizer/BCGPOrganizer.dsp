# Microsoft Developer Studio Project File - Name="BCGPOrganizer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BCGPOrganizer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BCGPOrganizer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BCGPOrganizer.mak" CFG="BCGPOrganizer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BCGPOrganizer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BCGPOrganizer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "BCGPOrganizer - Win32 ReleaseStatic" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BCGPOrganizer - Win32 Release"

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

!ELSEIF  "$(CFG)" == "BCGPOrganizer - Win32 Debug"

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
# ADD LINK32 /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"../../bin/BCGPOrganizerD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "BCGPOrganizer - Win32 ReleaseStatic"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BCGPOrganizer___Win32_ReleaseStatic"
# PROP BASE Intermediate_Dir "BCGPOrganizer___Win32_ReleaseStatic"
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

!ENDIF 

# Begin Target

# Name "BCGPOrganizer - Win32 Release"
# Name "BCGPOrganizer - Win32 Debug"
# Name "BCGPOrganizer - Win32 ReleaseStatic"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BCGPOrganizer.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPOrganizer.rc
# End Source File
# Begin Source File

SOURCE=.\BCGPOrganizerDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPOrganizerView.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBanner.cpp
# End Source File
# Begin Source File

SOURCE=.\EditDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\EditFrameDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\EditFrameView.cpp
# End Source File
# Begin Source File

SOURCE=.\FrameDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GlobalData.cpp
# End Source File
# Begin Source File

SOURCE=.\keys.cpp
# End Source File
# Begin Source File

SOURCE=.\MainButtonsGroup.cpp
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

SOURCE=.\BCGPOrganizer.h
# End Source File
# Begin Source File

SOURCE=.\BCGPOrganizerDoc.h
# End Source File
# Begin Source File

SOURCE=.\BCGPOrganizerView.h
# End Source File
# Begin Source File

SOURCE=.\DlgBanner.h
# End Source File
# Begin Source File

SOURCE=.\EditDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\EditFrameDialog.h
# End Source File
# Begin Source File

SOURCE=.\EditFrameView.h
# End Source File
# Begin Source File

SOURCE=.\FrameDialog.h
# End Source File
# Begin Source File

SOURCE=.\GlobalData.h
# End Source File
# Begin Source File

SOURCE=.\keys.h
# End Source File
# Begin Source File

SOURCE=.\MainButtonsGroup.h
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

SOURCE=.\RibbonTooltipCtrl.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Group "Planner_res"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\Planner\buttons.png
# End Source File
# Begin Source File

SOURCE=.\res\Planner\Clock_Clock.png
# End Source File
# Begin Source File

SOURCE=.\res\Planner\Clock_Hours.PNG
# End Source File
# Begin Source File

SOURCE=.\res\Planner\Clock_Minutes.png
# End Source File
# Begin Source File

SOURCE=.\res\Planner\file_large.png
# End Source File
# Begin Source File

SOURCE=.\res\Planner\file_small.png
# End Source File
# Begin Source File

SOURCE=.\res\Planner\frame.ico
# End Source File
# Begin Source File

SOURCE=.\res\Planner\home_large.png
# End Source File
# Begin Source File

SOURCE=.\res\Planner\home_small.png
# End Source File
# Begin Source File

SOURCE=.\res\Planner\icons.BMP
# End Source File
# Begin Source File

SOURCE=.\res\Planner\prntype_1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Planner\prntype_2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Planner\prntype_3.ico
# End Source File
# Begin Source File

SOURCE=.\res\Planner\prntype_4.ico
# End Source File
# Begin Source File

SOURCE=.\res\Planner\ribbon_large.png
# End Source File
# Begin Source File

SOURCE=.\res\Planner\ribbon_small.png
# End Source File
# Begin Source File

SOURCE=.\res\Planner\security.ico
# End Source File
# Begin Source File

SOURCE=.\res\Planner\toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Planner\toolbar_hc.png
# End Source File
# Begin Source File

SOURCE=.\res\Planner\users.ico
# End Source File
# End Group
# Begin Group "Mail_res"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\Mail\buttons.png
# End Source File
# Begin Source File

SOURCE=.\res\Mail\file_large.png
# End Source File
# Begin Source File

SOURCE=.\res\Mail\file_small.png
# End Source File
# Begin Source File

SOURCE=.\res\Mail\Flags.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Mail\folders.BMP
# End Source File
# Begin Source File

SOURCE=.\res\Mail\frame.ico
# End Source File
# Begin Source File

SOURCE=.\res\Mail\header.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Mail\home_large.png
# End Source File
# Begin Source File

SOURCE=.\res\Mail\home_small.png
# End Source File
# Begin Source File

SOURCE=.\res\Mail\icons.BMP
# End Source File
# Begin Source File

SOURCE=.\res\Mail\options_large.png
# End Source File
# Begin Source File

SOURCE=.\res\Mail\options_small.PNG
# End Source File
# Begin Source File

SOURCE=.\res\Mail\ribbon_large.png
# End Source File
# Begin Source File

SOURCE=.\res\Mail\ribbon_small.png
# End Source File
# End Group
# Begin Group "Tooltip_res"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\Tooltip\Font.png
# End Source File
# Begin Source File

SOURCE=.\res\Tooltip\Main.png
# End Source File
# End Group
# Begin Group "MacrosEdit_res"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\MacrosEdit\Accessibility.bas
# End Source File
# Begin Source File

SOURCE=.\res\MacrosEdit\AddDirAsSlnFolder.bas
# End Source File
# Begin Source File

SOURCE=.\res\MacrosEdit\bcgpedit.xml
# End Source File
# Begin Source File

SOURCE=.\res\MacrosEdit\DevStudio6Editor.bas
# End Source File
# Begin Source File

SOURCE=.\res\MacrosEdit\EnvironmentEvents.bas
# End Source File
# Begin Source File

SOURCE=.\res\MacrosEdit\folders.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MacrosEdit\font.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MacrosEdit\font_hc.png
# End Source File
# Begin Source File

SOURCE=.\res\MacrosEdit\intellisense.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MacrosEdit\intellisense_hc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MacrosEdit\MakeAddin.bas
# End Source File
# Begin Source File

SOURCE=.\res\MacrosEdit\ribbon_large.png
# End Source File
# Begin Source File

SOURCE=.\res\MacrosEdit\ribbon_small.png
# End Source File
# Begin Source File

SOURCE=.\res\MacrosEdit\Utilities.bas
# End Source File
# Begin Source File

SOURCE=.\res\MacrosEdit\VSDebugger.bas
# End Source File
# Begin Source File

SOURCE=.\res\MacrosEdit\VSEditor.bas
# End Source File
# End Group
# Begin Group "Tasks_res"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\Tasks\frame.ico
# End Source File
# Begin Source File

SOURCE=.\res\Tasks\header.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Tasks\icons.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Tasks\ribbon_large.png
# End Source File
# Begin Source File

SOURCE=.\res\Tasks\ribbon_small.png
# End Source File
# End Group
# Begin Group "Shortcuts_res"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\Shortcuts\ribbon_large.png
# End Source File
# Begin Source File

SOURCE=.\res\Shortcuts\ribbon_small.png
# End Source File
# End Group
# Begin Group "Gantt_res"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\Gantt\buttons.png
# End Source File
# Begin Source File

SOURCE=.\res\Gantt\complete.ico
# End Source File
# Begin Source File

SOURCE=.\res\Gantt\file_large.png
# End Source File
# Begin Source File

SOURCE=.\res\Gantt\file_small.png
# End Source File
# Begin Source File

SOURCE=.\res\Gantt\frame.ico
# End Source File
# Begin Source File

SOURCE=.\res\Gantt\home_large.png
# End Source File
# Begin Source File

SOURCE=.\res\Gantt\home_small.png
# End Source File
# Begin Source File

SOURCE=.\res\Gantt\milestone.ico
# End Source File
# Begin Source File

SOURCE=.\res\Gantt\milestone_c.ico
# End Source File
# Begin Source File

SOURCE=.\res\Gantt\ribbon_large.png
# End Source File
# Begin Source File

SOURCE=.\res\Gantt\ribbon_small.png
# End Source File
# Begin Source File

SOURCE=.\res\Gantt\toolbar_hc.png
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\BCGPOrganizer.ico
# End Source File
# Begin Source File

SOURCE=.\res\BCGPOrganizer.rc2
# End Source File
# Begin Source File

SOURCE=.\res\BCGPOrganizerDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\buttons.png
# End Source File
# Begin Source File

SOURCE=.\res\caption.bmp
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\res\category.bmp
# End Source File
# Begin Source File

SOURCE=.\res\category_hc.png
# End Source File
# Begin Source File

SOURCE=.\res\edit_large.png
# End Source File
# Begin Source File

SOURCE=.\res\edit_small.png
# End Source File
# Begin Source File

SOURCE=.\res\file_large.png
# End Source File
# Begin Source File

SOURCE=.\res\file_small.png
# End Source File
# Begin Source File

SOURCE=.\res\font_hc.png
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

SOURCE=.\res\home.png
# End Source File
# Begin Source File

SOURCE=.\res\main.png
# End Source File
# Begin Source File

SOURCE=.\res\options.png
# End Source File
# Begin Source File

SOURCE=.\res\refresh.ico
# End Source File
# Begin Source File

SOURCE=.\res\Mail\send.bmp
# End Source File
# Begin Source File

SOURCE=.\res\shortcuts_large.png
# End Source File
# Begin Source File

SOURCE=.\res\shortcuts_small.png
# End Source File
# Begin Source File

SOURCE=.\res\showas.bmp
# End Source File
# Begin Source File

SOURCE=.\res\showas_hc.png
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

SOURCE=.\res\Gantt\toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar_hc.png
# End Source File
# End Group
# Begin Group "Planner"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Planner\Appointment.cpp
# End Source File
# Begin Source File

SOURCE=.\Planner\Appointment.h
# End Source File
# Begin Source File

SOURCE=.\Planner\AppointmentFrame.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Planner\AppointmentFrame.h
# End Source File
# Begin Source File

SOURCE=.\Planner\GotoDayDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Planner\GotoDayDialog.h
# End Source File
# Begin Source File

SOURCE=.\Planner\PlannerClockIcons.cpp
# End Source File
# Begin Source File

SOURCE=.\Planner\PlannerClockIcons.h
# End Source File
# Begin Source File

SOURCE=.\Planner\PlannerTooltipCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Planner\PlannerTooltipCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Planner\PrintTypeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Planner\PrintTypeDlg.h
# End Source File
# Begin Source File

SOURCE=.\Planner\RecurrenceConfirmDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Planner\RecurrenceConfirmDlg.h
# End Source File
# Begin Source File

SOURCE=.\Planner\RecurrenceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Planner\RecurrenceDlg.h
# End Source File
# Begin Source File

SOURCE=.\Planner\RecurrenceRuleDailyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Planner\RecurrenceRuleDailyDlg.h
# End Source File
# Begin Source File

SOURCE=.\Planner\RecurrenceRuleDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Planner\RecurrenceRuleDlg.h
# End Source File
# Begin Source File

SOURCE=.\Planner\RecurrenceRuleMonthlyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Planner\RecurrenceRuleMonthlyDlg.h
# End Source File
# Begin Source File

SOURCE=.\Planner\RecurrenceRuleWeeklyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Planner\RecurrenceRuleWeeklyDlg.h
# End Source File
# Begin Source File

SOURCE=.\Planner\RecurrenceRuleYearlyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Planner\RecurrenceRuleYearlyDlg.h
# End Source File
# End Group
# Begin Group "Views"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Views\CalendarPlannerView.cpp
# End Source File
# Begin Source File

SOURCE=.\Views\CalendarPlannerView.h
# End Source File
# Begin Source File

SOURCE=.\Views\GanttView.cpp
# End Source File
# Begin Source File

SOURCE=.\Views\GanttView.h
# End Source File
# Begin Source File

SOURCE=.\Views\MacrosEditView.cpp
# End Source File
# Begin Source File

SOURCE=.\Views\MacrosEditView.h
# End Source File
# Begin Source File

SOURCE=.\Views\MailView.cpp
# End Source File
# Begin Source File

SOURCE=.\Views\MailView.h
# End Source File
# Begin Source File

SOURCE=.\Views\ShortcutsView.cpp
# End Source File
# Begin Source File

SOURCE=.\Views\ShortcutsView.h
# End Source File
# Begin Source File

SOURCE=.\Views\TasksView.cpp
# End Source File
# Begin Source File

SOURCE=.\Views\TasksView.h
# End Source File
# End Group
# Begin Group "Bars"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CalendarBar.cpp
# End Source File
# Begin Source File

SOURCE=.\CalendarBar.h
# End Source File
# Begin Source File

SOURCE=.\GanttBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GanttBar.h
# End Source File
# Begin Source File

SOURCE=.\MacrosBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MacrosBar.h
# End Source File
# Begin Source File

SOURCE=.\MailBar.cpp
# End Source File
# Begin Source File

SOURCE=.\MailBar.h
# End Source File
# Begin Source File

SOURCE=.\OutlookBar.cpp
# End Source File
# Begin Source File

SOURCE=.\OutlookBar.h
# End Source File
# Begin Source File

SOURCE=.\OutputBar.cpp
# End Source File
# Begin Source File

SOURCE=.\OutputBar.h
# End Source File
# Begin Source File

SOURCE=.\ShortcutsBar.cpp
# End Source File
# Begin Source File

SOURCE=.\ShortcutsBar.h
# End Source File
# Begin Source File

SOURCE=.\TasksBar.cpp
# End Source File
# Begin Source File

SOURCE=.\TasksBar.h
# End Source File
# End Group
# Begin Group "MacrosEdit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MacrosEdit\CustomEditCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\MacrosEdit\CustomEditCtrl.h
# End Source File
# Begin Source File

SOURCE=.\MacrosEdit\GotoLineDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MacrosEdit\GotoLineDlg.h
# End Source File
# End Group
# Begin Group "Mail"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Mail\MailFrame.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\Mail\MailFrame.h
# End Source File
# Begin Source File

SOURCE=.\Mail\MailReportCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Mail\MailReportCtrl.h
# End Source File
# End Group
# Begin Group "Tasks"

# PROP Default_Filter ""
# End Group
# Begin Group "Gantt"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Gantt\GanttFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\Gantt\GanttFrame.h
# End Source File
# Begin Source File

SOURCE=.\Gantt\GanttTooltipCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\Gantt\GanttTooltipCtrl.h
# End Source File
# Begin Source File

SOURCE=.\Gantt\GotoDayDialog2.cpp
# End Source File
# Begin Source File

SOURCE=.\Gantt\GotoDayDialog2.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\xptheme.xml
# End Source File
# End Target
# End Project
