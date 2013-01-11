AM_CXXFLAGS = -I$(top_srcdir)
LDADD = \
	$(top_builddir)/atom/libatom-@ATOM_API_VERSION@.la

check_PROGRAMS = \
	check_blob \
	check_values

TESTS = $(check_PROGRAMS)

check_values_SOURCES = check_values.cpp
check_blob_SOURCES = check_blob.cpp

