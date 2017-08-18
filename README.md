# STIL_Interpreter
Tool for parsing an integrated circuit test file from STIL to the particular file format of a Teradyne tester.

It includes the parsing,interpretation of the STIL input and the output files generation of the Teradyne particular format.

-----------------------------------------------

To build:

mkdir build && cd build
cmake ../
make

-----------------------------------------------

To install:

cd build
make install

If you don't want to install it in the default path:

mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=YOUR_PATH ..
make install

-----------------------------------------------

To run tests:

cd build
ctest [-R stil_file_name_in_test/input_files]

-----------------------------------------------

To run:

stil_converter input_file.stil [-v] [-c config_file.config] [-p pattern_exec_name]