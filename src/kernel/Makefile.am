include %D%/tests/Makefile.am
include %D%/routing/Makefile.am
include %D%/parsers/Makefile.am

CLEANFILES += %D%/*.class


TSBUILTSOURCES += \
	%D%/mut.hh \
	%D%/mut.cc \
	%D%/mutlex.cc \
	%D%/parsers/scala/scale_parser.hh \
	%D%/parsers/scala/scale_parser.cc \
	%D%/parsers/scala/location.hh \
	%D%/parsers/scala/position.hh \
	%D%/parsers/scala/stack.hh \
	%D%/parsers/scala/scale_lexer.cc 

EXTRA_DIST += \
	%D%/mut.yy \
	%D%/mutlex.ll \
	%D%/mut.hh \
	%D%/mut.cc \
	%D%/mutlex.cc \
	%D%/parsers/scala/scale_parser.hh \
	%D%/parsers/scala/scale_parser.cc \
	%D%/parsers/scala/location.hh \
	%D%/parsers/scala/position.hh \
	%D%/parsers/scala/stack.hh \
	%D%/parsers/scala/scale_lexer.cc 

noinst_LIBRARIES += \
	%D%/libmutaborkernel.a

#-------------------------------------------------------------
# libmutaborkernel.a
#-------------------------------------------------------------

%C%_libmutaborkernel_a_INLINEHEADERS = \
		%D%/mut.cc \
		%D%/mut.hh \
		%D%/mutlex.cc

%C%_libmutaborkernel_a_INDENTHEADERS = \
		%D%/Defs.h \
		%D%/box.h \
		%D%/Errors.h \
		%D%/Execute.h \
		%D%/Frac.h \
		%D%/Global.h \
		%D%/Hilfs.h \
		%D%/Interpre.h \
		%D%/Interval.h \
		%D%/Parser.h \
		%D%/MidiKern.h \
		%D%/Runtime.h \
		%D%/TabGen.h \
		%D%/treestorage.h \
		%D%/mutlex.h \
		%D%/debug.h \
		%D%/interface_deps.h \
		%D%/cow_container.h


%C%_libmutaborkernel_a_INDENTS = \
		%D%/box.cpp \
		%D%/Errors.cpp \
		%D%/Execute.cpp \
		%D%/Frac.cpp \
		%D%/Hilfs.cpp \
		%D%/Interval.c \
		%D%/Parser.cpp \
		%D%/Runtime.cpp \
		%D%/TabGen.cpp \
		%D%/debug.cpp 

noinst_HEADERS += $(%C%_libmutaborkernel_a_INLINEHEADERS) $(%C%_libmutaborkernel_a_INDENTHEADERS)

%C%_libmutaborkernel_a_POTSOURCES = $(%C%_libmutaborkernel_a_INLINEHEADERS) $(%C%_libmutaborkernel_a_INDENTHEADERS) $(libmutaborkernel_a_INDENTS)

%C%_libmutaborkernel_a_SOURCES = $(%C%_libmutaborkernel_a_INDENTS) \
			%D%/mut.yy \
			%D%/mutlex.ll \
			%D%/parsers/scala/scale_parser.yy \
			%D%/parsers/scala/scale_lexer.ll

POTSOURCES += %C%_libmutaborkernel_a_POTSOURCES
