compile: lex.yy.c parser.tab.c
	 gcc -o compile symbol.c symbolList.c symbolTable.c type.c ast.c memory.c lex.yy.c parser.tab.c -ll


parser.tab.c: parser.y
	     bison -d -v parser.y

lex.yy.c: lexer.l
	  flex lexer.l

clean:
	rm -rf lex.yy.c parser.tab.c parser.tab.h  parser.output compile *.o *.out
