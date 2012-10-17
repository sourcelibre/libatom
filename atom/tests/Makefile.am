AM_CXXFLAGS = -I$(top_srcdir)
LDADD = \
	$(top_builddir)/atom/libatom-@ATOM_API_VERSION@.la

check_PROGRAMS = \
    check_atom \
	check_values

TESTS = $(check_PROGRAMS)

check_atom_SOURCES = check_atom.cpp
check_values_SOURCES = check_values.cpp

