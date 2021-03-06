/** \file               -*- C++ -*-
 ********************************************************************
 * Data structures for the scala file parser and generator.
 *
 * Copyright:   (c) 2016 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.sf.net>
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
/* available groups: GUI, Parser, route, kernel, debug, docview, config, GUIroute */

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(SRC_PARSERS_SCALA_SCALA_H) && !defined(PRECOMPILE)) \
	|| (!defined(SRC_PARSERS_SCALA_SCALA_H_PRECOMPILED))
#ifndef PRECOMPILE
#define SRC_PARSERS_SCALA_SCALA_H
#endif

/* ---------------------------------------------------------------------------
 * headers
 * --------------------------------------------------------------------------- */

#include "src/kernel/Defs.h"
#include "src/kernel/routing/box_support.h"

#ifndef SRC_PARSERS_SCALA_SCALA_H_PRECOMPILED
#define SRC_PARSERS_SCALA_SCALA_H_PRECOMPILED

/* system headers which do seldom change */
#include <vector>
#include <iostream>

namespace mutabor {
	namespace scala_parser {
		class scale_lexer;
		class scale_parser;
		class location;


		struct mutabor_writer_options {
			std::string prefix; //< Interval prefix
			std::string tone_prefix;
			std::string tonesystem_name;
			std::string logic_name;
		};

		template<class T>
		struct scala_value {
			std::string comment; //< Commant before the value
			T value;             //< the value
			std::string description; //< Text after the value
			scala_value():value() {}
			scala_value (const T & v):value(v) {}
			scala_value<T> & swap(scala_value & o);
			bool operator == (const scala_value <T> & o) const {
				return value == o.value &&
					description == o.description &&
					comment == o.comment;
			}

			scala_value & operator ++ () {
				++value;
				return *this;
			}

			std::ostream & print(std::ostream & o) const;
			std::ostream & print_mutabor(std::ostream & o,
						     const std::string & name,
						     bool in_comment = false) const;
			scala_value & operator = (const T & v) {
				value = v;
				return *this;
			}
		};
		template<class T>
		std::ostream & operator << (std::ostream & o, const scala_value<T> & v);

		struct interval {
			enum interval_type {
				cent_value,
				ratio,
				cent_ratio
			} type;
			union {
				struct {
					int32_t numerator;
					int32_t denominator;
				} f;
				struct {
					int32_t numerator;
					double denominator;
				} df;
				double cents;
			} data;
			std::string comment; // comments before the interval
			std::string description; // text following in the same line
			interval ():type(ratio){
				data.f.numerator = 1;
				data.f.denominator = 1;
			}
			interval (double c):type(cent_value) {
				data.cents = c;
			}
			interval (int32_t i):type(ratio) {
				data.f.numerator = i;
				data.f.denominator = 1;
			}
			interval (int32_t n, int32_t d):type(ratio) {
				data.f.numerator = n;
				data.f.denominator = d;
			}
			interval (int32_t n, double d):type(cent_ratio) {
				data.df.numerator = n;
				data.df.denominator = d;
			}
			std::ostream & print (std::ostream & o) const;
			std::ostream & print_mutabor_interval(std::ostream & o,
							      int i,
							      const mutabor_writer_options & w) const;
			bool operator == (const interval & o) const;
		};
		inline std::ostream & operator<< (std::ostream & o, const interval & i);
		typedef typename std::vector<interval> interval_list;

		struct interval_pattern {
			std::string comment1;
			std::string name;
			std::string comment2;
			size_t count;
			std::string count_comment;
			interval_list intervals;
			std::string garbage;
			interval_pattern() {}

			/// Create a scala interval pattern from a mutabor tone system
			/** This a kind of a “copy contructor”.
			 *
			 * \param t The tone system from which the interval pattern is extracted.
			 */
			interval_pattern(const mutabor::box_support::tone_system & t,
					 const std::string & n = _mut("Mutabor tuning"));

			interval_pattern(const std::string & n,
					 size_t c):name(n),count(c) {}
			bool operator == (const interval_pattern & o) const {
				return name == o.name &&
					count == o.count &&
					intervals == o.intervals &&
					comment1 == o.comment1 &&
					comment2 == o.comment2 &&
					count_comment==o.count_comment &&
					garbage == o.garbage;
			}
			std::ostream & print (std::ostream & o) const;
			std::ostream & print_mutabor (std::ostream & o,
						      const mutabor_writer_options & w) const;
		};

		std::ostream & operator << (std::ostream & o,
					    const interval_pattern & i);



		struct key:public scala_value<int32_t> {
			typedef scala_value<int32_t> base;
			enum key_type {
				numeric,
				empty
			} type;

			key ():base(-1),type(empty) {}
			key (int32_t i):base(i),type(numeric) {}
			std::ostream & print (std::ostream & o) const;
			std::ostream & print_mutabor_tone (std::ostream & o,
							   int i,
							   const mutabor_writer_options & w) const;
			bool operator == (const key & o) const;
		};
		typedef typename std::vector<key> key_list;


		std::ostream & operator<< (std::ostream & o, const key & i);

		struct keymap {
			scala_value <int32_t> count;
			scala_value <int32_t> first_key;
			scala_value <int32_t> last_key;
			scala_value <int32_t> anchor;
			scala_value <int32_t> reference;
			scala_value <double> reference_frequency;
			scala_value <int32_t> repetition_interval;
			key_list keys;
			std::string garbage;
			keymap() {}

			/// Create a scala keyboard mapping from a mutabor tone system
			/** This a kind of a “copy contructor”.
			 *
			 * \param t The tone system from which the keyboard mapping is extracted.
			 */
			keymap(const mutabor::box_support::tone_system & t);

			/// create a default keymap with n tones
			/** \param n number of tones to generate
			 */
			keymap(size_t n): count(n),
					  first_key(0),
					  last_key(127),
					  anchor(60),
					  reference(60),
					  reference_frequency(261.625565),
					  repetition_interval(n)
			{
				keys.reserve(n);
				for (size_t i = 0; i < n ; i++) {
					keys.push_back(key(i));
				}
			}
#ifdef DEBUG
			bool compare(const keymap & o) const;
#endif
			bool operator == (const keymap & o) const {
#ifdef DEBUG
				return compare (o);
#else
				return count == o.count &&
					first_key == o.first_key &&
					last_key == o.last_key &&
					reference == o.reference &&
					anchor == o.anchor &&
					reference_frequency == o.reference_frequency &&
					repetition_interval == o.repetition_interval &&
					keys == o.keys &&
					garbage == o.garbage;
#endif
			}
			std::ostream & print (std::ostream & o) const;
			std::ostream & print_mutabor (std::ostream & o,
						     const mutabor_writer_options & w) const;
		};

		std::ostream & operator << (std::ostream & o,
					    const keymap & i);

		struct error_handler {
			virtual ~error_handler() {}
			virtual void error(const location & loc,
					   const char * message) = 0;
		};

		class parser: public error_handler {
		public:
			/// Create a scala “parser” from a mutabor tone system
			/** This a kind of a “copy contructor”. We are abusing the
			 * scala parser container for writing scala files at the moment.
			 *
			 * \param t The tone system from which the interval pattern is extracted.
			 */
			parser(const mutabor::box_support::tone_system & t);

			parser (const std::string & s,
				const std::string & f): handler(this),
							intervals(),
							keys(),
							lexer(NULL),
							bison_parser(NULL)
			{
				parse(s,f);
			}
			virtual ~parser();

			void parse (const std::string & s,
				    const std::string & filename);

			void load_keymap(const std::string & s,
					 const std::string & filename);

			void make_keymap() {
				keys = keymap (intervals.count);
			}

			void make_keymap(size_t s) {
				keys = keymap(s);
			}

			error_handler * get_error_handler() const;
			void set_error_handler(error_handler * h);

			virtual void error(const location &loc, const char *  message);

			const interval_pattern & get_intervals () { return intervals; }
			const keymap & get_keys () { return keys; }


			std::ostream & write_mutabor(std::ostream & o,
						     const mutabor_writer_options & w);
			std::ostream & write_scala(std::ostream & o) {
				return o << intervals;
			}

			std::ostream & write_keymaps(std::ostream & o) {
				return o << keys;
			}
		protected:
			error_handler * handler;
			interval_pattern intervals;
			keymap keys;
			scale_lexer * lexer;
			scale_parser * bison_parser;
			//			keymap_parser * key_parser;
		};

		/// Define the scala writer class
		/** Due to lack of originality we can simply reuse the
		 * parser class. But such things tend to change in the
		 * future.  so we give the writer a unique name in
		 * order to be somewhat upwards compatible.
		 */
		 typedef parser writer;
	}
}

#endif /* precompiled */
#endif /* header loaded */


/** \} */
