#!/usr/bin/env python
import finder
import maker
import sys

if __name__ == "__main__":
    args = sys.argv[1:]
    if len(args) < 2:
        pass
    if args[0] == 'find':
        finder.find_text(args[1], '.' if len(args) == 2 else args[2])
    if args[0] == 'make':
        maker.make_all('.' if len(args) == 2 else args[2])