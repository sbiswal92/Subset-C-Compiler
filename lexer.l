%option noyywrap
%x COMMENTC COMMENTCPP
%x INC_FILE 
%x DEF_IDENT



%{
#include<string.h>

#define MAX_INCLUDE_DEPTH 256

 enum token_name{
  MARK_EOF = -2,
  INCLUDE_ERR,
  TOKEN_ERR,
  DIR_ERR,
  TYPE,
  FOR,
  WHILE,
  DO,
  IF,
  ELSE,
  BREAK,
  CONTINUE,
  RETURN,
  IDENT,
  INTCONST,
  REALCONST,
  STRCONST,
  CHARCONST,
  LPAR,
  RPAR,
  LBRACKET,
  RBRACKET,
  LBRACE,
  RBRACE,
  COMMA,
  SEMI,
  QUEST,
  COLON,
  EQUALS,
  NEQUAL,
  GT,
  GE,
  LT,
  LE,
  PLUS,
  MINUS,
  STAR,
  SLASH,
  MOD,
  TILDE,
  PIPE,
  AMP,
  BANG,
  DPIPE,
  DAMP,
  ASSIGN,
  PLUSASSIGN,
  MINUSASSIGN,
  STARASSIGN,
  SLASHASSIGN,
  INCR,
  DECR,
  DEFAULT
 };

  char* getTokenName(int);
  
  struct  fileTracker{
  	char* name;
  	int current_line_no;
	FILE* file;
	YY_BUFFER_STATE bs_state;
  	struct  fileTracker* prev;
  }*FileStack=0;
  
  
  int pushToStack(char* fname);
  int popFromStack();
  int isIncludeCycle(char* fname);
  int include_stack_ptr = 0;
  
    
  struct fileNames{
  	char* name;
  	struct  fileNames* prev;
  }*FileList=0;
  
  int pushToList(char* fname);
  int foundInList(char* fname);
  
  int isCFile(char* fname);

  int oldstate;
  
%}

%%


<INITIAL>\n { yylineno++; }

"/*" 	{ oldstate = YY_START; BEGIN COMMENTC; }
<COMMENTC>"*/"  {BEGIN oldstate; }
<COMMENTC>.  { }
<COMMENTC>\n { yylineno++; }
<COMMENTC><<EOF>> { fprintf(stderr, "Error : Comment not closed, reached end of file\n"); return MARK_EOF; }


"//"    { oldstate = YY_START; BEGIN COMMENTCPP; }
<COMMENTCPP>.   { }
<COMMENTCPP>\n { yylineno++; BEGIN oldstate; }


^#[ \t]*include[ \t]*[\"] {   oldstate = YY_START; BEGIN INC_FILE; }
<INC_FILE>[^ \n\t\"]+     {	
			   { int c;
			     while((c = input()) && c != '\n') ;
			     yylineno++; 
		           }
			   
			   BEGIN oldstate;						 
			   if(pushToStack(yytext)==0)	 return INCLUDE_ERR;
			  
			  }	
			  					
<<EOF>> { if(!popFromStack())	return MARK_EOF; }



^"#"[ \t]*(define|undef|ifdef|ifndef|else|endif) { oldstate = YY_START; BEGIN DEF_IDENT; return DIR_ERR;}
<DEF_IDENT>. { }
<DEF_IDENT>\n { yylineno++; BEGIN oldstate;}	


[\t ]+ /*ignore whitespace*/; 



void |
string |
int |
float { return TYPE;}

for {return FOR;}

while {return WHILE;}

do {return DO;}

if {return IF;}

else {return ELSE;}

break {return BREAK;}

continue {return CONTINUE;}

return {return RETURN;}

[0-9]+ {return INTCONST;}

[0-9]*\.[0-9]+ {return REALCONST;}

["].*["] {return STRCONST;}

[']\\[abnrt]['] {return CHARCONST;}
['][a-zA-Z0-9]['] {return CHARCONST;}

[a-z_A-Z][a-zA-Z_0-9]* {return IDENT;}


\[ {return LBRACKET;}

\] {return RBRACKET;}

\{ {return LBRACE;}

\} {return RBRACE;}

\( {return LPAR;}

\) {return RPAR;}

, {return COMMA;}

; {return SEMI;}

\? {return QUEST;}

: {return COLON;}

== {return EQUALS;}

!= {return NEQUAL;}

>= {return GE;}

> {return GT;}

\<= {return LE;}

\< {return LT;}

\+= {return PLUSASSIGN;}

\+\+ {return INCR;}

\+ {return PLUS;}

-= {return MINUSASSIGN;}

-- {return DECR;}

- {return MINUS;}

\*= {return STARASSIGN;}

\* {return STAR;}

\/= {return SLASHASSIGN;}

\/ {return SLASH;}

~ {return TILDE;}

&& {return DAMP;}

& {return AMP;}

! {return BANG;}

\|\| {return DPIPE;}

\| {return PIPE;}

% {return MOD;}

= {return ASSIGN;}

. {return TOKEN_ERR;}

%%


char* getTokenName(int n)
{
	switch(n)
	{
		case TYPE 	: 	return "TYPE";
  		case FOR	: 	return "FOR";
  		case WHILE	: 	return "WHILE";
  		case DO		: 	return "DO";
  		case IF		: 	return "IF";
  		case ELSE	: 	return "ELSE";
  		case BREAK	: 	return "BREAK";
  		case CONTINUE	: 	return "CONTINUE";
  		case RETURN	: 	return "RETURN";
  		case IDENT	: 	return "IDENT";
  		case INTCONST	: 	return "INTCONST";
  		case REALCONST	: 	return "REALCONST";
  		case STRCONST	: 	return "STRCONST";
  		case CHARCONST	: 	return "CHARCONST";
  		case LPAR	:	return "LPAR";
		case RPAR	:	return "RPAR";
		case LBRACKET	:	return "LBRACKET";
		case RBRACKET	:	return "RBRACKET";
		case LBRACE	:	return "LBRACE";
		case RBRACE	:	return "RBRACE";
		case COMMA	:	return "COMMA";
		case SEMI	:	return "SEMI";
		case QUEST	:	return "QUEST";
		case COLON	:	return "COLON";
		case EQUALS	:	return "EQUALS";
		case NEQUAL	:	return "NEQUAL";
		case GT		:	return "GT";
		case GE		:	return "GE";
		case LT		:	return "LT";
		case LE		:	return "LE";
		case PLUS	:	return "PLUS";
		case MINUS	:	return "MINUS";
		case STAR	:	return "STAR";
		case SLASH	:	return "SLASH";
		case MOD	:	return "MOD";
		case TILDE	:	return "TILDE";
		case PIPE	:	return "PIPE";
		case AMP	:	return "AMP";
		case BANG	:	return "BANG";
		case DPIPE	:	return "DPIPE";
		case DAMP	:	return "DAMP";
		case ASSIGN	:	return "ASSIGN";
		case PLUSASSIGN	:	return "PLUSASSIGN";
		case MINUSASSIGN:	return "MINUSASSIGN";
		case STARASSIGN	:	return "STARASSIGN";
		case SLASHASSIGN:	return "SLASHASSIGN";
		case INCR	:	return "INCR";
		case DECR	:	return "DECR";
  		default		: 	return 0;
	}
}


int main(int argc, char **argv)
{

	if(argc<3)
	{
		fprintf(stderr, "Error: input expected in the form of './compile -l <inputfiles>'\n");
                exit(1);
	}
	
	else{
	 	int file_track=2;
	 	
	 	while(file_track<argc)
	 	{
	 		if(pushToStack(argv[file_track])==1){
			int token;
			for(;;){
			
	  		  	token = yylex();
	  		  	if(token==DIR_ERR) //Error for non-implemented features
	  		  		fprintf(stderr,"Error in %s line %d: \n\t directive ’%s’ not implemented, ignoring\n", FileStack->name, yylineno, yytext);

	  			else if(token==TOKEN_ERR) //Error for unknown tokens
                                        fprintf(stderr,"Error in %s line %d:\n\t unknown token'%s'\n", FileStack->name, yylineno, yytext);
	    	  	  	
				else if(token==INCLUDE_ERR)
					continue;

				else if(token==MARK_EOF)
					break;

				else
					printf("File %s Line %d Token %s Text '%s'\n", FileStack->name, yylineno, getTokenName(token), yytext);
				}
			}
			
			file_track+=1;
		}
		
	}

}

int pushToStack(char* fname)
{

	if(!isCFile(fname))
	{
	  if(FileStack!=0)
	  	fprintf(stderr, "Error in %s line %d :\n\t Included file is not a C header file or C source file, ignoring file '%s'\n",FileStack->name,yylineno,fname);
          else
	       fprintf(stderr, "Error:\t Input file is not a C header file or C source file, ignoring file '%s'\n",fname); 
	  return 0;		
	}

	if( isIncludeCycle(fname) == 1)
	{	fprintf(stderr, "Error in %s line %d : \n\t cyclical dependencies between header file objects, ignoring file '%s'\n",FileStack->name,yylineno,fname);
		return 0;
	}
	
	if( foundInList(fname) == 1)
		return 2;
		
		
	FILE* f;
	f = fopen(fname,"r");
	struct  fileTracker* new_file = (struct  fileTracker*)malloc(sizeof(struct  fileTracker));
	
	if(include_stack_ptr == MAX_INCLUDE_DEPTH)
	{
		fprintf(stderr, "Error in %s line %d :\n\t Too many nested include files: depth = %d, ignoring file '%s'\n",FileStack->name,yylineno,MAX_INCLUDE_DEPTH,fname);
		return 0;
	}

	if(!f)
	{
		fprintf(stderr, "Error in %s line %d :\n\t No such file exists : %s, ignoring\n",FileStack->name,yylineno,fname);
		return 0;
	}		
	
	if(!new_file)
	{
		fprintf(stderr, "Error:\t Memory exceeded");
		exit(1);
	}
	

	if(FileStack)
	{
		FileStack->current_line_no = yylineno;	
	}
	new_file->prev = FileStack;
	new_file->bs_state = yy_create_buffer( f, YY_BUF_SIZE );
	new_file->file = f;
	new_file->name = fname;
	yy_switch_to_buffer(new_file->bs_state);
	FileStack = new_file;
	include_stack_ptr++;
	pushToList(fname);
	yylineno = 1;
	return 1;
}

int popFromStack()
{
	struct  fileTracker* new_file = (struct  fileTracker*)malloc(sizeof(struct  fileTracker));
	struct  fileTracker* curr_file = (struct  fileTracker*)malloc(sizeof(struct  fileTracker));
	
	
	if(FileStack!=0) 
		curr_file = FileStack;
	else
	   return 0;

	fclose(curr_file->file);

	if(FileStack->prev !=0){
		new_file = FileStack->prev;
		FileStack = new_file;
	}else{
		FileStack = 0;
		return 0;
	}	
	

	FILE* f = fopen(new_file->name,"r");
	include_stack_ptr--;
	yy_switch_to_buffer(new_file->bs_state);
	yylineno = new_file->current_line_no;
	return 1; 
		
}

int isIncludeCycle(char* currFileName)
{
	struct  fileTracker* top_file = (struct  fileTracker*)malloc(sizeof(struct  fileTracker));
	top_file = FileStack;
	int flag = 0;
	while(top_file!=0)
	{
		if( strcmp(top_file->name, currFileName) == 0)
			{
				flag = 1;
				break;
			}
			
		top_file = top_file->prev;	
	}
		
	return flag;
}


int pushToList(char* fname)
{

	struct  fileNames* new_file = (struct fileNames*)malloc(sizeof(struct fileNames));
			
	if(!new_file)
	{
		fprintf(stderr, "Error:\t Memory exceeded");
		exit(1);
	}
	
	new_file->name = fname;
	new_file->prev = FileList;
	FileList = new_file;
	
	return 1;
}

int foundInList(char* fname)
{

	struct  fileNames* fileIterator = (struct fileNames*)malloc(sizeof(struct fileNames));
			
	if(!fileIterator)
	{
		fprintf(stderr, "Error:\t Memory exceeded");
		exit(1);
	}
	fileIterator = FileList;
	
	while(fileIterator!=0)
	{
		if( strcmp(fileIterator->name, fname) == 0)
			{
				return 1;
			}
		fileIterator = fileIterator->prev;
	}
	
	return 0;
}

int isCFile(char* fname)
{
	int n = strlen(fname);
	if(fname[n-2]!='.')
		return 0;
	else if( fname[n-1]!='h' && fname[n-1]!='c' )
		return 0;
	else
		return 1;
}
