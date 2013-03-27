#!/bin/env python
##
## $RCSfile: generate_classes.py,v $ $Revision: 1.7 $ $Date: 2013/01/12 17:17:22 $
##
##
## Copyright (c) 2013 Limit Point Systems, Inc.
##

################################################################################

## Python script to automate the creation of the field class hierarchy.

## WARNING: Execution of this script with resulting in overwriting exiting
##          file with the same name in the output directory.

################################################################################

import os, sys

h_code_name  = './code_template.h'  ## Path to the declarations code tempate.
cc_code_name = './code_template.cc' ## Path to the definitions code tempate.

## Destination directory (where generated code will be placed).

to_dir_path = './'

## Directory where the "include" files are to be found,
## ("include" files are files which are "#included"ed into
##  the generated code).

from_dir_path = './'


## The "placeholder" string which is used to indicate where
## "#include" statements are to be created in the generated code
## if needed.

PLACEHOLDER  = '//...'


################################################################################

## Create a dictionary containing fiber type name pairs
## representing the hierarchy with keys as derived classes
## and values as parent classes.

## Note: We do not generate field_vd, so it is not a key.

def make_hier():

    result = {'at0'        : 'atp',    \
              'at1'        : 'atp',    \
              'at2_e2'     : 'at2',    \
              'at2_e3'     : 'at2',    \
              'at2'        : 'atp',    \
              'at3_e3'     : 'at3',    \
              'at3'        : 'atp',    \
              'atp'        : 'tp',     \
              'e1'         : 'ed',     \
              'e1_uniform' : 'e1',     \
              'e2'         : 'ed',     \
              'e2_uniform' : 'e2',     \
              'e3'         : 'ed',     \
              'e3_uniform' : 'e3',     \
              'e4'         : 'ed',     \
              'ed'         : 'at1',    \
              'jcb_e13'    : 'jcb_ed', \
              'jcb_e23'    : 'jcb_ed', \
              'jcb_e33'    : 'jcb_ed', \
              'jcb_ed'     : 'jcb',    \
              'jcb'        : 'vd',     \
              'met_e1'     : 'met_ed', \
              'met_e2'     : 'met_ed', \
              'met_e3'     : 'met_ed', \
              'met_ed'     : 'met',    \
              'met'        : 'st2',    \
              'st2_e2'     : 'st2',    \
              'st2_e3'     : 'st2',    \
              'st2'        : 'stp',    \
              'st3_e3'     : 'st3',    \
              'st3'        : 'stp',    \
              'st4_e2'     : 'st4',    \
              'st4_e3'     : 'st4',    \
              'st4'        : 'stp',    \
              'stp'        : 'tp',     \
              't2_e2'      : 't2',     \
              't2_e3'      : 't2',     \
              't2'         : 'tp',     \
              't3_e3'      : 't3',     \
              't3'         : 'tp',     \
              't4_e2'      : 't4',     \
              't4_e3'      : 't4',     \
              't4'         : 'tp',     \
              'tp'         : 'vd'}

    return result

################################################################################

## Identifiers for python template strings:
## These identifiers are embedded in the code template files.
##
##   ${ABS_BASE}          = FIELD_VD
##   ${abs_base}          = field_vd
##   ${DERIVED}           = FIELD_DERIVED (eg: FIELD_TP)
##   ${BASE}              = FIELD_BASE    (eg: FIELD_VD)
##   ${derived}           = field_derived (eg: field_tp)
##   ${base}              = field_base    (eg: field_vd)
##   ${property}          = property      (eg: sec_tp)
##   ${coords}            = coordinates   (eg: sec_ed)
##   ${coords_invertible} = invertible coordinates (eg: sec_ed_invertible)

##   ${PLACEHOLDER}  = include string placeholder

##   ${fiber}  = persistent fiber (eg: tp)
##   ${volatile_fiber}  = volatile fiber   (eg: tp_lite)

################################################################################

## Arguments derived and base are the fiber type names.
## Create a dictionary with the derived name as keys
## and the base names as values.

def make_dict(derived, base):
    
    result = {}
    result['ABS_BASE']          = 'FIELD_VD'
    result['abs_base']          = 'field_vd'
    result['base']              = 'field_' + base
    result['derived']           = 'field_' + derived
    result['BASE']              = 'FIELD_' + base.upper()
    result['DERIVED']           = 'FIELD_' + derived.upper()
    result['property']          = 'sec_' + derived   
    result['coords']            = 'sec_ed'
    result['coords_invertible'] = 'sec_ed_invertible'
    
    result['PLACEHOLDER']  = PLACEHOLDER

    ## There are no *_uniform fiber types, so the identifiers
    ## have to exclude the "_uniform" part.
    
    loc = derived.find('_uniform')
    if loc == -1:
        result['fiber']  = derived
        result['volatile_fiber']  = derived + '_lite'
    else:
        result['fiber']  = derived[:loc]
        result['volatile_fiber']  = derived[:loc] + '_lite'

    return result

################################################################################
##
## Template class taken from the string.py module of Python 2.5.2
## Allows this application to work with older versions of Python.
## If your version of Python is 2.5.0 or newer, you can replace 
## the following with "from string import Template".
##
################################################################################

import re as _re

class _TemplateMetaclass(type):
    pattern = r"""
    %(delim)s(?:
      (?P<escaped>%(delim)s) |   # Escape sequence of two delimiters
      (?P<named>%(id)s)      |   # delimiter and a Python identifier
      {(?P<braced>%(id)s)}   |   # delimiter and a braced identifier
      (?P<invalid>)              # Other ill-formed delimiter exprs
    )
    """

    def __init__(cls, name, bases, dct):
        super(_TemplateMetaclass, cls).__init__(name, bases, dct)
        if 'pattern' in dct:
            pattern = cls.pattern
        else:
            pattern = _TemplateMetaclass.pattern % {
                'delim' : _re.escape(cls.delimiter),
                'id'    : cls.idpattern,
                }
        cls.pattern = _re.compile(pattern, _re.IGNORECASE | _re.VERBOSE)


class Template:
    """A string class for supporting $-substitutions."""
    __metaclass__ = _TemplateMetaclass

    delimiter = '$'
    idpattern = r'[_a-z][_a-z0-9]*'

    def __init__(self, template):
        self.template = template

    # Search for $$, $identifier, ${identifier}, and any bare $'s

    def _invalid(self, mo):
        i = mo.start('invalid')
        lines = self.template[:i].splitlines(True)
        if not lines:
            colno = 1
            lineno = 1
        else:
            colno = i - len(''.join(lines[:-1]))
            lineno = len(lines)
        raise ValueError('Invalid placeholder in string: line %d, col %d' %
                         (lineno, colno))

    def substitute(self, *args, **kws):
        if len(args) > 1:
            raise TypeError('Too many positional arguments')
        if not args:
            mapping = kws
        elif kws:
            mapping = _multimap(kws, args[0])
        else:
            mapping = args[0]
        # Helper function for .sub()
        def convert(mo):
            # Check the most common path first.
            named = mo.group('named') or mo.group('braced')
            if named is not None:
                val = mapping[named]
                # We use this idiom instead of str() because the latter will
                # fail if val is a Unicode containing non-ASCII characters.
                return '%s' % (val,)
            if mo.group('escaped') is not None:
                return self.delimiter
            if mo.group('invalid') is not None:
                self._invalid(mo)
            raise ValueError('Unrecognized named group in pattern',
                             self.pattern)
        return self.pattern.sub(convert, self.template)


################################################################################

def do_class(h_code, cc_code, names):

    funcs_h_file_name = from_dir_path + names['derived'] + '_funcs.h';

    ## h_code:

    if os.path.exists(funcs_h_file_name):
        names['PLACEHOLDER'] = '#include "' + names['derived'] + '_funcs.h"'

    h_template=Template(h_code)
    result = h_template.substitute(names)
  
    file_name = names['derived'] + '.h'
    print "Creating", file_name
    file = open(file_name, 'w')
    file.write(result)
    file.close()

    names['PLACEHOLDER'] = PLACEHOLDER ## Reset value for key 'PLACEHOLDER'
                                       ## to be safe.

    ## cc_code:

    funcs_impl_file_name = from_dir_path + names['derived'] + '_funcs.impl.h'

    if os.path.exists(funcs_impl_file_name):
        names['PLACEHOLDER'] = '#include "' + names['derived'] + '_funcs.impl.h"'
    
    cc_template=Template(cc_code)
    result = cc_template.substitute(names)
    
    file_name = names['derived'] + '.cc'
    print "Creating", file_name
    file = open(file_name, 'w')
    file.write(result)
    file.close()


################################################################################

def get_code_strings():

    h_code_file = open(h_code_name, 'r')
    h_code = h_code_file.read()
    h_code_file.close()

    cc_code_file = open(cc_code_name, 'r')
    cc_code = cc_code_file.read()
    cc_code_file.close()

    ## Because the cvs $$RCSfile wants "code_template" instead of ${derived},
    ## we need to do a string substitution here.

    h_code = h_code.replace('code_template', '${derived}', 1)
    cc_code = cc_code.replace('code_template', '${derived}', 1)

    return h_code, cc_code
 

################################################################################

def do_all_classes():

    hier = make_hier()

    h_code, cc_code = get_code_strings()
                           
    for key, value in hier.iteritems():
        names = make_dict(key, value)
        do_class(h_code, cc_code, names)


################################################################################

def check_args(args, hier):

  for arg in args:
      if not hier.has_key(arg):
          print "ERROR:", arg, "not in hierarchy"

################################################################################

def do_classes(args):

    hier = make_hier()
    check_args(args, hier)

    h_code, cc_code = get_code_strings()
    
    good_names = {}
    for name in args:
        if hier.has_key(name):
            good_names[name] = hier[name]
            
    for key, value in good_names.iteritems():
        names = make_dict(key, value)
        do_class(h_code, cc_code, names)

################################################################################

def usage():
    name = sys.argv[0]
    usage_text = """
Usage: %s -all
           -all: Generate all classes in hierarchy.
           
       %s [fiber_name(s)]
           [fiber_name(s)]: Generate only classes corresponding to fiber_name(s).
                            For example: %s e2 e3

       %s -help
       %s
           This usage message.
""" % (name, name, name, name, name)
    print usage_text
    sys.exit()

################################################################################

def main():
    args = sys.argv[1:]
    if len(args) == 0 or args[0] == '-help':
        usage()
    elif args[0] == '-all':
        do_all_classes()
    else:
        do_classes(args)  

################################################################################

if __name__ == '__main__':
    main()



