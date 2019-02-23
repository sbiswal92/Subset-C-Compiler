#include "symbol.h"
#include <stdlib.h>
#include <string.h>

static const char *kindString[] = {"var", "fun", "par"};

void initializeSymbol(struct symbol *symbol, const char *id, enum kind kind) {
    char *symbolId = (char*)malloc(sizeof(id));
    memcpy(symbolId, id, strlen(id));
    symbol->id = symbolId;
    memcpy(&(symbol->kind),&kind,sizeof(kind));
}



void printSymbol(struct symbol *symbol) {
    if(symbol==NULL) {
        printf("symbol==NULL\n");
        return;
    }
    printf("%s", symbol->id);
}

int symbolcmp(struct symbol symbol1, struct symbol symbol2) {
    if(
        symbol1.kind==symbol2.kind &&
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
