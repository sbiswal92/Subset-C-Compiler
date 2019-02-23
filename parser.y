//%define parse.error verbose
%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "symbolTable.h"
  #include<string.h>
  // stuff from flex that bison needs to know about:
  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;
  extern int yylineno;
  extern char* yytext;
  char* filename;

  
  void yyerror(const char *msg){
    fprintf(stderr, "Error in %s line %d: %s\n", filename, yylineno,msg);
  }

struct symbolTable *symT;
%}

%union {
        char* sval;
	int ival;
	float fval;
       }


%token <sval>  MARK_EOF DIR_ERR INCLUDE_ERR TOKEN_ERR
%token <sval>  COMMA SEMI TYPE LPAR RPAR LBRACKET RBRACKET LBRACE RBRACE
%token <sval>  DO BREAK CONTINUE RETURN INCR DECR COLON FOR WHILE IF ELSE
%token <sval>  ASSIGN PLUSASSIGN MINUSASSIGN STARASSIGN SLASHASSIGN BANG TILDE QUEST
%token <sval>  EQUALS NEQUAL GT GE LT LE PLUS MINUS STAR SLASH MOD PIPE DPIPE AMP DAMP
%token <sval>  STRCONST CHARCONST
%token <ival>  INTCONST 
%token <fval>  REALCONST
%token <sval> IDENT

%left COMMA
%right ASSIGN PLUSASSIGN MINUSASSIGN STARASSIGN SLASHASSIGN
%right QUEST
%left DPIPE
%left DAMP
%left PIPE
%left AMP
%left EQUALS NEQUAL
%left GT GE LT LE
%left PLUS MINUS
%left STAR SLASH MOD
%right BANG TILDE INCR DECR UAMP UMINUS TYPE
%left LPAR RPAR LBRACKET RBRACKET
%nonassoc NO_ELSE
%nonassoc ELSE


%expect 1

%start input

%%
 

input   : decList { printAllLists(symT,0); printf("\n");}
        ;

decList : decList dec { } 
        | dec  {}
	;

dec     : varDec        
	| funProto	{}
	;

varDec  : TYPE varDecList SEMI
        ;

varDecList : var
           | varDecList COMMA var
           ;

var     : IDENT   {
			struct symbol thisSym; 
			initializeSymbol(&thisSym, $1, variable); 
			symbolTable_insertSymbol(symT, thisSym,filename,yylineno); 
		  }
        | IDENT LBRACKET INTCONST RBRACKET {
						struct symbol thisSym; 
						initializeSymbol(&thisSym, $1, variable); 
						symbolTable_insertSymbol(symT, thisSym,filename,yylineno); 
					   }
        ;


funProto  : funDec SEMI  { 
			   symT = exit_scope(symT);
         		 }
	  | funDec fbodyB {
                           symT = exit_scope(symT);
		          }
	 ;

funDec : funName funPar
       ;

funName : TYPE IDENT {
			struct symbol thisSym; 
			initializeSymbol(&thisSym, $2, function1); 
			symbolTable_insertSymbol(symT, thisSym,filename,yylineno);  
			symT = enter_scope(symT);
		    }
	;

funPar : LPAR pList1 RPAR
       ;

pList1 : 
       | pList
       ;

pList : pList COMMA pvar
       | pvar
       ;

pvar   : TYPE IDENT {
			struct symbol thisSym; 
			initializeSymbol(&thisSym, $2, parameter); 
			symbolTable_insertSymbol(symT, thisSym,filename,yylineno); 
		    }
       | TYPE IDENT LBRACKET INTCONST RBRACKET {
                                                struct symbol thisSym;
                                                initializeSymbol(&thisSym, $2, parameter);
                                                symbolTable_insertSymbol(symT, thisSym,filename,yylineno);
                                               }

       ;


fbodyB : LBRACE some_stmt1 RBRACE	
       ;


some_stmt1 : some_stmt1 varDec 
	   | some_stmt1 some_stmt
	   | varDec
	   | some_stmt
	   ;

some_stmt : stmt_blk
	  | stmt
          ;


stmt_blk : Lstmtblock RBRACE {symT = exit_scope(symT);}	
	 ;

Lstmtblock : Lpart some_stmt
	   ;

Lpart : LBRACE {symT = enter_scope(symT);}
      ;


stmt : SEMI
     | expr SEMI
     | BREAK SEMI
     | CONTINUE SEMI
     | RETURN expr SEMI
     | RETURN SEMI
     | IF LPAR expr RPAR some_stmt  %prec NO_ELSE 
     | IF LPAR expr RPAR some_stmt ELSE some_stmt
     | FOR LPAR for_init for_chk for_upd RPAR some_stmt
     | WHILE LPAR expr RPAR some_stmt
     | DO some_stmt WHILE LPAR expr RPAR SEMI
     ;


for_init: expr SEMI
	| varDec SEMI
	| SEMI
	;


for_chk	: expr SEMI
	| SEMI
	;


for_upd	: expr
	|
	;


texpr : INTCONST
     | REALCONST
     | STRCONST
     | CHARCONST     
     | AMP IDENT %prec UAMP
     | IDENT
     ;


expr : texpr
     | IDENT LBRACKET expr RBRACKET
     | IDENT LPAR one_or_more_expr RPAR     
     | lval INCR
     | lval DECR
     | BANG expr
     | TILDE expr
     | MINUS expr %prec UMINUS
     | expr PLUS expr
     | expr MINUS expr
     | expr STAR expr 
     | expr MOD expr 
     | expr SLASH expr 
     | expr AMP expr 
     | expr DAMP expr
     | expr DPIPE expr 
     | expr PIPE expr  
     | LPAR TYPE RPAR expr
     | LPAR expr RPAR
     | lval ASSIGN expr
     | lval PLUSASSIGN expr
     | lval MINUSASSIGN expr
     | lval STARASSIGN expr
     | lval SLASHASSIGN expr
     | log_expr
     | ternary
     ;

log_expr : expr EQUALS expr
     	 | expr NEQUAL expr
     	 | expr GE expr
     	 | expr GT expr
     	 | expr LE expr
     	 | expr LT expr
     	 ;

ternary : log_expr QUEST expr COLON expr %prec QUEST
	;  


one_or_more_expr : one_or_more_expr  COMMA expr
		 | expr 
		 | 
		 ;

lval : IDENT
     | IDENT LBRACKET expr RBRACKET
     ; 

	
%%
/*
int main(int argc, char** argv) {
  // open a file handle to a particular file:
  filename = argv[1];
// printf("\nFile:%s",filename);
  FILE *myfile = fopen(argv[1], "r");
  // make sure it is valid:
 symT = (struct symbolTable*)malloc(sizeof(struct symbolTable));
 symT->symbolListHead = NULL;
 symT->parentSymbolTable = NULL;
 symT->childSymbolTableListHead = NULL;


  // Set flex to read from it instead of defaulting to STDIN:
  yyin = myfile;
  // Parse through the input:
  yyparse();
}i*/


int main(int argc, char **argv)
{

        if(argc<3)
        {
                fprintf(stderr, "Error: input expected in the form of './compile -p <inputfile>'\n");
                exit(1);
        }else if (strcmp(argv[1],"-l")==0){
                int file_track=2;
                
                while(file_track<argc)
                {
                        FILE *myfile = fopen(argv[file_track], "r");
			yyin = myfile;
			if(!myfile){
                        int token;
                        for(;;){
                        
                                token = yylex();
                                if(token==DIR_ERR) //Error for non-implemented features
                                        fprintf(stderr,"Error in %s line %d: \n\t directive ’%s’ not implemented, ignoring\n", argv[file_track], yylineno, yytext);

                                else if(token==TOKEN_ERR) //Error for unknown tokens
                                        fprintf(stderr,"Error in %s line %d:\n\t unknown token'%s'\n", argv[file_track], yylineno, yytext);
                                
                                else if(token==INCLUDE_ERR)
                                        fprintf(stderr,"Error in %s line %d: \n\t directive ’%s’ not implemented, ignoring\n", argv[file_track], yylineno, yytext);

                                else if(token==MARK_EOF)
                                        break;

                                else
                                	{}
				}
                        }
                        
                        file_track+=1;
                }
                
        } else if (strcmp(argv[1],"-p")==0){
          
		if(argc>4)
			fprintf(stderr, "Error: input expected in the form of './compile -l <inputfiles> or ./compile -p <inputfile>'\n");
		else{
			filename = argv[2];
			FILE *myfile = fopen(argv[2], "r");
			 // make sure it is valid:
 			symT = (struct symbolTable*)malloc(sizeof(struct symbolTable));
 			symT->symbolListHead = NULL;
 			symT->parentSymbolTable = NULL;
 			symT->childSymbolTableListHead = NULL;


  			// Set flex to read from it instead of defaulting to STDIN:
  			yyin = myfile;
  			// Parse through the input:
  			yyparse();
		     }
	 	
	}
}

