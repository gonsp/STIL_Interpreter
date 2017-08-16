#!/usr/bin/env python
import sys
from os import listdir

def test(file):
    print("Executing test", file)
    # execute stil_converter file -> test_output_files
    # redirecting its standar output to a log file in test_logs

    # if stil_converter exits with error code, return false
    # if not, check diff output_files/file with test_output_files/file
    # if not equal, return false, else, return true

def main():
    if len(sys.argv) == 2:
        input_files = [sys.argv[1]]
    else:
        input_files = [f for f in listdir("input_files")]

    for f in input_files:
        if not test(f):
            sys.exit(1)

    print("Test successful")

if __name__ == "__main__":
    main()