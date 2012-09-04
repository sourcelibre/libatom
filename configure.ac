# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])
AC_INIT(atom, [0.0.9], [http://code.sat.qc.ca/redmine/projects/libatom/issues], [libatom], [http://code.sat.qc.ca/redmine/projects/libatom])
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

# The version of the API. Should be major.minor and not change until not backward-compatible
AC_SUBST([ATOM_API_VERSION], [0.1])

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

# Beware! From now on, we might modify the CXXFLAGS and LDFLAGS.
# --------------------------------------------------------------

AC_TRY_COMPILE([#include <sys/types.h>
        #include <regex.h>],[  int i; 
        regex_t r;
        int cflags = REG_EXTENDED;
       const char *s = "abc";
       i = regcomp(&r,s,cflags);
       regfree(&r);
       ]; , have_regex=yes, have_regex=no)
if test "$have_regex" = yes; then
   AC_DEFINE(HAVE_REGEX,1,[Defined if found regex support. ])
fi

# Special cases
case "$host" in *-darwin* | *-macos10*)
  LIBTOOL="glibtool"
  CXXFLAGS+=" -D__Darwin"
  LDFLAGS+=" -undefined dynamic_lookup -Wl,-headerpad_max_install_names"
  if test -d /opt/local ; then
    CXXFLAGS+=" -I/usr/local/include -I/opt/local/include"
    #LDFLAGS+=" -L/usr/local/lib -L/opt/local/lib"
  elif test -d /sw ; then
    CXXFLAGS+=" -I/sw/include"
    #LDFLAGS+=" -L/sw/lib"
  fi
  # OSX does not include /usr/local/lib/pkgconfig path, so we export it here
  # (for everyone, just in case)
  PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH
  export PKG_CONFIG_PATH
  LDFLAGS+=" -fPIC -L/usr/local/lib -L/usr/local/lib64"
  ;;
esac

AC_ARG_ENABLE([universal],
    AS_HELP_STRING([--enable-universal], [Enables a universal i386 / x86_64 build on OSX]),
    [universal_build=$enableval],
    [universal_build=no])

if test "x$universal_build" = xyes; then
    CXXFLAGS+=" -arch i386 -arch x86_64"
    LDFLAGS+=" -arch i386 -arch x86_64"
fi

#CXXFLAGS+=" -g3 -ggdb -Wall -Wextra -Wfatal-errors"
CXXFLAGS+=" -Wall -Wextra -Wfatal-errors -Werror -Wnon-virtual-dtor "

#Set LIBLO with pkg-config
PKG_CHECK_MODULES(LIBLO, liblo, have_liblo=true, have_liblo=false)
if test "x${have_liblo}" = "xfalse" ; then
    AC_MSG_ERROR([Missing liblo])
fi

# libxml2
PKG_CHECK_MODULES([LIBXML], [libxml-2.0], have_libxml=true, have_libxml=false)
if test "x${have_libxml}" = "xfalse" ; then
    AC_MSG_ERROR([missing package: libxml2-dev])
fi

# log4cpp
PKG_CHECK_MODULES([LOG4CPP], [log4cpp], have_log4cpp=true, have_log4cpp=false)
if test "x${have_log4cpp}" = "xfalse" ; then
    AC_MSG_ERROR([missing package: liblog4cpp5-dev])
fi

BOOST_REQUIRE([1.35])
BOOST_REGEX
BOOST_SIGNALS
BOOST_SYSTEM
BOOST_THREADS

dnl AC_MSG_NOTICE([BOOST_LDFLAGS:              ${BOOST_LDFLAGS}])
AC_MSG_NOTICE([BOOST_CPPFLAGS:             ${BOOST_CPPFLAGS}])
AC_MSG_NOTICE([BOOST_SIGNALS_LIBS:         ${BOOST_SIGNALS_LIBS}])
AC_MSG_NOTICE([BOOST_SYSTEM_LIBS:          ${BOOST_SYSTEM_LIBS}])
AC_MSG_NOTICE([BOOST_THREAD_LIBS:         ${BOOST_THREAD_LIBS}])

# GNU help2man creates man pages from --help output; in many cases, this
# is sufficient, and obviates the need to maintain man pages separately.
# However, this means invoking executables, which we generally cannot do
# when cross-compiling, so we test to avoid that (the variable
# "cross_compiling" is set by AC_PROG_CC).
dnl (not used right now)
dnl if test $cross_compiling = no; then
dnl     AM_MISSING_PROG(HELP2MAN, help2man)
dnl else
dnl     HELP2MAN=:
dnl fi

# Override the template file name of the generated .pc file, so that there
# is no need to rename the template file when the API version changes.
AC_CONFIG_FILES([
        Makefile 
        atom/version.h
        atom/Makefile 
        atom/tests/Makefile
        build/Makefile
        doxyfile 
        atom-${ATOM_API_VERSION}.pc:atom.pc.in
        doc/Makefile
        ])

AC_OUTPUT

