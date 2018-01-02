dnl configure.ac for immediate-tiny-strings library
AC_PREREQ(2.59)
AC_INIT(immediate-tiny-strings, 0.1.0, github-issues)

dnl Move auxilary files into subdirectories to keep the top level
dnl directory as clean as possible.
AC_CONFIG_AUX_DIR(build-aux)
AC_CONFIG_MACRO_DIRS(m4)

dnl Let automake be pedantic, but don't complain about not being GNU
dnl compatible.
AM_INIT_AUTOMAKE(-Wall -Werror foreign)

dnl Use libtool to ease building of the library as both static and
dnl shared library. libtool needs a working archiver.
AM_PROG_AR
LT_INIT

dnl Generate a config.h which must be included by any source file.
AC_CONFIG_HEADERS(config.h)

dnl Get a working C compiler and some information about the platform
dnl we are building for.
AC_PROG_CC
AC_C_BIGENDIAN

dnl Check whether pointers are even large enough to store more than
dnl just a terminating null byte (plus one byte control information).
AC_CHECK_SIZEOF([char *])
if test $ac_cv_sizeof_char_p -le 2; then
  AC_MSG_ERROR([pointers are too small to be usefull])
fi

dnl Check that assert.h is available and add an option to disable
dnl assertions.
AC_HEADER_ASSERT

dnl Check for some standard headers to be around. If one of those is
dnl not found then good luck!
AC_CHECK_HEADERS(stdbool.h stddef.h stdint.h,,
  AC_MSG_WARN(Compilation is likely to fail without this header),)

dnl Check whether the system provides some function to allocate
dnl aligned memory.
AC_CHECK_FUNCS(aligned_alloc posix_memalign)

dnl Doxygen allows to generate nice documentation, but it should not
dnl be a strict requirement.
AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN"; then
  AC_MSG_WARN([Doxygen not found - continuing without])
fi
AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])

dnl Doxygen may use the dot tool if available
AC_ARG_VAR(DOT, dot program to use for generating graphs)
have_dot=YES
AC_PATH_PROGS(DOT, dot)
if test -z "$DOT"; then
  AC_MSG_WARN(dot not found, will omit graphs from documentation)
  have_dot=NO
fi
AC_SUBST(HAVE_DOT, $have_dot)

dnl Files to be generated
AC_CONFIG_FILES(Makefile src/Makefile test/Makefile
                docs/Doxyfile docs/Makefile)

dnl Do it!
AC_OUTPUT
