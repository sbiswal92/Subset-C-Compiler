
#include "symbol.h"

#define SIZE 4096

struct symbolListEntry {
    struct symbol symbol;
    int key;
};

struct symbolListEntry* symbolList[SIZE]; 



struct symbolListEntry *reverseList(struct symbolListEntry *head);
void printSymbolList(struct symbolListEntry *head);
void printSymbolListOnlyVar(struct symbolListEntry *head);
void printSymbolListOnlyPar(struct symbolListEntry *head);
int hasVar(struct symbolListEntry *head);
struct symbolListEntry* getNextFunOnSymbolList(struct symbolListEntry *head);


struct symbolListEntry* symbolList_findEntry(struct symbolListEntry *head,  const char *id);
struct symbol* symbolList_getSymbol(struct symbolListEntry *head,  const char *id);
struct symbolListEntry* symbolList_insertEntry(struct symbolListEntry *head, struct symbol symbol,char* fname, int lineno);

enum type getTypeOfSymbol(struct symbolListEntry *head, const char* sym_name);
