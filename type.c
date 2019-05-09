#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "type.h"
#include "symbolTable.h"


//0:error, 1: void , 2: char, 3: int, 4: float, 5: char[], 6: int[],  7: float[] 
char* type_arr_in[8]={
                        "error",
                        "void",
                        "char",
                        "int",
                        "float",
                        "char[]",
                        "int[]",
                        "float[]"
                    };
struct symbolTable* myCurrentTable;
int level = 1;
int L_loop;
int L_cmp;
int L_false;
int L_exit;
int L_true;

char* true_list = "T      ";
char* false_list = "F      ";



char *replaceWord(const char *s, const char *oldW, const char *newW) 
{ 
    char *result; 
    int i, cnt = 0; 
    int newWlen = strlen(newW); 
    int oldWlen = strlen(oldW); 

    // Counting the number of times old word 
    // occur in the string 
    for (i = 0; s[i] != '\0'; i++) 
    { 
        if (strstr(&s[i], oldW) == &s[i]) 
        { 
            cnt++; 
  
            // Jumping to index after the old word. 
            i += oldWlen - 1; 
        } 
    } 
  
    // Making new string of enough length 
    result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1); 
  
    i = 0; 
    while (*s) 
    { 
        // compare the substring with the result 
        if (strstr(s, oldW) == s) 
        { 
            strcpy(&result[i], newW); 
            i += newWlen; 
            s += oldWlen; 
        } 
        else
            result[i++] = *s++; 
    } 
  
    result[i] = '\0'; 
    return result; 
} 



char* getReverseOperation(char* op)
{
    char* rev_op = (char*)malloc(3);
    if(strcmp(op,"==")==0) {
        rev_op = "!=";
    } else if(strcmp(op,">=")==0) {
        rev_op = "<";
    } else if(strcmp(op,"<=")==0) {
        rev_op = ">";
    } else if(strcmp(op,">")==0) {
        rev_op = "<=";
    } else if(strcmp(op,"<")==0) {
        rev_op = ">=";
    } else {
        rev_op = "==";
    }
     return rev_op;
}

int dataTypeOf(exp_node *e)
{

    switch(e->node_type)
    {
        case cCnst: { e->data_type='c'; return CHAR_T;}
        
        case iCnst: { e->data_type='i'; return INT_T; }
        
        case flCnst: { e->data_type='f'; return FLOAT_T; }

        case cArr: { e->data_type='C'; return CHAR_ARR_T; }

        case iArr: { e->data_type='I'; return INT_ARR_T; }

        case flArr: { e->data_type='F'; return FLOAT_ARR_T; }

        case idName: { 
                        e->data_type=type_arr_in[e->contents.identE.entry->type][0];
                        char num[12];
                        sprintf(num, "%d", e->contents.identE.entry->kind_position);
                        if(e->contents.identE.entry->kind==variable)
                        {
                                int size = 1+strlen(num);
                                char *id_code = (char*)malloc(size);
                                id_code[0] = e->contents.identE.entry->whatTable;
                                strcat(id_code,num);
                                setCode(e, id_code);
                        } else if(e->contents.identE.entry->kind==parameter)
                        {
                                int size = 1+strlen(num);
                                char *id_code = (char*)malloc(size);
                                id_code[0] = e->contents.identE.entry->whatTable;
                                strcat(id_code,num);
                                setCode(e, id_code);
                        } 
                        return e->contents.identE.entry->type; 
                     }

        case un_pre_op:
                {
                    int dt_right = dataTypeOf(e->contents.unPreE.right);

                    if( (dt_right >= CHAR_T) && (dt_right <= FLOAT_T) )
                      { 
                        e->data_type=type_arr_in[dt_right][0];
                        char *dtChar = malloc(sizeof(char));
                        *dtChar = e->data_type; 
                        char *result;
                        char *op1;
                        if(e->contents.unPreE.right->node_type<3)
                            op1 = "\npushv ";
                        else if(e->contents.unPreE.right->node_type==6) //identifier
                            op1 = "\npush ";
                        else
                            op1 = "";

                        int size = strlen(op1)+strlen(e->contents.unPreE.right->code)+strlen("\n")+strlen(e->contents.unPreE.op)+strlen(dtChar)+1;
                        result = (char*)malloc(size);
                        strcpy(result, op1);
                        strcat(result,e->contents.unPreE.right->code);
                        strcat(result,"\n");
                        strcat(result,e->contents.unPreE.op);
                        strcat(result,dtChar);
                        setCode(e,result);
                        return dt_right; 
                      }
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Unary operator %s cannot be applied to expression of type %s\n",filename,yylineno,e->contents.unPreE.op,type_arr_in[dataTypeOf(e->contents.unPreE.right)]);
                        return ERROR_T;
                    }
                }
        
        case un_post_op:
                {
                    int dt_left = dataTypeOf(e->contents.unPostE.left);
                    if( (dt_left >= CHAR_T) && (dt_left <= FLOAT_T) )
                     { 
                         e->data_type=type_arr_in[dt_left][0];  
                         char *dtChar = malloc(sizeof(char));
                         *dtChar = e->data_type; 
                         char *result;
                         char *op1;
                         if(e->contents.unPostE.left->node_type<3)
                            op1 = "\npushv ";
                         else if(e->contents.unPostE.left->node_type==6) //identifier
                            op1 = "\npush ";
                         else
                            op1 = "";

                        int size = strlen(op1)+strlen(e->contents.unPostE.left->code)+strlen("\n")+strlen(e->contents.unPostE.op)+strlen(dtChar)+1;
                        result = (char*)malloc(size);
                        strcpy(result, op1);
                        strcat(result,e->contents.unPostE.left->code);
                        strcat(result,"\n");
                        strcat(result,dtChar);
                        strcat(result,e->contents.unPostE.op);
                        setCode(e,result); 
                        return dt_left; 
                     }
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Unary operator %s cannot be applied to expression of type %s\n",filename,yylineno,e->contents.unPostE.op,type_arr_in[dataTypeOf(e->contents.unPostE.left)]);
                        return ERROR_T;
                    }
                }

        case un_minus_op: 
                {
                    int dt_right = dataTypeOf(e->contents.unMinusE.right);

                    if( (dt_right >= CHAR_T) && (dt_right <= FLOAT_T) )
                      { 
                        e->data_type=type_arr_in[dt_right][0];
                        char *dtChar = malloc(sizeof(char));
                        *dtChar = e->data_type; 
                        char *result;
                        char *op1;
                        if(e->contents.unMinusE.right->node_type<3) //const
                            op1 = "\npushv ";
                        else if(e->contents.unMinusE.right->node_type==6) //identifier
                                op1 = "\npush ";
                            else
                                op1 = "";

                        int size = strlen(op1)+strlen(e->contents.unMinusE.right->code)+strlen("\nneg")+strlen(dtChar)+1;
                        result = (char*)malloc(size);
                        strcpy(result, op1);
                        strcat(result,e->contents.unMinusE.right->code);
                        strcat(result,"\nneg");
                        strcat(result,dtChar);
                        setCode(e,result);
                        return dt_right; 
                    }
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Unary operator - cannot be applied to expression of type %s\n",filename,yylineno,type_arr_in[dt_right]);
                        return ERROR_T;
                    }
                }

        case un_not_op: 
                {
                    if( (dataTypeOf(e->contents.unNotE.right) >= CHAR_T) && (dataTypeOf(e->contents.unNotE.right) <= FLOAT_T) )
                      { e->data_type=type_arr_in[dataTypeOf(e->contents.unNotE.right)][0];   return dataTypeOf(e->contents.unNotE.right); }
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Unary operator ! cannot be applied to expression of type %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.unNotE.right)]);
                        return ERROR_T;
                    }
                }

        case un_tilde_op: 
                {
                    int dt_right = dataTypeOf(e->contents.unTildeE.right);

                    if( (dt_right == CHAR_T) || (dt_right == INT_T) )
                      { 
                          e->data_type=type_arr_in[dt_right][0];
                          char *dtChar = malloc(sizeof(char));
                          *dtChar = e->data_type; 
                          char *result;
                          char *op1;
                          if(e->contents.unTildeE.right->node_type<3) //const
                            op1 = "\npushv ";
                          else if(e->contents.unTildeE.right->node_type==6) //identifier
                                op1 = "\npush ";
                            else
                                op1 = "";

                          int size = strlen(op1)+strlen(e->contents.unTildeE.right->code)+strlen("\nflip")+1;
                           result = (char*)malloc(size);
                           strcpy(result, op1);
                           strcat(result,e->contents.unTildeE.right->code);
                           strcat(result,"\nflip");
                           setCode(e,result);
                        return dt_right; 

                          return dataTypeOf(e->contents.unTildeE.right); 
                      }
                  else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Unary operator ~ cannot be applied to expression of type %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.unTildeE.right)]);
                        return ERROR_T;
                    }
                }


        case un_amp_op: 
                {
                    int dt_right = dataTypeOf(e->contents.unAmpE.right);
                    
                    if( (dt_right >= CHAR_T) && (dt_right <= FLOAT_T) )
                    {
                      { 
                          e->data_type=type_arr_in[dt_right+3][0];   
                          return dt_right+3;
                      }
                    }
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Unary operator & cannot be applied to expression of type %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.unAmpE.right)]);
                        return ERROR_T;
                    }
                }

        case arr_op: 
                {
                    int dt_left = dataTypeOf(e->contents.arrE.left);
                    int dt_right = dataTypeOf(e->contents.arrE.right); // index can be variable or constant 
                    
                    if( (dataTypeOf(e->contents.arrE.left) >= CHAR_ARR_T) && (dataTypeOf(e->contents.arrE.left) <= FLOAT_ARR_T))
                      { 
                        e->data_type=type_arr_in[dt_left-3][0];
                        char *dtChar = malloc(sizeof(char));
                        *dtChar = e->data_type; 
                        char *result;
                        char *op1;
                        if(e->contents.arrE.right->node_type==iCnst)
                            op1 = "\npushv ";
                        else if(e->contents.arrE.right->node_type==idName)
                            op1 = "\npush ";
                        else
                            op1 = "";
                       
                        int size = strlen(op1)+strlen(e->contents.arrE.right->code)+strlen("\npush ")+strlen(e->contents.arrE.left->code)+1;
                        result = (char*)malloc(size);
                        strcpy(result, op1);
                        strcat(result,e->contents.arrE.right->code);
                        strcat(result,"\npush ");
                        strcat(result,e->contents.arrE.left->code);
                        setCode(e,result);   
                        
                        return dt_left-3;
                      }
                    else 
                    {   fprintf(stderr, "Error in %s line %d:\n\t Unary operator [] cannot be applied to non-array data of type %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.arrE.left)]);
                        return ERROR_T;
                    }
                }
        case arith_op: 
                {
                    int dt_left = dataTypeOf(e->contents.arithE.left);
                    int dt_right = dataTypeOf(e->contents.arithE.right);
                    if(( (dt_left >= CHAR_T) && (dt_left <= FLOAT_T) ) && ( (dt_right >= CHAR_T) && (dt_right <= FLOAT_T) ))
                         { 
                            e->data_type=type_arr_in[dt_left>=dt_right?dt_left:dt_right][0]; 
                            char *dtChar = malloc(sizeof(char));
                            *dtChar = e->data_type; 
                                    
                            char *result;
                            char *op1, *op2;
                            if(e->contents.arithE.left->node_type<3)
                                op1 = "\npushv ";
                            else if(e->contents.arithE.left->node_type==6)
                                 op1 = "\npush ";
                            else
                                op1 = "";
                            
                            if(e->contents.arithE.right->node_type<3)
                                op2 = "\npushv ";
                            else if(e->contents.arithE.right->node_type==6)
                                 op2 = " \npush ";
                            else
                                op2 = "";
                        
                            int size = strlen(op1)+strlen(e->contents.arithE.left->code)+strlen(op2)+strlen(e->contents.arithE.right->code)+strlen("\n")+strlen(e->contents.arithE.op)+strlen(dtChar)+1;
                            result = (char*)malloc(size);
                            strcpy(result, op1);
                            strcat(result,e->contents.arithE.left->code);
                            strcat(result,op2);
                            strcat(result,e->contents.arithE.right->code);
                            strcat(result,"\n");
                            strcat(result,e->contents.arithE.op);
                            strcat(result,dtChar);
                            setCode(e,result);
                            
                            return dt_left>=dt_right?dt_left:dt_right;
                         }
                    else
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: %s %s %s\n", filename, yylineno, type_arr_in[dataTypeOf(e->contents.arithE.left)], e->contents.arithE.op, type_arr_in[dataTypeOf(e->contents.arithE.right)]);
                        return ERROR_T;
                    }
                }
        case mod_op: 
                {
                    int dt_left = dataTypeOf(e->contents.modE.left);
                    int dt_right = dataTypeOf(e->contents.modE.right);

                    if( ( ( dt_left == CHAR_T) || (dt_left == INT_T) ) &&  ( (dt_right == CHAR_T) || (dt_right == INT_T) ) )
                       { 
                           e->data_type=type_arr_in[dt_left>=dt_right ? dt_left:dt_right][0];
                           char *dtChar = malloc(sizeof(char));
                           *dtChar = e->data_type; 
                            char *result;
                            char *op1, *op2;
                            if(e->contents.modE.left->node_type<3)
                                op1 = "\npushv ";
                           else if(e->contents.modE.left->node_type==6)
                                 op1 = "\npush ";
                            else
                                op1 = "";
                          
                            if(e->contents.modE.right->node_type<3)
                                op2 = "\npushv ";
                            else if(e->contents.modE.right->node_type==6)
                                 op2 = " \npush ";
                            else
                                op2 = "";
                            
                            int size = strlen(op1)+strlen(e->contents.modE.left->code)+strlen(op2)+strlen(e->contents.modE.right->code)+strlen("\n%")+strlen(dtChar) + 1;
                            result = (char*)malloc(size);
                            strcpy(result, op1);
                            strcat(result,e->contents.modE.left->code);
                            strcat(result,op2);
                            strcat(result,e->contents.modE.right->code);
                            strcat(result,"\n%");
                            strcat(result,dtChar);
                            setCode(e,result);  
                           return  dt_left>=dt_right ? dt_left:dt_right ;
                        }
                        
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: %s %% %s\n",filename,yylineno,type_arr_in[dt_left],type_arr_in[dt_right]);
                        return ERROR_T;
                    }
                }
        case bit_op: 
                {   
                    int dt_left = dataTypeOf(e->contents.bitE.left);
                    int dt_right = dataTypeOf(e->contents.bitE.right);
                    
                    if( ( (dt_left == CHAR_T) || (dt_left == INT_T) ) &&  ( (dt_right == CHAR_T) || (dt_right == INT_T) ))
                      { 
                             e->data_type=type_arr_in[dt_left>=dt_right? dt_left : dt_right][0];   
                            char *result;
                            char *op1, *op2;
                            if(e->contents.bitE.left->node_type<3)
                                op1 = "\npushv ";
                            else    op1 = "\npush ";

                            if(e->contents.bitE.right->node_type<3)
                                op2 = "\npushv ";
                            else    op2 = "\npush ";

                            int size = strlen(op1)+strlen(e->contents.bitE.left->code)+strlen(op2)+strlen(e->contents.bitE.right->code)+strlen("\n") + 1;
                            result = (char*)malloc(size);
                            strcpy(result, op1);
                            strcat(result,e->contents.bitE.left->code);
                            strcat(result,op2);
                            strcat(result,e->contents.bitE.right->code);
                            strcat(result,"\n");
                            strcat(result,e->contents.bitE.op);
                            setCode(e,result);  
                           return  dt_left>=dt_right ? dt_left:dt_right ;

                          return  dt_left>=dt_right? dt_left : dt_right; }
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: %s %s %s\n",filename,yylineno,type_arr_in[dt_left],e->contents.bitE.op,type_arr_in[dt_right]);
                        return (ERROR_T);
                    }
                }

        case rel_op:
                {
                     int dt_left = dataTypeOf(e->contents.relE.left); // data type of left operand
                     int dt_right = dataTypeOf(e->contents.relE.right);  // data type of right operand
                   
                    if ( ( (dataTypeOf(e->contents.relE.left) >= CHAR_T) && (dataTypeOf(e->contents.relE.left) <= FLOAT_T) ) && ( (dataTypeOf(e->contents.relE.right) >= CHAR_T) && (dataTypeOf(e->contents.relE.right) <= FLOAT_T) ))
                       { 
                          e->data_type=type_arr_in[CHAR_T][0]; 
                          char *dtChar = malloc(sizeof(char));
                          *dtChar = e->data_type; 
                                
                          char *result;
                          char *op1, *op2;
                          if(e->contents.relE.left->node_type<3)
                            op1 = "\npushv ";
                          else if(e->contents.relE.left->node_type==6)
                            op1 = "\npush ";
                        else
                            op1 = "";
                        
                        if(e->contents.relE.right->node_type<3)
                            op2 = "\npushv ";
                        else if(e->contents.relE.right->node_type==6)
                                op2 = " \npush ";
                        else
                            op2 = "";
                    
                        int size = strlen(op1)+strlen(e->contents.relE.left->code)+strlen(op2)+strlen(e->contents.relE.right->code)+strlen("\n")+strlen(e->contents.relE.op)+strlen(dtChar)+1;
                        result = (char*)malloc(size);
                        strcpy(result, op1);
                        strcat(result,e->contents.relE.left->code);
                        strcat(result,op2);
                        strcat(result,e->contents.relE.right->code);
                        strcat(result,"\n");
                        strcat(result,getReverseOperation(e->contents.relE.op));
                        strcat(result,dtChar);
                        setCode(e,result); 
                        return  CHAR_T; 
                       }
                    
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: %s %s %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.relE.left)],e->contents.relE.op,type_arr_in[dataTypeOf(e->contents.relE.right)]);
                        return (ERROR_T);
                    }
                }
        case log_op:
                {
                    int dt_left = dataTypeOf(e->contents.logE.left); // data type of left operand
                    int dt_right = dataTypeOf(e->contents.logE.right); // data type of right operand

                    if ( ( (dt_left >= CHAR_T) && (dt_left <= FLOAT_T) ) && ( (dt_right >= CHAR_T) && (dt_right <= FLOAT_T) ))
                      { 
                          e->data_type=type_arr_in[CHAR_T][0];
                          if(strcmp(e->contents.logE.op,"&&")==0) // and : if left_op is false return false, else go to right
                          {
                                
                                char *op1, *op2;
                                char left_code[6], right_code[6];
                           
                                if(e->contents.logE.left->node_type<3)
                                {
                                    op1 = "\npushv ";
                                    char *dtChar = malloc(sizeof(char));
                                    *dtChar = type_arr_in[dt_left][0];
                                    strcpy(left_code, "\n==0");
                                    strcat(left_code,dtChar);
                                }
                                else if(e->contents.logE.left->node_type==6)
                                {
                                    op1 = "\npush ";
                                    char *dtChar = malloc(sizeof(char));
                                    *dtChar = type_arr_in[dt_left][0];
                                    strcpy(left_code, "\n==0");
                                    strcat(left_code,dtChar);
                                    
                                }
                                else
                                {
                                    op1 = "";
                                }
                                
                                if(e->contents.logE.right->node_type<3)
                                {
                                    op2 = "\npushv ";
                                    char *dtChar = malloc(sizeof(char));
                                    *dtChar = type_arr_in[dt_right][0];
                                    strcpy(right_code, "\n==0");
                                    strcat(right_code,dtChar);
                                }
                                else if(e->contents.logE.right->node_type==6)
                                {       
                                     op2 = " \npush ";
                                     char *dtChar = malloc(sizeof(char));
                                    *dtChar = type_arr_in[dt_right][0];
                                    strcpy(right_code, "\n==0");
                                    strcat(right_code,dtChar);
                                }
                                else
                                {
                                    op2 = "";
                                }
                                /**********/
                                int size = strlen(op1)+strlen(e->contents.logE.left->code)+strlen(left_code)+1+strlen(false_list)
                                           + strlen(op2)+strlen(e->contents.logE.right->code)+strlen(right_code)+1+strlen(false_list);
                                char* result = (char*)malloc(size);
                                strcpy(result,op1);
                                strcat(result,e->contents.logE.left->code);
                                strcat(result,left_code);
                                strcat(result," ");
                                strcat(result,false_list); 
                                strcat(result,op2);
                                strcat(result,e->contents.logE.right->code);
                                strcat(result,right_code);
                                strcat(result," ");
                                strcat(result,false_list);   
                                setCode(e,result); 
                                setFlag(e,-1); 
                               
                          } else if(strcmp(e->contents.logE.op,"||")==0) // and : if left_op is false return false, else go to right
                          {
                                
                               
                                char *op1, *op2;
                                char left_code[6], right_code[6];
                                
                                if(e->contents.logE.left->node_type<3)
                                {
                                    op1 = "\npushv ";
                                    char *dtChar = malloc(sizeof(char));
                                    *dtChar = type_arr_in[dt_left][0];
                                    strcpy(left_code, "\n!=0");
                                    strcat(left_code,dtChar);
                                }
                                else if(e->contents.logE.left->node_type==6)
                                {
                                    op1 = "\npush ";
                                    char *dtChar = malloc(sizeof(char));
                                    *dtChar = type_arr_in[dt_left][0];
                                    strcpy(left_code, "\n!=0");
                                    strcat(left_code,dtChar);
                                }
                                else
                                {
                                    op1 = "";
                                }
                                
                                if(e->contents.logE.right->node_type<3)
                                {
                                    op2 = "\npushv ";
                                    char *dtChar = malloc(sizeof(char));
                                    *dtChar = type_arr_in[dt_right][0];
                                    strcpy(right_code, "\n==0");
                                    strcat(right_code,dtChar);
                                }
                                else if(e->contents.logE.right->node_type==6)
                                {       
                                     op2 = " \npush ";
                                     char *dtChar = malloc(sizeof(char));
                                     *dtChar = type_arr_in[dt_right][0];
                                     strcpy(right_code, "\n==0");
                                     strcat(right_code,dtChar);
                                }
                                else
                                {
                                    op2 = "";
                                }
                                

                                int size = strlen(op1)+strlen(e->contents.logE.left->code)+strlen(left_code)+1+strlen(true_list)
                                           + strlen(op2)+strlen(e->contents.logE.right->code)+strlen(right_code)+1+strlen(false_list);

                                char* result = (char*)malloc(size);
                                strcpy(result,op1);
                                strcat(result,e->contents.logE.left->code);
                                strcat(result,left_code);
                                strcat(result," ");
                                strcat(result,true_list); 
                                strcat(result,op2);
                                strcat(result,e->contents.logE.right->code);
                                strcat(result,right_code);
                                strcat(result," ");
                                strcat(result,false_list);   
                                setCode(e,result); 
                                setFlag(e,0); 
                          }
                          return  CHAR_T; 
                      }
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: %s %s %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.logE.left)],e->contents.logE.op,type_arr_in[dataTypeOf(e->contents.logE.right)]);
                        return (ERROR_T);
                    }
                }
        case ass_op: 
                {
                    int dt_left = dataTypeOf(e->contents.assE.left); // data type of left operand
                    int dt_right = dataTypeOf(e->contents.assE.right);  // data type of right operand
                
                   if ( (dt_left == CHAR_ARR_T)  && (dt_right == CHAR_ARR_T) )
                    {
                         e->data_type=type_arr_in[dt_left][0];
                         if(strcmp(e->contents.assE.op,"=")==0)
                         {
                             char* left_code;
                             char* right_code;

                             //right side is strconst
                             if(e->contents.assE.right->node_type==3)// if the right side is an identifier push right code should be 
                                {
                                    int size = strlen("\npush ") + strlen(e->contents.assE.right->code)+ 1;
                                    right_code = (char*)malloc(size);
                                    strcpy(right_code,"\npush ");
                                    strcat(right_code, e->contents.assE.right->code);
                                    
                                }

                              //left side is char array
                              if(e->contents.assE.left->node_type==6)// if the right side is an identifier push right code should be 
                                {
                                    int size = strlen("\npop ") + strlen(e->contents.assE.left->code)+ 1;
                                    left_code = (char*)malloc(size);
                                    strcpy(left_code,"\npop ");
                                    strcat(left_code, e->contents.assE.left->code);
                                }

                                int size = strlen(right_code) + strlen(left_code) + strlen("\ncopy") + strlen("\npopx")+1;
                                char* result;
                                result = (char*)malloc(size);
                                 strcpy(result, right_code); // push answer_index; push answer_array;
                                 strcat(result, "\ncopy");  // push right array operand (index, array)
                                 strcat(result, left_code);
                                 strcat(result, "\npopx");  // push left array operands
                                 setCode(e,result);

                         }


                    }else if ( ( (dt_left >= CHAR_T) && (dt_left <= FLOAT_T) ) && ( (dt_right >= CHAR_T) && (dt_right <= FLOAT_T) ))
                      { 
                          e->data_type=type_arr_in[( dt_left>=dt_right?dt_left : dt_right )][0];
                          
                          if(strcmp(e->contents.assE.op,"=")==0) {
                                char* left_code;
                                char* right_code;

                                //what does right side contain
                                if(e->contents.assE.right->node_type==arr_op) // if the right side is array put right code should be push<t>[]
                                {

                                    int size = strlen(e->contents.assE.right->code)+strlen("\npushc[] ")+1;
                                    right_code = (char*)malloc(size);
                                    strcpy(right_code, e->contents.assE.right->code);

                                    if(dt_right==CHAR_T)
                                        strcat(right_code,"\npushc[] ");
                                    else if(dt_right==INT_T)
                                        strcat(right_code,"\npushi[] ");
                                    else if(dt_right==FLOAT_T)
                                        strcat(right_code,"\npushf[] ");

               
                                } else if(e->contents.assE.right->node_type==idName)// if the right side is an identifier push right code should be 
                                {
                                    int size = strlen("\npush ") + strlen(e->contents.assE.right->code)+ 1;
                                    right_code = (char*)malloc(size);
                                    strcpy(right_code,"\npush ");
                                    strcat(right_code, e->contents.assE.right->code);
                                } else if(e->contents.assE.right->node_type<3)// if the right side is an identifier push right code should be 
                                {
                                    int size = strlen("\npushv ") + strlen(e->contents.assE.right->code)+ 1;
                                    right_code = (char*)malloc(size);
                                    strcpy(right_code,"\npushv ");
                                    strcat(right_code, e->contents.assE.right->code);
                                } else // if the right side is not array or identifier put right code should be 
                                {
                                    int size = strlen(e->contents.assE.right->code)+ 1;
                                    right_code = (char*)malloc(size);
                                    strcpy(right_code, e->contents.assE.right->code);
                                }


                        
                                //what does left side contain
                                if(e->contents.assE.left->node_type==arr_op) // if the left side is array put left code first
                                {
                                    
                                    left_code = (char*)malloc(strlen("\npopc[] ")+1);
                                    if(dt_left==CHAR_T)
                                        strcpy(left_code,"\npopc[] ");
                                    else if(dt_left==INT_T)
                                        strcpy(left_code,"\npopi[] ");
                                    else if(dt_left==FLOAT_T)
                                        strcpy(left_code,"\npopf[] ");


                                    int size = strlen(e->contents.assE.left->code)+strlen(right_code)+strlen(left_code)+ 1;
                                    char* result;
                                    result = (char*)malloc(size);
                                    strcpy(result, e->contents.assE.left->code);
                                    strcat(result, right_code);
                                    strcat(result, left_code);
                                    setCode(e,result);
                                } else if(e->contents.assE.left->node_type==idName) // if the left side is not array put right code first
                                {
                                    int size = strlen(right_code)+strlen("\ncopy")+strlen("\npop ")+strlen(e->contents.assE.left->code)+strlen("\npopx")+strlen("\n") + 1;
                                    char* result;
                                    result = (char*)malloc(size);
                                    strcpy(result, right_code);
                                    strcat(result, "\ncopy");
                                    strcat(result, "\npop ");
                                    strcat(result, e->contents.assE.left->code);
                                    strcat(result, "\npopx");
                                    
                                    setCode(e,result);
                                }
                                
                           }  else  {
                             //if(strcmp(e->contents.assE.op,"+=")==0) these kind of operators then
                           
                                char* left_code;
                                char* left_code_ass;
                                char* right_code;
                                /*
                                    Semantics:
                                    left_code += right_code 
                                ==> left_code = left_code_ass + right_code 
                                
                                */

                                //what does right side contain
                                if(e->contents.assE.right->node_type==arr_op) // if the right side is array put right code should be push<t>[]
                                {

                                    int size = strlen(e->contents.assE.right->code)+strlen("\npushc[] ")+1;
                                    right_code = (char*)malloc(size);
                                    strcpy(right_code, e->contents.assE.right->code);

                                    if(dt_right==CHAR_T)
                                        strcat(right_code,"\npushc[] ");
                                    else if(dt_right==INT_T)
                                        strcat(right_code,"\npushi[] ");
                                    else if(dt_right==FLOAT_T)
                                        strcat(right_code,"\npushf[] ");

               
                                } else if(e->contents.assE.right->node_type==idName)// if the right side is an identifier push right code should be 
                                {
                                    int size = strlen("\npush ") + strlen(e->contents.assE.right->code)+ 1;
                                    right_code = (char*)malloc(size);
                                    strcpy(right_code,"\npush ");
                                    strcat(right_code, e->contents.assE.right->code);
                                } else if(e->contents.assE.right->node_type<3)// if the right side is an identifier push right code should be 
                                {
                                    int size = strlen("\npushv ") + strlen(e->contents.assE.right->code)+ 1;
                                    right_code = (char*)malloc(size);
                                    strcpy(right_code,"\npushv ");
                                    strcat(right_code, e->contents.assE.right->code);
                                } else // if the right side is not array or identifier put right code should be 
                                {
                                    int size = strlen(e->contents.assE.right->code)+ 1;
                                    right_code = (char*)malloc(size);
                                    strcpy(right_code, e->contents.assE.right->code);
                                }


                        
                                //what does left side contain
                                if(e->contents.assE.left->node_type==arr_op) // if the left side is array put left code first
                                { 
                                    
                                    left_code = (char*)malloc(strlen("\npopc[] ")+1);
                                    
                                    e->data_type=type_arr_in[dt_left][0];
                                    char *dtChar = malloc(2*sizeof(char));
                                    dtChar[0] = e->contents.assE.op[0];
                                    dtChar[1] = e->data_type;


                                    int size = strlen(e->contents.assE.left->code)+strlen("\npushc[] ")+1;
                                    left_code_ass = (char*)malloc(size);
                                    strcpy(left_code_ass, e->contents.assE.left->code); // contain the push index; push array_address;

                                    if(dt_left==CHAR_T)
                                       {
                                            strcpy(left_code,"\npopc[] ");
                                            strcat(left_code_ass,"\npushc[] ");
                                       }
                                    else if(dt_left==INT_T)
                                       {
                                          strcpy(left_code,"\npopi[] ");
                                          strcat(left_code_ass,"\npushi[] ");
                                       }
                                    else if(dt_left==FLOAT_T)
                                       {
                                          strcpy(left_code,"\npopf[] ");
                                          strcat(left_code_ass,"\npushf[] ");
                                       }


                                    size = strlen(e->contents.assE.left->code)+strlen(right_code)+strlen(left_code)+strlen(left_code_ass)+strlen("\n")+strlen(dtChar)+strlen("\ncopy")+strlen("\npopx")+ 1;
                                    char* result;
                                    result = (char*)malloc(size);
                                    strcpy(result, e->contents.assE.left->code); // push answer_index; push answer_array;
                                    strcat(result, right_code);  // push right array operand (index, array)
                                    strcat(result, left_code_ass);  // push left array operands
                                    strcat(result,"\n");
                                    strcat(result,dtChar);  // the operand
                                    strcat(result, left_code);   // code for popping answer
                                    setCode(e,result);
                                } else if(e->contents.assE.left->node_type==idName) // if the left side is not array put right code first
                                {
                                    e->data_type=type_arr_in[dt_left][0];
                                    char *dtChar = malloc(2*sizeof(char));
                                    dtChar[0] = e->contents.assE.op[0];
                                    dtChar[1] = e->data_type;
                                    int size = strlen(right_code)+strlen("\npush ")+strlen(e->contents.assE.left->code) + strlen("\n")+strlen(dtChar)+strlen("\npop ")+strlen(e->contents.assE.left->code)+strlen("\npopx")+strlen("\n") + 1;
                                    char* result;
                                    result = (char*)malloc(size);
                                    strcpy(result, right_code);
                                    strcat(result, "\npush ");
                                    strcat(result, e->contents.assE.left->code);
                                    strcat(result,"\n");
                                    strcat(result, dtChar);
                                    strcat(result, "\ncopy");
                                    strcat(result, "\npop ");
                                    strcat(result, e->contents.assE.left->code);
                                    strcat(result, "\npopx");
                                    
                                    setCode(e,result);
                                }
                                
                           }



                          return ( dt_left>=dt_right?dt_left : dt_right ); 
                        } //no_coercion
                    else
                     {
                        fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: %s %s %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.assE.left)],e->contents.assE.op,type_arr_in[dataTypeOf(e->contents.assE.right)]);
                        return (ERROR_T);
                     }
                }
                         
        case cond_op:  
                    {
                        int dt_cond = dataTypeOf(e->contents.condE.cond);
                        int dt_left = dataTypeOf(e->contents.condE.left);
                        int dt_right = dataTypeOf(e->contents.condE.right);

                        if ( (dt_cond >= CHAR_T) && (dt_cond <= FLOAT_T) )
                        if ( ( (dt_left >= CHAR_T) && (dt_left <= FLOAT_ARR_T) ) && ( (dt_right >= CHAR_T) && (dt_right <= FLOAT_ARR_T) ))
                           { 
                                e->data_type=type_arr_in[(dt_left>=dt_right? dt_left : dt_right)][0]; 

                                L_exit = getNewNum();  // if condition holds do true-stmt and jump to exit-part
                                L_false = getNewNum(); // goto false-part i.e else part

                                char string_L_false[6],stringI_L_false[9];
                                strcpy(stringI_L_false, " I");
                                sprintf(string_L_false,"%d", L_false);
                                strcat(stringI_L_false,string_L_false);

                                char string_L_false_loc[9];
                                strcpy(string_L_false_loc, "\nI");
                                strcat(string_L_false_loc,string_L_false);
                                strcat(string_L_false_loc,":");

                                char string_L_exit[6],stringI_L_exit[13];
                                strcpy(stringI_L_exit, "\ngoto I");
                                sprintf(string_L_exit,"%d", L_exit);
                                strcat(stringI_L_exit,string_L_exit);

                                char string_L_exit_loc[9];
                                strcpy(string_L_exit_loc, "\nI");
                                strcat(string_L_exit_loc,string_L_exit);
                                strcat(string_L_exit_loc,":");

                                char* op1;
                                char *op2;

                                if(e->contents.condE.left->node_type<3)
                                    op1 = "\npushv ";
                                else if(e->contents.condE.left->node_type==6) //identifier
                                    op1 = "\npush ";
                                else
                                    op1 = "";

                                if(e->contents.condE.right->node_type<3)
                                    op2 = "\npushv ";
                                else if(e->contents.condE.right->node_type==6) //identifier
                                    op2 = "\npush ";
                                else
                                    op2 = "";   

                                int size = strlen(e->contents.condE.cond->code) + strlen(stringI_L_false) + 
                                        strlen(op1)+strlen(e->contents.condE.left->code) + strlen(stringI_L_exit) + 
                                        strlen(string_L_false_loc) + strlen(op2)+strlen(e->contents.condE.right->code)+ strlen(string_L_exit_loc) + 1;
                                char* result = (char*)malloc(size);
                                
                                strcpy(result,e->contents.condE.cond->code);
                                strcat(result,stringI_L_false);
                                strcat(result,op1);
                                strcat(result,e->contents.condE.left->code); 
                                strcat(result,stringI_L_exit); 
                                strcat(result,string_L_false_loc); 
                                strcat(result,op2);
                                strcat(result,e->contents.condE.right->code);
                                strcat(result,string_L_exit_loc); 
                                
                                setCode(e,result);
                                return ( dt_left>=dt_right ? dt_left : dt_right ); 
                          } 
                        else
                            return ERROR_T;
                        
                    else
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: %s ? %s : %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.condE.cond)],type_arr_in[dataTypeOf(e->contents.condE.left)],type_arr_in[dataTypeOf(e->contents.condE.right)]);
                        return ERROR_T;
                    }
                    }

        case cast_op:
                { 
                    int dt_cast = dataTypeOf(e->contents.castE.cast_type);
                    int dt_right = dataTypeOf(e->contents.castE.right);

                    if ( (dt_cast >= CHAR_T) && (dt_cast <= FLOAT_T) )
                    {
                        if ( (dt_right>= CHAR_T) && (dt_right <= FLOAT_T) )
                          { 
                               e->data_type=type_arr_in[dt_cast][0];  
                               char *dtChar = malloc(sizeof(char));
                               *dtChar = e->data_type; 
                               char *result;
                               char *op1;
                               char *cop;
                               if(e->contents.unPreE.right->node_type<3)
                                    op1 = "\npushv ";
                                else if(e->contents.unPreE.right->node_type==6) //identifier
                                    op1 = "\npush ";
                                else
                                    op1 = "";

                                if((dt_right==FLOAT_T)&&(dt_cast==INT_T))
                                {
                                    cop = "\nconvfi";
                                } else if((dt_right==INT_T)&&(dt_cast==FLOAT_T))
                                {
                                    cop = "\nconvif";
                                } else
                                    cop = "";
                                
                                //
                                int size = strlen(op1)+strlen(e->contents.unPreE.right->code)+strlen(cop) + 1;
                                result = (char*)malloc(size);
                                strcpy(result, op1);
                                strcat(result,e->contents.unPreE.right->code);
                                strcat(result,cop);
                                setCode(e,result);
                                return dt_cast; 
                          }
                        else
                        {
                            fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: ( %s ) %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.castE.cast_type)],type_arr_in[dataTypeOf(e->contents.castE.right)]);
                            return ERROR_T;
                        }
                    }
                    else
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: ( %s ) %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.castE.cast_type)],type_arr_in[dataTypeOf(e->contents.castE.right)]);
                        return ERROR_T;
                    }
                }
        
        case ret_op: 
            {
                int dt_right = dataTypeOf(e->contents.retE.right);
                char *result;
                char *op1;
                if(e->contents.retE.right->node_type<3) //const
                     op1 = "\npushv ";
                else if(e->contents.retE.right->node_type==6) //identifier
                    op1 = "\npush ";
                else
                    op1 = "";
                int size = strlen(op1)+strlen(e->contents.retE.right->code)+strlen("\nret") + 1;
                result = (char*)malloc(size);
                strcpy(result, op1);
                strcat(result,e->contents.retE.right->code);
                strcat(result,"\nret");
                setCode(e,result);
                return dt_right;
            }
        case func_op:
                    //check if the param types match
                    {
                        
                        exp_node *left_node = e->contents.funcE.left; // This implies there exist some function dec, may be more than 1
                        exp_node *right_node = e->contents.funcE.right;
                        struct symbol *funSym  = left_node->contents.identE.entry;
                        int nPar = funSym->n;
                        enum type* par_types = funSym->par_types;
                        
                        sz = 0;  
                        par_types_fromExp = NULL;

                        char funStr[12];
                        int fun_id = left_node->contents.identE.entry->kind_position;
                        sprintf(funStr,"%d",fun_id);
                        int size = 2*nPar*strlen("\npush ") + strlen("\ncall ") + strlen(funStr) + 1;
                        char* result;
                        result=(char*)malloc(size);

                        dataTypesOf(e->contents.funcE.right, result);//, &par_types_fromExp); //reverse
                        if(!par_types_fromExp) { exit(1);}
                      
                        if( (sz!=nPar) || ((sz==nPar) && diffParamTypesRev(par_types,par_types_fromExp,nPar) && !coercionPossibleParamTypes(par_types,par_types_fromExp,nPar))){
                            fprintf(stderr,"Error in %s line %d:\n \t No match for function call %s(",filename,yylineno,left_node->contents.identE.entry->id);
                            for(int j=sz-1;j>0;j--)
                                fprintf(stderr,"%s, ",type_arr_in[par_types_fromExp[j]]);  
                            fprintf(stderr,"%s)\n \t",type_arr_in[par_types_fromExp[0]]);

                            fprintf(stderr," Candidates are: \n \t\t %s %s(",type_arr_in[funSym->type], funSym->id); 
                            for(int j=0;j<nPar-1;j++)
                                    fprintf(stderr,"%s, ",type_arr_in[par_types[j]]);  
                            fprintf(stderr,"%s) declared in %s near line %d\n",type_arr_in[par_types[nPar-1]], filename, funSym->lineno);
                            return ERROR_T;
                        } 
                        e->data_type=type_arr_in[dataTypeOf(e->contents.funcE.left)][0]; 
        
                        strcat(result,"\ncall ");
                        strcat(result,funStr);
                        setCode(e,result);
                        
                        return dataTypeOf(e->contents.funcE.left);
                    }
        case func_np_op:
                    { //check if the param types match
                        exp_node *left_node = e->contents.funcNPE.left;
                        int dt_left = dataTypeOf(e->contents.funcNPE.left);
                        int nPar = left_node->contents.identE.entry->n;
                        enum type* par_types =  e->contents.funcNPE.left->contents.identE.entry->par_types;
                        sz = 0;  
                        
                        if(sz!=nPar) 
                        {
                            fprintf(stderr,"Error in %s line %d:\n \t No match for function call %s():\n\t  ",filename,yylineno,left_node->contents.identE.entry->id);
                            fprintf(stderr,"Candidates are:%s %s(",type_arr_in[dataTypeOf(e->contents.funcE.left)], left_node->contents.identE.entry->id); 
                            for(int j=0;j<nPar-1;j++)
                                fprintf(stderr,"%s, ",type_arr_in[par_types[j]]);  
                            fprintf(stderr,"%s) declared in %s near line %d\n",type_arr_in[par_types[nPar-1]], filename, left_node->contents.identE.entry->lineno);
                            return ERROR_T;
                        } 
                        
                        e->data_type=type_arr_in[dataTypeOf(e->contents.funcNPE.left)][0]; 
                        
                        int fun_id = left_node->contents.identE.entry->kind_position;
                       
                        char funStr[5];
                        sprintf(funStr,"%d",fun_id);
                       
                        int size = strlen(funStr) + strlen("call ") + 1;
                        char *result = (char*)malloc(size);
                        strcpy(result,"call ");
                       
                        strcat(result,funStr);
                        setCode(e,result);
                        
                        return dt_left;
                    }

            case STMT_COMPOUND : {
                                 if(e->contents.compStmtE.rem_stmt!=NULL){
                                    int size = strlen(e->contents.compStmtE.first_stmt->code) + strlen(e->contents.compStmtE.rem_stmt->code) + 1;
                                    char* result = (char*)malloc(size);
                                    strcpy(result,e->contents.compStmtE.first_stmt->code);
                                    strcat(result,e->contents.compStmtE.rem_stmt->code);
                                    setCode(e,result);
                                 } else { 
                                    int size = strlen(e->contents.compStmtE.first_stmt->code)  + 1;
                                    char* result = (char*)malloc(size);
                                    strcpy(result,e->contents.compStmtE.first_stmt->code);
                                    setCode(e,result);
                                 }
                                 
                                 return VOID_T;
                                 }
            case STMT_IF : {
                        L_true = getNewNum();
                        L_exit = getNewNum(); // false-action and exit-actions are same
                        L_false = L_exit;

                        char string_L_false[6],stringI_L_false[9]; // to cntain the jump-label
                        strcpy(stringI_L_false, " I");
                        sprintf(string_L_false,"%d", L_exit); //If the condition is false, goto the exit of if
                        strcat(stringI_L_false,string_L_false);

                        char string_L_false_loc[9];  // to mark the location of false/exit stmt
                        strcpy(string_L_false_loc, "\nI");
                        strcat(string_L_false_loc,string_L_false);
                        strcat(string_L_false_loc,":");

                        char string_L_true[6],stringI_L_true[9]; // to cntain the jump-label
                        strcpy(stringI_L_true, " I");
                        sprintf(string_L_true,"%d", L_true); //If the condition is false, goto the exit of if
                        strcat(stringI_L_true,string_L_true);

                        char string_L_true_loc[9];  // to mark the location of false/exit stmt
                        strcpy(string_L_true_loc, "\nI");
                        strcat(string_L_true_loc,string_L_true);
                        strcat(string_L_true_loc,":");
                        
                        if(e->contents.ifStmtE.cond->flag==-1) // condition has false_list
                        {
                            char *old_code = e->contents.ifStmtE.cond->code;
                            char *new_code = replaceWord(old_code, false_list, stringI_L_false);
                            setCode(e->contents.ifStmtE.cond,new_code);
                        } else if(e->contents.ifStmtE.cond->flag==0) // condition has false_list && true_list
                        {
                            char *old_code = e->contents.ifStmtE.cond->code;
                            char *new_code = replaceWord(old_code, false_list, stringI_L_false);
                            setCode(e->contents.ifStmtE.cond,new_code);

                            char *old_code1 = e->contents.ifStmtE.cond->code;
                            char *new_code1 = replaceWord(old_code1, true_list, stringI_L_true);
                            setCode(e->contents.ifStmtE.cond,new_code1);
                        } 
                        
                        int size = strlen(e->contents.ifStmtE.cond->code) + strlen(string_L_false) + strlen(string_L_true_loc) + strlen(e->contents.ifStmtE.tstmt->code) + strlen(string_L_false_loc)+ 1;
                        char* result = (char*)malloc(size);
                        strcpy(result,e->contents.ifStmtE.cond->code);
                        if(e->contents.ifStmtE.cond->node_type!=log_op)
                            strcat(result,stringI_L_false);
                        strcat(result,string_L_true_loc);
                        strcat(result,e->contents.ifStmtE.tstmt->code);
                        strcat(result,string_L_false_loc);

                        setCode(e,result);

                        return VOID_T;
                    }
            case STMT_IF_ELSE : {
                      
                        L_true = getNewNum();
                        L_exit = getNewNum();  // if condition holds do true-stmt and jump to exit-part
                        L_false = getNewNum(); // goto false-part i.e else part

                        char string_L_false[6],stringI_L_false[9];
                        strcpy(stringI_L_false, " I");
                        sprintf(string_L_false,"%d", L_false);
                        strcat(stringI_L_false,string_L_false);

                        char string_L_false_loc[9];
                        strcpy(string_L_false_loc, "\nI");
                        strcat(string_L_false_loc,string_L_false);
                        strcat(string_L_false_loc,":");

                        char string_L_exit[6],stringI_L_exit[13];
                        strcpy(stringI_L_exit, "\ngoto I");
                        sprintf(string_L_exit,"%d", L_exit);
                        strcat(stringI_L_exit,string_L_exit);

                        char string_L_exit_loc[9];
                        strcpy(string_L_exit_loc, "\nI");
                        strcat(string_L_exit_loc,string_L_exit);
                        strcat(string_L_exit_loc,":");

                        char string_L_true[6],stringI_L_true[9]; // to cntain the jump-label
                        strcpy(stringI_L_true, " I");
                        sprintf(string_L_true,"%d", L_true); //If the condition is false, goto the exit of if
                        strcat(stringI_L_true,string_L_true);

                        char string_L_true_loc[9];  // to mark the location of false/exit stmt
                        strcpy(string_L_true_loc, "\nI");
                        strcat(string_L_true_loc,string_L_true);
                        strcat(string_L_true_loc,":");

                        if(e->contents.ifStmtE.cond->flag==-1) // condition has false_list
                        {
                            char *old_code = e->contents.ifStmtE.cond->code;
                            char *new_code = replaceWord(old_code, false_list, stringI_L_false);
                            setCode(e->contents.ifStmtE.cond,new_code);
                        } else if(e->contents.ifStmtE.cond->flag==0) // condition has false_list && true_list
                        {
                            char *old_code = e->contents.ifStmtE.cond->code;
                            char *new_code = replaceWord(old_code, false_list, stringI_L_false);
                            setCode(e->contents.ifStmtE.cond,new_code);

                            char *old_code1 = e->contents.ifStmtE.cond->code;
                            char *new_code1 = replaceWord(old_code1, true_list, stringI_L_true);
                            setCode(e->contents.ifStmtE.cond,new_code1);
                        } 



                        int size = strlen(e->contents.ifElseStmtE.cond->code) + strlen(stringI_L_false) + 
                                  + strlen(string_L_true_loc) + strlen(e->contents.ifElseStmtE.tstmt->code) + strlen(stringI_L_exit) + 
                                   strlen(string_L_false_loc) + strlen(e->contents.ifElseStmtE.fstmt->code)+ strlen(string_L_exit_loc) + 2;
                        char* result = (char*)malloc(size);
                        
                        strcpy(result,e->contents.ifElseStmtE.cond->code);
                        if(e->contents.ifStmtE.cond->node_type!=log_op)
                            strcat(result,stringI_L_false);
                        strcat(result,string_L_true_loc);
                        strcat(result,e->contents.ifElseStmtE.tstmt->code); 
                        strcat(result,stringI_L_exit); 
                        strcat(result,string_L_false_loc); 
                        strcat(result,e->contents.ifElseStmtE.fstmt->code);
                        strcat(result,string_L_exit_loc);  

                        setCode(e,result);

                        return VOID_T;
                    }
            case STMT_WHILE : {
                L_cmp = getNewNum(); // conduct comparison here
                L_exit = getNewNum(); // goto to outside loop
                L_false = L_exit;    
                char string_L_cmp[6],stringI_L_cmp[13]; // to contain the instruction to jump to comp-stmt
                strcpy(stringI_L_cmp, "\ngoto I");
                sprintf(string_L_cmp,"%d", L_cmp); 
                strcat(stringI_L_cmp,string_L_cmp);

                char string_L_cmp_loc[9];  // to mark the location of comp-stmt
                strcpy(string_L_cmp_loc, "\nI");
                strcat(string_L_cmp_loc,string_L_cmp);
                strcat(string_L_cmp_loc,":");

                char stringI_L_cmp_add[9];
                strcpy(stringI_L_cmp_add, " I");
                strcat(stringI_L_cmp_add,string_L_cmp);

                char string_L_false[6],stringI_L_false[9]; // to contain the instruction to jump to outside loop-stmt
                strcpy(stringI_L_false, " I");
                sprintf(string_L_false,"%d", L_false); 
                strcat(stringI_L_false,string_L_false);

                char string_L_false_loc[9];  // to mark the location of outside loop-stmt
                strcpy(string_L_false_loc, "\nI");
                strcat(string_L_false_loc,string_L_false);
                strcat(string_L_false_loc,":");
                
                //check if the body has break-statement
                if(e->contents.whileStmtE.tstmt->node_type==STMT_BREAK)
                {
                    char *replace_code =" SS";
                    char *old_code = e->contents.whileStmtE.tstmt->code;
                    char *new_code = replaceWord(old_code, replace_code, string_L_false);
                    setCode(e->contents.whileStmtE.tstmt,new_code);
                }else if(e->contents.whileStmtE.tstmt->node_type==STMT_CONTINUE)
                {
                    char *replace_code =" SS";
                    char *old_code = e->contents.whileStmtE.tstmt->code;
                    char *new_code = replaceWord(old_code, replace_code, stringI_L_cmp_add);
                    setCode(e->contents.whileStmtE.tstmt,new_code);
                }else if(e->contents.whileStmtE.tstmt->node_type==STMT_COMPOUND)
                {
                        exp_node* ET = e->contents.whileStmtE.tstmt;
                        exp_node* fs = ET->contents.compStmtE.first_stmt;
                        exp_node* rs = ET->contents.compStmtE.rem_stmt;
                        char *replace_code =" SS";
                        char *old_code = e->contents.whileStmtE.tstmt->code;
                            do{
                                if(fs->node_type==STMT_BREAK)
                                    { 
                                        char *new_code = replaceWord(old_code, replace_code, stringI_L_false);
                                        setCode(e->contents.whileStmtE.tstmt,new_code);
                                        break;
                                    }
                                else if(fs->node_type==STMT_CONTINUE)
                                {
                                    char *new_code = replaceWord(old_code, replace_code, stringI_L_cmp_add);
                                    setCode(e->contents.whileStmtE.tstmt,new_code);
                                    break;
                                }
                                else if(rs->node_type==STMT_COMPOUND)
                                {
                                    fs = rs->contents.compStmtE.first_stmt;
                                    rs = rs->contents.compStmtE.rem_stmt;
                                }
                            }while(rs->node_type!=STMT_COMPOUND);
                            if(fs->node_type==STMT_BREAK)
                            {
                                char *new_code = replaceWord(old_code, replace_code, stringI_L_false);
                                setCode(e->contents.whileStmtE.tstmt,new_code);
                            }
                            else if(fs->node_type==STMT_CONTINUE)
                            {
                                char *new_code = replaceWord(old_code, replace_code, stringI_L_cmp_add);
                                setCode(e->contents.whileStmtE.tstmt,new_code);
                            }
                            if(rs->node_type==STMT_BREAK)
                            {
                                char *new_code = replaceWord(old_code, replace_code, stringI_L_false);
                                setCode(e->contents.whileStmtE.tstmt,new_code);
                            }
                            else if(rs->node_type==STMT_CONTINUE)
                            {
                                char *new_code = replaceWord(old_code, replace_code, stringI_L_cmp_add);
                                setCode(e->contents.whileStmtE.tstmt,new_code);
                            }
                       

                }

              
                int size = strlen(string_L_cmp_loc) + strlen(e->contents.whileStmtE.cond->code) + strlen(stringI_L_false)
                         + strlen(e->contents.whileStmtE.tstmt->code) + strlen(stringI_L_cmp)
                         + strlen(string_L_false_loc);
                char* result = (char*)malloc(size);
                strcpy(result,string_L_cmp_loc);
                strcat(result,e->contents.whileStmtE.cond->code);
                strcat(result,stringI_L_false);
                strcat(result,e->contents.whileStmtE.tstmt->code);
                strcat(result,stringI_L_cmp);
                strcat(result,string_L_false_loc);
                setCode(e,result);

                return VOID_T;
            }

        case STMT_DO_WHILE : {
                L_cmp = getNewNum(); // conduct comparison here
                L_loop = getNewNum(); // goto into loop
                L_exit = getNewNum(); // goto to outside-loop
                L_false = L_exit;
                char string_L_loop[6],stringI_L_loop[13]; // to contain the instruction to jump to loop-stmt for first time
                strcpy(stringI_L_loop, "\ngoto I");
                sprintf(string_L_loop,"%d", L_loop); 
                strcat(stringI_L_loop,string_L_loop);

                char string_L_loop_loc[9];  // to mark the location of loop-stmt
                strcpy(string_L_loop_loc, "\nI");
                strcat(string_L_loop_loc,string_L_loop);
                strcat(string_L_loop_loc,":");

                        
                char string_L_cmp[6],stringI_L_cmp[13]; // to contain the instruction to jump to comp-stmt
                strcpy(stringI_L_cmp, "\ngoto I");
                sprintf(string_L_cmp,"%d", L_cmp); 
                strcat(stringI_L_cmp,string_L_cmp);

                char string_L_cmp_loc[9];  // to mark the location of comp-stmt
                strcpy(string_L_cmp_loc, "\nI");
                strcat(string_L_cmp_loc,string_L_cmp);
                strcat(string_L_cmp_loc,":");

                char stringI_L_cmp_add[9];
                strcpy(stringI_L_cmp_add, " I");
                strcat(stringI_L_cmp_add,string_L_cmp);

                char string_L_false[6],stringI_L_false[9]; // to contain the instruction to jump to loop-stmt
                strcpy(stringI_L_false, " I");
                sprintf(string_L_false,"%d", L_false); 
                strcat(stringI_L_false,string_L_false);

                char string_L_false_loc[9];  // to mark the location of loop-stmt
                strcpy(string_L_false_loc, "\nI");
                strcat(string_L_false_loc,string_L_false);
                strcat(string_L_false_loc,":");

                if(e->contents.doWhileStmtE.tstmt->node_type==STMT_BREAK)
                {
                    char *replace_code =" SS";
                    char *old_code = e->contents.doWhileStmtE.tstmt->code;
                    char *new_code = replaceWord(old_code, replace_code, string_L_false);
                    setCode(e->contents.doWhileStmtE.tstmt,new_code);
                }else if(e->contents.doWhileStmtE.tstmt->node_type==STMT_CONTINUE)
                {
                    char *replace_code =" SS";
                    char *old_code = e->contents.doWhileStmtE.tstmt->code;
                    char *new_code = replaceWord(old_code, replace_code, stringI_L_cmp_add);
                    setCode(e->contents.doWhileStmtE.tstmt,new_code);
                }else if(e->contents.doWhileStmtE.tstmt->node_type==STMT_COMPOUND)
                {
                        exp_node* ET = e->contents.doWhileStmtE.tstmt;
                        exp_node* fs = ET->contents.compStmtE.first_stmt;
                        exp_node* rs = ET->contents.compStmtE.rem_stmt;
                        char *replace_code =" SS";
                        char *old_code = e->contents.doWhileStmtE.tstmt->code;
                        do{
                            if(fs->node_type==STMT_BREAK)
                                { 
                                    char *new_code = replaceWord(old_code, replace_code, stringI_L_false);
                                    setCode(e->contents.doWhileStmtE.tstmt,new_code);
                                    break;
                                }
                            else if(fs->node_type==STMT_CONTINUE)
                            {
                                char *new_code = replaceWord(old_code, replace_code, stringI_L_cmp_add);
                                setCode(e->contents.doWhileStmtE.tstmt,new_code);
                                break;
                            }
                            else if(rs->node_type==STMT_COMPOUND)
                            {
                                fs = rs->contents.compStmtE.first_stmt;
                                rs = rs->contents.compStmtE.rem_stmt;
                            }
                        }while(rs->node_type!=STMT_COMPOUND);
                        if(fs->node_type==STMT_BREAK)
                        {
                            char *new_code = replaceWord(old_code, replace_code, stringI_L_false);
                            setCode(e->contents.doWhileStmtE.tstmt,new_code);
                        }
                        else if(fs->node_type==STMT_CONTINUE)
                        {
                            char *new_code = replaceWord(old_code, replace_code, stringI_L_cmp_add);
                            setCode(e->contents.doWhileStmtE.tstmt,new_code);
                        }

                        if(rs->node_type==STMT_BREAK)
                        {
                            char *new_code = replaceWord(old_code, replace_code, stringI_L_false);
                            setCode(e->contents.doWhileStmtE.tstmt,new_code);
                        }
                        else if(rs->node_type==STMT_CONTINUE)
                        {
                            char *new_code = replaceWord(old_code, replace_code, stringI_L_cmp_add);
                            setCode(e->contents.doWhileStmtE.tstmt,new_code);
                        }

                }

                int size = strlen(stringI_L_loop) + strlen(string_L_cmp_loc) + 
                           strlen(e->contents.doWhileStmtE.cond->code) + strlen(stringI_L_false) + strlen(string_L_loop_loc) +
                           strlen(e->contents.doWhileStmtE.tstmt->code) + strlen(stringI_L_cmp) +
                           strlen(string_L_false_loc);

                char* result = (char*)malloc(size);
                strcpy(result,stringI_L_loop);
                strcat(result,string_L_cmp_loc);
                strcat(result,e->contents.doWhileStmtE.cond->code);
                strcat(result,stringI_L_false);
                strcat(result,string_L_loop_loc);
                strcat(result,e->contents.doWhileStmtE.tstmt->code);
                strcat(result,stringI_L_cmp);
                strcat(result,string_L_false_loc);
                setCode(e,result);

                return VOID_T;   
            }

        case STMT_FOR : {
                L_cmp = getNewNum(); // conduct comparison here
                L_exit = getNewNum(); // goto to outside-loop
                L_false = L_exit;
                char string_L_cmp[6],stringI_L_cmp[13]; // to contain the instruction to jump to comp-stmt
                strcpy(stringI_L_cmp, "\ngoto I");
                sprintf(string_L_cmp,"%d", L_cmp); 
                strcat(stringI_L_cmp,string_L_cmp);

                char string_L_cmp_loc[9];  // to mark the location of comp-stmt
                strcpy(string_L_cmp_loc, "\nI");
                strcat(string_L_cmp_loc,string_L_cmp);
                strcat(string_L_cmp_loc,":");

                char stringI_L_cmp_add[9];
                strcpy(stringI_L_cmp_add, " I");
                strcat(stringI_L_cmp_add,string_L_cmp);

                char string_L_false[6],stringI_L_false[9]; // to contain the instruction to jump to loop-stmt
                strcpy(stringI_L_false, " I");
                sprintf(string_L_false,"%d", L_false); 
                strcat(stringI_L_false,string_L_false);

                char string_L_false_loc[9];  // to mark the location of loop-stmt
                strcpy(string_L_false_loc, "\nI");
                strcat(string_L_false_loc,string_L_false);
                strcat(string_L_false_loc,":");




                if(e->contents.forStmtE.tstmt->node_type==STMT_BREAK)
                {
                    char *replace_code =" SS";
                    char *old_code = e->contents.forStmtE.tstmt->code;
                    char *new_code = replaceWord(old_code, replace_code, string_L_false);
                    setCode(e->contents.forStmtE.tstmt,new_code);
                }else if(e->contents.forStmtE.tstmt->node_type==STMT_CONTINUE)
                {
                    char *replace_code =" SS";
                    char *old_code = e->contents.forStmtE.tstmt->code;
                    char *new_code = replaceWord(old_code, replace_code, stringI_L_cmp_add);
                    setCode(e->contents.forStmtE.tstmt,new_code);
                }else if(e->contents.forStmtE.tstmt->node_type==STMT_COMPOUND)
                {
                        exp_node* ET = e->contents.forStmtE.tstmt;
                        exp_node* fs = ET->contents.compStmtE.first_stmt;
                        exp_node* rs = ET->contents.compStmtE.rem_stmt;
                        char *replace_code =" SS";
                        char *old_code = e->contents.forStmtE.tstmt->code;
                    do{
                        if(fs->node_type==STMT_BREAK)
                            { 
                                char *new_code = replaceWord(old_code, replace_code, stringI_L_false);
                                setCode(e->contents.forStmtE.tstmt,new_code);
                                break;
                            }
                        else if(fs->node_type==STMT_CONTINUE)
                        {
                            char *new_code = replaceWord(old_code, replace_code, stringI_L_cmp_add);
                            setCode(e->contents.forStmtE.tstmt,new_code);
                            break;
                        }
                        else if(rs->node_type==STMT_COMPOUND)
                        {
                            fs = rs->contents.compStmtE.first_stmt;
                            rs = rs->contents.compStmtE.rem_stmt;
                        }
                    }while(rs->node_type!=STMT_COMPOUND);
                    if(fs->node_type==STMT_BREAK)
                    {
                        char *new_code = replaceWord(old_code, replace_code, stringI_L_false);
                        setCode(e->contents.forStmtE.tstmt,new_code);
                    }
                    else if(fs->node_type==STMT_CONTINUE)
                    {
                        char *new_code = replaceWord(old_code, replace_code, stringI_L_cmp_add);
                        setCode(e->contents.forStmtE.tstmt,new_code);
                    }

                    if(rs->node_type==STMT_BREAK)
                    {
                        char *new_code = replaceWord(old_code, replace_code, stringI_L_false);
                        setCode(e->contents.forStmtE.tstmt,new_code);
                    }
                    else if(rs->node_type==STMT_CONTINUE)
                    {
                        char *new_code = replaceWord(old_code, replace_code, stringI_L_cmp_add);
                        setCode(e->contents.forStmtE.tstmt,new_code);
                    }

                }



                int size = strlen(e->contents.forStmtE.assgn->code) + strlen(string_L_cmp_loc) + 
                           strlen(e->contents.forStmtE.cond->code) + strlen(stringI_L_false) + 
                           strlen(e->contents.forStmtE.tstmt->code) + 
                           strlen(e->contents.forStmtE.update->code) + strlen(stringI_L_cmp) +
                           strlen(string_L_false_loc);

                char* result = (char*)malloc(size);
                strcpy(result,e->contents.forStmtE.assgn->code);
                strcat(result,string_L_cmp_loc);
                strcat(result,e->contents.forStmtE.cond->code);
                strcat(result,stringI_L_false);
                strcat(result,e->contents.forStmtE.tstmt->code);
                strcat(result,e->contents.forStmtE.update->code);
                strcat(result,stringI_L_cmp);
                strcat(result,string_L_false_loc);
                setCode(e,result);

                return VOID_T;   
            }

        case STMT_BREAK : 
        {
            char stringI_L_brk[13]; // to contain the instruction to jump to comp-stmt
            strcpy(stringI_L_brk, "\ngoto SS");
            setCode(e,stringI_L_brk);

            return VOID_T;
        }

        case STMT_CONTINUE : 
        {
            char stringI_L_cont[13]; // to contain the instruction to jump to comp-stmt
            strcpy(stringI_L_cont, "\ngoto SS");
            setCode(e,stringI_L_cont);

            return VOID_T;
        }
                    
        default: return ERROR_T;
    }
}

char* dataTypesOf(exp_node *e, char* result)//, int* par_types_fromExp)
{ 
    sz=sz+1;
    par_types_fromExp = (enum type*)realloc(par_types_fromExp,sz*sizeof(int));
    switch(e->node_type)
    {
        case comma_op: 
                        {
                            par_types_fromExp[sz-1]=dataTypeOf(e->contents.commaE.left);
                            char* op1;
                            if(e->contents.commaE.left->node_type<3)
                                op1 = "\npushv ";
                            else if(e->contents.commaE.left->node_type==6) //identifier
                                op1 = "\npush ";
                            else
                                op1 = "";

                            int size = strlen(e->contents.commaE.left->code) + strlen(op1) + 1;
                            strcat(result,op1);
                            strcat(result,e->contents.commaE.left->code);
                            if(e->contents.commaE.right!=NULL)
                               dataTypesOf(e->contents.commaE.right, result);//, par_types_fromExp);
                            
                            break;
                        }

        case comma_last_op : {
                                
                                par_types_fromExp[sz-1]=dataTypeOf(e->contents.commaE.left);
                                char* op1;
                                if(e->contents.commaE.left->node_type<3)
                                    op1 = "\npushv ";
                                else if(e->contents.commaE.left->node_type==6) //identifier
                                    op1 = "\npush ";
                                else
                                    op1 = "";

                                int size = strlen(e->contents.commaE.left->code) + strlen(op1) + 1;
                                strcat(result,op1);
                                strcat(result,e->contents.commaE.left->code);
                                break;
                             }
        default : 
                { 
                  break;
                }

    } 
    return  result;
}

