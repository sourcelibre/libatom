SUBDIRS = tests

AM_CXXFLAGS = \
    $(LOG4CPP_CFLAGS) \
    $(BOOST_CPPFLAGS) \
    $(LIBXML_CFLAGS) \
    $(LIBLO_CFLAGS) \
    -I$(top_srcdir)

# XXX BOOST_FILESYSTEM_LIBS must be after BOOST_SYSTEM_LIBS

AM_LIBS = \
    $(BOOST_LIBS)  \
    $(BOOST_SYSTEM_LIBS) \
    $(BOOST_FILESYSTEM_LIBS) \
    $(BOOST_THREAD_LIBS) \
    $(LIBLO_LIBS) \
    $(LIBXML_LIBS) \
    $(LOG4CPP_LIBS)

# this file is not installed, just included by .cpp files at compile time.
EXTRA_DIST = config.h

# use lib_LTLIBRARIES to build a shared lib:
lib_LTLIBRARIES = libatom-@ATOM_API_VERSION@.la

## Instruct libtool to include ABI version information in the generated shared
## library file (.so).  The library ABI version is defined in configure.ac, so
## that all version information is kept in one place.
libatom_@ATOM_API_VERSION@_la_LDFLAGS = -export-dynamic -version-info $(ATOM_SO_VERSION) $(AM_LIBS)
libatom_@ATOM_API_VERSION@_la_LIBS = $(AM_LIBS)
libatom_@ATOM_API_VERSION@_la_CXXFLAGS = $(AM_CXXFLAGS)
libatom_@ATOM_API_VERSION@_la_includedir = $(includedir)/atom-$(ATOM_API_VERSION)/atom

## Define the source file list for the "libatom-@ATOM_API_VERSION@.la"
## target.  Note that @ATOM_API_VERSION@ is not interpreted by Automake and
## will therefore be treated as if it were literally part of the target name,
## and the variable name derived from that.
## PLEASE KEEP THEM IN ALPHABETICAL ORDER
libatom_@ATOM_API_VERSION@_la_SOURCES = \
    atom.cpp

## PLEASE KEEP THEM IN ALPHABETICAL ORDER
libatom_@ATOM_API_VERSION@_la_include_HEADERS = \
    atom.h \
	version.h

