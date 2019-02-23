
#include <stdio.h>

enum kind{variable, function1, parameter};

struct symbol {
    const char *id;
    enum kind kind;
};

void initializeSymbol(struct symbol *symbol, const char *id, enum kind kind);
void printSymbol(struct symbol *symbol);
int symbolcmp(struct symbol symbol1, struct symbol symbol2);
int symbolcmp_id(struct symbol symbol1, struct symbol symbol2);
int symbolCheckId(struct symbol symbol, const char *id);

