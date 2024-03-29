
#include <stdio.h>

enum kind{variable, parameter, function1};
enum type
{
	ERROR_T=0,
	VOID_T,
	CHAR_T,
	INT_T,
	FLOAT_T,
	CHAR_ARR_T,
	INT_ARR_T,
	FLOAT_ARR_T
};

struct symbol {
    int lineno;
    const char *id;
    enum type type;
    enum kind kind;
    enum type *par_types;
    int n; //num_of_par-->if function ; 
	int kind_position;//if:  n^th func if func or  n^th local variable if variable or n^th parameter if parameter
	int ret_value;//only in global table: contains 0 or 1;
    int isDefined;
	char whatTable;
};

void initializeSymbol(struct symbol *symbol, const char *id, enum type type, enum kind kind, int lineno, int pos);
void printSymbol(struct symbol *symbol);
int symbolcmp(struct symbol symbol1, struct symbol symbol2);
int symbolcmpline(struct symbol symbol1, struct symbol symbol2);
int symbolcmp_id(struct symbol symbol1, struct symbol symbol2);
int symbolCheckId(struct symbol symbol, const char *id);
int symbolcmpover(struct symbol symbol1, struct symbol symbol2);
enum type getType(char* type_str);

int diffParamTypes23(enum type* par_types1, enum type* par_types2,int nPar);