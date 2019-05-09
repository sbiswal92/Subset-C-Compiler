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
  
  char flag = 'x';
  int num_of_param = 0;
  int ret_param = 0;
  int id_num = 0;
  int param_num = 0;
  int fun_num = 0;

  int is_fun_alone = 0; // no parameters to the function
  extern int level ;
  int if_cond_flag = 1;
  int for_cond_flag = 1;
  int while_cond_flag = 1;
  

  int const_num = 0;
  char **all_const;



  int pass = 1;
  exp_node *temp;

  extern char* type_arr_in[8];/*={
                        "error",
                        "void",
                        "char",
                        "int",
                        "float",
                        "char[]",
                        "int[]",
                        "float[]"
                    };*/
  

  void yyerror(const char *msg){
    fprintf(stderr, "Error in %s line %d: %s\n", filename, yylineno,msg);
  }

struct symbolTable *symT;
int is_ret_there = 0;

/*sprintf(prefix,"%s: %s: %s",argv[0],cmd_argv[0],cmd_argv[1]);*/

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
%token <sval>  EQUALS NEQUAL GT GE LT LE PLUS STAR SLASH MOD PIPE DPIPE  DAMP MINUS BANG AMP TILDE
%token <sval>  STRCONST CHARCONST INTCONST REALCONST
%token <sval> IDENT

%type <sval> unary_op asgn_op rel_op add_op mul_op check_op
%type <eval> expr unary_expr cond_expr log_or_expr log_and_expr bit_or_expr bit_and_expr check_expr mul_expr add_expr rel_expr cast_expr texpr expr_stmt 
%type <eval> fun_call_Left idList fun_call_begin postfix_expr
%type <eval> declaration decl_init_list declarator
%type <eval> jump_stmt compound_stmt stmt block_item matched_item_list
%type <eval>  selection_stmt iteration_stmt 
%type <sval> decl_spec decl_init

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

trans_unit : input  { if(flag == 'p') printAllLists(symT,0); printf("\n"); } 

input : ext_decl 
      | input ext_decl {  } 
      ;

ext_decl : fun_definition {  }
	 | declaration 
	 | DIR_ERR { fprintf(stderr,"Error in %s line %d: \n\t directive '%s' not implemented, ignoring\n",filename, yylineno, yytext); }
         ;

declaration : decl_spec SEMI { $$ = makeDeclStmtE($1); }
	    | decl_spec decl_init_list SEMI { $$ = makeDeclStmtE($1); }
	    ;

decl_spec : TYPE { curr_type = getType($1); }
	  ;

decl_init_list : decl_init { }
	       | decl_init_list COMMA decl_init { }
	       ;

decl_init : declarator { }
	  | declarator ASSIGN texpr { }
	  ;


declarator : IDENT {    if(pass == 1)
                        {
                                struct symbol thisSym;
                                initializeSymbol(&thisSym, $1, curr_type, variable, yylineno, id_num);
                                id_num+=1;
                                symbolTable_insertSymbol(symT, thisSym,filename,yylineno);
                                
                        }
		   }
	    | IDENT LBRACKET INTCONST RBRACKET {
                                                        if(pass == 1)
                                                        {       
                                                                struct symbol thisSym;
                                                                initializeSymbol(&thisSym, $1, curr_type + 3, variable,yylineno, id_num);
                                                                id_num+=1;
                                                                symbolTable_insertSymbol(symT, thisSym,filename,yylineno);
                                                        }
                                                }
	  | fun_dec_Left RPAR { 
                                
                                if(pass==1) 
                                {
                                        int x=0; 
                                        symT = exit_scope(symT,&x,filename,yylineno); /*exit scope just a declaration*/  
                                        fun_num = symT->fun_num+1;
                                }  
                                if(pass==2) 
                                {
                                        int x=1; 
                                        symT = exit_scope(symT,&x,filename,yylineno); /*exit scope just a declaration*/  
                                        fun_num = symT->fun_num+1;
                                }       
                             }
          ;

fun_declarator : fun_dec_Left RPAR { /*do not exit scope because function body follows*/ }
	       ;

fun_dec_Left : fun_dec_begin paramList { if(pass==2) 
                                                {
                                                        printf("\n .params %d",num_of_param); 
                                                        printf("\n .return %d",ret_param); 
                                                        printf("\n .locals %d",symT->local_num+1); 
                                                }
                                        }                                              
	     | fun_dec_begin   {        num_of_param = 0;
                                        if(pass==2) 
                                                {
                                                        printf("\n .params %d",num_of_param); 
                                                        printf("\n .return %d",ret_param); 
                                                        printf("\n .locals %d",symT->local_num+1); 
                                                }
                               }
	     ;

fun_call_Left : fun_call_begin idList { $$ = makeFuncE($1,$2); }
	      | fun_call_begin { $$ = makeFuncNPE($1); }
	      ;

fun_dec_begin : IDENT LPAR {
                                 
                                  struct symbol thisSym;
                                  initializeSymbol(&thisSym, $1, curr_type, function1, yylineno, fun_num);
                                  fun_num +=1;
                                  if(pass == 1)
                                  {
                                        symbolTable_insertSymbol(symT,thisSym,filename,yylineno);
                                        symT = enter_scope(symT,thisSym,1);
                                  }
                                 if(pass==2) 
                                 {
                                        struct symbol *SymForFunIdent = lookup(symT, $1, filename, yylineno);
                                        char num[12];
                                        sprintf(num, "%d", SymForFunIdent->kind_position);
                                        int size = 1+strlen(" ")+strlen(SymForFunIdent->id)+strlen(num);
                                        char *id_code = (char*)malloc(size);
                                        strcpy(id_code,num);
                                        strcat(id_code," ");
                                        strcat(id_code,SymForFunIdent->id);
                                        printf("\n\n.FUNC %s",id_code);
                                        num_of_param = 0;
                                        ret_param = SymForFunIdent->ret_value;
                                        symT = enter_scope(symT,thisSym,0);
                                        

                                 } 
                                
			   }

fun_call_begin : IDENT LPAR {
                                 myCurrentTable = symbolTable_getParent(symT);
                                 struct symbol *SymForFunIdent = lookup(symbolTable_getParent(symT), $1, filename, yylineno);
                                 $$ = makeIdentifierNameE(SymForFunIdent);
                                 
                            }

idList : expr COMMA idList { $$ = makeCommaE($1,$3);  }
       | expr { $$ = makeCommaLastE($1); }
       ;

paramList : param { num_of_param +=1; }
	  | paramList COMMA param { num_of_param +=1; }
	  ;

param : param_TYPE pdeclarator
      ;

param_TYPE : TYPE { curr_type = getType($1); }
	   ;

pdeclarator : IDENT {
                        if(pass == 1) 
                        {
                                struct symbol thisSym;
                                initializeSymbol(&thisSym, $1, curr_type,  parameter, yylineno,id_num);
                                
                                symbolTable_insertSymbol(symT, thisSym,filename,yylineno);
                               
                        }
                    }
           | IDENT LBRACKET INTCONST RBRACKET {
                                  if(pass == 1)
                                  {
                                        struct symbol thisSym;
                                        initializeSymbol(&thisSym, $1, curr_type + 3, parameter,yylineno,id_num);
                                        symbolTable_insertSymbol(symT, thisSym,filename,yylineno);
                                        
                                  }
                                        }
	 ;

/*********************************************/

fun_definition : decl_spec fun_declarator function_body { }

function_body : function_body_left block_item_list RBRACE { 
                                                                if(pass==1)
                                                                {
                                                                        int x = 1;
                                                                        if((is_ret_there==0) && (symT->parentSymbolTableEntrySymbol.type>1))
                                                                                fprintf(stderr,"Error in %s line %d:\n \t Return type is missing for function %s:\n\t  Return type expected is %s (near line %d)\n",filename,yylineno, symT->parentSymbolTableEntrySymbol.id, type_arr_in[symT->parentSymbolTableEntrySymbol.type], symT->parentSymbolTableEntrySymbol.lineno);
                                                                        symT = exit_scope(symT,&x,filename,yylineno); 
                                                                        fun_num = symT->fun_num+1;
                                                                }
                                                                if(pass==2)
                                                                {
                                                                        int x = 1;
                                                                        symT = exit_scope(symT,&x,filename,yylineno); 
                                                                        if(is_ret_there == 0)
                                                                                {
                                                                                        printf("\nret");
                                                                                }
                                                                       
                                                                        printf("\n.end FUNC");
                                                                        is_ret_there = 0; // reset it to zero for other function
                                                                        
                                                                }
                                                                
                                                           }
	      ;

function_body_left :  LBRACE  { 

                           
                                if(pass==1)
                                {
                                        struct symbol parentSymbol = symT->parentSymbolTableEntrySymbol;
                                        int x = 0;
                                        is_ret_there = 0;
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
                                if(pass==2)
                                {
                                      
                                }  
                              }

/*********************************************/

stmt : compound_stmt  
	   | iteration_stmt 
	   | selection_stmt
	   | expr_stmt
	   | jump_stmt
	   ;

compound_stmt : compound_stmt_left matched_item_list RBRACE {
                                 /*int x = 0; 
                                 symT = exit_scope(symT,&x,filename,yylineno); */
                                 $$ = $2;
                        }
	      ;

compound_stmt_left : LBRACE  { 
                                /*if(pass == 1)
                                {
                                        struct symbol thisSym;
                                        initializeSymbol(&thisSym, "0", VOID_T, variable,yylineno,0);
                                        symT = enter_scope(symT,thisSym,1);
                                } 
                                if(pass == 2)
                                {
                                        struct symbol thisSym;
                                        initializeSymbol(&thisSym, "0", VOID_T, variable,yylineno,0);
                                        symT = enter_scope(symT,thisSym,0);
                                        
                                }*/
                             }

block_item_list : block_item 
	      	| block_item block_item_list 
		;

matched_item_list : block_item { if(pass==2){$$ = makeCompStmtE($1, NULL); dataTypeOf($$);}}
	      	| block_item matched_item_list { if(pass==2){$$ = makeCompStmtE($1, $2); dataTypeOf($$);} }
		;

block_item : declaration 
	   | stmt 
	   ;

expr_stmt : expr SEMI { int ans = dataTypeOf($1);
                        if( flag == 't' && ans) printf("Expression at file %s at line %d has type %s\n",filename, yylineno, type_arr_in[ans]); 
                        if(flag == 'i' && pass == 2 && level == 1 ) {
                                 if(is_fun_alone==1)  {
                                                appendCode($1,"\npopx");
                                                printCode($1);
                                                is_fun_alone = 0;
                                        } 
                                        else
                                          printCode($1);
                                
                                 }
                      }
          | SEMI
	  ;


jump_stmt : CONTINUE SEMI {
                                if(pass==2){
                                $$ = makeContinueStmtE();
                                dataTypeOf($$); }
                          }

	  | BREAK SEMI {
                                if(pass==2){
                                $$ = makeBreakStmtE();
                                dataTypeOf($$); }
                       }
          | RETURN expr SEMI  { 
                                $$ = makeRetE($2);
                                struct symbol parentSymbol = symT->parentSymbolTableEntrySymbol;
                                enum type ret_type = dataTypeOf($$);
                                is_ret_there = 1;
                                if( ret_type > parentSymbol.type)
                                      fprintf(stderr,"Error in %s line %d:\n \t No match for return type %s for function %s:\n\t Return type expected is %s (near line %d)\n",filename,yylineno,type_arr_in[ret_type], parentSymbol.id, type_arr_in[parentSymbol.type], parentSymbol.lineno);
                                if(flag == 'i' && pass == 2) printCode($$);
                              }
     	  | RETURN SEMI { 
                          struct symbol parentSymbol = symT->parentSymbolTableEntrySymbol;
                          is_ret_there = 0;
                          if(parentSymbol.type !=VOID_T)
                                fprintf(stderr,"Error in %s line %d:\n \t No match for return type %s for function %s:\n\t  Return type expected is void (near line %d)\n",filename,yylineno,parentSymbol.id,type_arr_in[parentSymbol.type], parentSymbol.lineno);
                          if(flag == 'i' && pass == 2) printf("\n");
                        }
          ; 

inc_level :     {       if(pass==2) level++;
                }
		;

dec_level :     {       if(pass==2) level--;
                }
		;


selection_stmt : IF inc_level LPAR expr RPAR stmt dec_level { 
                                                              if(pass==2)
                                                              {
                                                                $$ = makeIfStmtE($4,$6);
                                                                dataTypeOf($$);
                                                                if(level==1) printCode($$);
                                                              }
                                                             }  %prec NO_ELSE

               | IF inc_level LPAR expr RPAR stmt ELSE stmt dec_level 
                                                                { 
                                                                   if(pass==2){
                                                                        $$ = makeIfElseStmtE($4,$6,$8);
                                                                        dataTypeOf($$);
                                                                        if(level==1) printCode($$);
                                                                        }
                                                                 }
               ;

iteration_stmt : FOR inc_level LPAR expr_stmt expr_stmt expr RPAR stmt dec_level
                                         {
                                                 if(pass==2){
                                                dataTypeOf($6);
                                                $$ = makeForStmtE($4, $5, $8, $6);
                                                dataTypeOf($$);
                                                if(level==1) printCode($$);  }
                                          }
     	       | WHILE inc_level LPAR expr RPAR stmt dec_level
                                          {
                                                  if(pass==2){
                                                $$ = makeWhileStmtE($4,$6);
                                                dataTypeOf($$);
                                                if(level==1) printCode($$);  }
                                          }
               | DO inc_level stmt WHILE LPAR expr RPAR SEMI dec_level
                                          {
                                                  if(pass==2){
                                                $$ = makeDoWhileStmtE($6,$3);
                                                dataTypeOf($$);
                                                if(level==1) printCode($$); } 
                                          }
                                           
               ;


texpr : INTCONST  { $$ = makeIntConstE($1);  }
      | REALCONST { $$ = makeFloatConstE($1); }
      | STRCONST  { 
                        if(pass == 1)  
                        {
                          if(const_num==0)
                                all_const = (char**)malloc(1*sizeof(char*));
                          else
                                all_const = (char**)realloc(all_const,(const_num+1)*sizeof(char*));
                                
                          all_const[const_num] = (char*)malloc(strlen($1));
                          //strcpy(all_const[const_num],"0x");
                          strcpy(all_const[const_num],$1);
                          const_num +=1;
                          
                        } else if(pass == 2) {
                          for(int i=0;i<const_num;i++)
                          {
                                  if(strcmp(all_const[i],$1)==0)
                                  {
                                         char const_code[5];
                                         sprintf(const_code, "%d", i);
                                         $$ = makeCArrConstE(const_code); 
                                        
                                  }
                          }
                         
                        }
                }
      | CHARCONST { $$ = makeCharConstE($1); }    
      | IDENT       { 
                        /*variable call*/
                        struct symbol *SymForVarIdent = lookup(symT, $1,filename, yylineno);
                        $$ = makeIdentifierNameE(SymForVarIdent);
                    } 
      | LPAR expr RPAR { $$ = $2; } 
      ;

postfix_expr : texpr { $$ = $1; }
             | postfix_expr INCR { $$ = makeUnPostE($2,$1); }
             | postfix_expr DECR { $$ = makeUnPostE($2,$1); }
             | postfix_expr LBRACKET expr RBRACKET { $$ = makeArrE($1,$3); }
             ;


expr : unary_expr asgn_op expr { $$ = makeAssE($2,$1,$3); }
     | cond_expr  { $$ = $1; }
     | fun_call_Left RPAR { $$ = $1; if(pass==2) is_fun_alone = 1;}
     ;

/*rexpr : fun_call_Left RPAR { $$ = $1; if(pass==2) is_fun_alone = 0; }
      | cond_expr { $$ = $1; }
      ;*/

unary_expr : INCR unary_expr { $$ = makeUnPreE($1,$2); }
           | DECR unary_expr { $$ = makeUnPreE($1,$2); }
           | unary_op cast_expr { $$ = makeSomeUnE($1 ,$2); }
           | postfix_expr { $$ = $1;}
	   ;


unary_op : MINUS {$$ = $1; }
	 | BANG  {$$ = $1; }
	 | TILDE {$$ = $1; }
         | AMP   {$$ = $1; }
         ;

cast_expr : unary_expr { $$ = $1;  }
	  | LPAR TYPE RPAR cast_expr {$$ = makeCastE($2,$4);}
          ;

asgn_op  : PLUSASSIGN { $$ = $1; }
	      | MINUSASSIGN { $$ = $1; }
	      | STARASSIGN { $$ = $1; }
	      | SLASHASSIGN { $$ = $1; }
	      | ASSIGN  { $$ = $1; }
	      ;

cond_expr : log_or_expr {$$ = $1;}
	  | log_or_expr QUEST expr COLON cond_expr {$$ = makeCondE($1,$3,$5);}
	  ;

log_or_expr : log_and_expr {$$ = $1;}
	    | log_or_expr DPIPE log_and_expr {$$ = makeLogE($2,$1,$3); dataTypeOf($$);}
	    ;

log_and_expr : bit_or_expr {$$ = $1;}
	     | log_and_expr DAMP bit_or_expr  {$$ = makeLogE($2,$1,$3); dataTypeOf($$);}
	     ;

bit_or_expr : bit_and_expr {$$ = $1;}
	    | bit_or_expr PIPE bit_and_expr {$$ = makeBitE($2,$1,$3);}
	    ;

bit_and_expr : check_expr {$$ = $1;}
	     | bit_and_expr AMP check_expr {$$ = makeBitE($2,$1,$3);}
             ;

check_expr : rel_expr {$$ = $1;}
	   | check_expr check_op rel_expr {$$ = makeRelE($2,$1,$3); dataTypeOf($$);}
	   ;

check_op : EQUALS {$$ = $1; }
	 | NEQUAL {$$ = $1; }
         ;

rel_expr : add_expr {$$ = $1; }
         | rel_expr rel_op add_expr { $$ = makeRelE($2,$1,$3); dataTypeOf($$); }
         ;

rel_op : GE {$$ = $1; }
       | GT {$$ = $1; }
       | LE {$$ = $1; }
       | LT {$$ = $1; }
       ;

add_expr : mul_expr { $$ = $1; }
	 | add_expr add_op mul_expr { $$ = makeArithE($2,$1,$3);  }
         ;

add_op : PLUS  { $$ = $1; }
       | MINUS { $$ = $1; }
       ;

mul_op : STAR { $$ = $1; }
	 | SLASH { $$ = $1; }
	 ;  

mul_expr : cast_expr { $$ = $1;}
         | mul_expr mul_op cast_expr { $$ = makeArithE($2, $1, $3);}
         | mul_expr MOD cast_expr { $$ = makeModE($1,$3);  }
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

        if(argc<3) {

                fprintf(stderr, "Error: input expected in the form of './compile -[l|p|t|i] <inputfile>'\n");
                exit(1);

        } else if (strcmp(argv[1],"-l")==0) {
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
                
        } else if (argc>4) {

		fprintf(stderr, "Error: input expected in the form of './compile -[l|t|i] <inputfile> '\n");

        } else {
        
                if (strcmp(argv[1],"-p")==0) {
                
                        {
                                flag = 'p';
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
                        
                } else if (strcmp(argv[1],"-t")==0) {
                
                        {
                                flag = 't';
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
                        
                } else if (strcmp(argv[1],"-i")==0) {
                
                       {
                                flag = 'i';
                                filename = argv[2];
                                FILE *myfile = fopen(argv[2], "r");
                                // make sure it is valid:
                                struct symbol BlankSymbol;
                                initializeSymbol(&BlankSymbol, "0", getType("void"), variable, -10, -1);
                                symT = (struct symbolTable*)malloc(sizeof(struct symbolTable));
                                symT->symbolListHead = NULL;
                                symT->parentSymbolTable = NULL;
                                symT->parentSymbolTableEntrySymbol = BlankSymbol;
                                symT->childSymbolTableListHead = NULL;
                                symT->local_num = -1;
	                        symT->param_num = -1;
	                        symT->fun_num = -1;

                                //Add default functions to the table 
                                  struct symbol fun1;
                                  const char* getchar_name = "getchar";
                                  initializeSymbol(&fun1, getchar_name, getType("int"), function1, -1, -1);
                                  symbolTable_insertSymbol(symT,fun1,filename,-1);

                                  struct symbol fun2;
                                  initializeSymbol(&fun2, "putchar", getType("int"), function1, -2, 0);
                                  symbolTable_insertSymbol(symT,fun2,filename,-2);
                                  symT = enter_scope(symT,fun2,1);
                                        
                                        struct symbol fun2par1;
                                        initializeSymbol(&fun2par1, "c", getType("int"), parameter, -3, -1);
                                        symbolTable_insertSymbol(symT,fun2par1,filename,-3);
                                        int x = 0;
                                        symT = exit_scope(symT,&x,filename,-3);
                                  
                                  


                                // Set flex to read from it instead of defaulting to STDIN:
                                yyin = myfile;
                                // Parse through the input:
                                pass = 1;
                                yyparse();
                                printf("\n.CONSTANTS %d", const_num);
                                for(int i = 0;i<const_num;i++)
                                {
                                        printf("\n %s",all_const[i]);
                                }
                                printf("\n\n.GLOBALS %d",symT->local_num+1);
                                printf("\n\n.FUNCTIONS %d",symT->fun_num + 1 - 2);
                                printf("\n\n");
                                
                                pass = 2;
                                FILE *myfile1 = fopen(argv[2], "r");
                                yyin = myfile1;
                                yyparse();
                        }
                        
                }
        }

}

