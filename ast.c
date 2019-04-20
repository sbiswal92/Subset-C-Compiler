#include "memory.h"
#include "ast.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>


void setDataType(exp_node* E, char dt)
{
        E->data_type = dt;
}

void setCode(exp_node* E, char* code)
{
        E->code = (char*)malloc(strlen(code));
        strcpy(E->code, code);
}

void appendCode(exp_node* E, char* code)
{
        E->code = (char*)realloc(E->code,strlen(code));
        strcat(E->code, code);
      
}

void setAddress(exp_node* E, char* addr)
{
        E->address = addr;
}

void printCode(exp_node* E)
{
       printf("%s", E->code);
}

exp_node* convertToExpNode(char* cast_type)
{
        exp_node *e;                                                                                    
        e = NEW(exp_node);    

        if(strcmp(cast_type, "char")==0)      
        {                                                                    
                e->node_type = cCnst; 
                e->contents.value = "\0";   
        }
        else if(strcmp(cast_type, "int")==0)      
        {                                                                    
                e->node_type = iCnst; 
                e->contents.value = "0";   
        }
        else if(strcmp(cast_type, "float")==0)      
        {                                                                    
                e->node_type = flCnst; 
                e->contents.value = "0.0";   
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

exp_node* makeCharConstE(char* c)                                                                 
{                                                                                                       
        exp_node *e;                                                                                    
        e = NEW(exp_node);                                                                              
        e->node_type = cCnst; 
        e->contents.value = c;
        setCode(e, c); 
        return e;                                                                                       
}

exp_node* makeIntConstE(char* n)                                                                 
{                                                                                                       
        exp_node *e;                                                                                    
        e = NEW(exp_node);                                                                              
        e->node_type = iCnst;
        e->contents.value = n;
        setCode(e, n);  
        return e;                                                                                       
}

exp_node* makeFloatConstE(char* f)                                                                
{                                                                                                       
        exp_node *e;                                                                                    
        e = NEW(exp_node);                                                                              
        e->node_type = flCnst;  
        e->contents.value = f;
        setCode(e, f); 
        return e;                                                                                       
}

exp_node* makeCArrConstE(char* c)                                                                 
{                                                                                                       
        exp_node *e;                                                                                    
        e = NEW(exp_node);                                                                              
        e->node_type = cArr; 
        e->contents.value = c;
        setCode(e, "C");   
        appendCode(e, c);                                                                    
        return e;                                                                                       
}

exp_node* makeIArrConstE(char* n)                                                                 
{                                                                                                       
        exp_node *e;                                                                                    
        e = NEW(exp_node);                                                                              
        e->node_type = iArr;
        e->contents.value = n; 
        setCode(e, n);                                                                   
        return e;                                                                                       
}

exp_node* makeFlArrConstE(char* f)                                                                
{                                                                                                       
        exp_node *e;                                                                                    
        e = NEW(exp_node);                                                                              
        e->node_type = flArr;  
        e->contents.value = f;
        setCode(e, f);                                                                    
        return e;                                                                                       
}


exp_node* makeArithE(char* op, exp_node *left, exp_node *right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = arith_op;
        e->contents.arithE.op = op;
        e->contents.arithE.left = left; 
        e->contents.arithE.right = right;
        /*if(strcmp(op,"+")==0)
        {       
                char *result;
                result = (char*)malloc(strlen("push ")+strlen(left->code)+strlen("\npush ")+strlen(right->code)+strlen("\n++"));
                strcpy(result, "push ");
                strcat(result,left->code);
                strcat(result,"\npush ");
                strcat(result,right->code);
                strcat(result,"\n++");
                setCode(e,result);
        }*/   
        return e;
}

exp_node* makeModE(exp_node *left, exp_node *right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = mod_op;
        e->contents.modE.left = left; 
        e->contents.modE.right = right;     
        return e;
}

exp_node* makeAssE(char* op, exp_node *left, exp_node *right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = ass_op;
        e->contents.assE.op = op; 
        e->contents.assE.left = left; 
        e->contents.assE.right = right;
        /*if(strcmp(op,"=")==0){
                char* result;
                result = (char*)malloc(strlen(right->code)+strlen("\n")+strlen("copy\n")+strlen("pop ")+strlen(left->code)+strlen("\n")+strlen("popx\n")+1);
                strcpy(result, right->code);
                strcat(result, "\n");
                strcat(result, "copy\n");
                strcat(result, "pop ");
                strcat(result, left->code);
                strcat(result, "\n");
                strcat(result, "popx\n");
                setCode(e,result);
        }*/
        
        /*else if(strcmp(op,"+=")==0)
                sprintf(e->code," push %s\n push %s\n +type\n copy\n pop %s",right->code, left->code,left->code);*/

        return e;
}

exp_node* makeUnPreE(char* op, exp_node *right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = un_pre_op;
        e->contents.unPreE.op = op;
        e->contents.unPreE.right = right;  
        return e;
}

exp_node* makeUnPostE(char* op, exp_node* left)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = un_post_op;
        e->contents.unPostE.op = op;
        e->contents.unPostE.left = left;  
        return e;
}

exp_node* makeSomeUnE(char* some_unop, exp_node *right)
{
        /*if(some_unop == '!')
               return makeUnNotE(right);
        else if(some_unop == '-')
               return makeUnMinusE(right);
        else if(some_unop == '~')
               return makeUnTildeE(right);
        else if(some_unop == '&')
               return makeUnAmpE(right);*/

        if(strcmp(some_unop,"!")==0)
               return makeUnNotE(right);
        else if(strcmp(some_unop,"-")==0)
               return makeUnMinusE(right);
        else if(strcmp(some_unop,"~")==0)
               return makeUnTildeE(right);
        else if(strcmp(some_unop,"&")==0)
               return makeUnAmpE(right);
        else
        {
             exp_node *e = NULL;
             return e;
        }        
}

exp_node* makeUnMinusE(exp_node *right)
{
         exp_node *e;
        e = NEW(exp_node);  
        e->node_type = un_minus_op;
        e->contents.unMinusE.right = right; 
        return e;
}
exp_node* makeUnNotE(exp_node *right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = un_not_op;
        e->contents.unNotE.right = right;  
        return e;
}
exp_node* makeUnTildeE(exp_node *right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = un_tilde_op;
        e->contents.unTildeE.right = right;  
        return e;
}
exp_node* makeUnAmpE(exp_node *right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = un_amp_op;
        e->contents.unAmpE.right = right;  
        return e;
}

exp_node* makeBitE(char* op, exp_node *left, exp_node *right){
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = bit_op;
        e->contents.bitE.op = op;
        e->contents.bitE.left = left; 
        e->contents.bitE.right = right;  
        return e;
}
exp_node* makeRelE(char* op, exp_node *left, exp_node *right){
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = rel_op;
        e->contents.relE.op = op;
        e->contents.relE.left = left; 
        e->contents.relE.right = right;  
        return e;
}
exp_node* makeLogE(char* op, exp_node *left, exp_node *right){
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = log_op;
        e->contents.arithE.op = op;
        e->contents.logE.left = left; 
        e->contents.logE.right = right;  
        return e;
}
exp_node* makeCondE(exp_node *cond, exp_node *left, exp_node *right){
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = cond_op;
        e->contents.condE.cond = cond; 
        e->contents.condE.left = left; 
        e->contents.condE.right = right;  
        return e;
}
exp_node* makeCastE(char *cast_type, exp_node *right){
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = cast_op;
        e->contents.castE.cast_type = convertToExpNode(cast_type); 
        e->contents.castE.right = right;  
        return e;
}

exp_node* makeRetE(exp_node* right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = ret_op;
        e->contents.retE.right = right;
        return e;
}

exp_node* makeFuncE(exp_node *left, exp_node *right) {
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
exp_node* makeCommaE(exp_node* left, exp_node *right){
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

exp_node* makeArrE(exp_node* left, exp_node *right) {
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = arr_op;
        e->contents.arrE.left = left;  // pointer name
        e->contents.arrE.right = right;  // pointer index--> always integer
        return e;
}
