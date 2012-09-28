# "foreign" means not GNU, and is common for avoiding boring messages
# about files organized differently from what GNU expects

ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = foreign

SUBDIRS = \
    atom \
    build \
    doc

EXTRA_DIST = \
    COPYING \
    NEWS \
    README

# pkg-config file:
DISTCLEANFILES = atom.pc
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = atom-@ATOM_API_VERSION@.pc

html-local: htmldoc
htmldoc:
	@if [ -z `which doxygen` ]; then echo "No Doxygen!"; else doxygen; fi

# Documentation:

if HAVE_DOXYGEN

doxyfile.stamp:
	$(DOXYGEN) doxyfile
	echo `date -R` > doxyfile.stamp

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp

clean-local:
	rm -rf html

endif 

osx-pkg:
	@echo "Making atom .pkg installer for OSX";
	@echo "Creating build tree in /etc/atom";
	make DESTDIR=/tmp/atom install
	@echo "Running PackageMaker";
	@echo "...TODO";

