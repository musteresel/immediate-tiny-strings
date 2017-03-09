dnl configure.ac for immediate-tiny-strings library
AC_PREREQ(2.59)
AC_INIT(immediate-tiny-strings, 0.0.0, github-issues)

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

dnl Files to be generated
AC_CONFIG_FILES(Makefile src/Makefile test/Makefile)

dnl Do it!
AC_OUTPUT
