#! /usr/bin/env python
##
## Copyright (c) 2013 Limit Point Systems, Inc.
##


import sys ## for command line arguments
from sheaves_python_binding import *

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
