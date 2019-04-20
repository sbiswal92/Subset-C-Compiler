#include "ast.h"



enum type* par_types_fromExp;
int sz;
char* filename;
extern int yylineno;

int dataTypeOf(exp_node *e);

char* dataTypesOf(exp_node *e, char* result);
