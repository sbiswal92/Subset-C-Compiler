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
   enum {	idName = 0, 
   			cCnst, iCnst, flCnst, cArr, iArr, flArr, 
			un_minus_op, un_not_op, un_tilde_op, un_amp_op, 
			arith_op, bit_op, rel_op, log_op, un_pre_op, un_post_op, ass_op, mod_op,
			cond_op, cast_op, func_op, func_np_op,
			comma_op, comma_last_op, arr_op,
			ret_op
		} node_type;
   //int data_type; //0:error, 1: void , 2: char, 3: int, 4: float, 5: char[], 6: int[],  7: float[] 
   union
   {
	   char* identifierName;
	   char charConstE;
	   int intConstE;
	   float floatConstE;
	   char* cArrConstE;
	   int* iArrConstE;
	   float* flArrConstE;
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
	   struct { struct exp_node *cond; struct exp_node *left; struct exp_node *right;} condE;
	   struct { struct exp_node *cast_type; struct exp_node *right;} castE;
	   struct { struct exp_node *left; struct exp_node *right;} funcE; //left: ident, right: params
	   struct {struct exp_node *left;} funcNPE; //left: ident, right: params
	   struct { struct exp_node *left; struct exp_node *right;} commaE;
	   struct { struct exp_node *left;} commaLastE;
	  
   }contents;
} exp_node;


exp_node* makeIdentifierNameE(struct symbol *id_sym);
exp_node* makeCharConstE(char c);
exp_node* makeIntConstE(int n);
exp_node* makeFloatConstE(float f);
exp_node* makeSomeArrConstE(char some_unop, exp_node* right);
exp_node* makeCArrConstE(char* c);
exp_node* makeIArrConstE(int* n);
exp_node* makeFlArrConstE(float* f);
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
exp_node* makeFuncE(exp_node *left, exp_node* right);
exp_node* makeFuncNPE(exp_node *left);
exp_node* makeCommaE(exp_node *left, exp_node* right);
exp_node* makeCommaLastE(exp_node *left);
exp_node* convertToExpNode(char* cast_type);
//exp_node** addtoList(struct exp_node **params,struct exp_node *enode);
