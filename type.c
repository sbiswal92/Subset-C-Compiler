#include<stdio.h>
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
        case cCnst: return CHAR_T;
        
        case iCnst: return INT_T;
        
        case flCnst: return FLOAT_T;

        case cArr: return CHAR_ARR_T;

        case iArr: return INT_ARR_T;

        case flArr: return FLOAT_ARR_T;

        case idName: return e->contents.identE.entry->type;

        case un_pre_op:
                    if( (dataTypeOf(e->contents.unPreE.right) >= CHAR_T) && (dataTypeOf(e->contents.unPreE.right) <= FLOAT_T) )
                        return dataTypeOf(e->contents.unPreE.right);
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Unary operator %s cannot be applied to expression of type %s\n",filename,yylineno,e->contents.unPreE.op,type_arr_in[dataTypeOf(e->contents.unPreE.right)]);
                        return ERROR_T;
                    }
        
        case un_post_op:
                    if( (dataTypeOf(e->contents.unPostE.left) >= CHAR_T) && (dataTypeOf(e->contents.unPostE.left) <= FLOAT_T) )
                        return dataTypeOf(e->contents.unPostE.left);
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Unary operator %s cannot be applied to expression of type %s\n",filename,yylineno,e->contents.unPostE.op,type_arr_in[dataTypeOf(e->contents.unPostE.left)]);
                        return ERROR_T;
                    }

        case un_minus_op: 
                    if( (dataTypeOf(e->contents.unMinusE.right) >= CHAR_T) && (dataTypeOf(e->contents.unMinusE.right) <= FLOAT_T) )
                        return dataTypeOf(e->contents.unMinusE.right);
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Unary operator - cannot be applied to expression of type %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.unMinusE.right)]);
                        return ERROR_T;
                    }

        case un_not_op: 
                    if( (dataTypeOf(e->contents.unNotE.right) >= CHAR_T) && (dataTypeOf(e->contents.unNotE.right) <= FLOAT_T) )
                        return dataTypeOf(e->contents.unNotE.right);
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Unary operator ! cannot be applied to expression of type %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.unNotE.right)]);
                        return ERROR_T;
                    }

        case un_tilde_op: 
                    if( (dataTypeOf(e->contents.unTildeE.right) == CHAR_T) || (dataTypeOf(e->contents.unTildeE.right) == INT_T) )
                        return dataTypeOf(e->contents.unTildeE.right);
                  else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Unary operator ~ cannot be applied to expression of type %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.unTildeE.right)]);
                        return ERROR_T;
                    }


        case un_amp_op: 
                    if( (dataTypeOf(e->contents.unAmpE.right) >= CHAR_T) && (dataTypeOf(e->contents.unAmpE.right) <= FLOAT_T) )
                    {
                        return dataTypeOf(e->contents.unAmpE.right)+3;
                    }
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Unary operator & cannot be applied to expression of type %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.unAmpE.right)]);
                        return ERROR_T;
                    }

        case arr_op: 
                    
                    if( (dataTypeOf(e->contents.arrE.left) >= CHAR_ARR_T) && (dataTypeOf(e->contents.arrE.left) <= FLOAT_ARR_T))
                        return dataTypeOf(e->contents.arrE.left)-3;
                    else 
                    {   fprintf(stderr, "Error in %s line %d:\n\t Unary operator [] cannot be applied to non-array data of type %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.arrE.left)]);
                        return ERROR_T;
                    }
        

        case arith_op: 
                    if(( (dataTypeOf(e->contents.arithE.left) >= CHAR_T) && (dataTypeOf(e->contents.arithE.left) <= FLOAT_T) ) && ( (dataTypeOf(e->contents.arithE.right) >= CHAR_T) && (dataTypeOf(e->contents.arithE.right) <= FLOAT_T) ))
                            return dataTypeOf(e->contents.arithE.left)>=dataTypeOf(e->contents.arithE.right)?dataTypeOf(e->contents.arithE.left):dataTypeOf(e->contents.arithE.right);
                    else
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: %s %s %s\n", filename, yylineno, type_arr_in[dataTypeOf(e->contents.arithE.left)], e->contents.arithE.op, type_arr_in[dataTypeOf(e->contents.arithE.right)]);
                        return ERROR_T;
                    }

        case mod_op: 
                    if( ( (dataTypeOf(e->contents.modE.left) == CHAR_T) || (dataTypeOf(e->contents.modE.left) == INT_T) ) &&  ( (dataTypeOf(e->contents.modE.right) == CHAR_T) || (dataTypeOf(e->contents.modE.right) == INT_T) ) )
                        return  dataTypeOf(e->contents.modE.left)>=dataTypeOf(e->contents.modE.right) ? dataTypeOf(e->contents.modE.left):dataTypeOf(e->contents.modE.right) ;
                        
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: %s %% %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.modE.left)],type_arr_in[dataTypeOf(e->contents.modE.right)]);
                        return ERROR_T;
                    }
        case bit_op: 
                    
                    if( ( (dataTypeOf(e->contents.bitE.left) == CHAR_T) || (dataTypeOf(e->contents.bitE.left) == INT_T) ) &&  ( (dataTypeOf(e->contents.bitE.right) == CHAR_T) || (dataTypeOf(e->contents.bitE.right) == INT_T) ))
                        return  dataTypeOf(e->contents.bitE.left)>=dataTypeOf(e->contents.bitE.right)? dataTypeOf(e->contents.bitE.left) : dataTypeOf(e->contents.bitE.right);
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: %s %s %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.bitE.left)],e->contents.bitE.op,type_arr_in[dataTypeOf(e->contents.bitE.right)]);
                        return (ERROR_T);
                    }

        case rel_op:
                    if ( ( (dataTypeOf(e->contents.relE.left) >= CHAR_T) && (dataTypeOf(e->contents.relE.left) <= FLOAT_T) ) && ( (dataTypeOf(e->contents.relE.right) >= CHAR_T) && (dataTypeOf(e->contents.relE.right) <= FLOAT_T) ))
                        return  CHAR_T; 
                    
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: %s %s %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.relE.left)],e->contents.relE.op,type_arr_in[dataTypeOf(e->contents.relE.right)]);
                        return (ERROR_T);
                    }

        case log_op:
                    if ( ( (dataTypeOf(e->contents.logE.left) >= CHAR_T) && (dataTypeOf(e->contents.logE.left) <= FLOAT_T) ) && ( (dataTypeOf(e->contents.logE.right) >= CHAR_T) && (dataTypeOf(e->contents.logE.right) <= FLOAT_T) ))
                        return  CHAR_T;
                    else 
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: %s %s %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.logE.left)],e->contents.logE.op,type_arr_in[dataTypeOf(e->contents.logE.right)]);
                        return (ERROR_T);
                    }
                    
        
        case ass_op: 
                    if ( ( (dataTypeOf(e->contents.assE.left) >= CHAR_T) && (dataTypeOf(e->contents.assE.left) <= FLOAT_T) ) && ( (dataTypeOf(e->contents.assE.right) >= CHAR_T) && (dataTypeOf(e->contents.assE.right) <= FLOAT_T) ))
                        return ( dataTypeOf(e->contents.assE.left)>=dataTypeOf(e->contents.assE.right)?dataTypeOf(e->contents.assE.left) : dataTypeOf(e->contents.assE.right) ); //no_coercion
                    else
                     {
                        fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: %s %s %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.assE.left)],e->contents.assE.op,type_arr_in[dataTypeOf(e->contents.assE.right)]);
                        return (ERROR_T);
                     }
                         
        case cond_op:  
                    if ( (dataTypeOf(e->contents.condE.cond) >= CHAR_T) && (dataTypeOf(e->contents.condE.cond) <= FLOAT_T) )
                        if ( ( (dataTypeOf(e->contents.condE.left) >= CHAR_T) && (dataTypeOf(e->contents.condE.left) <= FLOAT_ARR_T) ) && ( (dataTypeOf(e->contents.condE.right) >= CHAR_T) && (dataTypeOf(e->contents.condE.right) <= FLOAT_ARR_T) ))
                            return ( dataTypeOf(e->contents.condE.left)>=dataTypeOf(e->contents.condE.right)?dataTypeOf(e->contents.condE.left) : dataTypeOf(e->contents.condE.right)); //no_coercion
                        else
                            return ERROR_T;
                        
                    else
                    {
                        fprintf(stderr, "Error in %s line %d:\n\t Operation not supported: %s ? %s : %s\n",filename,yylineno,type_arr_in[dataTypeOf(e->contents.condE.cond)],type_arr_in[dataTypeOf(e->contents.condE.left)],type_arr_in[dataTypeOf(e->contents.condE.right)]);
                        return ERROR_T;
                    }

        case cast_op: 
                    if ( (dataTypeOf(e->contents.castE.cast_type) >= CHAR_T) && (dataTypeOf(e->contents.castE.cast_type) <= FLOAT_T) )
                    {
                        if ( (dataTypeOf(e->contents.castE.right) >= CHAR_T) && (dataTypeOf(e->contents.castE.right) <= FLOAT_T) )
                            return dataTypeOf(e->contents.castE.cast_type);
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

        case func_op:
                    //check if the param types match
                    /*{
                        printf("\n I have come here!");
                        exp_node *left_node = e->contents.funcE.left; // This implies there exist some function dec, may be more than 1
                        exp_node *right_node = e->contents.funcE.right;
                        char* function_name = left_node->contents.identE.entry->id;
                        printf("\n Name I am looking for is %s!",function_name);
                        int found = 0; //nPar matches
                        int match = 0; //par types match
                        sz = 0;  
                        par_types_fromExp = NULL;
                        dataTypesOf(e->contents.funcE.right);//, &par_types_fromExp); //reverse
                        if(!par_types_fromExp) { exit(1);}
                         printf("\n I havefound the types of paramets from call here!");
                        printf("\nLooking in table %d",myCurrentTable);
                        int noofunc_overload = nooMatchesinSymTable(myCurrentTable,function_name);
                        printf("\nMatching %d",noofunc_overload);
                        struct symbolListEntry* matched_sym_ListHead = getMatchesinSymTable(myCurrentTable,function_name);
                        printf("\nMatching %d",noofunc_overload);
                        printf("\nMatching %d",noofunc_overload);
                        if(!matched_sym_ListHead)
                            exit(1);
                           
                        struct symbolListEntry* matched_sym_List=matched_sym_ListHead;
                        // = matched_sym_ListHead;
                        for(int k = 0;k<noofunc_overload;k++)
                        {
                            printf("\nInside loop %d",k);
                            printf("\nInside loop %d",k);
                            int nPar = matched_sym_List->symbol.n;
                            enum type *par_types = matched_sym_List->symbol.par_types;
                            if ( (nPar==sz) && !diffParamTypes(par_types,par_types_fromExp,nPar) )
                            {
                                printf("\nDid it match???",k);
                                e->contents.funcE.left = makeIdentifierNameE(&matched_sym_List->symbol);
                                found = 1;
                                match = 1;
                            }
                            matched_sym_List = matched_sym_List->nextEntry;
                        }
                        printf("\nMatching %d!!",noofunc_overload);
                        printf("\nMatching %d!!!",noofunc_overload);
                        if((match ==0) && (found==0)) // nothing worked! either no match or coercion-match
                        {
                            //trycoercion at first match
                            {
                                matched_sym_List = matched_sym_ListHead;
                                for(int k = 0;k<noofunc_overload;k++)
                                {
                                 int nPar = matched_sym_List->symbol.n;
                                 enum type *par_types = matched_sym_List->symbol.par_types;
                                 if ( (nPar==sz) && coercionPossibleParamTypes(par_types,par_types_fromExp,nPar) )
                                 {
                                    e->contents.funcE.left = makeIdentifierNameE(&matched_sym_List->symbol);
                                    found = 1;
                                    match = 1;
                                 }
                                 matched_sym_List = matched_sym_List->nextEntry;
                                }
                            }

                            //no-match
                            if((match ==0) && (found==0)){
                            fprintf(stderr,"Error in %s line %d:\n \t No match for function call %s(",filename,yylineno,left_node->contents.identE.entry->id);
                            for(int j=sz-1;j>0;j--)
                                fprintf(stderr,"%s, ",type_arr_in[par_types_fromExp[j]]);  
                            fprintf(stderr,"%s)\n \t",type_arr_in[par_types_fromExp[0]]);

                            matched_sym_List = matched_sym_ListHead;
                            for(int k = 0;k<noofunc_overload;k++)
                            {
                                fprintf(stderr," Candidates are: \n \t\t %s %s(",type_arr_in[matched_sym_List->symbol.type], matched_sym_List->symbol.id); 
                                for(int j=0;j<matched_sym_List->symbol.n-1;j++)
                                    fprintf(stderr,"%s, ",type_arr_in[matched_sym_List->symbol.par_types[j]]);  
                                fprintf(stderr,"%s) declared in %s near line %d\n",type_arr_in[matched_sym_List->symbol.par_types[matched_sym_List->symbol.n-1]], filename, matched_sym_List->symbol.lineno);
                                matched_sym_List = matched_sym_List->nextEntry;
                            }
                            return ERROR_T;
                            } 
                         } 
                        return dataTypeOf(e->contents.funcE.left);
                    }*/

                    {
                        exp_node *left_node = e->contents.funcE.left; // This implies there exist some function dec, may be more than 1
                        exp_node *right_node = e->contents.funcE.right;
                        struct symbol *funSym  = left_node->contents.identE.entry;
                        int nPar = funSym->n;
                        enum type* par_types = funSym->par_types;
                        
                        sz = 0;  
                        par_types_fromExp = NULL;
                        dataTypesOf(e->contents.funcE.right);//, &par_types_fromExp); //reverse
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
                        return dataTypeOf(e->contents.funcE.left);
                    }
        case func_np_op:
                    //check if the param types match
                    {
                        exp_node *left_node = e->contents.funcNPE.left;
                        int nPar = left_node->contents.identE.entry->n;
                        enum type *par_types =  e->contents.funcNPE.left->contents.identE.entry->par_types;
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
                        return dataTypeOf(e->contents.funcNPE.left);
                    }

        default: return ERROR_T;
    }
}

void dataTypesOf(exp_node *e)//, int* par_types_fromExp)
{ 
    sz=sz+1;
    par_types_fromExp = (enum type*)realloc(par_types_fromExp,sz*sizeof(int));
    switch(e->node_type)
    {
        case comma_op: 
                        {
                            par_types_fromExp[sz-1]=dataTypeOf(e->contents.commaE.right);
                            if(e->contents.commaE.left!=NULL)
                                dataTypesOf(e->contents.commaE.left);//, par_types_fromExp);
                            break;
                        }

        case comma_last_op : {
                                
                                par_types_fromExp[sz-1]=dataTypeOf(e->contents.commaE.left);
                                break;
                             }
        default : 
                { 
                  break;
                }

    } 
    return  ;
}

