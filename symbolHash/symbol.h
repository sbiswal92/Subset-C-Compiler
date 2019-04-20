
#include <stdio.h>

enum kind{variable, function1, parameter};
enum type
{
	ERROR_T,
	VOID_T,
	CHAR_T,
	INT_T,
	FLOAT_T,
	CHAR_ARR_T,
	INT_ARR_T,
	FLOAT_ARR_T
};

struct symbol {
    const char *id;
    enum type type;
    enum kind kind;
};

void initializeSymbol(struct symbol *symbol, const char *id, enum type type, enum kind kind);
void printSymbol(struct symbol *symbol);
int symbolcmp(struct symbol symbol1, struct symbol symbol2);
int symbolcmp_id(struct symbol symbol1, struct symbol symbol2);
int symbolCheckId(struct symbol symbol, const char *id);
enum type getType(char* type_str);
