/** \file                -*- bison -*-
 ********************************************************************
 * Scala parser gerneator file
 *
 * Copyright:   (c) 2016 Toblas Schlemmer
 * \author   Toblas Schlemmer <keinstein@users.sf.net>
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
 ********************************************************************
 * \addtogroup Parser
 * \{
 ********************************************************************/
/* Muta */
%skeleton "lalr1.cc"
%require "3.0.2"
/*			 %defines */
%define parser_class_name {scale_parser}
%define api.namespace {mutabor::scala_parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires
{
#include <string>
#include <cerrno>
#include "src/kernel/parsers/scala/scala.h"
namespace mutabor {
	namespace scala_parser {
			class scale_lexer;
        }
}
}
%param { scale_lexer & lexer }
%param { interval_pattern & result }
%param { keymap & keys }
%locations
%initial-action
{
	// intial location
	@$.begin.filename = @$.end.filename = &lexer.get_filename();
};
%define parse.trace
%define parse.error verbose
%code
{
#include "src/kernel/Defs.h"
#include "src/kernel/parsers/scala/scale_lexer.h"
#include "src/kernel/parsers/scala/scala-inlines.h"
#ifdef _
#undef _
#endif
#define _ _mut
#define YY_ _mut

// fix the interface to the scanner
#ifdef yylex
#undef yylex
#endif
#define yylex(x,y,z) lexer.get_token()

#if 0
#ifdef DEBUG
#define YYDEBUG 1
#endif
#endif
}
%define api.token.prefix {SCALA_TOKEN_}


/* %define api.token.prefix MUTABOR_TOKEN_ */
/* data types */
/*
        scl_data ".scl data"
        scl_data1 ".scl interval list"
        scl_data2 ".scl interval list (processed)"
        sclfile  ".scl file content"
        scl_data_start ".scl data header"
        scl_data_start1 ".scl data header (processed)"
*/
%token
	END 0        "end of file"
	SCL_START "Start token of a .scl file"
	KBM_START "Start token of a .kbm file"

%token <std::string>  STRING     "string token"
%token <std::string>  GARBAGE    "text after the last interval"
%token <std::string>  F_NUMBER   "floating point number"
%token <std::string>  INTEGER    "integer number"
%token <std::string>  SPACE      "white space"
%type  <std::string>  comment    "comment"
%type  <std::string>  comment_line   "single comment line"
%type  <int32_t>      integer    "integer (with leadig white space)"
%type  <int32_t>      nospace_integer    "integer"
%type  <int32_t>      ratio_start    "integer /"
%type  <double>       float      "double (with leadig white space)"
%type  <double>       nospace_float      "double"
%type  <std::string>  space      "whitespace"
%type  <std::string>  string     "character string with newline"
%type  <std::string>  lazy_string     "(non)empty character string with newline"
%type  <std::string>  string_element  "one of several tokens that can be in a string"
%type  <scala_parser::interval> interval "interval"
%type  <scala_parser::interval> interval1 "bare interval"
%type  <scala_parser::interval> interval2 "bare interval with description"
%type <scala_parser::scala_value<int32_t> > scala_int "scala int value"
%type <scala_parser::scala_value<int32_t> > scala_int1 "scala int value without comment"
%type <scala_parser::scala_value<double> > scala_float "scala double value"
%type <scala_parser::scala_value<double> > scala_float1 "scala double value without comment"
%type <scala_parser::key> key "key"
%type <scala_parser::key> key1 "key without comment"
%type <std::string> garbage     "The whole text after the file end"

%printer { yyoutput << $$; } <*>

%left '!' COMMENT_SIGN
%left STRING
%left '/' SLASH
%left '\n' NEWLINE



%% /* Grammar rules and actions */
%start scala_file;

scala_file: 	SCL_START sclfile
	|	KBM_START kbmfile
		;

kbmfile: 	kbm_data
                {
                   while (keys.keys.size() < (size_t)keys.count.value) {
			   keys.keys.push_back(scala_parser::key());
                   }
                   lexer.pop_state(scale_lexer::in_garbage);
                }
	|	kbm_data garbage END {
		std::swap(keys.garbage,$2);
		lexer.pop_state(scale_lexer::in_garbage);
		}
		;

sclfile:       	scl_data
                {
                   if (result.count != result.intervals.size()) {
			   error(@1,_mut("Too few intervals have been provided."));
                           YYERROR;
                   }
                   lexer.pop_state(scale_lexer::in_garbage);
                }
	|	scl_data garbage END {
		std::swap(result.garbage,$2);
		lexer.pop_state(scale_lexer::in_garbage);
		}
;
scl_data_start:	start_comment
		{ lexer.push_state(scale_lexer::in_string); } lazy_string {
	                std::swap(result.name,$3);
		        lexer.push_state(scale_lexer::in_integer);
		}
		count_comment
		interval_count
		{
		if (!result.count) {  lexer.push_state(scale_lexer::in_garbage); }
		else {
			result.intervals.reserve(result.count);
                        lexer.push_state(scale_lexer::in_interval);
		}
		}
	;

kbm_data_start: {
			lexer.push_state(scale_lexer::in_integer);
                }
		scala_int /* key count */
		scala_int /* lower MIDI boundary */
		scala_int /* upper MIDI boundary */
		scala_int /* reference key */
		scala_int /* anchor key */
		scala_float /* reference key frequency */
		scala_int /* repetition interval number */
		{
			lexer.pop_state(scale_lexer::in_integer);
			std::swap(keys.count,$2);
		        std::swap(keys.first_key,$3);
                        std::swap(keys.last_key,$4);
                        std::swap(keys.anchor,$5);
		        std::swap(keys.reference,$6);
                        std::swap(keys.reference_frequency,$7);
                        std::swap(keys.repetition_interval,$8);
			if (!keys.count.value) {
				lexer.push_state(scale_lexer::in_garbage);
		        }
 		        else {
			       keys.keys.reserve(keys.count.value);
		               lexer.push_state(scale_lexer::in_key);
		       }
		}
	;

kbm_data:	kbm_data_start
	|	kbm_data key {
	                keys.keys.push_back($2);
			DEBUGLOG(sclparser,"count: %d, size: %d",
		                 keys.count.value,
                                 keys.keys.size());
	                if ((size_t)keys.count.value == keys.keys.size()) {
			       lexer.pop_state(scale_lexer::in_key);
		               lexer.push_state(scale_lexer::in_garbage);
		        }
		}
		;



start_comment : /* empty */
	| 	comment { std::swap(result.comment1,$1); }
count_comment : /* empty */
	| 	comment { std::swap(result.comment2,$1); }

interval_count:	integer_number { lexer.pop_state(scale_lexer::in_integer); };

integer_number:integer string_end { result.count = $1; }
	| 	integer string { result.count = $1; std::swap(result.count_comment,$2); }
	| 	integer '.' {  lexer.push_state(scale_lexer::in_string); }  lazy_string {
		result.count = $1;
		std::swap(result.count_comment,$4);
		error(@3,_mut("The interval count must be an integer number, not a float."));
		}
	| 	integer '/' {  lexer.push_state(scale_lexer::in_string); }  lazy_string {
		result.count = $1;
		std::swap(result.count_comment,$4);
		error(@3,_mut("The interval count must be an integer number, not a ratio."));
		}
		;

scl_data:	scl_data_start
	|	scl_data interval {
	        result.intervals.push_back($2);
	        if (result.count == result.intervals.size()) {
			lexer.pop_state(scale_lexer::in_interval);
			lexer.push_state(scale_lexer::in_garbage);
		}
		}
		;

comment:	comment_line { std::swap($$,$1); }
	|	comment comment_line {
 	        std::swap($$,$1);
		$$ += "\n" + $2;
		}
	;
comment_line:	'!' { lexer.push_state(scale_lexer::in_string); } string {
			std::swap($$,$3);
		        lexer.pop_state(scale_lexer::in_string);
		}
		;

interval: 	interval2 {
	        $$.type = $1.type;
		$$.data = $1.data;
                std::swap($$.description,$1.description);
		lexer.pop_state(scale_lexer::in_string);
			}
	|	comment interval2 {
		$$.type = $2.type;
		$$.data = $2.data;
                std::swap($$.description,$2.description);
		std::swap($$.comment,$1);
		lexer.pop_state(scale_lexer::in_string);
			}
		;

interval2:	interval1 lazy_string {
		$$.type = $1.type;
		$$.data = $1.data;
                std::swap($$.description,$2);
		}
	|	integer lazy_string {
	        $$ = scala_parser::interval($1);
                std::swap($$.description,$2);
                lexer.push_state(scale_lexer::in_string);
		}
	| 	ratio_start lazy_string {
		lexer.error(@2, _mut("An incomplete ratio has been detected, and descriptions must not start with '/'."));
		$$ = scala_parser::interval($1);
                std::swap($$.description,$2);
		}
		;

interval1:	ratio_start integer {
		$$ = scala_parser::interval($1,$2);
                lexer.push_state(scale_lexer::in_string);
		}
	| 	ratio_start float {
		$$ = scala_parser::interval($1,$2);
                lexer.push_state(scale_lexer::in_string);
		}
	|	float {
		$$ = scala_parser::interval($1);
                lexer.push_state(scale_lexer::in_string);
		}
		;


key: 		key1 {
		$$.type = $1.type;
		$$.value = $1.value;
                std::swap($$.description,$1.description);
		lexer.pop_state(scale_lexer::in_string);
		}
	|	comment key1 {
		$$.type = $2.type;
		$$.value = $2.value;
                std::swap($$.description,$2.description);
		std::swap($$.comment,$1);
		lexer.pop_state(scale_lexer::in_string);
		}
		;

key1:		integer {
			lexer.push_state(scale_lexer::in_string);
		} lazy_string {
		$$.type = scala_parser::key::numeric;
	        $$.value = $1;
                std::swap($$.description,$3);
		}
	|	x {
			lexer.push_state(scale_lexer::in_string);
		} lazy_string {
		$$.type = scala_parser::key::empty;
                std::swap($$.description,$3);
		}
		;
x:		'x' | 'X';

scala_int: 	scala_int1 {
		$$.value = $1.value;
                std::swap($$.description,$1.description);
		lexer.pop_state(scale_lexer::in_string);
		}
	|	comment scala_int1 {
		$$.value = $2.value;
                std::swap($$.description,$2.description);
		std::swap($$.comment,$1);
		lexer.pop_state(scale_lexer::in_string);
		}
		;

scala_int1:	integer lazy_string {
	        $$.value = $1;
                std::swap($$.description,$2);
                lexer.push_state(scale_lexer::in_string);
		}
		;

scala_float: 	scala_float1 {
		$$.value = $1.value;
                std::swap($$.description,$1.description);
		lexer.pop_state(scale_lexer::in_string);
		}
	|	comment scala_float1 {
		$$.value = $2.value;
                std::swap($$.description,$2.description);
		std::swap($$.comment,$1);
		lexer.pop_state(scale_lexer::in_string);
		}
		;

scala_float1:	float lazy_string {
	        $$.value = $1;
                std::swap($$.description,$2);
                lexer.push_state(scale_lexer::in_string);
		}
		;


lazy_string:	string_end { $$.clear(); }
	|	space string_end { std::swap($$,$1); }
	|	string { std::swap($$,$1); }
	|	space string { std::swap($$,$1); $$ += $2; }
	;

ratio_sign:	'/'
	|	space '/'
	;

ratio_start:	integer ratio_sign  { $$ = $1; }
	;

string_element:	STRING { std::swap($$,$1); lexer.push_state(scale_lexer::in_string);  }
	|	string_element STRING { std::swap($$,$1); $$ += $2; }
		;

string_end:	'\n'
	|	END
		;

string: string_element string_end { std::swap($$,$1); lexer.pop_state(scale_lexer::in_string); }
		;




nospace_integer:INTEGER {
		errno = 0;
		long n = strtol ($1.c_str(), NULL, 10);
		if (! (0x80000000l+n >= 0 && n <= 0x7fFFffFFl && errno != ERANGE))
		lexer.error (@1, _mut("integer is out of range"));
		$$ = n;
		}
		;
integer: 	nospace_integer { $$ = $1; }
	|	space nospace_integer { $$ = $2; }
		;

nospace_float:	F_NUMBER {
		errno = 0;
                std::string tmp;
                tmp.reserve($1.length());
                for (std::string::iterator i = $1.begin();
		    i != $1.end();
		    ++i) {
			switch (*i) {
			case ' ':
		        case '\t':
                            break;
                        default:
                              tmp += *i;

		        }
		}
		double value = strtod(tmp.c_str(), NULL);
		if (! (errno != ERANGE))
		lexer.error (@1, _mut("float is out of range"));
		$$ = value;
		}

float: 		nospace_float { $$ = $1; }
	|	space nospace_float { $$ = $2; }
		;

space: 		space SPACE { std::swap($$,$1); $$ += $2; }
	|	SPACE { std::swap($$,$1); }
		;

garbage: 	GARBAGE { std::swap($$,$1); }
	|	garbage GARBAGE { std::swap($$,$1); $$ += $1; }
		;


%%
/// \		todo check whether this function is necessary for any system but windows

       /*
 void
yy::calcxx_parser::error (const location_type& l,
                          const std::string& m)
{
  driver.error (l, m);
}
       */

/*
 * \}
 */

namespace mutabor {
	namespace scala_parser {
		inline void scale_parser::error(location const& l, const std::string & s) {
			lexer.error(l,s.c_str());
		}
	}
}
