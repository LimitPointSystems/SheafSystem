#
#
# Copyright (c) 2013 Limit Point Systems, Inc.
#
#

find_program(7ZA NAMES 7za 7za.exe
	PATHS ENV${PATH}
	)
if(7ZA)
  set(7ZIP_FOUND "YES" )
endif(7ZA)
