#include "symbol.h"
#include <stdlib.h>
#include <string.h>

static const char *kindString[] = {"var", "fun", "par"};

void initializeSymbol(struct symbol *symbol, const char *id, enum type type, enum kind kind) {
    char *symbolId = (char*)malloc(sizeof(id));
    memcpy(symbolId, id, strlen(id));
    symbol->id = symbolId;
    memcpy(&(symbol->kind),&kind,sizeof(kind));
    memcpy(&(symbol->type),&type,sizeof(type));
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

int symbolcmp_id(struct symbol symbol1, struct symbol symbol2) {
    if(strcmp(symbol1.id,symbol2.id)==0) {
        return 0;
    }
    return 1;
}

int symbolCheckId(struct symbol symbol, const char *id) {
    if(strcmp(symbol.id,id)==0) {
        return 0;
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

	else
 		return -1;
	
}
