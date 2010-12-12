dnl This file is part of reSID, a MOS6581 SID emulator engine.
dnl Copyright (C) 2010  Dag Lem <resid@nimrod.no>
dnl
dnl Process this file with autoconf to produce a configure script.

dnl Use Autoconf
AC_PREREQ([2.62])
AC_INIT([reSID], [1.0-pre1], [resid@nimrod.no])
AC_CONFIG_SRCDIR([sid.h])

dnl Use Automake
AM_INIT_AUTOMAKE([1.11])

dnl Use Libtool
LT_PREREQ([2.2.2])
LT_INIT([disable-shared])
AC_CONFIG_MACRO_DIR([m4])
AC_SUBST([LTVERSION], [6:0:0])

dnl Use C++ for tests.
AC_LANG([C++])

dnl Enable inlining.
AC_ARG_ENABLE([inline],
  [AS_HELP_STRING([--enable-inline],
    [enable inlining of functions [default=yes]])],
  [],
  [enable_inline=yes])

AS_IF([test "$enable_inline" != no],
  [AC_SUBST([RESID_INLINING], [1])
   AC_SUBST([RESID_INLINE], [inline])],
  [AC_SUBST([RESID_INLINING], [0])
   AC_SUBST([RESID_INLINE], [])])

dnl Enable architecture specific compilation.
AC_ARG_ENABLE([arch],
  [AS_HELP_STRING([--enable-arch[[=arch]]],
    [enable architecture specific compilation [default=native]])],
  [],
  [enable_arch=yes])

AS_IF([test "$enable_arch" = no], [march=""],
      [test "$enable_arch" = yes], [march=" -march=native"],
      [march=" -march=$enable_arch"])

dnl Enable branch prediction hints.
AC_ARG_ENABLE([branch-hints],
  [AS_HELP_STRING([--enable-branch-hints],
    [enable static branch prediction hints [default=yes]])],
  [],
  [enable_branch_hints=yes])

AS_IF([test "$enable_branch_hints" != no],
  [AC_SUBST([RESID_BRANCH_HINTS], [1])],
  [AC_SUBST([RESID_BRANCH_HINTS], [0])])

dnl Store CXXFLAGS status.
resid_test_CXXFLAGS=${CXXFLAGS+set}

dnl Checks for programs.
AC_PROG_CXX

dnl Set CXXFLAGS for g++.
AS_IF([test "$GXX" = yes -a "$resid_test_CXXFLAGS" != set],
  [resid_save_CXXFLAGS=$CXXFLAGS
   CXXFLAGS="-g -Wall -O3$march -ffast-math -fno-exceptions"
   AC_MSG_CHECKING([whether g++ accepts $CXXFLAGS])
   AC_COMPILE_IFELSE([int test;],
                     [AC_MSG_RESULT(yes)],
                     [AC_MSG_RESULT(no)
                      CXXFLAGS="-g -Wall -O3 -fno-exceptions"
                      AC_MSG_CHECKING([whether g++ accepts $CXXFLAGS])
                      AC_COMPILE_IFELSE([int test;],
                                        [AC_MSG_RESULT(yes)],
                                        [AC_MSG_RESULT(no)
                                         CXXFLAGS=$resid_save_CXXFLAGS])])])

AC_PATH_PROG([PERL], [perl])

dnl Checks for libraries.

dnl Checks for header files.
AC_CHECK_HEADER([math.h], [], AC_MSG_ERROR([missing math.h]))

dnl Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_SIZEOF([int], [4])

AS_IF([test $ac_cv_sizeof_int -lt 4],
  AC_MSG_ERROR([only 32 bit or better CPUs are supported]))

AC_CACHE_CHECK([for working bool], [resid_cv_cxx_bool],
  [AC_COMPILE_IFELSE([bool flag;],
    [resid_cv_cxx_bool=yes], [resid_cv_cxx_bool=no])])

AS_IF([test "$resid_cv_cxx_bool" = no],
  [AC_SUBST([HAVE_BOOL], [0])],
  [AC_SUBST([HAVE_BOOL], [1])])

AC_CACHE_CHECK([for __builtin_expect], [resid_cv_builtin_expect],
  [AC_COMPILE_IFELSE([int main() { __builtin_expect(0, 0); }],
    [resid_cv_builtin_expect=yes], [resid_cv_builtin_expect=no])])

AS_IF([test "$resid_cv_builtin_expect" = no],
  [AC_SUBST([HAVE_BUILTIN_EXPECT], [0])],
  [AC_SUBST([HAVE_BUILTIN_EXPECT], [1])])

dnl Checks for library functions.

AC_CONFIG_FILES([Makefile siddefs.h])
AC_OUTPUT