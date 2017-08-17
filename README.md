# STIL_Interpreter
Tool for parsing an integrated circuit test file from STIL to the particular file format of a Teradyne tester.

It includes the parsing,interpretation of the STIL input and the output files generation of the Teradyne particular format.


To build:

mkdir build
cd build
cmake ../
make


To install:

cd build
make install


To run tests: (after install)

cd build
make test


To run:

stil_converter input_file.stil [-v] [-c config_file.config] [-p pattern_exec_name]