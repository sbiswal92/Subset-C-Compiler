
#include "symbolList.h"


struct symbolTableListEntry {
    void *entry;
    struct symbolTableListEntry *nextEntry;
};

struct symbolTable {
    struct symbolListEntry *symbolListHead;
    struct symbolTable *parentSymbolTable;
    struct symbol parentSymbolTableEntrySymbol;
   // struct symbol parentSymbolTableEntrySymbol1;
    struct symbolTableListEntry *childSymbolTableListHead;
};

struct symbolTableListEntry* symbolTableListEntry_initializeEntry();
struct symbolTableListEntry* symbolTableList_insertEntry(struct symbolTableListEntry *newEntry,struct symbolTableListEntry *head);


struct symbolTable* symbolTable_getParent(struct symbolTable* symbolTable);
struct symbolTable* symbolTable_addChild(struct symbolTable* symbolTable,struct symbol parentSymbol);
struct symbolTable* symbolTable_getMainChild(struct symbolTable* symbolTable,struct symbol parentSymbol);

struct symbol* symbolTable_getSymbol(struct symbolTable *symbolTable,  const char *id);
struct symbol* symbolTable_getSymbol1(struct symbolTable *symbolTable,  struct symbol symbol);
void symbolTable_insertSymbol(struct symbolTable *symbolTable, struct symbol symbol,char* fname, int lineno);

//void insert(struct symbolTable *symbolTable, const char *id, enum kind kind);
struct symbol* lookup(struct symbolTable *symbolTable, const char *id,char* fname, int lineno);
struct symbol* lookup1(struct symbolTable *symbolTable, struct symbol symbol,char* fname, int lineno);

struct symbolTable* enter_scope(struct symbolTable* symbolTable, struct symbol parentSymbol, int isNew); 
//isNew is set to 1 when a new local scope is entered
//if a functiond efinition body is entered, it means the func_SymTable already was created and needs to be re-accessed

struct symbolTable* exit_scope(struct symbolTable* symbolTable, int* isDef,char* fname, int lineno);


void check_return(struct symbolTable* symbolTable, enum type ret_type,char* fname, int lineno);
//void check_return(struct symbolTable* symbolTable);

void printAllLists(struct symbolTable* symbolTable, int prev);

void printGloLists(struct symbolTable* symbolTable,int prev);

int diffParamTypes(enum type* par_types1, enum type* par_types2,int nPar);
int diffParamTypesRev(enum type* par_types1, enum type* par_types2,int nPar);
int coercionPossibleParamTypes(enum type* par_typesFun, enum type* par_typesExp,int nPar);
int coercionPossibleParamTypesRev(enum type* par_typesFun, enum type* par_typesExp,int nPar);
