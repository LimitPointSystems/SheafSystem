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


import sys ## for command line arguments

from sheaves_python_binding import *
from fiber_bundles_python_binding import *
from fields_python_binding import *


TRUE = 1
FALSE = 0

###############################################################################
# read_namespace(file_name):
###############################################################################

def read_namespace(file_name):

    ## Make the default namespace.

    ns = namespace_poset(file_name[0:-4]) ## Splice off ".hdf" from file_name

    ## Read the namespace from the file;
    ## need write access in order to read it.

    ns.get_read_write_access()
    
    sa = storage_agent(file_name, sheaf_file.READ_ONLY, FALSE)
    sa.read_entire(ns)
    
    return ns

###############################################################################
# main(file_name):
###############################################################################

def main(file_name):

    ## Read the namespace from the file.
    
    ns = read_namespace(file_name)
    
    ## Output a text version to stdout.
    
    ns.to_stream()

###############################################################################

if __name__ == '__main__':  
    import sys   
    if len(sys.argv) < 2:
        print 'Usage: ' + sys.argv[0] + ' file_name' 
    else:
        main(sys.argv[1])
