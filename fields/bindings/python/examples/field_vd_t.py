#! /usr/bin/env python
#
# Copyright (c) 2013 Limit Point Systems, Inc. 
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

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

