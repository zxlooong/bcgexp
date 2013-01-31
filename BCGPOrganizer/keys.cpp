//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2008 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// keys.cpp:
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BCGPOrganizer.h"
#include "keys.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BCGPKey stdKeys [] =
{
	//-------------
	// Tab buttons:
	//-------------

	{    ID_APP_ABOUT, _T("a")    },
	{    ID_VIEW_APPLOOK, _T("s")    },

	//-----------
	// Main menu:
	//-----------

	{    ID_FILE_PRINT, _T("p&w")    },

	//-------------
	// "Home" keys:
	//-------------

	// 1. Edit:
	{    ID_EDIT_PASTE, _T("v")    },
	{    ID_EDIT_COPY, _T("c")    },
	{    ID_EDIT_CUT, _T("x")    },
    {    ID_EDIT_FIND, _T("fd")    },
    {    ID_EDIT_REPLACE, _T("r")    },
    {    ID_EDIT_SELECT_ALL, _T("sa")    },
	{    ID_EDIT_GOTO_LINE, _T("g")    },
    {    ID_EDIT_DECREASE_IDENT, _T("ao")    },
    {    ID_EDIT_INCREASE_IDENT, _T("ai")    },
	{    ID_EDIT_TOGGLEBOOKMARK, _T("b")    },
	{    ID_EDIT_NEXTBOOKMARK, _T("nb")    },
	{    ID_EDIT_PREVIOUSBOOKMARK, _T("pb")    },
	{    ID_EDIT_CLEAR_ALLBOOKMARKS, _T("lb")    },
	{    ID_EDIT_ENABLEOUTLINING, _T("oe")    },
	{    ID_EDIT_AUTOOUTLINING, _T("oa")    },
	{    ID_EDIT_LINENUMBERS, _T("ln")    },

	// 2. Font:
	{    ID_FONT_FONT, _T("ff")    },
	{    ID_FONT_SIZE, _T("fs")    },
    {    ID_FONT_INCREASE, _T("fg")    },
    {    ID_FONT_DECREASE, _T("fk")    },
    {    ID_FONT_CLEARFORMAT, _T("e")    },
    {    ID_FONT_BOLD, _T("1")    },
    {    ID_FONT_ITALIC, _T("2")    },
    {    ID_FONT_UNDERLINE, _T("3")    },
    {    ID_FONT_STRIKETHROUGH, _T("4")    },
    {    ID_FONT_SUBSCRIPT, _T("5")    },
    {    ID_FONT_SUPERSCRIPT, _T("6")    },
    {    ID_FONT_CHANGECASE, _T("7")    },
    {    ID_FONT_TEXTHIGHLIGHT, _T("i")    },
    {    ID_FONT_COLOR, _T("fc")    },

	// 3. Grid:
	{    ID_GRID_VIEW_GROUPBOX, _T("g")    },
	{    ID_GRID_VIEW_FIELDCHOOSER, _T("fc")    },
	{    ID_GRID_VIEW_COLUMN_AUTO_RESIZE, _T("ar")    },

	{    0, NULL    },
};


BCGPKey mainKeys [] =
{
	// 1. Shortcuts:
	{    ID_SHORTCUTS_HOME, _T("h")    },
	{    ID_SHORTCUTS_MAIL, _T("e")    },
	{    ID_SHORTCUTS_DOWNLOAD, _T("d")    },
	{    ID_SHORTCUTS_ABOUT, _T("a")    },

	// 2. Mail:
	{    ID_MAIL_NEW, _T("n")    },
	{    ID_MAIL_REMOVE, _T("d")    },
	{    ID_MAIL_FIND, _T("f")    },
	{    ID_MAIL_NAMES_AB, _T("ab")    },
	{    ID_MAIL_NAMES_CHECK, _T("m")    },

	// 3. Calendar:
	{    ID_PLANNER_NEW, _T("n")    },
	{    ID_PLANNER_OPEN_APP, _T("o")    },
	{    ID_PLANNER_REMOVE_APP, _T("d")    },
	{    ID_PLANNER_MODE_DAY, _T("md")    },
	{    ID_PLANNER_MODE_WORKWEEK, _T("mw")    },
	{    ID_PLANNER_MODE_WEEK, _T("me")    },
	{    ID_PLANNER_MODE_MONTH, _T("mm")    },
	{    ID_PLANNER_TIMESCALE, _T("t")    },
	{    ID_PLANNER_DRAW_TIME_AS_ICONS, _T("si")    },
	{    ID_PLANNER_DRAW_TIME_FINISH, _T("sf")    },
	{    ID_PLANNER_COMPRESS_WEEKEND, _T("sc")    },
	{    ID_PLANNER_DRAW_APP_GRADIENT, _T("sg")    },
	{    ID_PLANNER_DRAW_APP_ROUNDED, _T("sr")    },
	{    ID_PLANNER_DRAW_APP_DURATION, _T("sd")    },

	// 4. Tasks:
	{    ID_TASKS_NEW, _T("n")    },
	{    ID_TASKS_OPEN, _T("o")    },
	{    ID_TASKS_REMOVE, _T("d")    },
	{    ID_TASKS_MARK_COMPLETE, _T("m")    },

	// 5. Gantt:
	{    ID_GANTT_NEW, _T("n")    },
	{    ID_GANTT_OPEN_TASK, _T("o")    },
	{    ID_GANTT_REMOVE_TASK, _T("d")    },
	{    ID_GANTT_MARK_COMPLETE, _T("m")    },

	{    0, NULL    },
};

