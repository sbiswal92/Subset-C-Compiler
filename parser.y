//%define parse.error verbose
%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "symbolTable.h"
  #include "type.h"
  #include<string.h>

  // stuff from flex that bison needs to know about:
  extern int yylex();
  extern int yyparse();
  extern char* getTokenName(int);
  extern FILE *yyin;
  extern int yylineno;
  extern char* yytext;
  //char* filename;
  enum type curr_type=-1;
  exp_node *result_exp;
  extern struct symbolTable *myCurrentTable;

  char* type_arr[8]={
                        "error",
                        "void",
                        "char",
                        "int",
                        "float",
                        "char[]",
                        "int[]",
                        "float[]"
                    };
  

  void yyerror(const char *msg){
    fprintf(stderr, "Error in %s line %d: %s\n", filename, yylineno,msg);
  }

struct symbolTable *symT;
int is_ret_there = -1;
%}

%union {
	char cval;
        char* sval;
	int ival;
	float fval;
	struct exp_node *eval;
       }


%token <sval>  MARK_EOF DIR_ERR INCLUDE_ERR TOKEN_ERR
%token <sval>  COMMA SEMI TYPE LPAR RPAR LBRACKET RBRACKET LBRACE RBRACE
%token <sval>  DO BREAK CONTINUE RETURN INCR DECR COLON FOR WHILE IF ELSE
%token <sval>  ASSIGN PLUSASSIGN MINUSASSIGN STARASSIGN SLASHASSIGN   QUEST
%token <sval>  EQUALS NEQUAL GT GE LT LE PLUS  STAR SLASH MOD PIPE DPIPE  DAMP MINUS BANG AMP TILDE
%token <sval>  STRCONST
%token <cval>  CHARCONST
%token <ival>  INTCONST 
%token <fval>  REALCONST
%token <sval> IDENT

%type <sval> unary_op asgn_op rel_op add_op mul_op check_op

%type <eval> expr unary_expr cond_expr log_or_expr log_and_expr bit_or_expr bit_and_expr check_expr mul_expr add_expr rel_expr cast_expr texpr expr_stmt  
%type <eval> fun_call_Left idList fun_call_begin postfix_expr

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



%start trans_unit

%%

trans_unit : input  { /*printAllLists(symT,0);*/printf("\n"); } 

input : ext_decl 
      | input ext_decl {  } 
      ;

ext_decl : fun_definition {  }
	 | declaration 
	 | DIR_ERR { fprintf(stderr,"Error in %s line %d: \n\t directive '%s' not implemented, ignoring\n",filename, yylineno, yytext); }
         ;

declaration : decl_spec SEMI
	    | decl_spec decl_init_list SEMI { }
	    ;

decl_spec : TYPE { curr_type = getType($1); }
	  ;

decl_init_list : decl_init
	       | decl_init_list COMMA decl_init
	       ;

decl_init : declarator
	  | declarator EQUALS texpr
	  ;


declarator : IDENT {
			struct symbol thisSym; 
                        initializeSymbol(&thisSym, $1, curr_type, variable, yylineno );
			symbolTable_insertSymbol(symT, thisSym,filename,yylineno);

		   }
	    | IDENT LBRACKET INTCONST RBRACKET {
						        struct symbol thisSym;
                                                        initializeSymbol(&thisSym, $1, curr_type + 3, variable,yylineno);
                                                        symbolTable_insertSymbol(symT, thisSym,filename,yylineno);
					     }
	  | fun_dec_Left RPAR { int x=0; symT = exit_scope(symT,&x,filename,yylineno); /*exit scope just a declaration*/  }
          ;

fun_declarator : fun_dec_Left RPAR { /*do not exit scope because function body follows*/ }
	       ;

fun_dec_Left : fun_dec_begin paramList
	     | fun_dec_begin
	     ;

fun_call_Left : fun_call_begin idList { $$ = makeFuncE($1,$2); }
	      | fun_call_begin {  }
	      ;

fun_dec_begin : IDENT LPAR {
				 struct symbol thisSym;
                                 initializeSymbol(&thisSym, $1, curr_type, function1, yylineno);
                                 symbolTable_insertSymbol(symT,thisSym,filename,yylineno);
                                 symT = enter_scope(symT,thisSym,1);
			   }

fun_call_begin : IDENT LPAR {
                                 myCurrentTable = symbolTable_getParent(symT);
                                 struct symbol *SymForFunIdent = lookup(symbolTable_getParent(symT), $1, filename, yylineno);
                                 $$ = makeIdentifierNameE(SymForFunIdent);
                            }

idList : idList COMMA texpr { $$ = makeCommaE($1,$3);  }
       | texpr { $$ = makeCommaLastE($1); }
       ;

paramList : param
	  | paramList COMMA param
	  ;

param : param_TYPE pdeclarator
      ;

param_TYPE : TYPE { curr_type = getType($1); }
	   ;

pdeclarator : IDENT {
                        struct symbol thisSym;
                        initializeSymbol(&thisSym, $1, curr_type,  parameter, yylineno);
                        symbolTable_insertSymbol(symT, thisSym,filename,yylineno);

                    }
           | IDENT LBRACKET INTCONST RBRACKET {
                                                struct symbol thisSym;
                                                initializeSymbol(&thisSym, $1, curr_type, parameter,yylineno);
                                                symbolTable_insertSymbol(symT, thisSym,filename,yylineno);
                                             }
	 ;

/*********************************************/

fun_definition : decl_spec fun_declarator function_body

function_body : function_body_left block_item_list RBRACE { 
                                                                int x = 1;
                                                                if((is_ret_there==-1) && (symT->parentSymbolTableEntrySymbol.type>1))
                                                                        fprintf(stderr,"Error in %s line %d:\n \t Return type is missing for function %s:\n\t  Return type expected is %s (near line %d)\n",filename,yylineno, symT->parentSymbolTableEntrySymbol.id, type_arr[symT->parentSymbolTableEntrySymbol.type], symT->parentSymbolTableEntrySymbol.lineno);
                                                                symT = exit_scope(symT,&x,filename,yylineno); 
                                                           }
	      ;

function_body_left :  LBRACE  { 
                                struct symbol parentSymbol = symT->parentSymbolTableEntrySymbol;
                                int x = 0;
                                is_ret_there = -1;
                                symT = exit_scope(symT,&x,filename,yylineno);   //exit <post-processing> and re-enter
                                if(x==1)//this is first-time definition
                                {
                                    symT = enter_scope(symT,parentSymbol,0);
                                }
                                else if(x==2) //this is first-time definition
                                {
                                    struct symbol* newparentSymbol = lookup1(symT,parentSymbol,filename, yylineno);
                                    symT = enter_scope(symT,*newparentSymbol,0);
                                }
                                else if(x==-1) //function definition already exists
                                {
                                    struct symbol* oldSymbol = lookup(symT,parentSymbol.id,filename, yylineno);   
                                    fprintf(stderr,"Error in %s line %d:\n \t Function %s is already declared (near line %d)\n", filename, yylineno, oldSymbol->id, oldSymbol->lineno );
		                    exit(1);
                                }
                              }

/*********************************************/

stmt : compound_stmt  
	   | iteration_stmt 
	   | selection_stmt
	   | expr_stmt
	   | jump_stmt
	   ;

compound_stmt : compound_stmt_left block_item_list RBRACE { int x = 0; symT = exit_scope(symT,&x,filename,yylineno); }
	      ;

compound_stmt_left : LBRACE  { 
                                struct symbol thisSym;
                                initializeSymbol(&thisSym, "0", VOID_T, variable,yylineno);
                                symT = enter_scope(symT,thisSym,1); 
                             }

block_item_list : block_item
	      	| block_item_list block_item
		;

block_item : declaration
	   | stmt
	   ;

expr_stmt : expr SEMI { int ans = dataTypeOf($1); if(ans) printf("Expression at file %s at line %d has type %s\n",filename, yylineno, type_arr[ans]); }
          | SEMI
	  ;

jump_stmt : CONTINUE SEMI
	  | BREAK SEMI
          | RETURN expr SEMI  { 
                                struct symbol parentSymbol = symT->parentSymbolTableEntrySymbol;
                                enum type ret_type = dataTypeOf($2);
                                is_ret_there = 1;
                                if( ret_type > parentSymbol.type)
                                      fprintf(stderr,"Error in %s line %d:\n \t No match for return type %s for function %s:\n\t Return type expected is %s (near line %d)\n",filename,yylineno,type_arr[ret_type], parentSymbol.id, type_arr[parentSymbol.type], parentSymbol.lineno);
                        
                              }
     	  | RETURN SEMI { 
                          struct symbol parentSymbol = symT->parentSymbolTableEntrySymbol;
                          is_ret_there = 1;
                          if(parentSymbol.type !=VOID_T)
                                 fprintf(stderr,"Error in %s line %d:\n \t No match for return type %s for function %s:\n\t  Return type expected is void (near line %d)\n",filename,yylineno,parentSymbol.id,type_arr[parentSymbol.type], parentSymbol.lineno);
                                     
                        }
          ; 

selection_stmt : IF LPAR expr RPAR stmt  
	       | IF LPAR expr RPAR stmt ELSE stmt	 
               ;

iteration_stmt : FOR LPAR expr_stmt expr_stmt expr RPAR stmt
     	       | WHILE LPAR expr RPAR stmt
               | DO stmt WHILE LPAR expr RPAR SEMI
               ;


texpr : INTCONST  { $$ = makeIntConstE($1); }
      | REALCONST { $$ = makeFloatConstE($1); }
      | STRCONST  { $$ = makeCArrConstE($1); }
      | CHARCONST { $$ = makeCharConstE($1); }    
      | IDENT       { 
                        /*variable call*/
                        struct symbol *SymForVarIdent = lookup(symT, $1,filename, yylineno);
                        $$ = makeIdentifierNameE(SymForVarIdent);
                    } 
      | LPAR expr RPAR { $$ = $2; } 
      ;


expr : cond_expr  {  $$ = $1; }
     | unary_expr asgn_op expr { $$ = makeAssE($2,$1,$3); }
     | fun_call_Left RPAR {  }
     ;

unary_expr : INCR unary_expr { $$ = makeUnPreE($1,$2); }
           | DECR unary_expr { $$ = makeUnPreE($1,$2); }
           | unary_op cast_expr { $$ = makeSomeUnE($1 ,$2); }
           | postfix_expr { $$ = $1; }
	   ;


postfix_expr : texpr { $$ = $1; }
             | postfix_expr INCR { $$ = makeUnPostE($2,$1); }
             | postfix_expr DECR { $$ = makeUnPostE($2,$1); }
             | postfix_expr LBRACKET expr RBRACKET { $$ = makeArrE($1,$3); }

             ;

unary_op : MINUS {$$ = $1; }
	 | BANG  {$$ = $1; }
	 | TILDE {$$ = $1; }
         | AMP   {$$ = $1; }
         ;

cast_expr : unary_expr { $$ = $1;  }
	  | LPAR TYPE RPAR cast_expr {$$ = makeCastE($2,$4);}
          ;

asgn_op  : PLUSASSIGN {$$ = $1; }
	      | MINUSASSIGN {$$ = $1; }
	      | STARASSIGN {$$ = $1; }
	      | SLASHASSIGN {$$ = $1; }
	      | ASSIGN  {$$ = $1; }
	      ;

cond_expr : log_or_expr {$$ = $1;}
	  | log_or_expr QUEST expr COLON cond_expr {$$ = makeCondE($1,$3,$5);}
	  ;

log_or_expr : log_and_expr {$$ = $1;}
	    | log_or_expr DPIPE log_and_expr {$$ = makeLogE($2,$1,$3);}
	    ;

log_and_expr : bit_or_expr {$$ = $1;}
	     | log_and_expr DAMP bit_or_expr  {$$ = makeLogE($2,$1,$3);}
	     ;

bit_or_expr : bit_and_expr {$$ = $1;}
	    | bit_or_expr PIPE bit_and_expr {$$ = makeBitE($2,$1,$3);}
	    ;

bit_and_expr : check_expr {$$ = $1;}
	     | bit_and_expr AMP check_expr {$$ = makeBitE($2,$1,$3);}
             ;

check_expr : rel_expr {$$ = $1;}
	   | check_expr check_op rel_expr {$$ = makeRelE($2,$1,$3);}
	   ;

check_op : EQUALS {$$ = $1; }
	 | NEQUAL {$$ = $1; }
         ;

rel_expr : add_expr {$$ = $1}
         | rel_expr rel_op add_expr { $$ = makeRelE($2,$1,$3); }
         ;

rel_op : GE {$$ = $1; }
       | GT {$$ = $1; }
       | LE {$$ = $1; }
       | LT {$$ = $1; }
       ;

add_expr : mul_expr { $$ = $1 }
	 | add_expr add_op mul_expr { $$ = makeArithE($2,$1,$3); }
         ;

add_op : PLUS  { $$ = $1; }
       | MINUS { $$ = $1; }
       ;

mul_op : STAR { $$ = $1; }
	 | SLASH { $$ = $1; }
	 ;  

mul_expr : cast_expr
         | cast_expr mul_op cast_expr { $$ = makeArithE($2, $1, $3); }
         | cast_expr MOD cast_expr { $$ = makeModE($1,$3); }
	 ;


/*	
     | IDENT LBRACKET expr RBRACKET
     | IDENT LPAR one_or_more_expr RPAR     
     | lval INCR
     | lval DECR
     | BANG expr
     | TILDE expr
     | MINUS expr %prec UMINUS
     | bin_expr 
     | LPAR TYPE RPAR expr
     | LPAR expr RPAR
     | expr ternary
     ;

bin_expr : expr PLUS expr
         | expr MINUS expr
       	 | expr STAR expr 
         | expr MOD expr 
         | expr SLASH expr 
         | expr AMP expr 
         | expr DAMP expr
         | expr DPIPE expr 
         | expr PIPE expr 
         ;


log_expr : expr EQUALS expr
     	 | expr NEQUAL expr
     	 | expr GE expr
     	 | expr GT expr
     	 | expr LE expr
     	 | expr LT expr
     	 ;

ternary : QUEST expr COLON expr %prec QUEST
	| 
	;  


one_or_more_expr : expr CExpr
		 ;

CExpr : COMMA expr CExpr
      | 
      ;

lval : IDENT
     | IDENT LBRACKET expr RBRACKET
     ; 
*/
	
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
	 	
	} else if (strcmp(argv[1],"-t")==0){
          
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

