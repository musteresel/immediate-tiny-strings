dnl configure.ac for immediate-tiny-strings library
AC_PREREQ(2.59)
AC_INIT(immediate-tiny-strings, 0.0.0, github-issues)
AC_CONFIG_AUX_DIR(build-aux)
AC_CONFIG_MACRO_DIRS(m4)
AM_INIT_AUTOMAKE(-Wall -Werror foreign)
AM_PROG_AR
LT_INIT
AC_CONFIG_HEADERS(config.h)

AC_PROG_CC

AC_C_BIGENDIAN

AC_HEADER_ASSERT
AC_CHECK_HEADERS(stdbool.h stddef.h stdint.h,,
  AC_MSG_WARN(Compilation is likely to fail without this header),)

AC_CONFIG_FILES(Makefile src/Makefile test/Makefile)
AC_OUTPUT
