#include "memory.h"
#include "ast.h"
#include<string.h>


exp_node* convertToExpNode(char* cast_type)
{
        exp_node *e;                                                                                    
        e = NEW(exp_node);    

        if(strcmp(cast_type, "char")==0)      
        {                                                                    
                e->node_type = cCnst; 
                e->contents.charConstE = '\0';   
        }
        else if(strcmp(cast_type, "int")==0)      
        {                                                                    
                e->node_type = iCnst; 
                e->contents.intConstE = 0;   
        }
        else if(strcmp(cast_type, "float")==0)      
        {                                                                    
                e->node_type = flCnst; 
                e->contents.floatConstE = 0.0;   
        }

        return e;

}

exp_node* makeIdentifierNameE(struct symbol *id_sym)
{
	exp_node *e;
	e = NEW(exp_node);
	e->node_type = idName;
	e->contents.identE.entry = id_sym; 
	return e;
}

exp_node* makeCharConstE(char c)                                                                 
{                                                                                                       
        exp_node *e;                                                                                    
        e = NEW(exp_node);                                                                              
        e->node_type = cCnst; 
        e->contents.charConstE = c;                                                                    
        return e;                                                                                       
}

exp_node* makeIntConstE(int n)                                                                 
{                                                                                                       
        exp_node *e;                                                                                    
        e = NEW(exp_node);                                                                              
        e->node_type = iCnst;
        e->contents.intConstE = n;                                                                    
        return e;                                                                                       
}

exp_node* makeFloatConstE(float f)                                                                
{                                                                                                       
        exp_node *e;                                                                                    
        e = NEW(exp_node);                                                                              
        e->node_type = flCnst;  
        e->contents.floatConstE = f;                                                                    
        return e;                                                                                       
}

exp_node* makeCArrConstE(char* c)                                                                 
{                                                                                                       
        exp_node *e;                                                                                    
        e = NEW(exp_node);                                                                              
        e->node_type = cArr; 
        e->contents.cArrConstE = c;                                                                    
        return e;                                                                                       
}

exp_node* makeIArrConstE(int* n)                                                                 
{                                                                                                       
        exp_node *e;                                                                                    
        e = NEW(exp_node);                                                                              
        e->node_type = iArr;
        e->contents.iArrConstE = n;                                                                    
        return e;                                                                                       
}

exp_node* makeFlArrConstE(float* f)                                                                
{                                                                                                       
        exp_node *e;                                                                                    
        e = NEW(exp_node);                                                                              
        e->node_type = flArr;  
        e->contents.flArrConstE = f;                                                                    
        return e;                                                                                       
}


exp_node* makeArithE(char* op, exp_node *left, exp_node* right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = arith_op;
        e->contents.arithE.op = op;
        e->contents.arithE.left = left; 
        e->contents.arithE.right = right;     
        return e;
}

exp_node* makeModE(exp_node *left, exp_node* right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = arith_op;
        e->contents.modE.left = left; 
        e->contents.modE.right = right;     
        return e;
}

exp_node* makeAssE(char* op, exp_node *left, exp_node* right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = ass_op;
        e->contents.assE.left = left; 
        e->contents.assE.right = right;  
        return e;
}

exp_node* makeUnPreE(char* op, exp_node* right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = un_pre_op;
        e->contents.arithE.op = op;
        e->contents.unPreE.right = right;  
        return e;
}

exp_node* makeUnPostE(char* op, exp_node* left)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = un_post_op;
        e->contents.arithE.op = op;
        e->contents.unPostE.left = left;  
        return e;
}

exp_node* makeSomeUnE(char* some_unop, exp_node* right)
{
        /*if(some_unop == '!')
               return makeUnNotE(right);
        else if(some_unop == '-')
               return makeUnMinusE(right);
        else if(some_unop == '~')
               return makeUnTildeE(right);
        else if(some_unop == '&')
               return makeUnAmpE(right);*/
        if(strcmp(some_unop,"!"))
               return makeUnNotE(right);
        else if(strcmp(some_unop,"-"))
               return makeUnMinusE(right);
        else if(strcmp(some_unop,"~"))
               return makeUnTildeE(right);
        else if(strcmp(some_unop,"&"))
               return makeUnAmpE(right);
        else
        {
             exp_node *e = NULL;
             return e;
        }        
}

exp_node* makeUnMinusE(exp_node* right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = un_minus_op;
        e->contents.unMinusE.right = right;  
        return e;
}
exp_node* makeUnNotE(exp_node* right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = un_not_op;
        e->contents.unNotE.right = right;  
        return e;
}
exp_node* makeUnTildeE(exp_node* right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = un_tilde_op;
        e->contents.unTildeE.right = right;  
        return e;
}
exp_node* makeUnAmpE(exp_node* right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = un_amp_op;
        e->contents.unAmpE.right = right;  
        return e;
}

exp_node* makeBitE(char* op, exp_node *left, exp_node* right){
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = bit_op;
        e->contents.arithE.op = op;
        e->contents.bitE.left = left; 
        e->contents.bitE.right = right;  
        return e;
}
exp_node* makeRelE(char* op, exp_node *left, exp_node* right){
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = rel_op;
        e->contents.arithE.op = op;
        e->contents.relE.left = left; 
        e->contents.relE.right = right;  
        return e;
}
exp_node* makeLogE(char* op, exp_node *left, exp_node* right){
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = log_op;
        e->contents.arithE.op = op;
        e->contents.logE.left = left; 
        e->contents.logE.right = right;  
        return e;
}
exp_node* makeCondE(exp_node *cond, exp_node *left, exp_node* right){
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = cond_op;
        e->contents.condE.cond = cond; 
        e->contents.condE.left = left; 
        e->contents.condE.right = right;  
        return e;
}
exp_node* makeCastE(char *cast_type, exp_node* right){
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = cast_op;
        e->contents.castE.cast_type = convertToExpNode(cast_type); 
        e->contents.castE.right = right;  
        return e;
}

exp_node* makeFuncE(exp_node *left, exp_node* right) {
        exp_node *e;
        e = NEW(exp_node); 
        e->node_type = func_op;
        e->contents.funcE.left = left;
        e->contents.funcE.right = right;
        return e;
}

exp_node* makeFuncNPE(exp_node *left) {
        exp_node *e;
        e = NEW(exp_node); 
        e->node_type = func_np_op;
        e->contents.funcE.left = left;
        
        return e;
}
exp_node* makeCommaE(exp_node* left, exp_node* right){
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = comma_op;
        e->contents.commaE.left = left; 
        e->contents.commaE.right = right;  
        return e;
}
exp_node* makeCommaLastE(exp_node* left){
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = comma_last_op;
        e->contents.commaE.left = left;  
        return e;
}

exp_node* makeArrE(exp_node* left, exp_node* right) {
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = arr_op;
        e->contents.arrE.left = left;  
        e->contents.arrE.right = right; 
        return e;
}
