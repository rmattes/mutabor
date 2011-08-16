/** \file 
********************************************************************
* Document/View Document class for Mutabor source files.
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/muwx/MutDocument.cpp,v 1.6 2011/08/16 20:20:03 keinstein Exp $
* Copyright:   (c) 2011 TU Dresden
* \author  Tobias Schlemmer <keinstein@users.berlios.de>
* \date 
* $Date: 2011/08/16 20:20:03 $
* \version $Revision: 1.6 $
* \license GPL
*
* $Log: MutDocument.cpp,v $
* Revision 1.6  2011/08/16 20:20:03  keinstein
* Fix compiling on Mac OS X 10.5
*
* Revision 1.5  2011-08-11 19:00:48  keinstein
* get Document/View running.
* Needs further testing (possible segfaults).
*
* Revision 1.4  2011-08-06 09:20:16  keinstein
* documentation fixes
*
* Revision 1.3  2011-07-31 21:32:21  keinstein
* Slightly improved window positioning
* Suppress route window, when a Window is opened from the command line
*
* Revision 1.2  2011-07-31 20:16:04  keinstein
* Implemented opening files from command line using Document/View framework
*
* Revision 1.1  2011-07-31 12:40:41  keinstein
* Added classes and functions for Document/View support
*
*
*
********************************************************************
* \addtogroup docview
* \{
********************************************************************/
// availlable groups: GUI, route, kernel, muwx, debug

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "Defs.h"
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "MutDocument.h"
#include "MutView.h"
#include "MutApp.h"
#include <wx/debug.h>

#include <cstdio>
#include <iostream>

using mutaborGUI::MutDocument;
IMPLEMENT_DYNAMIC_CLASS(MutDocument, wxDocument)

BEGIN_EVENT_TABLE(MutDocument, wxDocument)
//	EVT_MENU(ID_NewViewFrame, MutDocument::CmdNewView)
//	EVT_UPDATE_UI(ID_NewViewFrame, MutDocument::OnNewViewUpdateUI)
//	EVT_MENU(ID_UpdateAllViews, MutDocument::CmdUpdateAllViews)
END_EVENT_TABLE()

namespace mutaborGUI {

	MutDocument::MutDocument():wxDocument()
	{


	}

	MutDocument::~MutDocument()
	{

	}


	bool MutDocument::DoSaveDocument(const wxString& filename)
	{
		MutView *view = (MutView *)GetFirstView();

		if (!view->GetTextsw()->SaveFile(filename))
			return false;

		return true;
	}

	bool MutDocument::DoOpenDocument(const wxString& filename)
	{
		MutView *view = (MutView *)GetFirstView();
		if (!view->GetTextsw()->LoadFile(filename))
			return false;
		DEBUGLOG(docview,_T("New title: ")+GetDocumentManager()->MakeFrameTitle(this));
		MutFrame * frame = view->GetMutFrame();
		if (frame)
			frame->SetTitle(GetDocumentManager()->MakeFrameTitle(this));
		return true;
	}

	bool MutDocument::OnNewDocument() 
	{
		if (!wxDocument::OnNewDocument()) 
			return false;
		DEBUGLOG(docview,_T("New title: ")+GetDocumentManager()->MakeFrameTitle(this));
		
		
		MutView *view = (MutView *)GetFirstView();
		if (view) {
			MutFrame * frame = view -> GetMutFrame();
			if (frame)
				frame -> SetTitle(GetDocumentManager()->MakeFrameTitle(this));
		} 
		return true;
	}

#if wxUSE_STD_IOSTREAM

	wxSTD ostream& MutDocument::SaveObject(wxSTD ostream& stream)
	{
		printf("cmydoc::saveobject\n");
		stream << 5;
		stream << 'j';
		return stream;
	}

	wxSTD istream& MutDocument::LoadObject(wxSTD istream& stream)
	{
		DEBUGLOG(docview,_T(""));
		bool bOK(false);
		int nA(0);
		char ch(0);

		stream >> nA;
		stream >> ch;

		if(stream.good())
		{
			DEBUGLOG(docview,_T("num is %d and char is %c"), nA, ch);
			bOK = true;
		}

		if(bOK == false)
		{
			DEBUGLOG(docview,_T("load error"));
			// tell the framework to abort the load procedure
			stream.clear(std::ios_base::badbit);
		}
		return stream;
	}

#else

	wxOutputStream& MutDocument::SaveObject(wxOutputStream& stream)
	{
		printf("mydoc::saveobject()\n");
		return stream;
	}

	wxInputStream& MutDocument::LoadObject(wxInputStream& stream)
	{
		printf("mydoc::loadobject()\n");
		return stream;
	}

#endif

	bool MutDocument::OnCreate(const wxString& path, long flags)
	{

		// you should call the one in the superclass
		return wxDocument::OnCreate(path, flags);
	}

	bool MutDocument::IsModified(void) const
	{
		MutView *view = (MutView *)GetFirstView();
		if (view && view -> GetTextsw())
		{
			return (wxDocument::IsModified() || view->GetTextsw()->IsModified());
		}
		else
			return wxDocument::IsModified();
	}

	void MutDocument::Modify(bool mod)
	{
		MutView *view = (MutView *)GetFirstView();

		wxDocument::Modify(mod);

		if (!mod && view && view->GetTextsw())
			view->GetTextsw()->DiscardEdits();
	}

	void MutDocument::CmdNewView(wxCommandEvent& event)
	{
		printf("MutDocument::CmdNewView\n");
		//wxMessageBox(wxT("doc newview 1"), _T("dialog"), wxOK | wxICON_INFORMATION, NULL);

		//  we manually create a view, and register it with the document.
		// the view needs to create a window for itself, which 
		//  it can do in OnCreate
		MutView* pview = new MutView();
		bool bKeep = pview->OnCreate(NULL, 0);
		if(bKeep)
		{
			AddView(pview);
			// we could set the title of the view's frame
			// AddView() does not set the document in the view, so we do that now
			pview->SetDocument(this);
		}
		else
		{
			// kill the view and its window. Hopefully nothing else.
			pview->Close(TRUE);
			// I don't think the Close function works
			wxFAIL;
		}	

		// wxMessageBox(wxT("doc newview 2"), _T("dialog"), wxOK | wxICON_INFORMATION, NULL);


	}

	void MutDocument::CmdUpdateAllViews(wxCommandEvent& event)
	{
		UpdateAllViews();
	}

	void MutDocument::OnNewViewUpdateUI(wxUpdateUIEvent& event)
	{
		event.Enable(true);
		// printf("MutDocument::OnNewViewUpdateUI\n");
	}

	
}


///\}
