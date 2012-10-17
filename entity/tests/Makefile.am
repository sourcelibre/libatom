AM_CXXFLAGS = -I$(top_srcdir)
LDADD = \
	$(top_builddir)/atom/libatom-@ATOM_API_VERSION@.la \
	$(top_builddir)/entity/libentity-@ENTITY_API_VERSION@.la

check_PROGRAMS = \
	check_entity

TESTS = $(check_PROGRAMS)

check_entity_SOURCES = check_entity.cpp

