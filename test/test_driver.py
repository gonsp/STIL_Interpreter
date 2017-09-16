#!/usr/bin/env python
import sys
import subprocess
import datetime

from os import listdir

def test(file):

    name = file.rsplit('.', 1)[0]
    time = datetime.datetime.now().strftime("_%I_%M%p-%B-%d")

    print("Executing test", name)

    with open("test_logs/" + name + time + ".txt", 'w+') as logs_file:
        process = subprocess.Popen([exec_path, "../input_files/" + file, "-v"], stdout = logs_file, stderr = logs_file, cwd = "test_output_files")
        exit_code = process.wait()

    if exit_code != 0:
        print("Program crashed")
        return False

    return True
    # diff = subprocess.call(["diff", "output_files/" + name + ".atp", "test_output_files/" + name + ".atp"])
    # return diff == 0


def main():

    global exec_path
    exec_path = sys.argv[1]

    if len(sys.argv) == 3:
        input_files = [sys.argv[2]]
    else:
        input_files = [f for f in listdir("input_files")]

    for f in input_files:
        if not test(f):
            sys.exit(1)

    print("Test successful")

if __name__ == "__main__":
    main()