#include "symbolTable.h"
#include <stdlib.h>

struct symbolTableListEntry* symbolTableListEntry_initializeEntry() {
    struct symbolTableListEntry *symbolTableListEntry = (struct symbolTableListEntry*) malloc(sizeof(struct symbolTableListEntry));
    symbolTableListEntry->entry = (struct symbolTable*) malloc(sizeof(struct symbolTable));
    symbolTableListEntry->nextEntry = NULL;
    return symbolTableListEntry;
}

struct symbolTableListEntry* symbolTableList_insertEntry(struct symbolTableListEntry *newEntry,struct symbolTableListEntry *head) {
    newEntry->nextEntry = head;
    return newEntry;
}


struct symbolTable* symbolTable_getParent(struct symbolTable* symbolTable) {
        return symbolTable->parentSymbolTable;
}

struct symbolTable* symbolTable_addChild(struct symbolTable* symbolTable) {
    struct symbolTableListEntry *childSymbolTableListEntry;
    childSymbolTableListEntry = symbolTableListEntry_initializeEntry();
   
    childSymbolTableListEntry->nextEntry = symbolTable->childSymbolTableListHead;
    symbolTable->childSymbolTableListHead = childSymbolTableListEntry;
    struct symbolTable *childSymbolTable = (struct symbolTable*)childSymbolTableListEntry->entry;
    childSymbolTable->parentSymbolTable = symbolTable;
    return childSymbolTable;
}


struct symbol* symbolTable_getSymbol(struct symbolTable *symbolTable,  const char *id) {
    return symbolList_getSymbol(symbolTable->symbolListHead, id);
}

void symbolTable_insertSymbol(struct symbolTable *symbolTable, struct symbol symbol,char* fname, int lineno) {
    symbolTable->symbolListHead = symbolList_insertEntry(symbolTable->symbolListHead, symbol,fname, lineno );
}


/*void insert(struct symbolTable *symbolTable, const char *id, enum kind kind) {
    struct symbol symbol;
    initializeSymbol(&symbol, id, kind);
    symbolTable_insertSymbol(symbolTable, symbol);
}*/

struct symbol* lookup(struct symbolTable *symbolTable, const char *id) {
    struct symbolTable *symbolTableIter = symbolTable;
    struct symbol *symbol = symbolTable_getSymbol(symbolTableIter, id);
    while(symbol==NULL) {
        symbolTableIter = symbolTable_getParent(symbolTableIter);
        if(symbolTableIter==NULL) {
            break;
        }
        symbol = symbolTable_getSymbol(symbolTableIter, id);
    }
    if(symbol==NULL) {
        fprintf(stderr,"\n Error symbol id: %s not found", id);
    }
    return symbol;
}

struct symbolTable* enter_scope(struct symbolTable* symbolTable) {
    return symbolTable_addChild(symbolTable);
}

struct symbolTable* exit_scope(struct symbolTable* symbolTable) {
	return symbolTable_getParent(symbolTable);
}

struct symbolTableListEntry * reverseTableList(struct symbolTableListEntry *head){
	struct symbolTableListEntry *curr=head;
        struct symbolTableListEntry *p=NULL, *n = NULL;;
        while(curr!=NULL){
		
                 n = curr->nextEntry;
                 curr->nextEntry = p;

                 p = curr;
                 curr = n;
        }

        return p;
}

void printAllLists(struct symbolTable* symbolTable,int prev){


	struct symbolListEntry* rev = reverseList(symbolTable->symbolListHead);
	
	if(symbolTable->parentSymbolTable == NULL)
		{
			//struct symbolListEntry* rev = reverseList(symbolTable->symbolListHead);
			
			printf("Global vars:\t");
			printSymbolListOnlyVar(rev);
			
			//struct symbolListEntry* rev = reverseList(symbolTable->symbolListHead);
			struct symbolListEntry* currFunSym = getNextFunOnSymbolList(rev);
			struct symbolTableListEntry *it = reverseTableList(symbolTable->childSymbolTableListHead);

			
			while(currFunSym && it){
				printf("\n\nFunction %s",currFunSym->symbol.id);
                        
				//Get hold of the table pertaining to this function
				struct symbolTable* tCh = (struct symbolTable*)it->entry;
				
				if(tCh->symbolListHead!=NULL)
				{
					struct symbolListEntry* revCh = reverseList(tCh->symbolListHead);
				
					printf("\n\tParameters:\t");
					printSymbolListOnlyPar(revCh);
				
					printf("\n\tLocal vars:\t");
					reverseList(revCh);
					printAllLists(tCh,0);			
				}else
				{
					printf("\n\tParameters:\t");

					printf("\n\tLocal vars:\t");
				}
				
				it = it->nextEntry;
				currFunSym = getNextFunOnSymbolList(currFunSym->nextEntry);
			}
		
		}
		else{
			if((hasVar(symbolTable->symbolListHead))) //If the parent is not global and this list has a variable
			{	
				if(prev!=0) printf(", ");	
				printSymbolListOnlyVar(rev);
			}
			struct symbolTableListEntry *it = reverseTableList(symbolTable->childSymbolTableListHead);		
			while(it!=NULL) // Might have to reverse this list
			{
				
				printAllLists((struct symbolTable*)it->entry,1);
				it = it->nextEntry;
			}	
	
		}
}


