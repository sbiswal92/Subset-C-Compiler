#include "symbol.h"
#include <stdlib.h>
#include <string.h>

static const char *kindString[] = {"var", "fun", "par"};

void initializeSymbol(struct symbol *symbol, const char *id, enum type type, enum kind kind,int lineno,int pos) {
    char *symbolId = (char*)malloc(strlen(id));
    strcpy(symbolId, id);
    symbol->id = symbolId;
    symbol->lineno = lineno;
    memcpy(&(symbol->kind),&kind,sizeof(kind));
    memcpy(&(symbol->type),&type,sizeof(type));
    symbol->par_types = NULL;
    symbol->n = -1;
    symbol->kind_position = pos;
    if( (kind==function1) && (type>=2)) symbol->ret_value = 1;
    else symbol->ret_value = 0;
    symbol->isDefined = 0;
    symbol->whatTable='\0';
}


void printSymbol(struct symbol *symbol) {
    if(symbol==NULL) {
        printf("symbol==NULL\n");
        return;
    }
    printf("(%d)%s", symbol->type,symbol->id);
}

int symbolcmp(struct symbol symbol1, struct symbol symbol2) {
    if(
        symbol1.kind==symbol2.kind &&
        
	    symbol1.type==symbol2.type &&
        strcmp(symbol1.id,symbol2.id)==0
    ) {
        return 0;
    }
    return 1;
}

int symbolcmpline(struct symbol symbol1, struct symbol symbol2) {
    if(
        symbol1.kind==symbol2.kind &&
        symbol1.lineno==symbol2.lineno &&
	    symbol1.type==symbol2.type &&
        strcmp(symbol1.id,symbol2.id)==0
    ) {
        return 0;
    }
    return 1;
}

int symbolcmpover(struct symbol symbol1, struct symbol symbol2) {
    if(
        symbol1.kind==symbol2.kind &&
        symbol1.n==symbol2.n &&
        !diffParamTypes23(symbol1.par_types,symbol2.par_types,symbol1.n) &&
	    symbol1.type==symbol2.type &&
        strcmp(symbol1.id,symbol2.id)==0
    ) {
        return 0;
    }
    return 1;
}

int symbolcmp_id(struct symbol symbol1, struct symbol symbol2) {
    if(strcmp(symbol1.id,symbol2.id)==0) {
        return 0;
    }
    return 1;
}

int symbolCheckId(struct symbol symbol, const char *id) {
    if(strcmp(symbol.id,id)==0) {
        return 0; //match
    }
    return 1;
}

enum type getType(char* type_str) {
	if(strcmp(type_str,"int")==0)
		return INT_T;
	else if(strcmp(type_str,"char")==0)
                return CHAR_T;
	else if(strcmp(type_str,"float")==0)
                return FLOAT_T;
    else if(strcmp(type_str,"void")==0)
                return VOID_T;
    else if(strcmp(type_str,"char[]")==0)
                return CHAR_ARR_T;
    else if(strcmp(type_str,"int[]")==0)
                return INT_ARR_T;
    else if(strcmp(type_str,"float[]")==0)
                return FLOAT_ARR_T;

	else
 		return -1;
	
}

int diffParamTypes23(enum type* par_types1, enum type* par_types2, int nPar) {

	for(int i=0;i<nPar;i++)
	{
		if(par_types1[i]!=par_types2[i])
			return 1;
	}

	return 0; // no mismatch

}

