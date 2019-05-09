Features:
--------
0. Intermediate code generation for control flows.
1. Translates if-then, if-then-else, for, while, do-while.
2. Translates all relational operations.
3. Translates break and continue only for single-statement loop body. Without break and continue, 
   multiline control flow body is translatable.
4. Does short circuit for AND and OR in if-then and if-then-else

Building the parser:
------------------

1. $ make
   Builds the executable for the code generation

2. $ ./compile -i <input_file>