#!/usr/bin/python3

import sys
# Strip off all '\x00' suffixes

def truncate(file):
    txt = file.read()
    trunc = txt.rstrip(b'\x00')
    file.truncate(len(trunc))


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} filename")
        sys.exit(1)
    with open(sys.argv[1], "r+b") as f:
        truncate(f)

