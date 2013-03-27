#! /usr/bin/perl
#
# Usage: add_dll_spec.pl file [file ...]
#
# Adds include of sheaf_dll_spec.h to file
# and inserts SHEAF_DLL_SPEC in front of every class or struct definition.
# Writes result to STDOUT.
#
undef $/;       # each read is whole file.
while(<>)
{
  # Include sheaf_dll_spec right after guard definition.

  s/(\#define[^\n]*\n)/$1\n\#ifndef SHEAF_DLL_SPEC_H\n\#include "sheaf_dll_spec.h"\n\#endif\n/;

  # Put SHEAF_DLL_SPEC after "class" in all class declarations.
  # Class declaration is "class " followed by 0 or more chars
  # that are not ";" followed by "{".
  # $1 is contents of first () delimited group in search pattern,
  # leading whitespace, and $2 is second group, class declaration itself.
  # /m modifer is necessary so ^ selects beginning of lines,
  # not just beginning of entire string (i.e. the whole file).

  s/^([ \t]*class)( [^;]*\{)/$1 SHEAF_DLL_SPEC$2/mg;

  # Also put SHEAF_DLL_SPEC in front of all struct declarations.

  s/^([ \t]*struct)( [^;]*\{)/$1 SHEAF_DLL_SPEC$2/mg;

  # alternates that just mark matches, for debugging
  #  s/^([ \t]*class)( [^;]*\{)/\$$1$2\$/mg;
  #  s/^([ \t]*struct)( [^;]*\{)/\$$1$2\$/mg;

  print;
}
