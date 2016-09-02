AC_PREREQ([2.59])
AC_INIT([Spider], [0.1], [clay AT lazarusid.com])
AM_PROG_AR

AM_INIT_AUTOMAKE([-Wall -Werror gnu 0.1])

AC_PROG_CC

PKG_CHECK_MODULES([CHECK], [check >= 0.9.6])
AM_PROG_CC_C_O

AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h])

AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([Makefile
		 src/Makefile
		 mocks/Makefile
		 tests/Makefile])

AC_OUTPUT
