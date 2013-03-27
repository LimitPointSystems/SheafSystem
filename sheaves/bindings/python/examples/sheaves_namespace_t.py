#! /usr/bin/env python
##
## $RCSfile: sheaves_namespace_t.py,v $ $Revision: 1.6 $ $Date: 2013/01/12 17:17:33 $
##
##
## Copyright (c) 2013 Limit Point Systems, Inc.
##

from sheaves_python_binding import *

## Make the sheaves namespace.

ns = sheaves_namespace("sheaves_namespace_t")

## Output a text version to stdout.

ns.to_stream()

##  Need read/write access to write namespace to a file.

ns.get_read_write_access()

##  Write it to a file.

sa = storage_agent("sheaves_namespace_t.hdf")
sa.write_entire(ns)
