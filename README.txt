Features:
--------
0. Basic lexer 
1. Handles more than one input file on command line
2. #include implemented with detection for cyclical dependency
3. #define,#undef not implemented and throw error if found in any of the input files. 
4. #ifdef, #ifndef, #else, #endif not implemented and throw error if found in any of the input files.


Building the lexer:
------------------

1. $ make
   Builds the executable for the lexer

