SUBDIRS = tests

AM_CXXFLAGS = \
    -I$(top_srcdir) \
    $(SIGC_CFLAGS) \
    $(LOG4CPP_CFLAGS)

# XXX BOOST_FILESYSTEM_LIBS must be after BOOST_SYSTEM_LIBS

AM_LIBS = \
    $(SIGC_LIBS) \
    $(LOG4CPP_LIBS)

# this file is not installed, just included by .cpp files at compile time.
EXTRA_DIST = config.h

# use lib_LTLIBRARIES to build a shared lib:
lib_LTLIBRARIES = libentity-@ENTITY_API_VERSION@.la

## Instruct libtool to include ABI version information in the generated shared
## library file (.so).  The library ABI version is defined in configure.ac, so
## that all version information is kept in one place.
libentity_@ENTITY_API_VERSION@_la_LDFLAGS = -export-dynamic -version-info $(ENTITY_SO_VERSION) $(AM_LIBS)
libentity_@ENTITY_API_VERSION@_la_LIBS = $(AM_LIBS)
libentity_@ENTITY_API_VERSION@_la_CXXFLAGS = $(AM_CXXFLAGS)
libentity_@ENTITY_API_VERSION@_la_includedir = $(includedir)/entity-$(ENTITY_API_VERSION)/entity

## Define the source file list for the "libatom-@ATOM_API_VERSION@.la"
## target.  Note that @ATOM_API_VERSION@ is not interpreted by Automake and
## will therefore be treated as if it were literally part of the target name,
## and the variable name derived from that.
## PLEASE KEEP THEM IN ALPHABETICAL ORDER
libentity_@ENTITY_API_VERSION@_la_SOURCES = \
    attribute.cpp \
    entity.cpp \
    entitymethod.cpp \
    entitysignal.cpp \
    logger.cpp \
    documented.cpp \
    namedobject.cpp

## PLEASE KEEP THEM IN ALPHABETICAL ORDER
libentity_@ENTITY_API_VERSION@_la_include_HEADERS = \
    attribute.h \
    entity.h \
    entitymethod.h \
    entitysignal.h \
    exceptions.h \
    namedobjectmap.h \
    documented.h \
    logger.h \
    namedobject.h \
    version.h

