#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.


AC_PREREQ([2.67])
AC_INIT([Mutabor],[4.0.0rc1],[mutabor@mailbox.tu-dresden.de])

# we don't want to debug leaks while configuring.
# some checks trigger errors
ASAN_OPTIONS="detect_leaks=0"
export ASAN_OPTIONS

AC_ARG_ENABLE(XCode,
	AS_HELP_STRING([--enable-XCode],[Enable XCode compilation mode]),
	[XCode="$enableval"
])

AC_MSG_CHECKING(whether we are running from XCode)
if test -n "$XCode" -o -n "${XCODE_VERSION_MAJOR}"
then
	XCode=yes
	AC_MSG_RESULT($XCode)
	AC_MSG_CHECKING(XCode version)
	AC_MSG_RESULT(${XCODE_VERSION_MAJOR})
	ac_cv_prog_CC="gcc-$GCC_VERSION"
	ac_cv_prog_CXX="g++-$GCC_VERSION"
else
	AC_MSG_RESULT(no)
fi

AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AC_USE_SYSTEM_EXTENSIONS
echo target_os: $target_os
AC_CONFIG_SRCDIR([README.md])
AC_CONFIG_MACRO_DIR([m4])


AM_INIT_AUTOMAKE([dist-bzip2 silent-rules subdir-objects -Wall])
AS_IF(test "${enable_silent_rules+set}" != set,
   enable_silent_rules=yes
   AM_DEFAULT_VERBOSITY=0)
AM_CONDITIONAL(VPATH_BUILD, test "$ac_abs_confdir" != "$ac_pwd")

m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
AM_SILENT_RULES
LT_INIT

AC_CONFIG_HEADER([config.h])


dnl PACKAGE=$PACKAGE_NAME
dnl VERSION=$PACKAGE_VERSION
PACKAGE_TARNAME=mutabor

AC_SUBST(PACKAGE)
AC_SUBST(VERSION)
AC_DEFINE_UNQUOTED(PACKAGE, "$PACKAGE", [Name of this package])
AC_DEFINE_UNQUOTED(VERSION, "$VERSION", [Version of this package])

AC_DEFINE_UNQUOTED(PACKAGE_BUGREPORT, "$PACKAGE_BUGREPORT",
                                      [address for reporting bugs])

AM_OPTIONS_WXCONFIG


AH_TOP([
#ifndef MUTABOR_CONFIG_H_INCLUDED
#define MUTABOR_CONFIG_H_INCLUDED
/* We need this, because some autoconf tests rely on this (e.g. stpcpy)
    and it should be used for new programs anyway */
#define _GNU_SOURCE  1
])

AH_BOTTOM([
/* Debug also for Bison output. */
#ifdef DEBUG
/* #  define __WXDEBUG__ */
#  define YYDEBUG 1
#  ifndef _GLIBCXX_DEBUG
#    define _GLIBCXX_DEBUG
#  endif
#endif

#ifdef MUST_REUSE_C
#  define REUSE_C(x) x
#else
#  define REUSE_C(x)
#endif

#ifdef LOAD_LIBGNUINTL_H
#  include "libgnuintl.h"
#endif

#endif /* MUTABOR_CONFIG_H_INCLUDED */
])

wxflags=""
AM_MAINTAINER_MODE


# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AM_PROG_CC_C_O
PKG_PROG_PKG_CONFIG([0.14.0])

AC_LANG_PUSH(C++)
tmpcxxflags="$CXXFLAGS"
CXXFLAGS="$CXXFLAGS -pipe"
AC_MSG_CHECKING([whether $CXX supports -pipe])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
		[AC_MSG_RESULT([yes])],
		[CXXFLAGS="$tmpcxxflags"]
		[AC_MSG_RESULT([no])])
AC_LANG_POP(C++)
AC_LANG_PUSH(C)
tmpcflags="$CFLAGS"
CFLAGS="$CFLAGS -pipe"
AC_MSG_CHECKING([whether $CC supports -pipe])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
		[AC_MSG_RESULT([yes])],
		[CFLAGS="$tmpcflags"]
		[AC_MSG_RESULT([no])])
AC_LANG_POP(C)
DEBUGCPPFLAGS=
dnl for final we could consider --repo to reduce object size
AC_ARG_ENABLE(debug,
	AS_HELP_STRING([--enable-debug],[Enable extra debugging functionality]),
	[AS_IF(test "$enableval" = yes,
	       AC_DEFINE(DEBUG,1,[Define to 1 for compiling in debug mode.]),
               AC_DEFINE_UNQUOTED(DEBUG,[$enableval]))
	       CFLAGS="$CFLAGS -g"
	       CXXFLAGS="$CXXFLAGS -g -D_GLIBCXX_DEBUG -D__RTMIDI_DEBUG__"
	       AC_LANG_PUSH(C++)
	       for flag in -Wall  -Wno-unused-local-typedefs  -fdump-class-hierarchy \
	       	    -fbounds-check  -pedantic  -fdiagnostics-show-option  -Wno-long-long \
		     -Wno-variadic-macros -Wno-nested-anon-types -Wno-c++11-extensions -ggdb3 -g3 -fipa-icf
	       do
	       	       tmpcxxflags="$CXXFLAGS"
	       	       CXXFLAGS="$CXXFLAGS $flag"
		       AC_MSG_CHECKING([whether $CXX supports $flag])
      	       	       AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
	      	                         [AC_MSG_RESULT([yes])],
					 [CXXFLAGS="$tmpcxxflags"
              			         AC_MSG_RESULT([no])])
		       AC_LANG_PUSH(C)
	       	       tmpcflags="$CFLAGS"
	       	       CFLAGS="$CFLAGS $flag"
		       AC_MSG_CHECKING([whether $CC supports $flag])
      	       	       AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
	      	                         [AC_MSG_RESULT([yes])],
					 [CFLAGS="$tmpcflags"
              			         AC_MSG_RESULT([no])])
		       AC_LANG_POP(C)
	       done
dnl mudflap is not possible with g++ 4.7.1 and wxWidgets 2.8
dnl	       tmpcxxflags="$CXXFLAGS"
dnl	       tmplibs="$LIBS"
dnl	       CXXFLAGS="$CXXFLAGS -fmudflapth"
dnl	       LIBS="-lmudflapth"
dnl	       AC_MSG_CHECKING([whether $CXX supports  -fmudflapth -lmudflapth])
dnl      	       AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
dnl	       			[AC_MSG_RESULT([yes])],
dnl				[CXXFLAGS="$tmpcxxflags"
dnl				LIBS="$tmplibs"]
dnl	       			[AC_MSG_RESULT([no])])
dnl
	       case "$host_os" in
	       darwin*)
	       	       tmpcxxflags="$CXXFLAGS"
	       	       CXXFLAGS="$CXXFLAGS -ggdb"
		       	       AC_MSG_CHECKING([whether $CXX supports -ggdb])
			       AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
					       	 [AC_MSG_RESULT([yes])],
						 [CXXFLAGS="$tmpcxxflags"]
	       					 [AC_MSG_RESULT([no])])
		       AC_LANG_PUSH(C)
	       	       tmpcxxflags="$CFLAGS"
	       	       CXXFLAGS="$CFLAGS -ggdb"
		       	       AC_MSG_CHECKING([whether $CC supports -ggdb])
			       AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
					       	 [AC_MSG_RESULT([yes])],
						 [CFLAGS="$tmpcflags"]
	       					 [AC_MSG_RESULT([no])])
                       AC_LANG_POP(C)
			;;
	       esac
      	       AC_LANG_POP(C++)
	       wxflags="--debug"
])


AC_ARG_ENABLE(oink-support,
	AS_HELP_STRING([--enable-oink-support],[Prepare sources for Oink checks]),
	[AS_IF(test "$enableval" = yes,
	       AC_LANG_PUSH(C++)
	       for flag in -save-temps
	       do
	       	       tmpcxxflags="$CXXFLAGS"
	       	       CXXFLAGS="$CXXFLAGS $flag"
		       AC_MSG_CHECKING([whether $CXX supports $flag])
      	       	       AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
	      	                         [AC_MSG_RESULT([yes])],
					 [CXXFLAGS="$tmpcxxflags"
              			         AC_MSG_RESULT([no])])
		       AC_LANG_PUSH(C)
	       	       tmpcflags="$CFLAGS"
	       	       CFLAGS="$CFLAGS $flag"
		       AC_MSG_CHECKING([whether $CC supports $flag])
      	       	       AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
	      	                         [AC_MSG_RESULT([yes])],
					 [CFLAGS="$tmpcflags"
              			         AC_MSG_RESULT([no])])
		       AC_LANG_POP(C)
	       done
      	       AC_LANG_POP(C++)
	  )
])

AC_ARG_ENABLE(address-sanitizer,
	AS_HELP_STRING([--enable-address-sanitizer],[Enable gcc/clang address santizer]),
	[AS_IF(test "$enableval" = yes,

	       AC_LANG_PUSH(C++)
	       for flag in  -fsanitize=address  -fno-omit-frame-pointer  -fno-common
	       do
		       tmpcxxflags="$CXXFLAGS"
		       CXXFLAGS="$CXXFLAGS $flag"
		       AC_MSG_CHECKING([whether $CXX supports $flag])
		       AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
		                         [AC_MSG_RESULT([yes])],
					 [CXXFLAGS="$tmpcxxflags"
			         AC_MSG_RESULT([no])])
			AC_LANG_PUSH(C)
			tmpcflags="$CFLAGS"
			CFLAGS="$CFLAGS $flag"
			AC_MSG_CHECKING([whether $CC supports $flag])
			AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
		                          [AC_MSG_RESULT([yes])],
					  [CFLAGS="$tmpcflags"
			          AC_MSG_RESULT([no])])
			AC_LANG_POP(C)
	       done
	       tmpcxxflags="$CXXFLAGS"
	       CXXFLAGS="$CXXFLAGS -fsanitize-blacklist"
	       AC_MSG_CHECKING([whether $CXX supports $flag])
	       AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
	                         [AC_MSG_RESULT([yes])],
				 [CXXFLAGS="$tmpcxxflags"
		         AC_MSG_RESULT([no])])
		AC_LANG_PUSH(C)
		tmpcflags="$CFLAGS"
		CFLAGS="$CFLAGS $flag"
		AC_MSG_CHECKING([whether $CC supports $flag])
		AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
	                          [AC_MSG_RESULT([yes])],
				  [CFLAGS="$tmpcflags"
		          AC_MSG_RESULT([no])])
		AC_LANG_POP(C)
	       AC_LANG_POP(C++)
	       )
	]
)

AC_ARG_ENABLE(thread-sanitizer,
	AS_HELP_STRING([--enable-thread-sanitizer],[Enable gcc/clang thread santizer]),
	[AS_IF(test "$enableval" = yes,
	       AC_LANG_PUSH(C++)
	       for flag in  -fsanitize=thread  -fno-omit-frame-pointer  -fno-common
	       do
		       tmpcxxflags="$CXXFLAGS"
		       CXXFLAGS="$CXXFLAGS $flag"
		       AC_MSG_CHECKING([whether $CXX supports $flag])
		       AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
		                         [AC_MSG_RESULT([yes])],
					 [CXXFLAGS="$tmpcxxflags"
			         AC_MSG_RESULT([no])])
		       AC_LANG_PUSH(C)
		       tmpcflags="$CFLAGS"
		       CFLAGS="$CFLAGS $flag"
		       AC_MSG_CHECKING([whether $CC supports $flag])
		       AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
		                         [AC_MSG_RESULT([yes])],
					 [CFLAGS="$tmpcflags"
			         AC_MSG_RESULT([no])])
		       AC_LANG_POP(C)
	       done
dnl	       for flag in  -pie
dnl	       do
dnl		       tmpldflags="$LDFLAGS"
dnl		       LDFLAGS="$LDFLAGS $flag"
dnl		       AC_MSG_CHECKING([whether $LD supports $flag])
dnl		       AC_LINK_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
dnl		                         [AC_MSG_RESULT([yes])],
dnl					 [LDFLAGS="$tmpldflags"
dnl			         AC_MSG_RESULT([no])])
dnl	       done
dnl	       AC_LANG_POP(C++)
	       )
	]
)

AC_ARG_ENABLE(ansi,
	AS_HELP_STRING([--enable-ansi],[Enable strict ansi compiling and warnings]),
	[AS_IF(test "$enableval" = yes,
	       AC_DEFINE(ANSI,1,[Define to 1 for compiling in ansi mode.]),
               AC_DEFINE_UNQUOTED(ANSI,[$enableval]))
	 AX_CXXFLAGS_WARN_ALL_ANSI
	 AX_CFLAGS_WARN_ALL_ANSI
])
AC_ARG_ENABLE(gui,
	AS_HELP_STRING([--enable-gui],[Enable compiling ]),
	[AS_IF(test "$enableval" = yes,
	       AC_DEFINE(MUTWIN,1,[Define to 1 for compiling the gui version of $PACKAGE.]),
               AC_DEFINE_UNQUOTED(MUTWIN,[$enableval]))
],[
	       AC_DEFINE(MUTWIN,1,[Define to 1 for compiling the gui version of $PACKAGE.])
])
AM_WITH_DMALLOC
AC_DEFINE(RTMIDI,1,[Define to 1 for usage of the RtMidi Library.])

dnl Flex search as suggested at http://people.cs.aau.dk/~marius/sw/flex/Using-Flex-with-the-GNU-Build-System.html
dnl Sometimes Flex is installed as Lex, e.g., NetBSD.
AC_CHECK_PROG([FLEX], [flex lex], [flex])
dnl Force the use of `missing' to wrap Flex invocations.
AM_MISSING_PROG([LEX], [$FLEX])
dnl Perform all the tests Automake and Autoconf need.
AC_PROG_LEX

AC_PROG_YACC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MKDIR_P
AC_PATH_PROG(GIT,git)
AS_IF(test -n "$GIT",
	   tmpval=`$GIT --describe --tags 2>/dev/null`
	   AS_IF(test -z "$tmpval",GIT="")
)
AM_CONDITIONAL(COND_GIT, test -n "$GIT")
AC_PATH_PROG(PERL,perl)
AM_CONDITIONAL(COND_PERL, test -n "$PERL")
AS_IF(test -z "$PERL",
  AC_MSG_WARN([
          Some source files are generated using Perl. But I could not find
	  Perl. So changing those files will possibly have not the desired
	  effect.

	  Simple compiling should work fine. Otherwise complain at
	     $PACKAGE_BUGREPORT
	  please.
]))

AC_PATH_PROG(INKSCAPE,inkscape)
AM_CONDITIONAL(COND_INKSCAPE, test -n "$INKSCAPE")
dnl this test must be implemented if necessary
AC_SUBST(SHUFFLE,["sort -R"])


CXX_FOR_SCOPING
AS_IF(test "$cxx_cv_iso_for_loop_scope" = yes,
  AC_DEFINE(REUSE(x), x, [Define if variables must be declared again in for loops]),
  AC_DEFINE(REUSE(x), , [Define if variables must be declared again in for loops]))
#./  AC_DEFINE_UNQUOTED(MUST_REUSE, [$cxx_iso_for_loop_scope]))

# Checks for libraries.
AC_CHECK_LIB(m,pow)
AC_CHECK_LIB(backtrace,backtrace_print)

dnl check for boost earlier as it might correct the library path.
dnl some systems don't set it correctly
BOOST_REQUIRE([1.53.0])
dnl AX_BOOST_BASE([1.53.0])
PKG_PROG_PKG_CONFIG

AC_CANONICAL_HOST
AC_MSG_CHECKING(for MIDI API)
AC_SUBST( midiapi, [""] )

copydlls=false

echo $host_os

case "$host_os" in
dnl GNU/Linux on an Intel or compatible
*linux*)
	AC_LANG_PUSH(C++)
	tmpcxxflags="$CXXFLAGS"
	CXXFLAGS="$CXXFLAGS -fvisibility-inlines-hidden"
	AC_MSG_CHECKING([whether $CXX supports -fvisibility-inlines-hidden])
	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
				[AC_MSG_RESULT([yes])],
				[CXXFLAGS="$tmpcxxflags"]
				[AC_MSG_RESULT([yes])])
	AC_LANG_POP(C++)

	PLATFORM=linux

	AC_MSG_CHECKING(for MIDI API)
	AC_ARG_WITH(jack, [  --with-jack = choose JACK server support (mac and linux only)], [
		midiapi="$midiapi -D__UNIX_JACK__"
		AC_MSG_RESULT(using JACK)
		PKG_CHECK_MODULES(JACK,[jack], , AC_MSG_ERROR(JACK support requires the jack library!) ) ], )

	# Look for ALSA flag
	AC_ARG_WITH(alsa, [  --with-alsa = choose native ALSA sequencer API support (linux only)], [
	midiapi="$midiapi -D__LINUX_ALSA__"
	AC_MSG_RESULT(using ALSA)
	AC_CHECK_LIB(asound, snd_seq_open, , AC_MSG_ERROR(ALSA support requires the asound library!))], )

	if [[ "$midiapi" = "" ]]
	then
	    AC_MSG_RESULT(searching for ALSA and Jack)
	    AC_CHECK_LIB(asound, snd_seq_open)
	    if test "x$ac_cv_lib_asound_snd_seq_open" = xyes; then :
	      midiapi="$midiapi -D__LINUX_ALSA__"
	    fi
	    dnl the 4th argument to PKG_CHECK_MODULES should must be provided to prevent an error message, here
	    AS_IF(test -n "$PKG_CONFIG",
		    PKG_CHECK_MODULES([JACK],[jack],[midiapi="$midiapi -D__UNIX_JACK__"],[true]))
	fi

	if [[ "$midiapi" = "" ]]
	then
	    AC_MSG_ERROR(ALSA or Jack are needed to configure MIDI support!)
	fi

	# Checks for pthread library.
	AC_CHECK_LIB(pthread, pthread_create, , AC_MSG_ERROR(RtMidi requires the pthread library!))

	;;

darwin*)
	PLATFORM=macosx
	# Check for CoreAudio framework
	LIBS="$LIBS -framework CoreMIDI -framework CoreFoundation -framework CoreAudio"

	LDFLAGS="$LDFLAGS -framework Cocoa -framework Carbon -Wl,-Y,1455 -framework CoreAudio -framework CoreMIDI -framework CoreFoundation"

	  AC_ARG_WITH(jack, [  --with-jack = choose JACK server support (mac and linux only)], [
	    midiapi="$midiapi -D__UNIX_JACK__"
	    AC_MSG_RESULT(using JACK)
	    PKG_CHECK_MODULES(JACK,[jack], , AC_MSG_ERROR(JACK support requires the jack library!))], )

	 # Look for Core flag
	 AC_ARG_WITH(core, [  --with-core = choose CoreMidi API support (mac only)], [
		midiapi="$midiapi -D__MACOSX_CORE__"
		AC_MSG_RESULT(using CoreMidi)
		AC_CHECK_HEADER(CoreMIDI/CoreMIDI.h, [], [AC_MSG_ERROR(CoreMIDI header files not found!)] )
		LIBS="$LIBS -framework CoreMIDI -framework CoreFoundation -framework CoreAudio" ], )

	# If no api flags specified, use CoreMidi
	if [[ "$midiapi" = "" ]]
	then
	   AC_MSG_RESULT(using both CoreMIDI and Jack if possible)
	   AC_CHECK_HEADER(CoreMIDI/CoreMIDI.h,[
		midiapi="$midiapi -D__MACOSX_CORE__"]
		LIBS="$LIBS -framework CoreMIDI -framework CoreFoundation -framework CoreAudio"
	   , )
	   dnl the 4th argument to PKG_CHECK_MODULES should must be provided to prevent an error message, here
	   AS_IF(test -n "$PKG_CONFIG",
		    PKG_CHECK_MODULES(JACK,[jack],[midiapi="$midiapi -D__UNIX_JACK__"],))
	fi

	if [[ "$midiapi" = "" ]]
	then
	    AC_MSG_ERROR(Core MIDI or Jack are needed to configure MIDI support!)
	fi

	;;

*winnt*|*interix*|cygwin*|*mingw*|uwin*)
	PLATFORM=windows
	copydlls=true
	LT_LANG([Windows Resource])
	AC_LIBTOOL_LANG_RC_CONFIG
	AC_DEFINE(__USE_MINGW_ANSI_STDIO,1,[prefer POSIX printf & Co. over microsofts one])
	AC_DEFINE(_GNU_SOURCE,1)
	AC_CHECK_HEADERS([winsock2.h])
	AC_LANG_PUSH(C++)
	AC_CHECK_FUNCS([vasprintf])
	AC_LANG_POP(C++)
	AC_CHECK_LIB_HEADER(ws2_32,ntohs,[
	#include <winsock2.h>
	])
	# Look for WinMM flag
	AC_ARG_WITH(winmm, [  --with-winmm = choose Windows MultiMedia (MM) API support (windoze only)], [
	    midiapi="$midiapi -D__WINDOWS_MM__"
	    ac_includes_default="$ac_includes_default
#include <windows.h>
#include <mmsystem.h>
"
	    AC_LANG_PUSH(C)
	    AC_LIB_WINMM([midiOutGetNumDevs])
	    AC_LANG_POP(C)
	    AC_MSG_RESULT(using WinMM)
	    dnl LIBS="$LIBS -lwinmm
	    ], )

	AC_ARG_WITH(winks, [  --with-winks = choose kernel streaming support (windoze only)], [
	    api="$api -D__WINDOWS_KS__"
	    AC_SUBST( LIBS, ["-lsetupapi -lksuser"] )
	    AC_MSG_RESULT(using kernel streaming) ], )

  # 	    If no api flags specified, use WinMM
   	    if [[ "$api" = "" ]]
	    then
	    	    midiapi="$midiapi -D__WINDOWS_MM__"
	    	    ac_includes_default="$ac_includes_default
#include <windows.h>
#include <mmsystem.h>
"
		    AC_LANG_PUSH(C)
	    	    AC_LIB_WINMM([midiOutGetNumDevs])
		    AC_LANG_POP(C)
		    AC_MSG_RESULT(using WinMM)
		    dnl LIBS="$LIBS -lwinmm
	    fi

	if test "$cross_compiling" = yes; then
		case "$target_os" in
		mingw*|cygwin*)
			AC_MSG_NOTICE([
  Cross compiling for windows. Assuming you use a compiler
  with gcc style malloc and realloc.
            ])
			ac_cv_func_malloc_0_nonnull=yes
			ac_cv_func_realloc_0_nonnull=yes
			;;
		*)
			AC_MSG_WARN([
			Cross compiling for $target_os can not detect your
			compiler behavior. Please, contact the author and help
			supplying needed information!
			])
		esac
	fi
	AC_LANG_PUSH(C++)
	tmpcxxflags="$CXXFLAGS"
	CXXFLAGS="$CXXFLAGS -Wl,-Map,symbols.map"
	AC_MSG_CHECKING([whether $CXX supports -Wl,-Map,symbols.map])
	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
				[AC_MSG_RESULT([yes])],
				[CXXFLAGS="$tmpcxxflags"]
				[AC_MSG_RESULT([yes])])
	AC_LANG_POP(C++)
	AC_LANG_PUSH(C)
	tmpcflags="$CFLAGS"
	CFLAGS="$CFLAGS -Wl,-Map,symbols.map"
	AC_MSG_CHECKING([whether $CC supports ])
	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[]])],
				[AC_MSG_RESULT([yes])],
				[CXXFLAGS="$tmpcxxflags"]
				[AC_MSG_RESULT([yes])])
	AC_LANG_POP(C)

	;;
*)
	AC_MSG_ERROR([
		Your target system could not be recognized. $PACKAGE depends on
		a working MIDI configuration for your System. So it can't be built
		without knowing it.

		Please contact the Development team at

		    $PACKAGE_BUGREPORT

		and provide the following information:

		* The output of configure
		* The description of your System.

	])

esac
CPPFLAGS="$CPPFLAGS $midiapi"
AM_CONDITIONAL(COPYDLLS,$copydlls)

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.18])
AM_GNU_GETTEXT_INTL_SUBDIR
BISON_I18N
dnl wxMenuItem::GetItemLabel is implemented from 2.8.5
AM_PATH_WXCONFIG(2.8.5, wxWin=1, wxWin=0, [aui,adv,html,xrc,stc,xml,core],[$wxflags])
if test "$wxWin" != 1 -a -z "$XCode"; then
         AC_MSG_ERROR([
                wxWindows must be installed on your system
                but wx-config script couldn't be found.

                Please check that wx-config is in path, the directory
                where wxWindows libraries are installed (returned by
                'wx-config --libs' command) is in LD_LIBRARY_PATH or
                equivalent variable and wxWindows version is 2.8.0 or above.
        ])
	AC_SUBST(USE_INCLUDED_LIBWXINTL,no)
	AC_SUBST(BUILD_INCLUDED_LIBWXINTL,no)
else
	AC_DEFINE(WX,1,[Define to 1 if $PACKAGE should be compiled using wxWidgets.])
	AC_SUBST(WXINTLDIR,src/wxintl)
	AC_SUBST(USE_INCLUDED_LIBWXINTL,yes)
	AC_SUBST(BUILD_INCLUDED_LIBWXINTL,yes)
	AC_SUBST(WXINTLLDADD,[\$\(WXINTLDIR\)/libwxintl.a])
	AC_SUBST(WXINTLCFLAGS,[-I\$\(top_srcdir\)/$\(WXINTLDIR\)])
	AC_SUBST(USE_INCLUDED_LIBINTL,no)
	AC_SUBST(BUILD_INCLUDED_LIBINTL,no)
	CXXFLAGS="$CXXFLAGS -DRTMIDI_GETTEXT"
	WX_LIBS=`echo -n "$WX_LIBS"|sed -e 's/-mwindows//g'`
	enable_nls="no"
fi

case "`basename "$WX_CONFIG_PATH"`" in
inplace-*)
	wx_is_inplace=yes
	;;
*)
	wx_is_inplace=no
esac
AM_CONDITIONAL(WX_INPLACE,test "$wx_is_inplace")

AS_IF(test "$wx_is_inplace" = yes,
	   AC_CACHE_CHECK([for wxWidgets locale directories], [ac_cv_wx_locale_dirs],
	   [
		ac_cv_wx_locale_dirs="`$WX_CONFIG_WITH_ARGS --prefix`/locale"
	   ]),
	   AC_CACHE_CHECK([for wxWidgets locale directories], [ac_cv_wx_locale_dirs],
	   [

		for dir in `$WX_CONFIG_WITH_ARGS --prefix` \
		    /usr /usr/local /opt /opt/local ;
		do
			if test -d "$dir"/share/locale  ; then
			   found=""
			   for dirx in "$dir"/share/locale/*
			   do
			      test -f "$dirx"/LC_MESSAGES/wxstd.mo && found="yes"
			   done

			   if test "$found" = yes ; then
			      ac_cv_wx_locale_dirs="$ac_cv_wx_locale_dirs $dir/share/locale"
			   fi
			fi
		done
	  ])
)
AC_SUBST(WX_LOCALE_DIRS,$ac_cv_wx_locale_dirs)


AC_CACHE_CHECK([where to find support dlls], [ac_cv_mingw_dll_dirs],
[
       wxsearchdirs=`$WX_CONFIG_PATH --exec-prefix`/lib
       gccsearchdirs=`$CXX $CXXFLAGS -print-search-dirs|\
			sed -e '/^libraries:/ { s/^libraries: *=\?//;s/:/ /g; p } ; d'`
       SEARCHDIRS=""
       for d in $wxsearchdirs $gccsearchdirs /usr/share/doc/mingw32-runtime /mingw/lib /mingw/bin  /usr/lib /lib /usr/bin /bin
       do
	  AS_IF(test -d $d,
	  [ SEARCHDIRS="$SEARCHDIRS $d" ])
       done
       ac_cv_mingw_dll_dirs="$SEARCHDIRS"
])

AC_SUBST(DLLSEARCHPATH,"$ac_cv_mingw_dll_dirs")

AS_IF(test -n "$WX_RESCOMP",RC="$WX_RESCOMP")
AM_CONDITIONAL(COND_WINRC,test -n "$RC")
AS_IF(test "$PLATFORM" = "macosx",[
	COND_WINRC_TRUE='#'
	COND_WINRC_FALSE=
])

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_STDBOOL
AC_HEADER_TIME
AC_CHECK_HEADERS_ONCE([limits.h stddef.h math.h netinet/in.h sys/time.h malloc.h mcheck.h])
AC_LANG_PUSH(C++)
dnl AC_CHECK_HEADERS_ONCE is too restricted to check for C++ headers
AC_CHECK_HEADERS([FlexLexer.h])
AM_CONDITIONAL(COND_INTERNAL_FLEXLEXER,test "$ac_cv_header_FlexLexer_h" = "no" )
AC_LANG_POP(C++)
ac_includes_default="$ac_includes_default
#if HAVE_MALLOC_H
#  include <malloc.h>
#endif
"

dnl echo \|$HAVE_NETINET_IN_H\|
if test "$ac_cv_header_netinet_in_h" = no ; then
	AC_SUBST(NETINET_INC,"-I\$(top_srcdir)/includes/netinet")
fi
if test "$HAVE_MCHECK_H"; then
	AC_SUBST(MCHECK,"mcheck")
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_SIZE_T
AC_C_RESTRICT
AC_C_VOLATILE
AC_C_INLINE

AC_LANG_PUSH(C)
if test "$ac_cv_c_inline" != no ; then
  AC_DEFINE(HAVE_INLINE,1,[Define to 1 if the C Compiler supports inline functions.])
  AC_SUBST(HAVE_INLINE)
fi

dnl Check for "extern inline", using a modified version
dnl of the test for AC_C_INLINE from acspecific.mt
dnl
AC_CACHE_CHECK([for extern inline], ac_cv_c_extern_inline,
[ac_cv_c_extern_inline=no
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[extern $ac_cv_c_inline double foo(double x);
extern $ac_cv_c_inline double foo(double x) { return x+1.0; };
double foo (double x) { return x + 1.0; };]], [[  foo(1.0)  ]])],[ac_cv_c_extern_inline="yes"],[])
])

if test "$ac_cv_c_extern_inline" != no ; then
  AC_DEFINE(HAVE_EXTERN_INLINE,1,[Define to 1 if "extern inline" works.])
  AC_SUBST(HAVE_EXTERN_INLINE)
fi

AC_CACHE_CHECK([for variable scope in for loops in C mode], ac_cv_c_scope_reuse,
[
 AC_COMPILE_IFELSE([
	AC_LANG_PROGRAM([],[
	for (int i=1; i<3; i++) ;
	for (int i=1; i<4; i++) ;
	exit (0);
	])],[ac_cv_c_scope_reuse=inside],[ac_cv_c_scope_reuse=outside])
])

if test $ac_cv_c_scope_reuse = inside
then
	AC_DEFINE(MUST_REUSE_C,1,[Define to x if the scope of C loop variables is inside the loop])
fi

AC_LANG_PUSH(C++)
AC_CACHE_CHECK([syntax for signalling printf format attributes], ac_cv_format_arg,
[
 AC_COMPILE_IFELSE([
	AC_LANG_PROGRAM([
	int test (const char * auto, ...) __attribute_format_arg__(1);
	],[])],[ac_cv_format_arg="__attribute_format_arg__"],[])
 AS_IF(test -z "$ac_cv_format_arg",
  AC_COMPILE_IFELSE([
	AC_LANG_PROGRAM([
	int test (const char * auto, ...) __attribute__((format_arg(1)));
	],[])],[ac_cv_format_arg="__attribute__(format_arg(number))"],[]))
 AS_IF(test -z "$ac_cv_format_arg",
  AC_COMPILE_IFELSE([
	AC_LANG_PROGRAM([
	int test (const char * auto, ...) __attribute__((__format_arg__(1)));
	],[])],[ac_cv_format_arg="__attribute__(format_arg(number))"],[]))
 AS_IF(test -z "$ac_cv_format_arg",
  AC_COMPILE_IFELSE([
	AC_LANG_PROGRAM([
	int test (const char * auto, ...) __attribute__((__format_arg__(1)));
	],[])],[ac_cv_format_arg="__attribute__(format_arg(number))"],[]))
])

AS_IF(test "$ac_cv_format_arg" != __attribute_format_arg,
    AC_DEFINE_UNQUOTED(__mutabor_attribute_format_arg__(number,parameter),[$ac_cv_format_arg],[Define if the compiler does not support __attribute_format_arg__]))

AC_LANG_POP(C++)


AC_LANG(C++)

dnl AC_CACHE_CHECK([for variable scope in for loops in C++ mode], ac_cv_cxx_scope_reuse,
dnl [
dnl AC_COMPILE_IFELSE([
dnl	AC_LANG_PROGRAM([],[
dnl	for (int i=1; i<3; i++) ;
dnl	for (int i=1; i<4; i++) ;
dnl	exit(0);
dnl	])],[ac_cv_cxx_scope_reuse=inside],[ac_cv_cxx_scope_reuse=outside])
dnl ])
dnl if test $ac_cv_cxx_scope_reuse = inside
dnl then
dnl	AC_DEFINE(MUST_REUSE,1,[Define to x if the scope of C++ loop variables is inside the loop])
dnl fi

dnl BOOST_REQUIRE([1.53.0])
BOOST_LOCALE
BOOST_FORMAT
dnl BOOST_INTRUSIVE_PTR
dnl BOOST_RATIONAL
BOOST_FOREACH
dnl BOOST_SPIRIT
dnl BOOST_ALGORITHM
BOOST_SMART_PTR
BOOST_FILESYSTEM
BOOST_SYSTEM
BOOST_THREADS
BOOST_PROGRAM_OPTIONS

dnl AX_BOOST_FORMAT
dnl AX_BOOST_BASE
dnl AX_BOOST_SYSTEM
dnl AX_BOOST_FILESYSTEM
dnl AX_BOOST_IOSTREAMS
tmpcppflags="$CPPFLAGS"
CPPFLAGS="$CPPFLAGS $BOOST_CPPFLAGS"
AC_CHECK_HEADERS([boost/intrusive_ptr.hpp])
AC_CHECK_HEADERS([boost/rational.hpp])
AC_CHECK_HEADERS([boost/lexical_cast.hpp])
AC_CHECK_HEADERS([boost/foreach.hpp])
AC_CHECK_HEADERS([boost/format.hpp])
AC_CHECK_HEADERS([boost/spirit/core.hpp])
AC_CHECK_HEADERS([boost/spirit/actor/push_back_actor.hpp])
AC_CHECK_HEADERS([boost/exception/diagnostic_information.hpp])
AC_CHECK_HEADERS([boost/algorithm/string.hpp])
CPPFLAGS="$tmpcppflags"
AC_LANG_POP(C++)

AC_CACHE_SAVE
AC_ARG_ENABLE(precompile,
	AS_HELP_STRING([--enable-precompile],[use precompiled headers]),
	[ AX_COMPILER_PCH_CXX
	  AX_COMPILER_PCH_C
	  ],[
		AM_CONDITIONAL(COND_PRECOMP_C,false)
		AM_CONDITIONAL(COND_PRECOMP_CXX,false)
	  ])

# Checks for library functions.
AM_INTL_SUBDIR
AC_FUNC_MALLOC
AC_FUNC_ALLOCA
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MEMCMP
dnl AC_FUNC_REALLOC
AC_FUNC_SELECT_ARGTYPES
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([memmove pow getcwd gettimeofday memset select stpcpy strchr strstr bcopy bzero bcmp])
AC_CHECK_FUNC(strdup)
AC_FUNCTION_VECTOR_DATA

# Locate CppUnit (minimum version 1.8.0) for testing.
AM_PATH_CPPUNIT(1.8.0)

# You can set up an automake conditional and use it to conditionally
# build cppunit-using test programs.
AM_CONDITIONAL(HAVE_CPPUNIT, test "$CPPUNIT_LIBS")
CPPUNIT_CFLAGS="$CPPUNIT_CFLAGS -DMUTABOR_CPPUNIT -DMUTABOR_TEST"
DLLSEARCHPATH="$DLLSEARCHPATH `echo $CPPUNIT_LIBS  | tr ' ' '\n' | sed -e '/^-L/ { s/^-L//; s,$,/../bin, ; p }; d'`"

dnl non verbose

dnl AC_SUBST(top_srcdir_nsi,[`echo "$srcdir"|sed -e 's,/,\\\\,g'`])
AC_SUBST(top_srcdir_nsi,[`echo "$srcdir"|sed -e 's,/,/,g'`])

abspath () {
	if [[ -d "$1" ]]
	then
		pushd "$1" >/dev/null
		pwd
		popd >/dev/null
	elif [[ -e $1 ]]
	then
		pushd $(dirname $1) >/dev/null
		echo $(pwd)/$(basename $1)
		popd >/dev/null
	else
		echo $1 does not exist! >&2
		return 127
	fi
}

dnl preserve some variables for cross compiling
# propagate selected configure variables to DISTCHECK_CONFIGURE_FLAGS
for v in CPPFLAGS CXX CXXFLAGS CXXCPP LDFLAGS LIBS; do
    eval s=\${$v+set}
    if test "$s" = set
    then
       eval val=\$`echo $v`
       preserve_flags="${preserve_flags}'${v}=${val}' "
    fi
done
# propagate Host triplets to DISTCHECK_CONFIGURE_FLAGS
for v in host build target; do
    tmp="${v}_alias"
    eval s=\${$tmp+set}
    if test "$s" = 'set' ; then
       eval val=\$`echo $tmp`
       preserve_flags="${preserve_flags}'--${v}=${val}' "
    fi
done
# propagate certain configure options to DISTCHECK_CONFIGURE_FLAGS
for v in with-wx-config with-wx-dir with-boost with-cppunit-prefix with-cppunit-exec-prefix ; do
    tmp="`echo "$v" | sed -e 's/-/_/g'`"
    eval s=\${$tmp+set}
    if test "$s" = 'set' ; then
       eval val=\$`echo $tmp`
       val=`abspath "$val"`
       preserve_flags="${preserve_flags}'--${v}=${val}' "
    fi
done
DISTCHECK_CONFIGURE_FLAGS="$preserve_flags"

AC_SUBST(DISTCHECK_CONFIGURE_FLAGS)
AC_SUBST(LIBS)

AC_CONFIG_FILES([
po/Makefile.in
Makefile
intl/Makefile
src/includes/mutabor/Makefile
src/includes/mutabor/tests/Makefile
src/wxintl/tests/Makefile
lib/Makefile
lib/missfunc/Makefile
Images/Icons/png/16x16/Makefile
Images/Icons/png/20x20/Makefile
osdep/macosx/Info.plist
osdep/win/Mutabor.nsi
doc/Makefile
doc/mutabor.1
doc/localized/Makefile
doc/localized/de/Makefile
doc/localized/en/Makefile
Doxyfile
osdep/linux/OpenSuse.spec
tools/midi2text/Makefile
])
dnl src/wxintl/Makefile
dnl src/kernel/routing/midi/tests/Makefile
dnl src/kernel/routing/gmn/tests/Makefile
dnl src/kernel/routing/tests/Makefile
dnl src/tests/Makefile
dnl src/wxGUI/tests/Makefile
dnl src/kernel/tests/Makefile
dnl src/wxGUI/Routing/tests/Makefile
dnl Images/Makefile
dnl src/Makefile
dnl src/xrc/Makefile
dnl src/xrc/tests/Makefile
dnl src/wxGUI/Makefile
dnl src/wxGUI/generic/Makefile
dnl src/wxGUI/generic/tests/Makefile
dnl src/wxGUI/Routing/Makefile
dnl src/gmut/Makefile
dnl src/gmut/tests/Makefile
dnl src/includes/Makefile
dnl src/includes/netinet/Makefile
dnl src/includes/tests/Makefile
dnl src/kernel/Makefile
dnl src/kernel/routing/Makefile
dnl src/kernel/routing/midi/Makefile
dnl osrc/kernel/routing/gmn/Makefile
dnl src/kernel/parsers/Makefile
dnl src/kernel/parsers/scala/Makefile
dnl src/kernel/parsers/scala/tests/Makefile
dnl  src/libmutabor/lextables/Makefile
dnl  src/libmutabor/lextables/tests/Makefile
dnl  src/libmutabor/Makefile
dnl  src/libmutabor/tests/Makefile
dnl  dnl AC_CONFIG_FILES([
dnl libmutabor/Makefile
dnl libmutabor/tests/Makefile
dnl includes/mutabor/Makefile
dnl ])
AC_OUTPUT


