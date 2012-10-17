# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])
AC_INIT(atom, [0.1.5], [http://code.sat.qc.ca/redmine/projects/libatom/issues], [libatom], [http://code.sat.qc.ca/redmine/projects/libatom])
AC_CONFIG_MACRO_DIR([m4])
AC_MSG_NOTICE([Configuring libatom])
AM_INIT_AUTOMAKE([subdir-objects -Wno-portability])
AC_CONFIG_HEADERS([atom/config.h])
AC_CANONICAL_HOST # fills $host variable

# Define these substitions here to keep all version information in one place.
# For information on how to properly maintain the library version information,
# refer to the libtool manual, section "Updating library version information":
# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
# see http://sourceware.org/autobook/autobook/autobook_91.html
# format is [current:revision:age]
# libtool versioning is different than the project's versioning. It's for the ABI and API.
# It's in the form "current:revision:age" where:
#  * current: Increment when the interface changes. (and set revision to 0)
#  * revision: Increment when the implementation changes, but not the interface.
#  * age: Backward-compatible with how many interface numbers.
AC_SUBST([ATOM_SO_VERSION], [0:0:0])
AC_SUBST([ENTITY_SO_VERSION], [0:0:0])

# The version of the API. Should be major.minor and not change until not backward-compatible
AC_SUBST([ATOM_API_VERSION], [0.1])
AC_SUBST([ENTITY_API_VERSION], [0.1])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LIBTOOL

AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN";
    then AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
fi

AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])
# AM_COND_IF([HAVE_DOXYGEN], [AC_CONFIG_FILES([doxyfile])])


# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for libraries
AC_CHECK_LIB([m],[sqrt])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h stddef.h stdlib.h string.h sys/time.h])

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_CHECK_FUNCS([gettimeofday memmove mkdir setenv sqrt strchr strpbrk uname])

AX_PTHREAD

#CXXFLAGS+=" -g3 -ggdb -Wall -Wextra -Wfatal-errors"
CXXFLAGS+=" -Wall -Wextra -Wfatal-errors -Werror -Wnon-virtual-dtor "

#Set LIBLO with pkg-config
PKG_CHECK_MODULES(LIBLO, liblo, have_liblo=true, have_liblo=false)
if test "x${have_liblo}" = "xfalse" ; then
    AC_MSG_ERROR([Missing liblo])
fi

# Override the template file name of the generated .pc file, so that there
# is no need to rename the template file when the API version changes.
AC_CONFIG_FILES([
        Makefile 
        atom/version.h
        atom/Makefile 
        atom/tests/Makefile
        entity/version.h
        entity/Makefile 
        entity/tests/Makefile
        build/Makefile
        doxyfile 
        atom-${ATOM_API_VERSION}.pc:atom.pc.in
        entity-${ENTITY_API_VERSION}.pc:entity.pc.in
        doc/Makefile
        ])

AC_OUTPUT

