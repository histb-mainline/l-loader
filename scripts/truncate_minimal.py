#!/usr/bin/python3

import sys
from optparse import OptionParser

# Strip off all '\x00' suffixes

def truncate(file, align):
    txt = file.read()
    trunc = txt.rstrip(b'\x00')
    length = len(trunc)
    if len(trunc) % align:
        # Align to the requirement
        length += align - 1
        length -= length % align
    file.truncate(length)

if __name__ == "__main__":
    usage = "Usage: %prog [options] filename"
    parser = OptionParser(usage = usage)
    parser.add_option("-a", "--align", action = "store", dest = "align", type="int", help = "align up to given size", default = 1)
    options, args = parser.parse_args()
    if len(args) != 1:
        parser.print_usage()
        exit(1)
    with open(args[0], "r+b") as file:
        truncate(file, options.align)
