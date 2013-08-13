#! /usr/bin/env python
##
##
## Copyright (c) 2013 Limit Point Systems, Inc.
##

##$$SCRIBBLE: This is just a placeholder.  It will be
##            further developed as part of the field algebra project.

##$$TODO: Figure out how to combine these.

from sheaves_python_binding import *
from fiber_bundles_python_binding import *
from fields_python_binding import *

## Make the sheaves namespace.

ns = fiber_bundles_namespace("field_vd_t")

## Output a text version to stdout.

ns.to_stream()

##  Need read access to write namespace to a file.

ns.get_read_write_access()

##  Write it to a file.

sa = storage_agent("field_vd_t.hdf")
sa.write_entire(ns)

