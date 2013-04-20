#!/usr/bin/env python
#
import sys
import py_compile

def main():
    if len(sys.argv) == 1: return
    else: py_compile.compile(sys.argv[1])

if __name__ == "__main__":
    main()