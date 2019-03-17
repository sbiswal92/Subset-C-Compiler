#include "ast.h"



enum type* par_types_fromExp;
int sz;
char* filename;
extern int yylineno;

int dataTypeOf(exp_node *e);
//void dataTypesOf(exp_node *e, int* par_types_fromExp);
void dataTypesOf(exp_node *e);
