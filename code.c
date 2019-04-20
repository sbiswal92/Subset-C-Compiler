#include<stdio.h>
#include<stdlib.h>
#include "code.h"
#include "symbolTable.h"

void printCode(exp_node *e)
{
    switch(e->node_type)
    {
        case cCnst: setCode(e, e->contents.value);  
        
        case iCnst: setCode(e, e->contents.value); 
        
        case flCnst: setCode(e, e->contents.value); 

        case cArr: setCode(e, e->contents.value); 

        case iArr: setCode(e, e->contents.value); 

        case flArr: setCode(e, e->contents.value); 

        case idName: setCode(e, "L0");

        case arith_op: 
                        if((e->contents.arithE.op,"+")==0)
                        {       
                            char *result;
                            result = (char*)malloc(strlen("push ")+strlen(e->contents.arithE.left->code)+strlen("\npush ")+strlen(e->contents.arithE.right->code)+strlen("\n+")+1);
                            strcpy(result, "push ");
                            strcat(result,e->contents.arithE.left->code);
                            strcat(result,"\npush ");
                            strcat(result,e->contents.arithE.right->code);
                            strcat(result,"\n+");
                            setCode(e,result);
                        }   
        
        case ass_op:

                    if((e->contents.assE.op,"=")==0)
                    {
                        char* result;
                        result = (char*)malloc(strlen(e->contents.assE.right->code)+strlen("\n")+strlen("copy\n")+strlen("pop ")+strlen(e->contents.assE.left->code)+strlen("\n")+strlen("popx\n")+1);
                        strcpy(result, e->contents.assE.right->code);
                        strcat(result, "\n");
                        strcat(result, "copy\n");
                        strcat(result, "pop ");
                        strcat(result, e->contents.assE.left->code);
                        strcat(result, "\n");
                        strcat(result, "popx\n");
                        setCode(e,result);
                    }


    }
}