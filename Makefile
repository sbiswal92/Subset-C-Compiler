compile: lex.yy.c
	 gcc -o compile lex.yy.c -ll

lex.yy.c: lexer.l
	  flex lexer.l

clean:
	rm -rf lex.yy.c compile *.o *.out
