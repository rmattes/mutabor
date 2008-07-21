/////////////////////////////////////////////////////////////////////////////
// Name:        MuMutTextBox.cpp
// Purpose:     Textbox for Lists
// Author:      R. Krauﬂe
// Modified by:
// Created:     12.08.05
// Copyright:   (c) R. Krauﬂe
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

// ===========================================================================
// declarations
// ===========================================================================

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------
#include <iostream>

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#include "Defs.h"
//#include "Mutabor.rh"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/tokenzr.h"
#include "MutTextBox.h"
#include "MutFrame.h"

wxString TextBoxTitle[] =
  { _("Current keys"), _("Tone system"), _("Actions") };

BEGIN_EVENT_TABLE(MutTextBox, wxListBox)
	EVT_CLOSE(MutTextBox::OnClose)
/*  EV_WM_SIZE,
  EV_WM_CHAR,
  EV_WM_SETFOCUS,
  EV_WM_RBUTTONDOWN,*/
END_EVENT_TABLE()

wxString ListInit[1] = { _("<init>") };

MutTextBox::MutTextBox(WinKind winKind,
		       WinAttr *winAttr, 
		       wxWindow* parent,
		       wxWindowID id, 
		       const wxPoint& pos, 
		       const wxSize& size): 
  wxListBox(parent, id, pos, size, 1, ListInit), 
  winAttr(winAttr),
  winKind(winKind)
{
  DEBUGLOG(_T(""));
/*  Attr.Style &= ~LBS_SORT;
  Attr.Style |= LBS_NOINTEGRALHEIGHT | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL | LBS_NOSEL;
  ColorBar1 = new TControl(this, 0, "", 1, 1, 1000, 1);
  ColorBar2 = new TControl(this, 0, "", 1, 1, 1, 1000);*/
  ColorBox = -1;
}


void MutTextBox::OnClose(wxCloseEvent& event)
{
  DEBUGLOG(_T(""));
  //	if ( LogicOn )
  TextBoxWanted[curBox][winKind] = false;
  //       	event.Skip(true);
  Destroy();
}

void MutTextBox::NewText(char *s, bool newTitle)
{
  DEBUGLOG(_T(""));
  // Text in Liste
  Clear();
  char s1[2000];
  int i = 0, j = 0;
  while ( s[i] )
  {
    if ( s[i] == '\r' || s[i] == '\n' )
    {
      s1[j] = 0;
      if ( j )
        Append(wxString(muT(s1)));
      j = 0;
      i++;
    }
    else
      s1[j++] = s[i++];
  }
  s1[j] = 0;
  if ( j )
    Append(wxString(muT(s1)));
  // Titel setzen
  if ( newTitle )
  {  
  
	std::cerr << "Not implemented: MutTextBox::NewText(...,newTitle=true);" << std::endl;
  /*
    GetParent()->SetName(PARENT_KIND != WK_ACT || !CAW ? wxString::Format(_("%s - Box %d"), TextBoxTitle[PARENT_KIND].c_str(), Box()) : wxString(_("Actions - all boxes")));
    int NewColorBox = UseColorBars ? Box() : -1;
    if ( ColorBox != NewColorBox )
    {
      ColorBox = NewColorBox;
	*/
/*wx      ColorBar1->SetBkgndColor(BoxColor(ColorBox));
      ColorBar2->SetBkgndColor(BoxColor(ColorBox));
      ColorBar1->Invalidate();
      ColorBar2->Invalidate();
      ColorBar1->SendMessage(WM_PAINT);
      ColorBar2->SendMessage(WM_PAINT);*/
//    }
  }
	// Scrollen, falls Aktion-Window
	if ( winKind == WK_ACT )
		SetSelection(GetCount()-1);
  // Farbbalken ggf. korrigieren
/*  if ( GetTopIndex() == 0 && PARENT_KIND != WK_ACT )
  {
    ColorBar1->MoveWindow(1, 1, 1000, 1, true);
    ColorBar2->MoveWindow(1, 1, 1, 1000, true);
  }*/
}

void MutTextBox::NewText(wxString s, bool newTitle)
{
  DEBUGLOG(_T(""));
  // Text in Liste
  Clear();
  
  
  
  wxStringTokenizer tokenizer(s,_T("\r\n"));
  while (tokenizer.HasMoreTokens()) 
	Append(tokenizer.GetNextToken());

  // Titel setzen
  if ( newTitle )
  {  
	std::cerr << "Not implemented: MutTextBox::NewText(...,newTitle=true);" << std::endl;

/*    GetParent()->SetName(PARENT_KIND != WK_ACT || !CAW ? wxString::Format(_("%s - Box %d"), TextBoxTitle[PARENT_KIND].c_str(), Box()) : wxString(_("Actions - all boxes")));
    int NewColorBox = UseColorBars ? Box() : -1;
    if ( ColorBox != NewColorBox )
    {
      ColorBox = NewColorBox;
	  */
/*wx      ColorBar1->SetBkgndColor(BoxColor(ColorBox));
      ColorBar2->SetBkgndColor(BoxColor(ColorBox));
      ColorBar1->Invalidate();
      ColorBar2->Invalidate();
      ColorBar1->SendMessage(WM_PAINT);
      ColorBar2->SendMessage(WM_PAINT);*/
//    }
  }

	// Scrollen, falls Aktion-Window
	if ( winKind == WK_ACT )
		SetSelection(GetCount()-1);
  // Farbbalken ggf. korrigieren
/*  if ( GetTopIndex() == 0 && PARENT_KIND != WK_ACT )
  {
    ColorBar1->MoveWindow(1, 1, 1000, 1, true);
    ColorBar2->MoveWindow(1, 1, 1, 1000, true);
  }*/
}

/*wx void MutTextBox::EvSize(uint sizeType, TSize &size)
{
  TListBox::EvSize(sizeType, size);
  TRect R = GetWindowRect();
  TRect RC = ColorBar1->GetWindowRect();
  if ( GetTopIndex() == 0 )
  {
    ColorBar1->MoveWindow(1, 1, 1000, 1, true);
    ColorBar2->MoveWindow(1, 1, 1, 1000, true);
  }
}
*/

/*wx void MutTextBox::EvChar(uint key, uint repeatCount, uint flags)
{
  TListBox::EvChar(key, repeatCount, flags);
  if ( 'A' <= key && key <= 'z' || key == VK_TAB
       || key == VK_UP || key == VK_DOWN
       || key == VK_LEFT || key == VK_RIGHT )
  {
    pubTaste = key;
    if ( IsOpen(WK_LOGIC, Box()) )
      GetWinAttr(WK_LOGIC, Box())->Win->SendMessage(WM_COMMAND, CM_TASTE);
    else
      KeyboardAnalyseSimple(Box(), key);
  }
}*/

/*wx void MutTextBox::EvSetFocus(HWND hWndLostFocus)
{
  TListBox::EvSetFocus(hWndLostFocus);
}

void
MutTextBox::EvRButtonDown(uint, TPoint& point)
{
  RightButtonMenu(this, point);
}*/


