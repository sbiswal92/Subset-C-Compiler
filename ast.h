/*enum arith_op
{
 PLUS, MINUS, STAR, SLASH
};

enum rel_op
{
 LT, LE, GT, GE
};


enum eq_op
{
  EQUALS,
  NEQUAL
};

enum bit_op
{
 AMP, PIPE
};

enum log_op
{
 DPIPE, DAMP, BANG 
};

enum ass_op
{
 ASSIGN, PLUSASSIGN, MINUSASSIGN, STARASSIGN, SLASHASSIGN
};*/

/*enum data_type
{
	ERROR_T,
	VOID_T,
	CHAR_T,
	INT_T,
	FLOAT_T,
	CHAR_ARR_T,
	INT_ARR_T,
	FLOAT_ARR_T
};*/

typedef struct exp_node
{

   char data_type;
   enum {	 
   			cCnst = 0, iCnst, flCnst, cArr, iArr, flArr, 
				idName,   
				un_minus_op, un_not_op, un_tilde_op, un_amp_op, 
				arith_op, bit_op, rel_op, log_op, un_pre_op, un_post_op, ass_op, mod_op,
				cond_op, cast_op, func_op, func_np_op,
				comma_op, comma_last_op, arr_op,
				ret_op,
				STMT_DECL,
				STMT_VAR_LIST,
				STMT_COMPOUND,
				STMT_IF, STMT_IF_ELSE,
				STMT_WHILE, STMT_DO_WHILE, STMT_FOR,
				STMT_BREAK, STMT_CONTINUE
		} node_type;
   //int data_type; //0:error, 1: void , 2: char, 3: int, 4: float, 5: char[], 6: int[],  7: float[] 
   union
   {
	   char* identifierName;
	   char* value;
	   /*char charConstE;
	   int intConstE;
	   float floatConstE;
	   char* cArrConstE;
	   int* iArrConstE;
	   float* flArrConstE;*/
	   struct {struct exp_node *right;} unMinusE;
	   struct {struct exp_node *right;} unNotE;
	   struct {struct exp_node *right;} unTildeE;
	   struct {struct exp_node *right;} unAmpE;
	   struct {char* op; struct exp_node *right;} unPreE;
	   struct {char* op;  struct exp_node *left;} unPostE;
	   struct { struct symbol *entry; } identE;
	   struct { char* op; struct exp_node *left; struct exp_node *right;} arithE;
	   struct { struct exp_node *left; struct exp_node *right;} arrE;
	   struct { struct exp_node *left; struct exp_node *right;} modE;
	   struct { char* op; struct exp_node *left; struct exp_node *right;} bitE;
	   struct { char* op; struct exp_node *left; struct exp_node *right;} relE;
	   struct { char* op; struct exp_node *left; struct exp_node *right;} logE;
	   struct { char* op; struct exp_node *left; struct exp_node *right;} assE;
	   struct { struct exp_node *right;} retE;
	   struct { struct exp_node *cond; struct exp_node *left; struct exp_node *right;} condE;
	   struct { struct exp_node *cast_type; struct exp_node *right;} castE;
	   struct { struct exp_node *left; struct exp_node *right;} funcE; //left: ident, right: params
	   struct {struct exp_node *left;} funcNPE; //left: ident, right: params
	   struct { struct exp_node *left; struct exp_node *right;} commaE;
	   struct { struct exp_node *left;} commaLastE;

		 /**********************/
		 struct{ char* dtype;} declStmtE;
		 struct{ struct exp_node *first_var; char* rem_var; } varListStmtE;
		 struct{ struct exp_node *first_stmt; struct exp_node *rem_stmt; } compStmtE;
		 struct{ struct exp_node *cond; struct exp_node *tstmt; } ifStmtE;
		 struct{ struct exp_node *cond; struct exp_node *tstmt; struct exp_node *fstmt; } ifElseStmtE;
		 struct{ struct exp_node *cond; struct exp_node *tstmt; } whileStmtE;
		 struct{ struct exp_node *cond; struct exp_node *tstmt; } doWhileStmtE;
		 struct{ struct exp_node *assgn; struct exp_node *cond; struct exp_node *tstmt; struct exp_node *update; } forStmtE;
		 struct{  } forBreakE;
		 struct{  } forContinueE;
		 
   }contents;
   char* code;
   int inst_num;
   char* address;
	 int flag ; // flag = -1 has false_list else flag = 1 has true_list
} exp_node;


void setDataType(exp_node* E, char dt);
void setCode(exp_node* E, char* code);
void setFlag(exp_node* E, int f);
int getFlag(exp_node* E);
void setNum(exp_node* E);
int getNewNum();
void appendCode(exp_node* E, char* code);
void setAddress(exp_node* E, char* addr);
void printCode(exp_node* E);

exp_node* makeIdentifierNameE(struct symbol *id_sym);
exp_node* makeCharConstE(char* c);
exp_node* makeIntConstE(char* n);
exp_node* makeFloatConstE(char* f);
exp_node* makeSomeArrConstE(char some_unop, exp_node* right);
exp_node* makeCArrConstE(char* c);
exp_node* makeIArrConstE(char* n);
exp_node* makeFlArrConstE(char* f);
exp_node* makeUnPreE(char* op, exp_node* right);
exp_node* makeUnPostE(char* op, exp_node* left);
exp_node* makeSomeUnE(char* some_unop, exp_node* right);
exp_node* makeArrE(exp_node* left, exp_node* right);
exp_node* makeUnMinusE(exp_node* right);
exp_node* makeUnTildeE(exp_node* right);
exp_node* makeUnAmpE(exp_node* right);
exp_node* makeUnNotE(exp_node* right);
exp_node* makeArithE(char* op, exp_node *left, exp_node* right);
exp_node* makeModE(exp_node *left, exp_node* right);
exp_node* makeBitE(char* op, exp_node *left, exp_node* right);
exp_node* makeRelE(char* op, exp_node *left, exp_node* right);
exp_node* makeLogE(char* op, exp_node *left, exp_node* right);
exp_node* makeAssE(char* op, exp_node *left, exp_node* right);
exp_node* makeCondE(exp_node *cond, exp_node *left, exp_node* right);
exp_node* makeCastE(char *cast_type, exp_node* right);
exp_node* makeRetE(exp_node* right);
exp_node* makeFuncE(exp_node *left, exp_node* right);
exp_node* makeFuncNPE(exp_node *left);
exp_node* makeCommaE(exp_node *left, exp_node* right);
exp_node* makeCommaLastE(exp_node *left);
exp_node* convertToExpNode(char* cast_type);
//exp_node** addtoList(struct exp_node **params,struct exp_node *enode);


/***************************************************/

exp_node* makeDeclStmtE(char* dtype);
exp_node* makeVarListStmtE(exp_node *first_var, char *rem_var);
exp_node* makeCompStmtE(exp_node *first_stmt, exp_node *rem_stmt);
exp_node* makeIfStmtE(exp_node *left, exp_node* right);
exp_node* makeIfElseStmtE(exp_node *left, exp_node* tright, exp_node* fright);
exp_node* makeWhileStmtE(exp_node *left, exp_node* right);
exp_node* makeDoWhileStmtE(exp_node *left, exp_node* right);
exp_node* makeForStmtE(exp_node *a, exp_node *c, exp_node *ts, exp_node *up);
exp_node* makeBreakStmtE();
exp_node* makeContinueStmtE();


/*
typedef struct stmt_node
{

   enum {	 
   			STMT_DECL,
            STMT_IF,
            STMT_IFELSE,
            STMT_FOR,
            STMT_WHILE,
            STMT_RET,
            STMT_BREAK
		} stmt_type;
 
   union
   {
       //struct{struct exp_node *cond; struct stmt_node *tstmt;} ifStmt;
       struct{ struct exp_node *cond; struct exp_node *tstmt; } ifStmt;
			 struct{ struct exp_node *cond; struct stmt_node *tstmt; } ifStmtS;
       
   }contents;
   char* code;
   int stmt_num;
} stmt_node;


void setCodeS(stmt_node* E, char* code);
void appendCodeS(stmt_node* E, char* code);
void printCodeS(stmt_node* E);
void setNumS(stmt_node* E);

stmt_node* makeIfS(struct exp_node *cond, struct exp_node *tstmt);
stmt_node* makeIfSS(struct exp_node *cond, struct stmt_node *tstmt);
*/