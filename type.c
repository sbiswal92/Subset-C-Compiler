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
                    if ( ( (dataTypeOf(e->contents.relE.left) >= CHAR_T) && (dataTypeOf(e->contents.relE.left) <= FLOAT_T) ) && ( (dataTypeOf(e->contents.relE.right) >= CHAR_T) && (dataTypeOf(e->contents.relE.right) <= FLOAT_T) ))
                       { e->data_type=type_arr_in[CHAR_T][0];  return  CHAR_T; }
                    
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: %s %s %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.relE.left)],e->contents.relE.op,type_arr_in[dataTypeOf(e->contents.relE.right)]);
                        return (ERROR_T);
                    }

        case log_op:
                    if ( ( (dataTypeOf(e->contents.logE.left) >= CHAR_T) && (dataTypeOf(e->contents.logE.left) <= FLOAT_T) ) && ( (dataTypeOf(e->contents.logE.right) >= CHAR_T) && (dataTypeOf(e->contents.logE.right) <= FLOAT_T) ))
                      { e->data_type=type_arr_in[CHAR_T][0];   return  CHAR_T; }
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: %s %s %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.logE.left)],e->contents.logE.op,type_arr_in[dataTypeOf(e->contents.logE.right)]);
                        return (ERROR_T);
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
                                    strcat(result, "\ncopy");
                                    strcat(result, left_code);   // code for popping answer
                                    strcat(result, "\npopx");
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
                    if ( (dataTypeOf(e->contents.condE.cond) >= CHAR_T) && (dataTypeOf(e->contents.condE.cond) <= FLOAT_T) )
                        if ( ( (dataTypeOf(e->contents.condE.left) >= CHAR_T) && (dataTypeOf(e->contents.condE.left) <= FLOAT_ARR_T) ) && ( (dataTypeOf(e->contents.condE.right) >= CHAR_T) && (dataTypeOf(e->contents.condE.right) <= FLOAT_ARR_T) ))
                           { e->data_type=type_arr_in[( dataTypeOf(e->contents.condE.left)>=dataTypeOf(e->contents.condE.right)?dataTypeOf(e->contents.condE.left) : dataTypeOf(e->contents.condE.right))][0];  return ( dataTypeOf(e->contents.condE.left)>=dataTypeOf(e->contents.condE.right)?dataTypeOf(e->contents.condE.left) : dataTypeOf(e->contents.condE.right)); } //no_coercion
                        else
                            return ERROR_T;
                        
                    else
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: %s ? %s : %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.condE.cond)],type_arr_in[dataTypeOf(e->contents.condE.left)],type_arr_in[dataTypeOf(e->contents.condE.right)]);
                        return ERROR_T;
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

