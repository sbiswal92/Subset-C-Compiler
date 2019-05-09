#include "memory.h"
#include "ast.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int global_inst_num = 0;

void setFlag(exp_node* E, int f)
{
        E->flag = f;
}

int getFlag(exp_node* E)
{
        return E->flag;
}

void setDataType(exp_node* E, char dt)
{
        E->data_type = dt;
}

void setCode(exp_node* E, char* code)
{
        E->code  = NULL;
        E->code = (char*)malloc(strlen(code));
        strcpy(E->code, code);
        //setNum(E);
}

void appendCode(exp_node* E, char* code)
{
        E->code = (char*)realloc(E->code,strlen(code));
        strcat(E->code, code);
      
}
void setNum(exp_node* E) 
{
       E->inst_num = global_inst_num;
       global_inst_num++;
}

int getNewNum()
{
        int old = global_inst_num;
        global_inst_num++;
        return old;

}

void setAddress(exp_node* E, char* addr)
{
        E->address = addr;
}

void printCode(exp_node* E)
{
       printf("\n%s", E->code);
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
        e->contents.logE.op = op;
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

/***************************************************/

exp_node* makeDeclStmtE(char* dt)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = STMT_DECL;
        e->contents.declStmtE.dtype = dt; //condition
        return e;

}
exp_node* makeVarListStmtE(exp_node *fv, char* rv)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = STMT_VAR_LIST;
        e->contents.varListStmtE.first_var = fv; //condition
        e->contents.varListStmtE.rem_var = rv; //statement
        return e;
}


exp_node* makeCompStmtE(exp_node *fs, exp_node *rs)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = STMT_COMPOUND;
        e->contents.compStmtE.first_stmt = fs; //condition
        e->contents.compStmtE.rem_stmt = rs; //statement
        return e;
}

exp_node* makeIfStmtE(exp_node *left, exp_node* right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = STMT_IF;
        e->contents.ifStmtE.cond = left; //condition
        e->contents.ifStmtE.tstmt = right; //statement
        return e;
}

exp_node* makeIfElseStmtE(exp_node *left, exp_node* tright, exp_node* fright)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = STMT_IF_ELSE;
        e->contents.ifElseStmtE.cond = left; //condition
        e->contents.ifElseStmtE.tstmt = tright; //statement
        e->contents.ifElseStmtE.fstmt = fright; //statement
        return e;
}


exp_node* makeWhileStmtE(exp_node *left, exp_node* right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = STMT_WHILE;
        e->contents.whileStmtE.cond = left; //condition
        e->contents.whileStmtE.tstmt = right; //statement
        return e;
}

exp_node* makeDoWhileStmtE(exp_node *left, exp_node* right)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = STMT_DO_WHILE;
        e->contents.doWhileStmtE.cond = left; //condition
        e->contents.doWhileStmtE.tstmt = right; //statement
        return e;
}

exp_node* makeForStmtE(struct exp_node *a, struct exp_node *c, struct exp_node *ts, struct exp_node *up)
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = STMT_FOR;
        e->contents.forStmtE.assgn = a; //assignment
        e->contents.forStmtE.cond = c; //condition
        e->contents.forStmtE.tstmt = ts; //statement
        e->contents.forStmtE.update = up; //update
        return e;
}

exp_node* makeBreakStmtE()
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = STMT_BREAK;
        return e;
}

exp_node* makeContinueStmtE()
{
        exp_node *e;
        e = NEW(exp_node);  
        e->node_type = STMT_CONTINUE;
        return e;
}


/*
void setCodeS(stmt_node* E, char* code)
{
        E->code = (char*)malloc(strlen(code));
        strcpy(E->code, code);
        setNumS(E);
}

void appendCodeS(stmt_node* E, char* code)
{
        E->code = (char*)realloc(E->code,strlen(code));
        strcat(E->code, code);
      
}

void printCodeS(stmt_node* E)
{
       printf("\n%s",E->code);
}

void setNumS(stmt_node* E) 
{
       E->stmt_num = global_inst_num;
       global_inst_num++;
       char prepend_char[10];
       sprintf(prepend_char, "I%d: ", E->stmt_num);
       char* postpend_char = (char*)malloc(strlen(E->code));
       strcpy(postpend_char,E->code);
       //E->code = (char*)realloc(E->code,strlen(prepend_char)+2);
       E->code = (char*)realloc(E->code,strlen(postpend_char)+strlen(prepend_char)+1);
       memmove( E->code + strlen(prepend_char), E->code, strlen(postpend_char));
       memmove( E->code , prepend_char, strlen(prepend_char));
       strcpy(E->code,prepend_char);
       strcat(E->code,postpend_char);
}


stmt_node* makeIfS(struct exp_node *cond, struct exp_node *tstmt) {
        stmt_node *e;
        e = NEW(stmt_node);  
        e->stmt_type = STMT_IF;
        e->contents.ifStmt.cond = cond;
        e->contents.ifStmt.tstmt = tstmt;  
        char numberstring[10000], numberstring1[10000],numberstring2[10000];
        strcpy(numberstring1, " I");
        sprintf(numberstring,"%d", e->contents.ifStmt.tstmt->inst_num);
        strcat(numberstring1,numberstring);

        strcpy(numberstring2, "\nI");
        strcat(numberstring2,numberstring);
        strcat(numberstring2,":");
        

        appendCode(e->contents.ifStmt.cond, numberstring1);
        setCodeS(e,e->contents.ifStmt.cond->code);
        appendCodeS(e,numberstring2);
        appendCodeS(e,e->contents.ifStmt.tstmt->code);
        setNumS(e);
        return e;
    }

stmt_node* makeIfSS(struct exp_node *cond, struct stmt_node *tstmt) {
        stmt_node *e;
        e = NEW(stmt_node);  
        e->stmt_type = STMT_IF;
        e->contents.ifStmtS.cond = cond;
        e->contents.ifStmtS.tstmt = tstmt;  
        char numberstring[10000], numberstring1[10000],numberstring2[10000];
        strcpy(numberstring1, " I");
        sprintf(numberstring,"%d", e->contents.ifStmtS.tstmt->stmt_num);
        strcat(numberstring1,numberstring);

        strcpy(numberstring2, "\nI");
        strcat(numberstring2,numberstring);
        strcat(numberstring2,":");
        

        appendCode(e->contents.ifStmtS.cond, numberstring1);
        setCodeS(e,e->contents.ifStmtS.cond->code);
        appendCodeS(e,numberstring2);
        appendCodeS(e,e->contents.ifStmtS.tstmt->code);
        setNumS(e);
        return e;
    }

*/
