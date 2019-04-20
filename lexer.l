%x COMMENTC COMMENTCPP
%x INC_FILE
%x DEF_IDENT

%{
 #include "parser.tab.h"
 #include<stdio.h>
#include<inttypes.h>
 
int yywrap() {
    return 1;
  }

#define MAX_INCLUDE_DEPTH 256

 
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

"/*"    { oldstate = YY_START; BEGIN COMMENTC; }
<COMMENTC>"*/"  {BEGIN oldstate; }
<COMMENTC>.  { }
<COMMENTC>\n { yylineno++; }
<COMMENTC><<EOF>> { fprintf(stderr, "Error : Comment not closed, reached end of file\n"); return MARK_EOF; }


"//"    { oldstate = YY_START; BEGIN COMMENTCPP; }
<COMMENTCPP>.   { }
<COMMENTCPP>\n { yylineno++; BEGIN oldstate; }


^#[ \t]*include {  oldstate = YY_START; BEGIN DEF_IDENT; return DIR_ERR; }



^"#"[ \t]*(define|undef|ifdef|ifndef|else|endif) { oldstate = YY_START; BEGIN DEF_IDENT; return DIR_ERR;}
<DEF_IDENT>. { }
<DEF_IDENT>\n { yylineno++; BEGIN oldstate;}




[ \t]*  { /* Ignore */ }

void |
char |
string |
int |
float {yylval.sval = (strdup(yytext));  return TYPE;}

for {return FOR;}

while {return WHILE;}

do {return DO;}

if {return IF;}

else {return ELSE;}

break {return BREAK;}

continue {return CONTINUE;}

return {return RETURN;}

[0-9]+ {
		int ival = (atoi(yytext)); 
		char hval[32]; 
		sprintf(hval, "0x%x", ival ); 
		yylval.sval = (char*)malloc(strlen(hval));
		strcpy(yylval.sval, hval);  /* = (strdup(yytext));*/ 
		return INTCONST;
		}

[0-9]*\.[0-9]+ { 
				float ival = (atof(yytext));
				char hval[90]; 
				sprintf(hval, "0x%x", *(unsigned int*)&ival );
				yylval.sval = (char*)malloc(strlen(hval)); 
				strcpy(yylval.sval, hval); 
				/*yylval.fval = (atof(yytext)) yylval.sval = (strdup(yytext))*/;
				return REALCONST;
				}

["].*["] { 
			//yylval.sval = ((yytext)); 
			char hval[32]; 
			for(int i=1;i<yyleng-1;i++)
			  sprintf(&hval[(i-1)*2], "%02x", yytext[i] );
			
			yylval.sval = (char*)malloc(2*(yyleng-2)); 
			strcpy(yylval.sval, hval); 
			return STRCONST;
		}

[']\\[abnrt]['] { /*yylval.cval = yytext[0];*/  
				  char hval[32]; 
				  for(int i=1;i<yyleng-1;i++)
			  	  sprintf(&hval[(i-1)*2], "%02x", yytext[i] );
				  yylval.sval = (char*)malloc(2*(yyleng-2)+2); 
				  strcpy(yylval.sval, "0x");
				  strcat(yylval.sval, hval);
				  return CHARCONST; 
				}
['][a-zA-Z0-9]['] { /*yylval.cval = yytext[0];*/ 
				    char hval[32]; 
				  	for(int i=1;i<yyleng-1;i++)
			  	  		sprintf(&hval[(i-1)*2], "%02x", yytext[i] );
				    yylval.sval = (char*)malloc(2*(yyleng-2)+2); 
					strcpy(yylval.sval, "0x");
				    strcat(yylval.sval, hval); 
					return CHARCONST; 
				  }

[a-z_A-Z][a-zA-Z_0-9]* {yylval.sval = (strdup(yytext)); return IDENT;}


\[ {yylval.sval = strdup(yytext); return LBRACKET;}

\] {yylval.sval = strdup(yytext); return RBRACKET;}

\{ {yylval.sval = strdup(yytext); return LBRACE;}

\} {yylval.sval = strdup(yytext); return RBRACE;}

\( {yylval.sval = strdup(yytext); return LPAR;}

\) {yylval.sval = strdup(yytext); return RPAR;}

, {yylval.sval = strdup(yytext); return COMMA;}

; {yylval.sval = strdup(yytext); return SEMI;}

\? {yylval.sval = strdup(yytext); return QUEST;}

: {yylval.sval = strdup(yytext); return COLON;}

== {yylval.sval = strdup(yytext); return EQUALS;}

!= {yylval.sval = strdup(yytext); return NEQUAL;}

>= {yylval.sval = strdup(yytext); return GE;}

> {yylval.sval = strdup(yytext); return GT;}

\<= {yylval.sval = strdup(yytext); return LE;}

\< {yylval.sval = strdup(yytext); return LT;}

\+= {yylval.sval = strdup(yytext); return PLUSASSIGN;}

\+\+ {yylval.sval = strdup(yytext); return INCR;}

\+ {yylval.sval = strdup(yytext); return PLUS;}

-= {yylval.sval = strdup(yytext); return MINUSASSIGN;}

-- {yylval.sval = strdup(yytext); return DECR;}

- {yylval.sval = strdup(yytext); return MINUS;}

\*= {yylval.sval = strdup(yytext); return STARASSIGN;}

\* {yylval.sval = strdup(yytext); return STAR;}

\/= {yylval.sval = strdup(yytext); return SLASHASSIGN;}

\/ {yylval.sval = strdup(yytext); return SLASH;}

~ {yylval.sval = strdup(yytext); return TILDE;}

&& {yylval.sval = strdup(yytext); return DAMP;}

& {yylval.sval = strdup(yytext);  return AMP;}

! {yylval.sval = strdup(yytext); return BANG;}

\|\| { yylval.sval = strdup(yytext); return DPIPE;}

\| { yylval.sval = strdup(yytext); return PIPE;}

% { yylval.sval = strdup(yytext); return MOD;}

= { yylval.sval = strdup(yytext); return ASSIGN;}

.           { fprintf(stderr, "Error - ignoring character '%c'\n", yytext[0]); }

%%


/*int main()
{
 yylex();
}*/

/*
struct symbols {
      char *idname;
      int level;
      int isParam;
      int type; // 1: Variable, 2: Function
      struct word *next;
}*symTab=0;

struct symbols* last = 0;

void insertSym(char* idname, int type)
{

struct symbols* newSym = (struct symbols*)malloc(sizeof(struct symbols));
newSym->idname = idname;
newSym->type = type;
newSym->level = level;
newSym->isParam = isParam;
newSym-> next = 0;

	if(head==0)
	{
	  last = newSym;
	  symTab = last; 
	}else{
	 last = newSym;
	 symTab->next = last;
	}	
	
}

void printSym()                                                             
{               
        
struct symbols* newSym = (struct symbols*)malloc(sizeof(struct symbols));                
  
 newSym = head;

 while(newSym!=last)
 {
	
	if(newSym->level==0)
	{
	 if(newSym->type == 2)
	{
		printf("\nFunction %s", newSym->idname);
 	}else
		if(newSym->isParam==1)
			printf("\n Param %s", newSym->idname);
		else
			printf("\n LocalVar %s", newSym->idname);
      }
 
     newSym = newSym->next;

}

}*/


char* getTokenName(int n)
{
        switch(n)
        {
                case TYPE       :       return "TYPE";
                case FOR        :       return "FOR";
                case WHILE      :       return "WHILE";
                case DO         :       return "DO";
                case IF         :       return "IF";
                case ELSE       :       return "ELSE";
                case BREAK      :       return "BREAK";
                case CONTINUE   :       return "CONTINUE";
                case RETURN     :       return "RETURN";
                case IDENT      :       return "IDENT";
                case INTCONST   :       return "INTCONST";
                case REALCONST  :       return "REALCONST";
                case STRCONST   :       return "STRCONST";
                case CHARCONST  :       return "CHARCONST";
                case LPAR       :       return "LPAR";
                case RPAR       :       return "RPAR";
                case LBRACKET   :       return "LBRACKET";
                case RBRACKET   :       return "RBRACKET";
                case LBRACE     :       return "LBRACE";
                case RBRACE     :       return "RBRACE";
                case COMMA      :       return "COMMA";
                case SEMI       :       return "SEMI";
                case QUEST      :       return "QUEST";
                case COLON      :       return "COLON";
                case EQUALS     :       return "EQUALS";
                case NEQUAL     :       return "NEQUAL";
                case GT         :       return "GT";
                case GE         :       return "GE";
                case LT         :       return "LT";
                case LE         :       return "LE";
                case PLUS       :       return "PLUS";
                case MINUS      :       return "MINUS";
                case STAR       :       return "STAR";
                case SLASH      :       return "SLASH";
                case MOD        :       return "MOD";
                case TILDE      :       return "TILDE";
                case PIPE       :       return "PIPE";
                case AMP        :       return "AMP";
                case BANG       :       return "BANG";
                case DPIPE      :       return "DPIPE";
		case DAMP       :       return "DAMP";
                case ASSIGN     :       return "ASSIGN";
                case PLUSASSIGN :       return "PLUSASSIGN";
                case MINUSASSIGN:       return "MINUSASSIGN";
                case STARASSIGN :       return "STARASSIGN";
                case SLASHASSIGN:       return "SLASHASSIGN";
                case INCR       :       return "INCR";
                case DECR       :       return "DECR";
                default         :       return 0;
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

