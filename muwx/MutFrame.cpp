/** \file MutFrame.cpp
 ********************************************************************
 * Mutabor Frame.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutFrame.cpp,v 1.40 2011/08/28 20:09:11 keinstein Exp $
 * Copyright:   (c) 2005,2006,2007 TU Dresden
 * \author Rüdiger Krauße <krausze@mail.berlios.de>
 * Tobias Schlemmer <keinstein@users.berlios.de>
 * \date $Date: 2011/08/28 20:09:11 $
 * \version $Revision: 1.40 $
 * \license GPL
 *
 * $Log: MutFrame.cpp,v $
 * Revision 1.40  2011/08/28 20:09:11  keinstein
 * several impovements for opening and saving files
 *
 * Revision 1.39  2011-08-27 17:44:44  keinstein
 * Implemented Search and Search/Replace
 *
 * Revision 1.38  2011-08-24 21:19:36  keinstein
 * first run with 2.9.2+
 *
 * Revision 1.37  2011-08-21 16:52:05  keinstein
 * Integrate a more sophisticated editor menu based on the stc sample
 *
 * Revision 1.36  2011-08-20 17:50:39  keinstein
 * use  wxSTC for the editor windows
 *
 * Revision 1.35  2011-08-16 20:20:03  keinstein
 * Fix compiling on Mac OS X 10.5
 *
 * Revision 1.34  2011-08-14 18:32:18  keinstein
 * Use of m_childView of wxDocChildFrame instead of own view fixes a bad access.
 * Use wxDocChildFrame::OnCloseWindow
 * remove some unneeded code
 *
 * Revision 1.33  2011-08-11 19:00:48  keinstein
 * get Document/View running.
 * Needs further testing (possible segfaults).
 *
 * Revision 1.32  2011-08-06 09:21:23  keinstein
 * activated and debugged document manager
 *
 * Revision 1.31  2011-07-31 21:32:21  keinstein
 * Slightly improved window positioning
 * Suppress route window, when a Window is opened from the command line
 *
 * Revision 1.30  2011-07-31 20:16:04  keinstein
 * Implemented opening files from command line using Document/View framework
 *
 * Revision 1.29  2011-07-31 12:40:42  keinstein
 * Added classes and functions for Document/View support
 *
 * Revision 1.28  2011-03-06 13:15:41  keinstein
 * some rearrangement for update callback kernel->GUI
 *
 * Revision 1.27  2011-02-20 22:35:57  keinstein
 * updated license information; some file headers have to be revised, though
 *
 * Revision 1.26  2011-02-13 17:20:46  keinstein
 * Implemented missing toolbar icons (except search and edit funcitons)
 *
 * Revision 1.25  2011-01-13 21:12:37  keinstein
 * reactivate config restore on Activate in debug mode
 *
 * Revision 1.24  2010-12-11 02:10:09  keinstein
 * make 2.9.1 build but Mutabor crashes still at runtime in an infinite recursion :-(
 *
 * Revision 1.23  2010-11-21 13:15:47  keinstein
 * merged experimental_tobias
 *
 * Revision 1.21.2.10  2010-11-20 21:58:16  keinstein
 * reactivate midi playback
 *
 * Revision 1.21.2.9  2010-11-18 21:46:14  keinstein
 * MutFrame: get rid of OnIdle (this may break something, but saves much more CPU cycles
 * Some further steps to get rid of EDevice*
 *
 * Revision 1.21.2.8  2010-11-14 22:29:53  keinstein
 * Remvoed EDevice.cpp and EDevice.h from the sources list
 * They still reside in the source tree, since they have been used for Midi/GMN
 * file playing. That funcitonality has been disabled so far.
 * After reimplementation the files can be removed.
 *
 * Revision 1.21.2.7  2010-09-30 16:26:26  keinstein
 * remove global variables routewindow and frame
 * move route loading and route saving into MutRouteWnd
 * implement MutRouteWnd::InitShapes.
 * Destroy Route children before loading new route configuration (still some crashes)
 *
 * Revision 1.21.2.6  2010/04/20 17:41:38  keinstein
 * One step towards using Mutabor: Activation of a logic now honours the state of the Device Editor.
 *
 * Revision 1.21.2.5  2010/04/15 09:28:43  keinstein
 * changing routes works, but is not honoured by MIDI, yet
 *
 * Revision 1.21.2.4  2010/03/30 08:38:26  keinstein
 * added rudimentary command line support
 * changed debug system to allow selection of messages via command line
 * further enhancements to the route dialogs
 *
 * Revision 1.21.2.3  2010/02/15 12:08:21  keinstein
 * intermediate update for backup progress
 *
 * Revision 1.21.2.2  2010/01/14 09:34:24  keinstein
 * Checkin searching for a bug
 *
 * Revision 1.21.2.1  2009/08/10 11:23:12  keinstein
 * merged from wrong tree
 *
 * Revision 1.22  2009/08/10 11:15:46  keinstein
 * some steps towards new route window
 *
 * Revision 1.21  2008/10/09 15:14:02  keinstein
 * make compile on mingw
 *
 * Revision 1.20  2008/10/01 09:33:49  keinstein
 * fixed inclution for XCode build
 *
 * Revision 1.19  2008/08/18 15:10:37  keinstein
 * Fix subwindow creation when on other window
 *
 * Revision 1.18  2008/08/01 16:24:30  keinstein
 * Fix some segfaults on stopping Mutabor
 *
 * Revision 1.17  2008/07/22 07:57:06  keinstein
 * solved some valgrind issues
 *
 * Revision 1.16  2008/07/21 09:25:29  keinstein
 * RcfFile: removed
 * TextBoxWanted: one variable per box and type
 * removed ROUTE_WIN and REPAINT_ROUTE definitions
 * reformatted debug logging
 * Implement box selection Menu
 * MutFrame::repaint_route(): New function
 *
 * Revision 1.15  2008/06/30 08:57:17  keinstein
 * Fix UPDATE_UI for CM_PANIC and CM_EXECUTE
 * MurFileData: new struct
 * theFrame: new variable
 * ~MutFrame(): empty event loop
 * PassEventToEditor(): Runtime Class check for client
 * OnClose(): implement Veto if logic is active
 * 	stop logic if running
 * 	close all clients before deletion to make AUI on reopening happy
 * CmDoActivate(): Separate Logic window creation from other windows
 * 	Create box selection submenu
 * ClearMenuItem(), ClearSubMenu(), RaiseLogic(), CmStop(), CeActivate(): New functions.
 * CmRoutes(): Raise window and return if we have a route window already.
 * 	Set window ID.
 * LogicWinOpen(): remove close button
 * 	Set unique name
 * TextBoxOpen(): don't destroy on close
 * 	set unique window name
 * StopInDev(): new function.
 * CmInDevStop(): sooutsourcing to StopInDev().
 * CmRouteLoad(): New function.
 * CmRouteSave(), CmRouteSaveAs(): New funcitons.
 * CloseAll(): Some reorganization.
 * ActiveWindow, BoxCommandIds: new Attributes.
 *
 * Revision 1.14  2008/06/02 16:25:26  keinstein
 * don't include Mutabor.rh
 * implement CM_EXECUTE action
 * disable CM_COMPILE, CM_EXECUTE, CM_DOACTIVATE if logic is active
 * implement CM_SETTITLE for setting the window title
 * FileNameDialog(): reimplemented
 * CmFileOpen() and other: correct Event Skipping.
 * MutFrame::ToggleTextBox(), CloseAll():
 * use DetachPane and Close instead of ClosePane
 *
 * Revision 1.13  2008/04/28 08:21:33  keinstein
 * Silence a warning since it is issued every normal start.
 *
 * Revision 1.12  2008/03/11 10:37:34  keinstein
 * Holyday edition
 * put CM_xxx in an enum
 * use wx constants
 * document mutframe
 * some white space formattings
 * make route saving more system specific
 * many other fixes
 *
 * Revision 1.11  2008/01/25 09:37:11  keinstein
 * Enable CM_ACTIVATE, CM_FILENEW and CM_FILEOPEN in event table
 * Inherit wxFrame
 * Use AUIManager
 * Let Application handle CM_FILENEW/CM_FILEOPEN if we have already a client
 * New titles for Subframes
 * Some Debug output
 * use wxConfig
 *
 * MutFrame::CloseAll,
 * MutFrame::OnSize,
 * MutFrame::OnEraseBackground,
 * MutFrame::OnActivate:        New Functions.
 *
 * Revision 1.10  2007/10/09 14:56:13  keinstein
 * MutFrame::DetermineFrameSize: New Function.
 * MutFrame::MutFrame: Automagic Frame size detection.
 *
 * Revision 1.9  2007/10/08 12:21:50  keinstein
 * Moved major Handling of file opening and new file to MutApp event handler.
 *
 * Revision 1.8  2007/10/05 12:41:44  keinstein
 * first steps towards a real mac version:
 *  - move OnAbout to MutApp
 *  - set ext on frame delete on Quitting, so that program quits too
 *
 * Revision 1.7  2006/01/18 15:37:02  kewxWindows licenseinstein
 * no MDI Windows in some environments
 *
 * Revision 1.6  2005/11/07 19:42:54  keinstein
 * Some additional changes
 *
 * \addtogroup muwx
 * \{
 ********************************************************************/


// ===========================================================================
// declarations
// ===========================================================================

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "Defs.h"
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#include "wx/mdi.h"
#endif

#include "wx/toolbar.h"

#if !defined(__WXMSW__) && 0
#include "Icon/Mutabor.xpm"
#include "Icon/Document.xpm"
#include "Icon/KeyTextBox.xpm"
#include "Icon/TSTextBox.xpm"
#include "Icon/ActTextBox.xpm"
#endif

#include "Icon/Route.xpm"


#if 0
#include "bitmaps/new.xpm"
#include "bitmaps/open.xpm"
#include "bitmaps/save.xpm"
#include "bitmaps/copy.xpm"
#include "bitmaps/cut.xpm"
#include "bitmaps/paste.xpm"
#include "bitmaps/print.xpm"
#include "bitmaps/help.xpm"
#endif

#include "wx/filename.h"
#include "wx/config.h"
#include "wx/confbase.h"
#include "wx/fileconf.h"
#ifdef __WXMSW__
#  include <wx/msw/regconf.h>
#endif
#include "wx/ffile.h"
#include "MutFrame.h"
#include "MutDocument.h"
#include "MutView.h"
#include "MutChild.h"
//#include "Mutabor.rh"
#include "MutApp.h"

#include "Defs.h"
#include "mhDefs.h"
#include "Runtime.h"
#include "GrafKern.h"
#include "Action.h"
#include "MutRouteWnd.h"
#include "MutLogicWnd.h"
#include "MutTextBox.h"
#include "MutBitmaps.h"

using mutaborGUI::MutEditFile;
using mutaborGUI::MutDocument;
using mutaborGUI::MutView;

#define OPENMENU \
	menu = new wxMenu;

#define CLOSEMENU(name) \
	menuBar->Append(menu, name);

#define MENUITEM(name, id, help) \
	menu->Append(id, name, help)

#define MENUCHECKITEM(name, id, help) \
	menu->AppendCheckItem(id, name, help)

#define MENUITEM_ADD(name, id, help, add) \
	menu->Append(id, name, help, add)

#define MENUITEM_SEPARATOR \
    menu->AppendSeparator()

// ---------------------------------------------------------------------------
// global variables
// ---------------------------------------------------------------------------

#ifndef HAVE_CONFIG_H
#  define PACKAGE_NAME "Mutabor"
#endif

#define APPNAME _(PACKAGE_NAME)

//wxString RcfFile = wxT("Routes.cfg");
MutFrame* theFrame = 0;
bool demo = false;

bool asTS = true;
bool SaveEditor = true;
bool UseColorBars = true;
bool OWM = false; // One Window Mode
bool CAW = false; // Common Action Window
bool LogicOn = false;
int curBox = 0;
wxWindow *ChildToClose = NULL;

wxString CompiledFile;

wxString curLogic[MAX_BOX];
wxString curTS[MAX_BOX];
int curTaste[MAX_BOX][2]; // [0] ... ToneSyst, [1] ... Logic

bool TextBoxWanted[MAX_BOX][3] = {
                                         { false, false, false },
                                         { false, false, false },
                                         { false, false, false },
                                         { false, false, false },
                                         { false, false, false },
                                         { false, false, false },
                                         { false, false, false },
                                         { false, false, false },
                                         { false, false, false },
                                         { false, false, false },
                                         { false, false, false },
                                         { false, false, false },
                                         { false, false, false },
                                         { false, false, false },
                                         { false, false, false },
                                         { false, false, false }
                                 };
char WinName[5][12] = { "KEYWIN", "TONSYSTWIN", "ACTIONWIN", "LOGICWIN", "ROUTEWIN" };

int MutFrame::boxCommandIds[MAX_BOX];

#define SG_NOTHING 1
#define SG_LOGIC   0
#define SG_RECORD  2
#define SG_PLAY    3
#define SG_PAUSE   4

#define Compiled (!CompiledFile.IsEmpty())
//#define ROUTE_WIN ((MutRouteWnd*)(Get(WK_ROUTE)->Win))
//#define REPAINT_ROUTE if ( IsOpen(WK_ROUTE) ) ROUTE_WIN->Refresh()

// ---------------------------------------------------------------------------
// event tables
// ---------------------------------------------------------------------------

BEGIN_EVENT_TABLE(MutFrame, wxDocChildFrame)
	EVT_ERASE_BACKGROUND(MutFrame::OnEraseBackground)
	EVT_SIZE(MutFrame::OnSize)

//        EVT_MENU(CM_EXECUTE, MutFrame::CmFileOpen)
//	EVT_MENU(CM_FILESAVE, MutFrame::PassEventToEditor)
	//    EVT_MENU(CM_FILESAVEAS, MutFrame::CmFileOpen)
	EVT_MENU(CM_DOACTIVATE, MutFrame::CmDoActivate)
	EVT_MENU(CM_STOP, MutFrame::CmStop)
	EVT_MENU(CM_PANIC, MutFrame::CmPanic)
	EVT_UPDATE_UI(CM_EXECUTE, MutFrame::CeExecute)
	EVT_UPDATE_UI(CM_ACTIVATE, MutFrame::CeActivate)
	EVT_UPDATE_UI(CM_COMPILE, MutFrame::CeActivate)
	EVT_UPDATE_UI(CM_DOACTIVATE, MutFrame::CeActivate)
	EVT_UPDATE_UI(CM_STOP, MutFrame::CeStop)
	EVT_UPDATE_UI(CM_PANIC, MutFrame::CeStop)
EVT_UPDATE_UI(wxID_UNDO, MutFrame::PassEventToEditorUI)
EVT_UPDATE_UI(wxID_REDO, MutFrame::PassEventToEditorUI)
	EVT_MENU(CM_COMPILE, MutFrame::PassEventToEditor)
	EVT_MENU(CM_COMPACT, MutFrame::PassEventToEditor)
	EVT_MENU(CM_ACTIVATE, MutFrame::PassEventToEditor)
	EVT_MENU(CM_GETLINE, MutFrame::PassEventToEditor)
EVT_MENU (wxID_CLEAR,            MutFrame::PassEventToEditor)
EVT_MENU (wxID_CUT,              MutFrame::PassEventToEditor)
EVT_MENU (wxID_COPY,             MutFrame::PassEventToEditor)
EVT_MENU (wxID_PASTE,            MutFrame::PassEventToEditor)
    EVT_MENU (CM_INDENTINC,        MutFrame::PassEventToEditor)
    EVT_MENU (CM_INDENTRED,        MutFrame::PassEventToEditor)
    EVT_MENU (wxID_SELECTALL,        MutFrame::PassEventToEditor)
    EVT_MENU (CM_SELECTLINE,       MutFrame::PassEventToEditor)
    EVT_MENU (wxID_REDO,             MutFrame::PassEventToEditor)
    EVT_MENU (wxID_UNDO,             MutFrame::PassEventToEditor)
    // find
    EVT_MENU (wxID_FIND,             MutFrame::PassEventToEditor)
    EVT_MENU (CM_FINDNEXT,         MutFrame::PassEventToEditor)

    EVT_MENU (wxID_REPLACE,          MutFrame::PassEventToEditor)
    EVT_MENU (CM_REPLACENEXT,      MutFrame::PassEventToEditor)
    EVT_MENU (CM_BRACEMATCH,       MutFrame::PassEventToEditor)
    EVT_MENU (CM_GOTO,             MutFrame::PassEventToEditor)
EVT_FIND(wxID_ANY,               MutFrame::PassEventToEditorFind)
EVT_FIND_NEXT(wxID_ANY,          MutFrame::PassEventToEditorFind)
EVT_FIND_REPLACE(wxID_ANY,       MutFrame::PassEventToEditorFind)
EVT_FIND_REPLACE_ALL(wxID_ANY,   MutFrame::PassEventToEditorFind)
EVT_FIND_CLOSE(wxID_ANY,         MutFrame::PassEventToEditorFind)
    // view
    EVT_MENU_RANGE (CM_HILIGHTFIRST, CM_HILIGHTLAST,
                                     MutFrame::PassEventToEditor)
    EVT_MENU (CM_DISPLAYEOL,       MutFrame::PassEventToEditor)
    EVT_MENU (CM_INDENTGUIDE,      MutFrame::PassEventToEditor)
    EVT_MENU (CM_LINENUMBER,       MutFrame::PassEventToEditor)
    EVT_MENU (CM_LONGLINEON,       MutFrame::PassEventToEditor)
    EVT_MENU (CM_WHITESPACE,       MutFrame::PassEventToEditor)
    EVT_MENU (CM_FOLDTOGGLE,       MutFrame::PassEventToEditor)
    EVT_MENU (CM_OVERTYPE,         MutFrame::PassEventToEditor)
    EVT_MENU (CM_READONLY,         MutFrame::PassEventToEditor)
    EVT_MENU (CM_WRAPMODEON,       MutFrame::PassEventToEditor)
    // extra
    EVT_MENU (CM_CHANGELOWER,      MutFrame::PassEventToEditor)
    EVT_MENU (CM_CHANGEUPPER,      MutFrame::PassEventToEditor)
    EVT_MENU (CM_CONVERTCR,        MutFrame::PassEventToEditor)
    EVT_MENU (CM_CONVERTCRLF,      MutFrame::PassEventToEditor)
    EVT_MENU (CM_CONVERTLF,        MutFrame::PassEventToEditor)
    EVT_MENU (CM_CHARSETANSI,      MutFrame::PassEventToEditor)
    EVT_MENU (CM_CHARSETMAC,       MutFrame::PassEventToEditor)
	//    EVT_MENU(CM_ROUTES, MutFrame::CmRoutes)

EVT_MENU(CM_TOGGLEKEY, MutFrame::CmToggleKey)
EVT_MENU(CM_TOGGLETS, MutFrame::CmToggleTS)
EVT_MENU(CM_TOGGLEACT, MutFrame::CmToggleAct)
EVT_MENU(CM_OWM, MutFrame::CmToggleOWM)
EVT_MENU(CM_CAW, MutFrame::CmToggleCAW)
EVT_UPDATE_UI(CM_TOGGLEKEY, MutFrame::CeToggleKey)
EVT_UPDATE_UI(CM_TOGGLETS, MutFrame::CeToggleTS)
EVT_UPDATE_UI(CM_TOGGLEACT, MutFrame::CeToggleAct)
EVT_UPDATE_UI(CM_OWM, MutFrame::CeToggleOWM)
EVT_UPDATE_UI(CM_CAW, MutFrame::CeToggleCAW)

EVT_MENU(CM_INDEVSTOP, MutFrame::CmInDevStop)
EVT_MENU(CM_INDEVPLAY, MutFrame::CmInDevPlay)
EVT_MENU(CM_INDEVPAUSE, MutFrame::CmInDevPause)
EVT_UPDATE_UI(CM_INDEVSTOP, MutFrame::CeInDevStop)
EVT_UPDATE_UI(CM_INDEVPLAY, MutFrame::CeInDevPlay)
EVT_UPDATE_UI(CM_INDEVPAUSE, MutFrame::CeInDevPause)
//    EVT_ACTIVATE(MutFrame::OnActivate)

EVT_CLOSE(MutFrame::OnClose)
EVT_MENU(CM_UPDATEUI, MutFrame::UpdateUI)
//	EVT_IDLE(MutFrame::OnIdle)
EVT_MENU(CM_SETTITLE, MutFrame::CmSetTitle)
	//    EVT_SIZE(MutFrame::OnSize)
END_EVENT_TABLE()

// ===========================================================================
// implementation
// ===========================================================================

// ---------------------------------------------------------------------------
// MutFrame
// ---------------------------------------------------------------------------

// Define my frame constructor
MutFrame::MutFrame(wxFrame *parent,

                   const wxWindowID id,
                   const wxString& title,
                   const wxPoint& pos,
                   const wxSize& size,
                   const long style): wxDocChildFrame(NULL, 
						      NULL, 
						      parent, 
						      id, 
						      title, 
						      pos, 
						      size,
						      style | wxNO_FULL_REPAINT_ON_RESIZE),
	curStatusImg(0)
{

	SetSize (DetermineFrameSize ());
	client = NULL;
	editmenu = filemenu = NULL;

	auimanager.SetManagedWindow(this);


#if wxUSE_TOOLBAR
	wxToolBar * tb = new  wxToolBar(this,
	                                wxID_ANY,
	                                wxDefaultPosition,
	                                wxDefaultSize,
	                                wxTB_DOCKABLE);
	InitToolBar(tb);

	auimanager.AddPane(tb, wxAuiPaneInfo().
	                   Name(_T("tb")).Caption(_("Toolbar")).
	                   ToolbarPane().Top().
	                   LeftDockable(false).RightDockable(false));
#endif // wxUSE_TOOLBAR


	// Accelerators
	/*    wxAcceleratorEntry entries[3];
	    entries[0].Set(wxACCEL_CTRL, (int) 'N', MDI_NEW_WINDOW);
	    entries[1].Set(wxACCEL_CTRL, (int) 'X', MDI_QUIT);
	    entries[2].Set(wxACCEL_CTRL, (int) 'A', MDI_ABOUT);
	    wxAcceleratorTable accel(3, entries);
	    SetAcceleratorTable(accel);*/
}

MutFrame::MutFrame(MutDocument *doc,
		   MutView *v,
		   wxFrame *frame,
		   wxWindowID id,
		   const wxString& title,
		   const wxPoint& pos,
		   const wxSize& size,
		   long type,
		   const wxString& name):
	wxDocChildFrame(doc,v,frame,id,title,pos,size,type,name),
	curStatusImg(0)
{

	SetSize (DetermineFrameSize ());
	client = NULL;
	editmenu = filemenu = NULL;

	auimanager.SetManagedWindow(this);


#if wxUSE_TOOLBAR
	wxToolBar * tb = new  wxToolBar(this,
	                                wxID_ANY,
	                                wxDefaultPosition,
	                                wxDefaultSize,
	                                wxTB_DOCKABLE);
	InitToolBar(tb);

	auimanager.AddPane(tb, wxAuiPaneInfo().
	                   Name(_T("tb")).Caption(_("Toolbar")).
	                   ToolbarPane().Top().
	                   LeftDockable(false).RightDockable(false));
#endif // wxUSE_TOOLBAR


	// Accelerators
	/*    wxAcceleratorEntry entries[3];
	    entries[0].Set(wxACCEL_CTRL, (int) 'N', MDI_NEW_WINDOW);
	    entries[1].Set(wxACCEL_CTRL, (int) 'X', MDI_QUIT);
	    entries[2].Set(wxACCEL_CTRL, (int) 'A', MDI_ABOUT);
	    wxAcceleratorTable accel(3, entries);
	    SetAcceleratorTable(accel);*/
}




MutFrame::~MutFrame()

{
	if (filemenu) {
		if (wxGetApp().GetDocumentManager()) 
			wxGetApp().GetDocumentManager()->FileHistoryRemoveMenu(filemenu);
	}
	if (m_childView) {
		wxASSERT(dynamic_cast<MutView *>(m_childView));
		MutView * v = (MutView *) m_childView;
		v->SetFrame(NULL);
		v->SetTextsw(NULL);
	}
	auimanager.UnInit();

//	while (wxGetApp().Pending()) wxGetApp().Dispatch();
}

#if wxUSE_TOOLBAR
void MutFrame::InitToolBar(wxToolBar* toolBar)
{

	// Stock Id's are currently not availlable for wxToolBar() :-(
	MutToolBarBitmaps::Init();

	toolBar->AddTool(CM_FILENEW, _("New"), MutToolBarBitmaps::New, _("New file"));
	toolBar->AddTool(CM_FILEOPEN, _("Open"), MutToolBarBitmaps::Open , _("Open file"));
	toolBar->AddTool(CM_FILESAVE, _("Save"), MutToolBarBitmaps::Save, _("Save file"));
	toolBar->AddTool(CM_FILESAVEAS, _("Save as"), MutToolBarBitmaps::SaveAs, _("Save file with new name"));
	toolBar->AddTool(wxID_PRINT, _("Print"), MutToolBarBitmaps::Print, _("Print"));
	toolBar->AddSeparator();
	toolBar->AddTool(CM_ACTIVATE, _("Activate"), MutToolBarBitmaps::LogicActivate, _("Activate the logic"));	
	toolBar->AddTool(CM_STOP, _("Stop"), MutToolBarBitmaps::LogicStop, _("Stop the logic"));	
	toolBar->AddTool(CM_PANIC, _("Panic"), MutToolBarBitmaps::LogicPanic, _("Panic: switch all notes off"));	
	toolBar->AddSeparator();
	toolBar->AddTool(wxID_UNDO, _("Undo"), MutToolBarBitmaps::Undo, _("Undo last changes"));
	toolBar->AddTool(wxID_REDO, _("Redo"), MutToolBarBitmaps::Redo,  _("Redo last undone changes"));
	toolBar->AddTool(wxID_COPY, _("Copy"), MutToolBarBitmaps::Copy, _("Copy"));
	toolBar->AddTool(wxID_CUT, _("Cut"), MutToolBarBitmaps::Cut,  _("Cut"));
	toolBar->AddTool(wxID_PASTE, _("Paste"), MutToolBarBitmaps::Paste, _("Paste"));
	toolBar->AddSeparator();
	// \todo implement search and replace and corresponding toolbar buttons
	// toolBar->AddSeparator();
       	toolBar->AddTool(CM_ROUTELOAD,_("&Load routes"), MutToolBarBitmaps::RouteLoad,
                 _("Load the current route configuration from a file"));
        toolBar->AddTool(CM_ROUTESAVE,_("&Save routes"), MutToolBarBitmaps::RouteSave,
                 _("Save current route configuration to a file."));
	toolBar->AddSeparator();
        toolBar->AddTool(CM_INDEVPLAY,_("&Play"), MutToolBarBitmaps::IndevsPlay,
                 _("Start playing the music from input file devices"));
        toolBar->AddTool(CM_INDEVSTOP,_("St&op"), MutToolBarBitmaps::IndevsStop,
                 _("Stop playing the music from input file devices"));
        toolBar->AddTool(CM_INDEVPAUSE,_("P&ause"), MutToolBarBitmaps::IndevsPause,
                 _("Pause plaing the music from input file devices"));
  	toolBar->AddSeparator();
	toolBar->AddTool( CM_ABOUT, _("About"), MutToolBarBitmaps::About, _("Help"));
	toolBar->AddSeparator();
	toolBar->Realize();
}

#endif // wxUSE_TOOLBAR

void MutFrame::PassEventToEditor(wxCommandEvent &event)
{
	event.Skip(false);

	if (dynamic_cast<MutEditFile*>(client)) {
		wxPostEvent(client,event);
	}
}

void MutFrame::PassEventToEditorUI(wxUpdateUIEvent &event)
{
	event.Skip(false);

	if (dynamic_cast<MutEditFile*>(client)) {
		client->GetEventHandler()->ProcessEvent(event);
	}
}

void MutFrame::PassEventToEditorFind(wxFindDialogEvent &event)
{
	event.Skip(false);

	if (dynamic_cast<MutEditFile*>(client)) {
		client->GetEventHandler()->ProcessEvent(event);
	}
}

void MutFrame::EventPassOn(wxCommandEvent& event)
{
	if ( event.GetEventObject() == NULL )
		// als Flag zur Sicherheit vor Endlosschleifen
		return;

	event.SetEventObject(NULL);

	/*	wxAUIPaneInfoArray &info = auimanager.GetAllPanes();

		if (!info.empty()) {
			wxAUIPaneInfoArray::iterator it = info.first();

		}
	*/
	std::cout << "Skippen? " << event.GetSkipped() <<
	" Propagate? " << event.ShouldPropagate() << std::endl;

	//        if (!GetClientWindow()->ProcessEvent(event)) {
	//	std::cout << "Event ignoriert von:" << GetClientWindow()->GetName().fn_str() << std::endl;
	//

	wxWindow * frame = auimanager.GetManagedWindow();

	if (frame) {
		wxPostEvent(frame,event);
		std::cout << "Event " << event.ShouldPropagate() << " war da:"
		<< (frame->GetName().fn_str()) << std::endl;
	}

	//	}text.mb_str(*wxConvFileName)
	std::cout << frame << std::endl;

	event.Skip();

}

void MutFrame::OnClose(wxCloseEvent& event)
{
	DEBUGLOG (other, _T("%x == %x"),this,theFrame);

	if (theFrame == this) {
		DEBUGLOG (other, _T("We are the active window."));

		if ( event.CanVeto() ) {
			wxString msg;
			msg.Printf(_("This logic is currently active. On closing it will be deactivated. Really close this window?"));

			if ( wxMessageBox(msg, _("Please confirm closing."),
			                  wxICON_QUESTION | wxYES_NO) != wxYES ) {
				event.Veto();
				return;
			}
		}

		DoStop();
	}


	SaveState();


	// wxDocChildFrame will veto if there is no View associated
	if (m_childView) {
#if wxCHECK_VERSION(2,9,0)
		STUBC;
		event.Skip();	
#else	
		wxDocChildFrame::OnCloseWindow(event);
#endif
	} else 
		Destroy();
}

void MutFrame::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    STUBC; 
/* this code is just copied and must be changed 
  to paint into the subwindow which is managed by 
  the AUI manager.

  Propably it must be simply moved to the client window.
*/
    
    if (m_childView) 
	    m_childView->OnDraw(&dc);
}




void MutFrame::CmFileNew(wxCommandEvent& event)
{
	STUBC;
	return;

#ifdef DEBUG
	printf("MutFrame::CmFileNew\n");
#endif

	if (client) {
		event.Skip(true);
		return ;
	}

	event.Skip(false); // Its our task to try create the file

	OpenFile(wxEmptyString);
}


void MutFrame::CmFileOpen(wxCommandEvent& event)
{
	STUBC;
	return;

	if (client) {
		event . Skip (true);
		return;
	}

	event . Skip (false); // it's our task to try to open that file

	wxString path = FileNameDialog(this, event.GetId());

	if ( !path )
		return;


#ifdef DEBUG
	std::cerr << "MutFrame:CmFileOpen " << CM_EXECUTE << " == "
	<< event . GetId () << "?" << std::endl;

#endif


	switch (event.GetId()) {

	case CM_FILEOPEN:
		OpenFile(path);

		break;

	case CM_EXECUTE: {
		OpenFile(path);
		wxCommandEvent e (wxEVT_COMMAND_MENU_SELECTED, CM_ACTIVATE);
		ProcessEvent (e);
	}

	break;

	case CM_FILESAVEAS:
		event.SetString(path);

		PassEventToEditor(event);

		break;

	default:
		wxLogError(_("Unexpected Event in MutFrame::CmFileOpen: %d"),event.GetId());
	}
}

/**
 * open a file in a new frame.
 * \param path Path of the file to open
 * \todo file loading fails silently if it is not in the systems encoding.
 * */

bool MutFrame::OpenFile (wxString path, bool newfile)
{
	STUBC;
	return false;

	if (client) return false;

	wxString filename = !path ? wxString(_("noname.mut"))
	                    : wxFileName(path).GetFullName();

	MutEditFile * editor = new MutEditFile(this, wxPoint(0, 0), wxDefaultSize);

#ifdef DEBUG
	std::cout << "MutFrame::OpenFile(): Loading " << (path.fn_str()) << std::endl;

#endif
	if (!(!path))
		editor->LoadFile(path);

	editor->SetSelection(0, 0);
	SetTitle(wxString().Format(_("%s -- %s"),APPNAME,filename.c_str()));

	return SetClient(editor,filename);
}
/**
 * Attach a client
 * \param window to  be attached as the client.
 * */

bool MutFrame::SetClient (wxWindow * win, const wxString &title)
{
	if (client || !win) {
		wxASSERT(!client);
		wxASSERT(win);
		return false;
	}
	
	DEBUGLOG(docview,_T("Setting client of %x to %x with title '%s'"),
		 this,
		 win,
		 (const wxChar *)title.c_str());

	client = win;
	SetTitle(title);
	auimanager.AddPane(client,wxAuiPaneInfo().
	                   Caption(title).CenterPane().PaneBorder(false));
	auimanager.Update();
	return true;
}


// Logic-Arbeit: CmDoActivate, CmStop, CmPanic, CmExecute


void UpdateUIcallback(int box,bool logic_changed)
{
        // todo Update UI
	if ( theFrame ) {
		wxCommandEvent event1(wxEVT_COMMAND_MENU_SELECTED,
		                           CM_UPDATEUI);
		wxPostEvent(theFrame,event1);
	}
}

void MutFrame::CmDoActivate(wxCommandEvent& event)
{
	if (LogicOn) return;

#ifdef DEBUG
	std::cout << "MutFrame::CmDoActivate" << std::endl;
#endif

	if ( !Compiled )
		return;

	wxGetApp().SaveState();

#ifdef DEBUG
	DEBUGLOG (other, _T("Restoring state for debugging"));
	wxGetApp().RestoreState();
#endif

//	ScanDevices(); 

	AktionTraceReset();

	// aktivieren
#ifndef NOACTIVATE
#ifdef DEBUG
	std::cerr << "MutFrame::CmDoActivate: Activate" << std::endl;

#endif
	RealTime = true;

	if ( !CheckNeedsRealTime() )
		RealTime = (wxMessageBox(_("There are no realtime \
		                           instruments in the routes.\n\
		                           Shall Mutabor translate the files in batch mode, \
		                           to keep the MIDI files with the original time stamp?\n\
		                           (This means also, that you can't modify the tunings \
		                           while playing by computer keyboard.)"),
		                         _("No realtime => batch mode?"),
		                         wxYES_NO | wxICON_QUESTION
		                         /*| MB_DEFBUTTON2*/) == wxNO);

	theFrame = this;

	if ( !Activate(RealTime, &UpdateUIcallback) )
		return;

#endif

#ifdef DEBUG
	std::cerr << "MutFrame::CmDoActivate: Initialize state" << std::endl;

#endif

	// Variablen initialisieren
	for (int instr = 0; instr < MAX_BOX; instr++) {
		curLogic[instr] = _T("(INITIAL)");
		curTS[instr] = _T("0");
		curTaste[instr][0] = 0;
		curTaste[instr][1] = 0;
	}

#ifdef DEBUG
	std::cout << "MutFrame::CmDoActivate: Check used boxes" << std::endl;

#endif
	// curBox checken
	CheckBoxesUsed();

	if ( !BoxUsed[curBox] ) {
		curBox = 0;

		for (int i = 0; i < MAX_BOX; i++)
			if ( BoxUsed[i] ) {
				curBox = i;
				break;
			}
	}

	SetAktuellesKeyboardInstrument(curBox);

	// WinAttrs säubern
	DEBUGLOG (other, _T("Clear window attributes"));

	for (WinKind kind = WK_KEY; kind < WK_NULL; kind++) {
		size_t i;

		while ( (i = WinAttrs[kind].GetCount()) > 0)
			if ( !BoxUsed[WinAttrs[kind][i].Box] )
				WinAttrs[kind].RemoveAt(i);
	}

	DEBUGLOG (other, _T("Open other than logic; One window mode: %d"),OWM);

	// set windows except curBox setzen
	if ( !OWM )
		for (WinKind kind = WK_KEY; kind < WK_LOGIC; kind++)
			for (size_t i = 0; i < WinAttrs[kind].GetCount(); i++)
				if ( WinAttrs[kind][i].Box != curBox
				                &&  WinAttrs[kind][i].Wanted )
					TextBoxOpen(kind, WinAttrs[kind][i].Box);

	UpdateBoxMenu();
	MutFrame * routewin = dynamic_cast<MutFrame *>(FindWindowById(WK_ROUTE));
	if ( routewin ) routewin->UpdateBoxMenu();
	DEBUGLOG (other, _T("Open Logic window"));
	// curBox-Fenstersetzen
	//  LogicWinOpen(curBox);
	LogicOn = true;

	// Toolbar
	/*2	ControlBar->Remove(*ButtonActivate);
	ControlBar->Insert(*ButtonStop, TGadgetWindow::Before, ButtonPanic);
	ControlBar->LayoutSession();*/
	// Statusbar
	SetStatus(SG_LOGIC);

	DEBUGLOG (other, _T("Open Text boxes: %d -- %d"),WK_KEY,WK_ACT);

	for (size_t i = 0; i < MAX_BOX; i++)
		if (BoxUsed[i])
			for (WinKind kind = WK_KEY; kind <= WK_ACT; kind++) {
				if ( TextBoxWanted[i][kind] )
					TextBoxOpen(kind, i);
				else
					DontWant(kind, i);
			}


	DEBUGLOG (other, _T("Repaint route"));

	repaint_route();

	DEBUGLOG (other, _T("event.Skip()"));
	event.Skip(false);
}

wxMenuItem * MutFrame::ClearMenuItem(int id)
{
	wxMenuItem * item = GetMenuBar()->FindItem(id);

	if (item->IsSubMenu())
		ClearSubMenu(item);

	return item;
}

void MutFrame::ClearSubMenu(wxMenuItem * item)
{

	wxMenu * menu = item->GetSubMenu();
#ifdef DEBUG
	DEBUGLOG (other, _T("item: %s\n"),(item->GetText()).c_str())
	std::cerr << " (" << item << ")" << std::endl;
#endif

	if (! menu) return;

	menu->AppendSeparator(); // just to make sure, the item group is finished.


	wxMenuItemList& l = menu->GetMenuItems();

	DEBUGLOG (other, _T(" %d items"),l.GetCount());

	for (wxMenuItemList::iterator i = l.begin(); i!=l.end(); i=l.begin()) {
		wxMenuItem * node = *i;
		DEBUGLOG (other, _T("ptr %x handling %s"), node,(node->GetText()).c_str());

		if (node->IsSubMenu())
			ClearSubMenu(node);

		Disconnect(node->GetId(),wxEVT_COMMAND_MENU_SELECTED);

		DEBUGLOG (other, _T("destroying %s"),(node->GetText()).c_str());

		//    node->GetNext();
		menu->Destroy(node);
	}
}

void MutFrame::RaiseLogic(wxCommandEvent& event)
{
	if (!RaiseTheFrame()) {
		DEBUGLOG (other, _T("Calling Logic frame for id %d"), event.GetId());
		theFrame -> RaiseLogic(event);
		return;
	}

	DEBUGLOG (other, _T("Reached logic frame"));

	wxASSERT(theFrame == this);
	DEBUGLOG (other, _T("%d"),event.GetId());

	size_t i = 0;

	while (i < MAX_BOX && boxCommandIds[i] != event.GetId()) i++;

	wxASSERT(i!=MAX_BOX);

	DEBUGLOG (other, _T("%d"),i);

	curBox = i;

	if (WinAttrs[WK_LOGIC][i].Win) {
		WinAttrs[WK_LOGIC][i].Win->SetFocus();

		wxFrame * win =
		        dynamic_cast<wxFrame *>(WinAttrs[WK_LOGIC][i].Win->GetParent());

		if (win) win->Raise();

		DEBUGLOG (other, _T("Parent type: %s"), muT(typeid(*( WinAttrs[WK_LOGIC][i].Win->GetParent())).name()).c_str());

		GetMenuBar()->Check(event.GetId(),true);
	}
}

void MutFrame::DoStop()
{
	if ( LogicOn ) {
		LogicOn = false;
		StopInDev();
		Stop();

		// Ampel umschalten
		/*		ControlBar->Remove(*ButtonStop);
		ControlBar->Insert(*ButtonActivate, TGadgetWindow::Before, ButtonPanic);
		ControlBar->LayoutSession();*/
		// Statusleiste
		SetStatus(SG_NOTHING);
		//		StatusBar->SetText("");
		// Titel
		//    SetTitle(APPNAME);
		// alle Fenser schlieﬂen
		wxMenuItem * boxSelector = ClearMenuItem(CM_SELECTBOX);
		wxASSERT(boxSelector->IsSubMenu());

		for (WinKind kind = WK_KEY; kind <= WK_LOGIC; kind++) {
			DEBUGLOG (other, _T("Closing kind %d"),kind);
			theFrame->CloseAll(kind);
		}

		AktionTraceReset();

		repaint_route();
		theFrame = NULL;
	}
}

void MutFrame::CmStop(wxCommandEvent& event)
{
	DoStop();
}

void MutFrame::CmPanic(wxCommandEvent& WXUNUSED(event))
{
	if ( LogicOn )
		Panic();
}

void MutFrame::CeExecute(wxUpdateUIEvent& event)
{
	//	event.Enable(!LogicOn && (Compiled || ActiveWinKind == WK_EDIT));
	event.Enable(!LogicOn);
}


void MutFrame::CeActivate(wxUpdateUIEvent& event)
{
	//	event.Enable(!LogicOn && (Compiled || ActiveWinKind == WK_EDIT));
	bool enable = !LogicOn && (dynamic_cast<MutEditFile *>(client)); 
	event.Enable(enable);
	event.Show(enable);
}

void MutFrame::CeStop(wxUpdateUIEvent& event)
{
	event.Enable(LogicOn);
	event.Show(LogicOn);
}

// Routenfenster anzeigen

void MutFrame::CmRoutes(wxCommandEvent& event)
{
	if ( GetId()== WK_ROUTE ) {
		DEBUGLOG (other, _T("setting Focus"));
		auimanager.Update();
		Raise();
		return;
	}

	if (client) {
		event.Skip(true);
		return;
	}

//	MutFrame *subframe = new MutFrame((wxFrame *) NULL,WK_ROUTE, wxString().Format(_("%s -- Routes"),_(PACKAGE_NAME)),
//		wxDefaultPosition,wxDefaultSize,wxDEFAULT_FRAME_STYLE | wxHSCROLL | wxVSCROLL);
//	subframe->SetIcon(ICON(route));

	SetId(WK_ROUTE);

	int width, height;

	GetClientSize(&width, &height);

	client = new MutRouteWnd(this, wxPoint(0, 0), wxSize(width, height));

	auimanager.AddPane(client,wxAuiPaneInfo().Caption(_("Routes")).CenterPane().PaneBorder(false));

	auimanager.Update();

	SetIcon(ICON(route));

	if (LogicOn) UpdateBoxMenu();
	
	SetSize(wxDefaultSize);

//	subframe->Show(true);

}

// TextBox-Arbeit: ToggleTextBox, TextBoxOpen, CmToggleKey, CmToggleTS

void MutFrame::LogicWinOpen(int box)
{
//  TMDIChild* curChild = Client->GetActiveMDIChild();
	/*  TMDIMutChild *Win = new TMDIMutChild(WK_LOGIC, GeWinAttr(WK_LOGIC, box), *Client, "", new TMutWin(0, Module));
	  Win->SetIcon(this, IDI_MUTABOR);
	  Win->SetIconSm(this, IDI_MUTABOR);
	  if (curChild && (curChild->GetWindowLong(GWL_STYLE) & WS_MAXIMIZE))
		  Win->Attr.Style |= WS_MAXIMIZE;
	  Win->Create();*/
//	MutChild *subframe = NewFrame(WK_LOGIC, box, _("Logic"), ICON(mutabor));



	int width, height;
	GetClientSize(&width, &height);
	width /= 2;
	height /= 2;
	MutLogicWnd *client = new MutLogicWnd(this, box,
	                                      wxPoint(0, 0),
	                                      wxSize(width,height));
	wxString Name;
	Name.Printf(_("Logic -- Box %d"),box);
	DEBUGLOG (other, _T("Adding pane '%s' with caption '%s'"), Name.Format(_T("Logic%d"),box).c_str(),Name.c_str());
	auimanager.AddPane(client,
	                   wxAuiPaneInfo().Name(Name.Format(_T("Logic%d"),box))
	                   .Caption(Name)
	                   .Bottom()
	                   .Floatable(true)
	                   .CloseButton(false)
	                   .MaximizeButton(true)
	                   .Float());
	client->SetFocus();
	auimanager.Update();
}

void MutFrame::ToggleTextBox(WinKind kind)
{
#ifdef DEBUG
	std::cerr << "MutFrame::ToggleTextBox: kind: " << kind << std::endl
	<< "MutFrame::ToggleTextBox: TextBoxWanted:"
	<< TextBoxWanted[curBox][kind] << std::endl;
#endif

	if (theFrame && (theFrame != this)) {
		theFrame->ToggleTextBox(kind);
		return;
	}


	TextBoxWanted[curBox][kind] = !TextBoxWanted[curBox][kind];

#ifdef DEBUG
	std::cerr << "MutFrame::ToggleTextBox: LogicOn"
	<< LogicOn << std::endl;
#endif

	if ( !LogicOn ) return;

#ifdef DEBUG
	std::cerr << "MutFrame::ToggleTextBox: IsOpen(kind, curBox)"
	<< IsOpen(kind, curBox) << std::endl;

#endif
	if ( IsOpen(kind, curBox) ) {
		wxWindow *win = Get(kind, curBox)->Win;
		//Get(kind, curBox)->Win->SendMessage(WM_CLOSE);
		auimanager.DetachPane(win);
		win->Close();
		auimanager.Update();
		//win->Close();
		//win->Destroy();
	} else
		TextBoxOpen(kind, curBox);
}

void MutFrame::TextBoxOpen(WinKind kind, int box)
{
	DEBUGLOG (other, _T("%d,%d"),kind,box);

	char *s = NULL;
	wxString title;

	switch ( kind ) {

	case WK_KEY:
		s = GetKeyString(box, asTS);

		title.Printf(_("Current keys at Box %d"),box);

		break;

	case WK_TS:
		s = GetTSString(box, asTS);

		title.Printf(_("Current tone system at Box %d"),box);

		break;

	case WK_ACT:
		if (CAW) {
			s = GenerateCAWString();
			title=_("Action log");
		} else {
			s = GenerateACTString(box);
			title.Printf(_("Actions at Box %d"),box);
		}

		break;

	case WK_LOGIC:
		wxLogWarning(_("Unexpected value: WK_LOGIC"));

		break;

	case WK_ROUTE:
		wxLogWarning(_("Unexpected value: WK_ROUTE"));

		break;

	case WK_EDIT:
		wxLogWarning(_("Unexpected value: WK_EDIT"));

		break;

	case WK_NULL:
		wxLogWarning(_("Unexpected value: WK_NULL"));

		break;

	default:
		wxLogError(_("Unexpected window kind: %d"), kind);
	}

	int width, height;

	GetClientSize(&width, &height);
	width /= 2;
	height /= 2;

	WinAttr *attr = GetWinAttr(kind, box);
	MutTextBox *client = new MutChild(kind,
	                                  attr,
	                                  this,
	                                  -1,
	                                  wxDefaultPosition,
	                                  wxSize(width, height));
	DEBUGLOG (other, _T("client->winKind=%d"),client->GetKind());
	DEBUGLOG (other, _T("s:= %s"),s);
	DEBUGLOG (other, _T("client->winKind=%d"),client->GetKind());

	wxString str;

	if (s)
		str = muT(s);
	else
		str = wxEmptyString;

	DEBUGLOG (other, _T("client->winKind=%d"),client->GetKind());

	auimanager.AddPane(client,wxAuiPaneInfo().Caption(title)
	                   .CloseButton(true).MaximizeButton(true)
	                   .Float()
	                   .Name(wxString::Format(_T("WK_%d_%d"),kind,box)));

	DEBUGLOG (other, _T("client->winKind=%d"),client->GetKind());

	client->NewText(str, true);

	DEBUGLOG (other, _T("client->winKind=%d"),client->GetKind());

	auimanager.Update();
}

void MutFrame::CmToggleKey(wxCommandEvent& WXUNUSED(event))
{
	ToggleTextBox(WK_KEY);
}

void MutFrame::CmToggleTS(wxCommandEvent& WXUNUSED(event))
{
	ToggleTextBox(WK_TS);
}

void MutFrame::CmToggleAct(wxCommandEvent& WXUNUSED(event))
{
	ToggleTextBox(WK_ACT);
}

void MutFrame::CmToggleOWM(wxCommandEvent& WXUNUSED(event))
{
	OWM = !OWM;

	if ( !LogicOn )
		return;

	if ( OWM ) {
		for (WinKind kind = WK_KEY; kind <= WK_LOGIC; kind++)
			for (size_t i = 0; i < WinAttrs[kind].Count(); i++)
				if ( WinAttrs[kind][i].Box != curBox && WinAttrs[kind][i].Win ) {
					WinAttrs[kind][i].Wanted = 2; // um Wanted zu erhalten
					auimanager.DetachPane(WinAttrs[kind][i].Win);
				}
	} else
		for (WinKind kind = WK_KEY; kind <= WK_LOGIC; kind++)
			for (size_t i = 0; i < WinAttrs[kind].Count(); i++)
				if ( WinAttrs[kind][i].Box != curBox && WinAttrs[kind][i].Wanted )
                                {
					if ( kind == WK_LOGIC )
						LogicWinOpen(WinAttrs[kind][i].Box);
					else
						TextBoxOpen(kind, WinAttrs[kind][i].Box);
                                }
}

void MutFrame::CmToggleCAW(wxCommandEvent& WXUNUSED(event))
{
	CAW = !CAW;

	if ( !LogicOn )
		return;

	// ActWin f¸r curBox updaten
	WinAttr *WinAttr = Get(WK_ACT, curBox);

	if ( WinAttr && WinAttr->Win )
		((MutTextBox*)WinAttr->Win)->NewText(CAW ? GenerateCAWString() : GenerateACTString(curBox), 1);

	// andere Action-Fenster schlieﬂen bzw. ˆffnen
	if ( CAW ) {
		for (size_t i = 0; i < WinAttrs[WK_ACT].Count(); i++)
			if ( WinAttrs[WK_ACT][i].Box != curBox && WinAttrs[WK_ACT][i].Win ) {
				WinAttrs[WK_ACT][i].Wanted = 2; // um Wanted zu erhalten
				auimanager.DetachPane(WinAttrs[WK_ACT][i].Win);
			}
	} else
		for (size_t i = 0; i < WinAttrs[WK_ACT].Count(); i++)
			if ( WinAttrs[WK_ACT][i].Box != curBox && WinAttrs[WK_ACT][i].Wanted )
				TextBoxOpen(WK_ACT, WinAttrs[WK_ACT][i].Box);
}

void MutFrame::CeToggleKey(wxUpdateUIEvent& event)
{
	event.Check(TextBoxWanted[curBox][WK_KEY]);
}

void MutFrame::CeToggleTS(wxUpdateUIEvent& event)
{
	event.Check(TextBoxWanted[curBox][WK_TS]);
}

void MutFrame::CeToggleAct(wxUpdateUIEvent& event)
{
	event.Check(TextBoxWanted[curBox][WK_ACT]);
}

void MutFrame::CeToggleOWM(wxUpdateUIEvent& event)
{
	event.Check(OWM);
}

void MutFrame::CeToggleCAW(wxUpdateUIEvent& event)
{
	event.Check(CAW);
}

void MutFrame::CmSelectBox()
{
	/*wx  TPopupMenu *Menu = new TPopupMenu();
	  Menu->AppendMenu(0, -1, "Select a box");
	  Menu->AppendMenu(MF_SEPARATOR	, -1, "");
	  for (int box = 0; box < MAX_BOX; box++)
	    if ( BoxUsed[box] )
	    {
	      char s[80];
	      sprintf(s, "Box %d", box);
	      Menu->AppendMenu((box == curBox) ? MF_CHECKED : 0, 10000+box, strdup(s));
	    }
	  TPoint p(200, 180);
	  GetMainWindow()->ClientToScreen(p);
	  Menu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON,
	    p, 0, *GetMainWindow(), 0);
	  delete Menu;*/
}

void MutFrame::CmCloseChild()
{
	if ( ChildToClose )
		ChildToClose->Close();
}

// Windowsize -------------------------------------------------------

wxSize subSize = wxDefaultSize;

int WSize[4][3] =
        { { 640, 530, 252},
          { 800, 646, 328},
          {1024, 826, 425},
          {1280, 994, 620} };

void MutFrame::WindowSize(MutChild *win)
{
	wxLogWarning(_("MutFrame::WindowSize:  not implemented" ));
#if 0

	if ( !subSize.IsFullySpecified() ) {
		wxScreenDC *sdc = new wxScreenDC();
		wxSize deskSize = sdc->GetSize();
		delete sdc;
		subSize.Set(0, 0);

		for (int i = 0; i < 4; i++)
			if ( deskSize.GetWidth() == WSize[i][0] )
				subSize.Set(WSize[i][1], WSize[i][2]);
	}

	if ( win->winAttr->W ) {
		win->SetSize(win->winAttr->X, win->winAttr->Y,
		             win->winAttr->W, win->winAttr->H);
	} else {
		int w, h;
		GetClientSize(&w, &h);
		// get size of editor window
		int w1 = w * 4 / 5, h1 = h * 2 / 3;

		if ( subSize.GetWidth() != 0 ) {
			w1 = subSize.GetWidth();
			h1 = subSize.GetHeight();
		}

		if ( w - w1 < 112 )
			w1 = w - 112;

		int n = (NumberOfOpen(win->winKind)-1)*22;

		if ( demo )
			switch ( win->winKind ) {

			case WK_KEY:
				win->SetSize(w / 2-n, n, w / 4, h / 2);

				break;

			case WK_TS:
				win->SetSize(w / 2 + w / 4-n, n, w / 4, h);

				break;

			case WK_ACT:
				win->SetSize(w / 2 + n, h / 2-n, w / 4, h - h / 2);

				break;

			case WK_LOGIC:
				win->SetSize(n, n, w / 2, h);

				break;

			case WK_ROUTE:
				win->SetSize(n, n, w / 2, h);

				break;
			}
		else
			switch ( win->winKind ) {

			case WK_KEY:
				win->SetSize(w1-n, n, w - w1, h / 2);

				break;

			case WK_TS:
				win->SetSize(w1-n, h / 2-n, w - w1, h - h / 2);

				break;

			case WK_ACT:
				win->SetSize(w1 * 3 / 4-n, h1-n, w1 - w1 * 3 / 4, h - h1);

				break;

			case WK_LOGIC:
				win->SetSize(n, h1-n, w1 * 3 / 4, h - h1);

				break;

			case WK_ROUTE:
				win->SetSize(n, h1-n, w1 * 3 / 4, h - h1);

				break;
			};
	}

#endif
}

//
// Save the the position and contents of the windows to the "desktop" file.
//
void MutFrame::SaveState()
{
	wxConfigBase *config = wxConfig::Get();

	wxPoint pos = GetPosition();
	wxSize size = GetSize();
	int DeskMax = size.GetWidth() < GetClientSize().GetWidth();
	config->SetPath(_T("Desktop"));
	config->Write(_T("X Position"),pos.x);
	config->Write(_T("Y Position"),pos.y);
	config->Write(_T("Width"),size.GetWidth());
	config->Write(_T("Height"),size.GetHeight());
	config->Write(_T("DeskMax"),DeskMax);

	config->SetPath(_T(".."));
}

/*bool CheckMutChild(char *name, char *data)
{
	for (TWinKind kind = WK_KEY; kind <= WK_ROUTE; kind++)
		if ( !stricmp(name, WinName[kind]) )
		{
      int box, x, y, w, h, wanted;
      int test = sscanf (data, " = %d %d %d %d %d %d",
        &box, &x, &y, &w, &h, &wanted);
		  if (test < 5)
		  {
		    break;
		  }
      TWinAttr *WinAttr = GetWinAttr(kind, box);
      WinAttr->X = x; WinAttr->Y = y;
      WinAttr->W = w; WinAttr->H = h;
      WinAttr->Wanted = wanted;
      return true;
	  }
  return false;
}*/

void MutFrame::RestoreState()
{
	//  int DeskMax = 1, WinMax = 2, HelpMax = 0;
	wxConfigBase *config = wxConfig::Get();
	
/* TODO: implement this in a robust way. The current implementation does not check that the window is inside the accesible area of the screen.
	int x=0, y=0, w=0, h=0;

	config->SetPath(_T("Desktop"));
	//  DeskMax=config->Read(_T("DeskMax"),0l);

	if ((x=config->Read(_T("X Position"),0l)) &&
	                (y=config->Read(_T("Y Position"),0l)) &&
	                (w=config->Read(_T("Width"),0l)) &&
	                (h=config->Read(_T("Height"),0l))) {
		SetSize(x, y, w, h);

#ifdef DEBUG
		std::cerr << "x=" << x << ", y=" << y << ", w=" << w << ", h=" << h << std::endl;
#endif
	}

	config->SetPath(_T(".."));
*/
	//  wxLogWarning(_("MutFrame::RestoreState() doesn't handle multiple windows"));
}

// Recorder-Knöpfe --------------------------------------------------

void MutFrame::StopInDev()
{
	int nr = 0;

	for ( InDevice *In = InDevice::GetDeviceList(); In; In = In->GetNext(), 
		nr++)
	  if ( In->GetMode() == MutaborDevicePlay || In->GetMode() == MutaborDevicePause ) {
	    //	    In->Mode = MutaborDeviceStop;
	    //		InDeviceAction(nr, In->Mode);
	    In->Stop();
	  }

	SetStatus(1-LogicOn);
}


void MutFrame::CmInDevStop(wxCommandEvent& WXUNUSED(event))
{
	StopInDev();
	repaint_route();
	SetStatus(1-LogicOn);
}

void MutFrame::CmInDevPlay(wxCommandEvent& event)
{
	DEBUGLOG (other, _T(""));

	if ( !LogicOn )
		CmDoActivate(event);

	int nr = 0;

	for ( InDevice *In = InDevice::GetDeviceList(); In; In = In->GetNext(), nr++)
	  if ( In->GetMode() == MutaborDeviceStop ||
	       In->GetMode() == MutaborDevicePause ) {
	    //			In->Mode = MutaborDevicePlay;
	    In->Play();
	    //			InDeviceAction(nr, In->Mode);
	  }
	
	repaint_route();

	SetStatus(SG_PLAY);
}

void MutFrame::CmInDevPause(wxCommandEvent& WXUNUSED(event))
{
  int nr = 0;

  for ( InDevice *In = InDevice::GetDeviceList(); In; In = In->GetNext(), nr++)
    if ( In->GetMode() == MutaborDevicePlay ) {
      //			In->Mode = MutaborDevicePause;
      //		InDeviceAction(nr, In->Mode);
      In->Pause();
    }
  
  repaint_route();
  
  SetStatus(SG_PAUSE);
}

void MutFrame::CeInDevStop(wxUpdateUIEvent& event)
{
  for ( InDevice *In = InDevice::GetDeviceList(); In; In = In->GetNext())
    if ( In->GetType() >= DTMidiFile &&
	 (In->GetMode() == MutaborDevicePlay ||
	  In->GetMode() == MutaborDevicePause) ) {
      event.Enable(true);
      return;
    }
  event.Enable(false);
}

void MutFrame::CeInDevPlay(wxUpdateUIEvent& event)
{
  if ( !LogicOn ) {
    DEBUGLOG (other, _T("Logic is off"));
    event.Enable(false);
    return;
  }

  for ( InDevice *In = InDevice::GetDeviceList(); In; In = In->GetNext()) {
    DEBUGLOG (routing, _T("checking Device type %d >= %d with mode %d for pointer %p"),
	      In->GetType(),
	      DTMidiFile,
	      In->GetMode(),
	      In);

    if ( In->GetType() >= DTMidiFile &&
	 (In->GetMode() == MutaborDeviceStop ||
	  In->GetMode() == MutaborDevicePause) ) {
      DEBUGLOG (other, _T("Device can be activated"));
      event.Enable(true);
      return;
    }
    
    DEBUGLOG (other, _T("Device can not be activated"));
  }

  event.Enable(false);
}

void MutFrame::CeInDevPause(wxUpdateUIEvent& event)
{
  bool Pause = 0;
  
  for ( InDevice *In = InDevice::GetDeviceList(); In; In = In->GetNext())
    if ( In->GetType() >= DTMidiFile ) {
      if ( In->GetMode() == MutaborDevicePlay ) {
	event.Enable(true);
	
	if ( curStatusImg != SG_PLAY )
	  SetStatus(SG_PLAY);
	
	return;
      } else if ( In->GetMode() == MutaborDevicePause )
	Pause = true;
    }
  if ( Pause ) {
    if ( curStatusImg != SG_PAUSE )
      SetStatus(SG_PAUSE);
  } else if ( curStatusImg != 1-LogicOn )
    SetStatus(1-LogicOn);
  
  event.Enable(false);
}

void MutFrame::CmSetTitle(wxCommandEvent& event)
{
	SetTitle(wxString::Format(_("%s -- %s"), APPNAME, event.GetString().c_str()));
}

// Updaten der Protokollfenster
void MutFrame::UpdateUI(wxCommandEvent& WXUNUSED(event))
{
	for (size_t i = 0; i < WinAttrs[WK_KEY].GetCount(); i++) {
		WinAttr *winAttr = &WinAttrs[WK_KEY][i];

		if ( winAttr->Win && KeyChanged(winAttr->Box) )
			((MutTextBox*)winAttr->Win)->
			NewText(GetKeyString(winAttr->Box, asTS), 1);
	}

	for (size_t i = 0; i < WinAttrs[WK_TS].GetCount(); i++) {
		WinAttr *winAttr = &WinAttrs[WK_TS][i];

		if ( winAttr->Win && TSChanged(winAttr->Box) )
			((MutTextBox*)winAttr->Win)->
			NewText(GetTSString(winAttr->Box, asTS), 1);
	}

	// Aktionen
	if ( TakeOverAktions() )
        {
		if ( CAW ) {
			WinAttr *winAttr = Get(WK_ACT, curBox);

			if ( winAttr && winAttr->Win )
				((MutTextBox*)winAttr->Win)->NewText(GenerateCAWString(), 1);
		} else {
			for (size_t i = 0; i < WinAttrs[WK_ACT].GetCount(); i++) {
				WinAttr *winAttr = &WinAttrs[WK_ACT][i];

				if ( winAttr->Win && ACTChanged(winAttr->Box) )
					((MutTextBox*)winAttr->Win)->
					NewText(GenerateACTString(winAttr->Box), 1);
			}
		}
        }
	// Zeilen/Spalte
	/*  if ( ActiveWinKind == WK_EDIT )
	    {
	    TMDIChild* curChild = Client->GetActiveMDIChild();
	    if ( curChild )
	    curChild->SendMessage(WM_COMMAND, CM_GETLINE);
	    }
	    else
	    EditLine = -1;
	    if ( EditLine != oldEditLine || EditRow != oldEditRow )
	    {
	    char s[10] = "";
	    if ( EditLine != -1 ) sprintf(s, "%d:%d", EditLine, EditRow);
	    IndikatorGadget->SetText(s);
	    oldEditLine = EditLine; oldEditRow = EditRow;
	    }*/


	if ( InDevicesChanged() ) {
		bool NRT_Finish = false;


		for (InDevice *In = InDevice::GetDeviceList(); In; In = In->GetNext()) {
		  if ( !In || In->GetMode() == MutaborDeviceCompileError ) continue;
		  if ( In->GetMode() ==  MutaborDeviceTimingError ) {
		    In->SetMode(MutaborDeviceStop);
		    In->Stop();
		    NRT_Finish = !RealTime;
		  }
		}

		repaint_route();

		if ( !RealTime )
			wxMessageBox(_("Translation in batch mode completed. Output was generated."),
			             _("Batch translation finished"), wxOK);
	}
}


#if 0
void MutFrame::OnIdle(wxIdleEvent& event)
{
  /// \todo check if this is correct
  //	wxCommandEvent event1(wxEVT_COMMAND_MENU_SELECTED, CM_UPDATEUI);
  //	UpdateUI(event1);
	event.Skip();
}
#endif

void MutFrame::OnEraseBackground(wxEraseEvent& event)
{
	if (client)
		event.Skip();
}

wxAuiDockArt* MutFrame::GetDockArt()
{
	std::cout << "MutFrame::GetDockArt()" << std::endl;
	return auimanager.GetArtProvider();
}



void MutFrame::OnSize(wxSizeEvent& event)
{
	event.Skip();
}



wxRect MutFrame::DetermineFrameSize ()
{
	DEBUGLOG (other, _T(""));

	wxSize scr = wxGetDisplaySize();

	// determine default frame position/size
	wxRect normal;
	wxPoint currpos = GetPosition();

	if (scr.x <= 800) {
		normal.x = 40 / 2;
		normal.width = scr.x - 40;
	} else {
		normal.x = currpos.x;
		normal.width = 800;			
	}

	if (scr.y <= 600) {
		normal.y = 80 / 2;
		normal.height = scr.y - 80;
	} else {
		normal.y = currpos.y;
		normal.height = 600;
	}

	return normal;
}

/// Close all child windows of given kind
/** This function closes all child windows of the given kind.
 *
 * \param kind any wk_kind, that describes which kind of windows shall
 * be closed.
 */
void MutFrame::CloseAll(WinKind kind)
{
	DEBUGLOG (other, _T(""));

	auimanager.Update();

	for (size_t i = WinAttrs[kind].Count(); i >0; i--) {
		DEBUGLOG (other, _T("kind %d (%d of %d)"),kind,i,WinAttrs[kind].Count());
		WinAttr &win = WinAttrs[kind].Item(i-1);

		if ( win.Win ) {
			DEBUGLOG (other, _("Closing window of class %s"), muT(typeid(*(win.Win)).name()).c_str());
			win.Wanted = 2;

			CloseClientWindow(win.Win);
			DEBUGLOG (other, _T("Returned."));
		}
	}
}

void MutFrame::UpdateBoxMenu()
{
#ifdef DEBUG
	std::cout << "MutFrame::CmDoActivate: Set Box selection menu" << std::endl;
#endif
	wxMenuItem * boxSelector = ClearMenuItem(CM_SELECTBOX);
	wxASSERT(boxSelector->IsSubMenu());
	wxMenu * boxMenu = boxSelector->GetSubMenu();
	wxASSERT(boxMenu);
	DEBUGLOG (other, _T("boxMenu = %p"),boxMenu);
	//  wxID_HIGHEST
	//  wxMenu *

	for (int i = 0, j=0; i < MAX_BOX; i++) {
		if (BoxUsed[i]) {
			if (theFrame == this) LogicWinOpen(i);

			if (!boxCommandIds[i]) {
				boxCommandIds[i]=wxNewId();
				DEBUGLOG (other, _("Box %d got id %d"),i,boxCommandIds[i]);
			}

			DEBUGLOG (other, _("Currently %d items in box menu"),boxMenu->GetMenuItemCount());

			DEBUGLOG (other, _("Appending menu for box %d with id %d"),i,boxCommandIds[i]);
			wxString name = wxString::Format(_("Select box %d\tCtrl+%d"),i,i);
                        wxString description = wxString::Format(_("Select box %d as the active Box for box specific commands."),i);
			wxASSERT(!(GetMenuBar()->FindItem(boxCommandIds[i])));
			wxMenuItem * item = new wxMenuItem(boxMenu,boxCommandIds[i],
			                                   name,
			                                   description,
			                                   wxITEM_RADIO);
			boxMenu->Append(item);

			if (i == curBox) boxMenu->Check(boxCommandIds[i],true);

			DEBUGLOG (other, _("Connecting command with id %d for box %d"),
			         i,boxCommandIds[i]);

			Connect( boxCommandIds[i],
			         wxEVT_COMMAND_MENU_SELECTED,
			         wxCommandEventHandler(MutFrame::RaiseLogic) );

		}
	}
}

bool MutFrame::RaiseTheFrame()
{
	if (this == theFrame) return true;

	theFrame->Raise();

	return false;
}

// Boxes used

bool BoxUsed[MAX_BOX];

void CheckBoxesUsed()
{
	for (int i = 0; i < MAX_BOX; i++)
		BoxUsed[i] = false;

	for (InDevice *In = InDevice::GetDeviceList(); In; In = In->GetNext())
	  for (Route *R = In->GetRoutes(); R; R = R->GetNext())
	    if ( R->Box >= 0 ) {
	      if (R->Box >= MAX_BOX) UNREACHABLE;
	      else
		BoxUsed[R->Box] = true;
	    }
}


int SmallestBoxUsed()

{
  int Box = MAX_BOX; // unused value

	for (InDevice *In = InDevice::GetDeviceList(); In; In = In->GetNext())
	  for (Route *R = In->GetRoutes(); R; R = R->GetNext())
	    if ( R->Box >= 0 )
	      Box = STD_PRE::min(Box, R->Box);

	if ( Box == MAX_BOX )
		return 0;
	else
		return Box;
}


//\}
