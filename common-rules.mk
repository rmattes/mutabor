#AM_TESTS_ENVIRONMENT= $(top_srcdir)/run-test.sh
buildincludedir=$(top_builddir)
AM_CPPFLAGS = -I$(buildincludedir)  \
	-I$(top_srcdir)/includes \
	-I$(top_srcdir)/lib/rtmidi \
	-I$(top_srcdir) \
	@NETINET_INC@ \
	-I$(top_builddir)/intl \
	$(WX_CPPFLAGS) \
	-DPREFIX='"$(prefix)"' \
	$(BOOST_CPPFLAGS)
LIBS += $(JACK_LIBS) $(ALSA_LIBS) $(WX_LIBS)
#LIBS += $(BOOST_LDFLAGS)
LOCALEDIR = @localedir@
AM_CFLAGS = $(ALSA_CFLAGS) $(JACK_LIBS)  $(WX_CFLAGS) $(WXINTLCFLAGS) "-DLOCALEDIR=\"$(LOCALEDIR)\""
AM_CXXFLAGS = $(AM_CFLAGS)
AM_CXX = $(MAKE) $(AM_MAKEFLAGS) mutabor-precompile && $(CXX)
AM_YFLAGS = -d -v --report=all -x --graph
EXTRA_PROGRAMS =

TAGS_FILES = $(POTFILES)
AM_ETAGSFLAGS = -I --members --declarations -r '/inline[ \t]+\([^ \t(]+[ \t]+\)*\([^ \t(]+\)[ \t]*(/\2/m'

if COND_INTERNAL_FLEXLEXER
AM_CXXFLAGS += -I$(top_srcdir)/lib/includes/flex
endif

POTSOURCES = 

TSBUILTSOURCES = \
	$(top_srcdir)/src/xrc/wxresource.h \
	$(top_srcdir)/osdep/win/Mutabor.nsi

BUILT_SOURCES = $(TSBUILTSOURCES)

# no need to add debugPaths.cpp as it will be generated by the sources rules.
# it should be added to the nodist sources


SUFFIXES = .$(PCHEXT_CXX) .rc .res
INDENT = astyle --style=linux --indent=tab=8



CLEANFILES = \
	mutabor-cxxprecompiled.$(PCHEXT_CXX) \
	mutabor-cxxprecompiled.h \
	mutabor-cxxprecompiled.stamp \
	*.class \
	*.dll \
	TAGS


INDENTS = $(INDENTSOURCES) $(INDENTHEADERS) $(INLINEHEADERS)

noinst_HEADERS =  $(INDENTHEADERS) \
		  $(INLINEHEADERS)

mutabordir=$(datadir)/mutabor

DISTCLEANFILES = \
	libstdc++*.dll \
	libgcc*.dll \
	wx*.dll

DLLCOPYPATTERN = \(wx\|mingw\)
DLLEXEDIR = Mutabor



#-------------------------------------------------------------------------------------
# Overriding Yacc and Bison
#-------------------------------------------------------------------------------------

SUFFIXES += .h .l

.l.h:
	cd $(srcdir) && $(LEXCOMPILE) "`basename '$<'`"

#YACCCOMPILE = $(YACC) $(YFLAGS) $(AM_YFLAGS)
#
#
#.y.cpp: 
#	rm -f $*.h
#	$(MAKE) $*.h
#
#.y.h:
#	$(YACCCOMPILE) `test -f '$<' || echo '$(srcdir)/'`$<
#	if test -f y.tab.h; then \
#	  to=`echo "$*_H" | sed \
#		-e 'y/abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ/' \
#		-e 's/[^ABCDEFGHIJKLMNOPQRSTUVWXYZ]/_/g'`; \
#	  sed "/^#/ s/Y_TAB_H/$$to/g" y.tab.h >$*.ht; \
#	  rm -f y.tab.h; \
#	  if cmp -s $*.ht $*.h; then \
#	    rm -f $*.ht ;\
#	  else \
#	    mv $*.ht $*.h; \
#	  fi; \
#	fi
#	if test -f y.output; then \
#	  mv y.output $*.output; \
#	fi
#	sed '/^#/ s|y\.tab\.c|$@|' y.tab.c >$@t && mv $@t $@
#	mv y.tab.c $*.cpp
#

#-------------------------------------------------------------------------------------
# Compiling Windows Resources
#-------------------------------------------------------------------------------------

SUFFIXES += .rc

if COND_WINRC
.rc.$(OBJEXT):
	$(RCCOMPILE) $< $@
endif




.PHONY: mutabor-cxxprecompiled mutabor-cxxprecompiled.h.shuffle \
	mac mac-recursive 

#-------------------------------------------------------------------------------------
# Dealing with precompiled headers
#-------------------------------------------------------------------------------------

.h.$(PCHEXT_CXX):
if am__fastdepCXX
	if $(CXXCOMPILE) $(mutabor_CPPFLAGS) $(mutabor_CallFLAGS) -MT $@ \
		-MD -MP -MF "$(DEPDIR)/$*.Tpo" -o $@ \
		-c `test -f '$<' || echo '$(srcdir)/'`$<; \
	then mv -f "$(DEPDIR)/$*.Tpo" "$(DEPDIR)/$*.Po"; \
	else rm -f "$(DEPDIR)/$*.Tpo"; exit 1; fi 
else
if AMDEP
	source='$<' object='$@' libtool=no @AMDEPBACKSLASH@
	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) @AMDEPBACKSLASH@
endif
	$(CXXCOMPILE) $(mutabor_CPPFLAGS) $(mutabor_CallFLAGS) \
		 -c  `test -f '$<' || echo '$(srcdir)/'`$<
endif

#Makefile:remove-podeps.stamp $(srcdir)/Makefile.in $(top_builddir)/config.status
#	@case '$?' in \
#	  *config.status*) \
#	    echo ' $(SHELL) ./config.status'; \
#	    $(SHELL) ./config.status;; \
#	  *) \
#	    echo ' cd $(top_builddir) && $(SHELL) ./config.status $@ $(am__depfiles_maybe)'; \
#	    cd $(top_builddir) && $(SHELL) ./config.status $@ $(am__depfiles_maybe);; \
#	esac;

DISTCLEANFILES += podeps.stamp remove-podeps.stamp ./$(DEPDIR)/podeps.dep

podeps.stamp:remove-podeps.stamp
	touch $@

remove-podeps.stamp:Makefile
	rm -f podeps.stamp
	touch $@



./$(DEPDIR)/podeps.dep:$(precompCOMPILESOURCES) podeps.stamp
	$(MKDIR_P) `dirname $@`
	echo >$@
	for obj in $(mutabor_OBJECTS) ; do \
		base=`basename "$$obj"` ; \
		dir=`dirname "$$obj"` ; \
		pofilebase=`echo "$$base" | sed 's/\.$(OBJEXT)\$$/.Po/g'` ; \
		pofile="$$dir/\$$(DEPDIR)/$$pofilebase" ; \
		echo >>$@ ; \
		echo >>$@ ; \
		echo "$$pofile: $$pofile.stamp" >>$@ ; \
		echo "$$pofile.stamp:" >>$@ ; \
		echo "	-$(SED) -i 's/ mutabor-cxxprecompiled\.[a-zA-Z0-9]* / /g' $$pofile" >>$@ ; \
		echo '	touch $$@' >>$@ ; \
		echo >>$@ ; \
		echo "$$obj:$$pofile.stamp-remove" >>$@ ; \
		echo "$$pofile.stamp-remove:" >>$@ ; \
		echo "	rm -f '$$pofile.stamp'" >>$@ ; \
		echo '	touch $$@' >>$@ ; \
	done
@am__include@ @am__quote@./$(DEPDIR)/podeps.dep@am__quote@


if COND_PRECOMP_CXX

#./$(DEPDIR)/mutabor-cxxprecompiled.Po:fixdependencies.stamp

mutabor-cxxprecompiled.stamp:mutabor-cxxprecompiled.$(PCHEXT_CXX)
	if test \! -f mutabor-cxxprecompiled.stamp ; then touch mutabor-cxxprecompiled.stamp ; fi
	touch -d '2001-01-01 00:00:00' mutabor-cxxprecompiled.$(PCHEXT_CXX)
	touch -d '2002-01-01 00:00:00' $@

mutabor-cxxprecompiled:mutabor-cxxprecompiled.stamp


$(mutabor_OBJECTS):mutabor-cxxprecompiled.stamp


mutabor-cxxprecompiled.sorted: Makefile
	@echo 'creating $@'
	@for datei in $(INDENTHEADERS) ; \
	do  \
		echo $$datei | $(EGREP) '\.h$$' >/dev/null && \
		echo '#include "'"$$datei"'"' >>$@.tmp ; \
	done ; true
	@if cmp -s $@.tmp $@ ; then \
		rm -f $@.tmp ;\
        else \
		mv $@.tmp $@; \
	fi 

mutabor-cxxprecompiled.h:mutabor-cxxprecompiled.h.shuffle

mutabor-cxxprecompiled.h.shuffle: mutabor-cxxprecompiled.sorted
	$(MAKE) mutabor-cxxprecompiled.sorted
	@echo 'Shuffling mutabor-cxxprecompiled.h ...'
	echo '#define PRECOMPILE 1' >mutabor-cxxprecompiled.h
	echo '#include "src/kernel/Defs.h"' >> mutabor-cxxprecompiled.h
	$(SHUFFLE) <$< >> mutabor-cxxprecompiled.h
	echo '#undef PRECOMPILE' >> mutabor-cxxprecompiled.h
	touch -d '2000-01-01 00:00:00' mutabor-cxxprecompiled.h
	rm -f mutabor-cxxprecompiled.$(PCHEXT_CXX)
endif

#-------------------------------------------------------------------------------------
# Handling XRC
#-------------------------------------------------------------------------------------



Mutabor.xrc: $(top_srcdir)/src/xrc/Mutabor.xrc
	cp $< $@


$(top_srcdir)/src/xrc/wxresource.h : $(top_srcdir)/src/xrc/Mutabor.xrc
	(cd $(top_srcdir)/src/xrc; \
	wxrc -c -e -o wxresource.cpp Mutabor.xrc)

reslocale.cpp: $(top_srcdir)/src/xrc/reslocale.cpp $(top_srcdir)/src/xrc/Mutabor.xrc
$(top_srcdir)/src/xrc/reslocale.cpp : $(top_srcdir)/src/xrc/Mutabor.xrc
	(cd $(top_srcdir)/src/xrc; \
	wxrc -g -o reslocale.cpp Mutabor.xrc)

DEBUGPATHS =
BUILT_SOURCES += $(DEBUGPATHS)
$(DEBUGPATHS): Makefile
	@localpath=`dirname "$@"`; \
	echo '#include "src/kernel/Defs.h"' >"$@.tmp" ; \
	echo 'const char * srcdir = "$(top_srcdir)/'"$$localpath"'";' >> "$@.tmp" ; \
	echo 'const char * builddir = "'"$$localpath"'";' >> "$@.tmp" ; \
	echo 'const char * top_srcdir = "$(top_srcdir)";' >> "$@.tmp" ; \
	echo 'const char * top_builddir = "$(top_builddir)";' >> "$@.tmp" ; \
	cmp $@ $@.tmp && rm -f $@.tmp || ( mv "$@.tmp" "$@" ; echo "created $@")



#-------------------------------------------------------------------------------------
# Installing DLLs
#-------------------------------------------------------------------------------------


installdll:
	@echo 'solving references for $(DLLLINKFILE)... '
	DLLSEARCHPATH="$(DLLSEARCHPATH)" ; \
	for d in `LANG=C $(OBJDUMP) -p  $(DLLEXEDIR)/$(DLLLINKFILE) |sed '/^\s*DLL Name:.*\(lib\|thread\|wx\|mingw\|gcc\|stdc++\)/ { s/^\s*DLL Name:\s*//; p } ; d '` ; \
	do \
		echo -n checking "$$d ... " ; \
		if [ ! -f $(DLLEXEDIR)/$$d ] ; then \
			echo -n "searching... " ; \
			f=`( find $$DLLSEARCHPATH -name "$$d" || \
			find $$DLLSEARCHPATH -name "$$d.*")|head -n 1` ; \
			if test -f "$$f" ; \
			then \
				echo "installing $$f " ; \
				$(INSTALL_PROGRAM_ENV) $(INSTALL_DATA) "$$f" "`pwd`/$(DLLEXEDIR)" ; \
				case "$$f" in \
				*.gz)  GZIP=$(GZIP_ENV) gzip -dc $(DLLEXEDIR)/`basename "$$f"` >$(DLLEXEDIR)/"$$d" ;; \
				esac ; \
				$(MAKE) $(AM_MAKEFLAGS) DLLLINKFILE="$$d" DLLEXEDIR="$(DLLEXEDIR)" installdll ; \
			else \
				echo "not found." ; \
			fi ; \
		fi ; \
		echo "done." ;\
	done ;


#-------------------------------------------------------------------------------------
# Recursive generation of potfiles.chk
#-------------------------------------------------------------------------------------

CLEANFILES += POTFILES.tmp POTFILES.tmp.local $(DEBUGPATHS)

potfilechk-recursive:potfilechk-makerecursive

potfilechk-makerecursive:
	-test '$(RECURSIVE_TARGETS)' != 'potfilechk-recursive' && \
		$(MAKE) $(AM_MAKEFLAGS) RECURSIVE_TARGETS=potfilechk-recursive potfilechk-recursive -k

potfilechk: potfilechk-am

potfilechk-am: POTFILES.tmp.local

potfilechk-local:


POTFILES.tmp.local:Makefile
	-echo '$(POTSOURCES)' | tr ' ' "\n" | grep -e '\(\.cpp\|\.h\|\.c\|\.hpp\|\.rh\)' >$@

potfilechk: POTFILES.tmp Makefile
	$(MAKE) $(AM_MAKEFLAGS) potfilechk-local

POTFILES.tmp:POTFILES.tmp.local Makefile  potfilechk-recursive
	filelist="`echo $< ; \
		for d in $(SUBDIRS) ; \
		do \
			test '(' -f $$d/POTFILES.tmp ')' -a '(' $$d != . ')' && echo $$d/POTFILES.tmp ; \
		done`" ; \
	cat $$filelist|LC_ALL=C sort -u >$@


#-------------------------------------------------------------------------------------
# mf2txt and txt2mf generation
#-------------------------------------------------------------------------------------

midi2text: mf2txt txt2mf

mf2txt txt2mf:
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_builddir)/tools/midi2text $@$(EXEEXT)
	cp $(top_builddir)/tools/midi2text/$@$(EXEEXT) .

SUFFIXES += .mid .txt
.txt.mid:
	$(MAKE) $(AM_MAKEFLAGS) txt2mf
	./txt2mf $< $@
