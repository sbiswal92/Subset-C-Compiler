#include "symbolList.h"
#include <stdlib.h>
#include <string.h>


struct symbolListEntry *reverseList(struct symbolListEntry *head){
	struct symbolListEntry *curr=head;
	struct symbolListEntry *p=NULL, *n = NULL;;
   	while(curr!=NULL){
                 n = curr->nextEntry;
                 curr->nextEntry = p;

                 p = curr;
                 curr = n;
        }

 	return p;	
}

void printSymbolList(struct symbolListEntry *head) {
    if(head==NULL) {
        printf("\tNo symbols\n");
    }

    struct symbolListEntry *rev = head;//reverseList(head);  
    
    while(rev->nextEntry!=NULL) {
        printSymbol(&(rev->symbol));
	printf(", ");
        rev = rev->nextEntry;
    }
	printSymbol(&(rev->symbol));
}

void printSymbolListOnlyVar(struct symbolListEntry *head) {
    if(head==NULL) {
        printf("");
    }
    
    struct symbolListEntry *rev = head; //reverseList(head);
    int flag = 0;    
    while(rev->nextEntry!=NULL) {
        if(rev->symbol.kind == variable){
        	if(flag == 1)  printf(", ");
		if(flag==0) flag = 1;
		printSymbol(&(rev->symbol));
        }
	rev = rev->nextEntry;
    }
	if(rev->symbol.kind == variable)  { 
		if(flag==1) printf(", ");
		printSymbol(&(rev->symbol));
		}
}


int hasVar(struct symbolListEntry *head) {

    struct symbolListEntry *rev = head; //reverseList(head);

    while(rev!=NULL) {
        if(rev->symbol.kind == variable){
        	return 1;
	}
        rev = rev->nextEntry;
    }
return 0;     
}


void printSymbolListOnlyPar(struct symbolListEntry *head) {
    if(head==NULL) {
        printf("");
    }

    struct symbolListEntry *rev = head;//reverseList(head);
    int flag = 0;
    while(rev->nextEntry!=NULL) {
        if(rev->symbol.kind == parameter){
                if(flag == 1)  printf(", ");
		if(flag==0) flag = 1;
                printSymbol(&(rev->symbol));
	}
        rev = rev->nextEntry;
    }
    if(rev->symbol.kind == parameter){
		if(flag==1) printf(", ");
                printSymbol(&(rev->symbol));
                }

}


struct symbolListEntry* getNextFunOnSymbolList(struct symbolListEntry *head) {

    while(head!=NULL) {
        if(head->symbol.kind == function1){
         	 return head;
	}
        head = head->nextEntry;
    }

    return NULL;
}

enum type getTypeOfSymbol(struct symbolListEntry *head, const char *id) {
	struct symbolListEntry *entry = symbolList_findEntry(head, id);
        if(entry==NULL) {
         return -1;
        }
    return (entry->symbol.type);
}
static struct symbolListEntry* initializeEntry(struct symbol symbol) {
    struct symbolListEntry *entry = (struct symbolListEntry*) malloc(sizeof(struct symbolListEntry));
    entry->symbol = symbol;
    entry->nextEntry = NULL;
    return entry;
}

struct symbolListEntry* symbolList_findEntry(struct symbolListEntry *head, const char *id) {
    while(head!=NULL && symbolCheckId(head->symbol, id)) {
        head = head->nextEntry;
    }
    return head;
}

struct symbol* symbolList_getSymbol(struct symbolListEntry *head,  const char *id) {
    struct symbolListEntry *entry = symbolList_findEntry(head, id);
    if(entry==NULL) {
        return NULL;
    }
    return &(entry->symbol);
}

struct symbolListEntry* symbolList_insertEntry(struct symbolListEntry *head, struct symbol symbol,char* fname, int lineno) {
    if(symbolList_findEntry(head, symbol.id)!=NULL) {
        fprintf(stderr,"\nError in file %s line %d \n\t duplicate identifier %s in the scope\n",fname,lineno,symbol.id);
	exit(1);
        return head;
    }
    //Insert at the beginning of the list
    struct symbolListEntry *headTemp = initializeEntry(symbol);
    headTemp->nextEntry = head;
    return headTemp;
}

