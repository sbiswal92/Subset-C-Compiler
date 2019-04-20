Features:
--------
0. Intermediate code generation for subset of C-language
1. Handles one input file on command line
2. Lists the counts of variables, functions, parameters and constants at the top of the output file
3. Translates arithmetic operators, bitwise operators, casting, increment, decrement, unary minus, flipping and assignment operators array and non-array type arguments.
4. Translates function calls with integer, character, float type identifiers and literals
5. Translates function calls with array-type identifiers. String literal cannot be passed directly to function calls only via array-initialization.

Building the parser:
------------------

1. $ make
   Builds the executable for the code generation

2. $ ./compile -i <input_file>