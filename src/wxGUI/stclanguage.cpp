/** \file               -*- C++ -*-
********************************************************************
* Language definitions for wxStyledTextControl (wxScintilla)
*
* $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/wxGUI/stclanguage.cpp,v 1.3 2011/08/24 21:19:36 keinstein Exp $
* Copyright:   (c) 2011 TU Dresden
* \author  Tobias Schlemmer <keinstein@users.berlios.de>
* \date 
* $Date: 2011/08/24 21:19:36 $
* \version $Revision: 1.3 $
* \license GPL
*
*    This program is free software; you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation; either version 2 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software
*    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*
* $Log: stclanguage.cpp,v $
* Revision 1.3  2011/08/24 21:19:36  keinstein
* first run with 2.9.2+
*
* Revision 1.2  2011-08-21 16:52:05  keinstein
* Integrate a more sophisticated editor menu based on the stc sample
*
* Revision 1.1  2011-08-20 18:15:36  keinstein
* new files
*
*
*
********************************************************************
* \addtogroup src/wxGUI
* \{
********************************************************************/
#include "src/wxGUI/stclanguage.h"       // Preferences

namespace mutaborGUI {
//============================================================================
// declarations
//============================================================================

//----------------------------------------------------------------------------
//! language types
	const CommonInfo g_CommonPrefs = {
		// editor functionality prefs
		true,  // syntaxEnable
		true,  // foldEnable
		true,  // indentEnable
		// display defaults prefs
		false, // overTypeInitial
		false, // readOnlyInitial
		false,  // wrapModeInitial
		false, // displayEOLEnable
		false, // IndentGuideEnable
		true,  // lineNumberEnable
		false, // longLineOnEnable
		false, // whiteSpaceEnable
	};

//----------------------------------------------------------------------------
// keywordlists
// Mutabor
	const wxChar* MutSectionKeywords =
		_T("interval intervall logic logik midiin midiout tonsystem tonesystem ")
		_T("tone ton retuning umstimmung pattern harmonie ");
	const wxChar* MutOperators = 
		_T("* - / + wurzel root :");
	const wxChar* MutReservedWords =
		_T("shifted form key taste");
	const wxChar* MutDelimiters =
		_T("{ } [ ] ( ) << >>  < >");
	const wxChar* MutParameters =
		_T("distance abstand @");
//----------------------------------------------------------------------------
// keywordlists
// C++
	const wxChar* CppWordlist1 =
		_T("asm auto bool break case catch char class const const_cast ")
		_T("continue default delete do double dynamic_cast else enum explicit ")
		_T("export extern false float for friend goto if inline int long ")
		_T("mutable namespace new operator private protected public register ")
		_T("reinterpret_cast return short signed sizeof static static_cast ")
		_T("struct switch template this throw true try typedef typeid ")
		_T("typename union unsigned using virtual void volatile wchar_t ")
		_T("while");
	const wxChar* CppWordlist2 =
		_T("file");
	const wxChar* CppWordlist3 =
		_T("a addindex addtogroup anchor arg attention author b brief bug c ")
		_T("class code date def defgroup deprecated dontinclude e em endcode ")
		_T("endhtmlonly endif endlatexonly endlink endverbatim enum example ")
		_T("exception f$ f[ f] file fn hideinitializer htmlinclude ")
		_T("htmlonly if image include ingroup internal invariant interface ")
		_T("latexonly li line link mainpage name namespace nosubgrouping note ")
		_T("overload p page par param post pre ref relates remarks return ")
		_T("retval sa section see showinitializer since skip skipline struct ")
		_T("subsection test throw todo typedef union until var verbatim ")
		_T("verbinclude version warning weakgroup $ @ \"\" & < > # { }");

// Python
	const wxChar* PythonWordlist1 =
		_T("and assert break class continue def del elif else except exec ")
		_T("finally for from global if import in is lambda None not or pass ")
		_T("print raise return try while yield");
	const wxChar* PythonWordlist2 =
		_T("ACCELERATORS ALT AUTO3STATE AUTOCHECKBOX AUTORADIOBUTTON BEGIN ")
		_T("BITMAP BLOCK BUTTON CAPTION CHARACTERISTICS CHECKBOX CLASS ")
		_T("COMBOBOX CONTROL CTEXT CURSOR DEFPUSHBUTTON DIALOG DIALOGEX ")
		_T("DISCARDABLE EDITTEXT END EXSTYLE FONT GROUPBOX ICON LANGUAGE ")
		_T("LISTBOX LTEXT MENU MENUEX MENUITEM MESSAGETABLE POPUP PUSHBUTTON ")
		_T("RADIOBUTTON RCDATA RTEXT SCROLLBAR SEPARATOR SHIFT STATE3 ")
		_T("STRINGTABLE STYLE TEXTINCLUDE VALUE VERSION VERSIONINFO VIRTKEY");


//----------------------------------------------------------------------------
//! languages
	const LanguageInfo g_LanguagePrefs [] = {
		// Mutabor
		{_T("Mutabor"),
		 _T("*.mut;*.mus"),
		 _T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789'"),
		 wxSTC_LEX_CONTAINER,
		 {{MutSTCLexer::DEFAULT, NULL},
		  {MutSTCLexer::IDENTIFIER, NULL},
		  {MutSTCLexer::SECTIONKEYWORD, MutSectionKeywords},
		  {MutSTCLexer::OPERATOR, MutOperators},
		  {MutSTCLexer::RESERVEDWORD, MutReservedWords},
		  {MutSTCLexer::DELIMITER, MutDelimiters},
		  {MutSTCLexer::COMMENT, NULL},
		  {MutSTCLexer::NUMBER, NULL},
		  {MutSTCLexer::PARAMETER, MutParameters},
		  {MutSTCLexer::ERROR, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL}, // VERBATIM
		  {-1, NULL},
		  {-1, NULL}, // DOXY
		  {-1, NULL}, // EXTRA WORDS
		  {-1, NULL}, // DOXY KEYWORDS
		  {-1, NULL}, // KEYWORDS ERROR
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL}},
		 MutSTC_FOLD_COMMENT | MutSTC_FOLD_COMPACT | MutSTC_FOLD_PREPROC},
		// C++
		{_T("C++"),
		 _T("*.c;*.cc;*.cpp;*.cxx;*.cs;*.h;*.hh;*.hpp;*.hxx;*.sma"),
		 _T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_"),
		 wxSTC_LEX_CPP,
		 {{MutSTC_TYPE_DEFAULT, NULL},
		  {MutSTC_TYPE_COMMENT, NULL},
		  {MutSTC_TYPE_COMMENT_LINE, NULL},
		  {MutSTC_TYPE_COMMENT_DOC, NULL},
		  {MutSTC_TYPE_NUMBER, NULL},
		  {MutSTC_TYPE_WORD1, CppWordlist1}, // KEYWORDS
		  {MutSTC_TYPE_STRING, NULL},
		  {MutSTC_TYPE_CHARACTER, NULL},
		  {MutSTC_TYPE_UUID, NULL},
		  {MutSTC_TYPE_PREPROCESSOR, NULL},
		  {MutSTC_TYPE_OPERATOR, NULL},
		  {MutSTC_TYPE_IDENTIFIER, NULL},
		  {MutSTC_TYPE_STRING_EOL, NULL},
		  {MutSTC_TYPE_DEFAULT, NULL}, // VERBATIM
		  {MutSTC_TYPE_REGEX, NULL},
		  {MutSTC_TYPE_COMMENT_SPECIAL, NULL}, // DOXY
		  {MutSTC_TYPE_WORD2, CppWordlist2}, // EXTRA WORDS
		  {MutSTC_TYPE_WORD3, CppWordlist3}, // DOXY KEYWORDS
		  {MutSTC_TYPE_ERROR, NULL}, // KEYWORDS ERROR
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL}},
		 MutSTC_FOLD_COMMENT | MutSTC_FOLD_COMPACT | MutSTC_FOLD_PREPROC},
		// Python
		{_T("Python"),
		 _T("*.py;*.pyw"),
		 _T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_"),
		 wxSTC_LEX_PYTHON,
		 {{MutSTC_TYPE_DEFAULT, NULL},
		  {MutSTC_TYPE_COMMENT_LINE, NULL},
		  {MutSTC_TYPE_NUMBER, NULL},
		  {MutSTC_TYPE_STRING, NULL},
		  {MutSTC_TYPE_CHARACTER, NULL},
		  {MutSTC_TYPE_WORD1, PythonWordlist1}, // KEYWORDS
		  {MutSTC_TYPE_DEFAULT, NULL}, // TRIPLE
		  {MutSTC_TYPE_DEFAULT, NULL}, // TRIPLEDOUBLE
		  {MutSTC_TYPE_DEFAULT, NULL}, // CLASSNAME
		  {MutSTC_TYPE_DEFAULT, PythonWordlist2}, // DEFNAME
		  {MutSTC_TYPE_OPERATOR, NULL},
		  {MutSTC_TYPE_IDENTIFIER, NULL},
		  {MutSTC_TYPE_DEFAULT, NULL}, // COMMENT_BLOCK
		  {MutSTC_TYPE_STRING_EOL, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL}},
		 MutSTC_FOLD_COMMENTPY | MutSTC_FOLD_QUOTESPY},
		// * (any)
		{(const wxChar *)DEFAULT_LANGUAGE,
		 _T("*.*"),
		 _T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"),
		 wxSTC_LEX_PROPERTIES,
		 {{MutSTC_TYPE_DEFAULT, NULL},
		  {MutSTC_TYPE_DEFAULT, NULL},
		  {MutSTC_TYPE_DEFAULT, NULL},
		  {MutSTC_TYPE_DEFAULT, NULL},
		  {MutSTC_TYPE_DEFAULT, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL},
		  {-1, NULL}},
		 0},
	};

	const int g_LanguagePrefsSize = WXSIZEOF(g_LanguagePrefs);

//----------------------------------------------------------------------------
//! style types
	const StyleInfo g_StylePrefs [] = {
		// mySTC_TYPE_DEFAULT
		{_T("Default"),
		 _T("BLACK"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_WORD1
		{_T("Keyword1"),
		 _T("BLUE"), _T("WHITE"),
		 _T(""), 10, MutSTC_STYLE_BOLD, 0},

		// MutSTC_TYPE_WORD2
		{_T("Keyword2"),
		 _T("DARK BLUE"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_WORD3
		{_T("Keyword3"),
		 _T("CORNFLOWER BLUE"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_WORD4
		{_T("Keyword4"),
		 _T("CYAN"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_WORD5
		{_T("Keyword5"),
		 _T("DARK GREY"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_WORD6
		{_T("Keyword6"),
		 _T("GREY"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_COMMENT
		{_T("Comment"),
		 _T("FOREST GREEN"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_COMMENT_DOC
		{_T("Comment (Doc)"),
		 _T("FOREST GREEN"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_COMMENT_LINE
		{_T("Comment line"),
		 _T("FOREST GREEN"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_COMMENT_SPECIAL
		{_T("Special comment"),
		 _T("FOREST GREEN"), _T("WHITE"),
		 _T(""), 10, MutSTC_STYLE_ITALIC, 0},

		// MutSTC_TYPE_CHARACTER
		{_T("Character"),
		 _T("KHAKI"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_CHARACTER_EOL
		{_T("Character (EOL)"),
		 _T("KHAKI"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_STRING
		{_T("String"),
		 _T("BROWN"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_STRING_EOL
		{_T("String (EOL)"),
		 _T("BROWN"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_DELIMITER
		{_T("Delimiter"),
		 _T("ORANGE"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_PUNCTUATION
		{_T("Punctuation"),
		 _T("ORANGE"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_OPERATOR
		{_T("Operator"),
		 _T("BLACK"), _T("WHITE"),
		 _T(""), 10, MutSTC_STYLE_BOLD, 0},

		// MutSTC_TYPE_BRACE
		{_T("Label"),
		 _T("VIOLET"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_COMMAND
		{_T("Command"),
		 _T("BLUE"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_IDENTIFIER
		{_T("Identifier"),
		 _T("BLACK"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_LABEL
		{_T("Label"),
		 _T("VIOLET"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_NUMBER
		{_T("Number"),
		 _T("SIENNA"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_PARAMETER
		{_T("Parameter"),
		 _T("VIOLET"), _T("WHITE"),
		 _T(""), 10, MutSTC_STYLE_ITALIC, 0},

		// MutSTC_TYPE_REGEX
		{_T("Regular expression"),
		 _T("ORCHID"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_UUID
		{_T("UUID"),
		 _T("ORCHID"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_VALUE
		{_T("Value"),
		 _T("ORCHID"), _T("WHITE"),
		 _T(""), 10, MutSTC_STYLE_ITALIC, 0},

		// MutSTC_TYPE_PREPROCESSOR
		{_T("Preprocessor"),
		 _T("GREY"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_SCRIPT
		{_T("Script"),
		 _T("DARK GREY"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_ERROR
		{_T("Error"),
		 _T("RED"), _T("WHITE"),
		 _T(""), 10, 0, 0},

		// MutSTC_TYPE_UNDEFINED
		{_T("Undefined"),
		 _T("ORANGE"), _T("WHITE"),
		 _T(""), 10, 0, 0}

	};

	const int g_StylePrefsSize = WXSIZEOF(g_StylePrefs);


// Lexer
#ifdef DEBUG
	inline wxString cbGetSubstring(wxCharBuffer & b, size_t pos, size_t length) {
		return wxString::FromUTF8(b.data()+pos, length);
	}
#endif

	void MutSTCLexer::OnStyleNeeded(wxStyledTextEvent & event) {
		int pos = event.GetPosition();
		wxPoint editpos = editor->GetPosition();
		int laststyled = editor->GetEndStyled();
		DEBUGLOG(editlexer, 
			 _T("event.pos = %d, editor pos = (%d,%d), last syled pos = %d"),
			 pos,editpos.x,editpos.y,laststyled);
		int style = ERROR;
		if (laststyled) {
			style = editor->GetStyleAt(laststyled-1);
		}
		DEBUGLOG(editlexer,_T("laststyed style = %x"),style);

		wxCharBuffer text = editor->GetTextRangeRaw(laststyled,pos);
		int counter = 0; 
		int length = 0;

		editor->StartStyling (laststyled, 0x1f);

		do {
			mutChar c = text[counter+length];
			switch (style) {
			case COMMENT:
			{
				while ((counter+length < text.length())
				       && ((c = text[counter + length]) != '"')) length++;
				length++;
				laststyled = SetStyling(COMMENT, laststyled, length);
				
				DEBUGLOG(editlexer,
					 _T("comment: %s"),
					 cbGetSubstring(text,counter,length).c_str());
				counter += length;
				length = 0;
				style = ERROR;
			}
				break;
			}
			if (counter + length >= text.length()) break;
			c = text[counter+length];
			int newstyle = style;
			if (isspace(c)) newstyle = DEFAULT;
			else if ((isdigit(c) && style != IDENTIFIER) || c == '#') newstyle = NUMBER;
			else if (isalpha(c) || (style == IDENTIFIER && isdigit(c))|| c == '_' || c == '\'') 
				newstyle = IDENTIFIER;
			else switch (c) {
				case '+':
				case '-':
				case '*':
				case ':':
				case '/':
				case '~':
					newstyle = OPERATOR;
					break;
				case '[':
				case ']':
				case '(':
				case ')':
				case '<':
				case '>':
 				case '{':
				case '}':
					newstyle = DELIMITER;
					break;

				case '@':
					newstyle = PARAMETER;
					break;

				case '=':
				case ',':
				case ';':
					newstyle = OTHER;
					break;
				case '"':
					newstyle = COMMENT;
					break;
				default:
					newstyle = ERROR;
				}
			if (length && newstyle != style) {
				laststyled = SetStyling(style, laststyled, length);
				DEBUGLOG(editlexer,
					 _T("style %d: %s"),
					 style,
					 cbGetSubstring(text,counter,length).c_str());
				counter += length;
				length = 1;

			} else length++;
			style = newstyle;
			
		} while (counter+length < text.length());
		if (length) {
			laststyled = SetStyling(style, laststyled, length);
			DEBUGLOG(editlexer,
				 _T("style %d: %s"),
				 style,
				 cbGetSubstring(text,counter,length).c_str());
		}
		event.Skip();
	}

	int MutSTCLexer::SetStyling(int style, int pos, int length) {
		if (!editor) return pos;
#if wxCHECK_VERSION(2,9,0)
		wxTextAttr styleattrs(editor->StyleGetForeground(style),
				      editor->StyleGetBackground(style),
				      editor->StyleGetFont(style));
#endif
		int delta, endpos = pos+length;
		editor->SetStyling(endpos-pos,style);
#if wxCHECK_VERSION(2,9,0)
		//	editor->SetStyle(pos,pos+length,styleattrs);
#endif
#ifdef DEBUG
		for (size_t i = pos ; i< pos+length; i++) {
			if ((editor->GetStyleAt(i) & 0x1f) != style) {
				DEBUGLOG(editlexer,
					 _T("checking style at %d (%d – %d), %x == %x"),
					 (int)i,(int)pos,(int)pos+length,(int)editor->GetStyleAt(i),(int)style);
				mutASSERT((editor->GetStyleAt(i) & 0x1f) == style);
			}
		}
#endif
		return pos+length;
	}


}

///\}
