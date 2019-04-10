#!/usr/bin/env python
import finder
import sys

if __name__ == "__main__":
    args = sys.argv[1:]
    if len(args) == 0:
        pass
    if len(args) == 1:
        pass
    if args[0] == 'find':
        finder.find_text(args[1], '.' if len(args) == 2 else args[2])