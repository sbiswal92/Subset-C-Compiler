#include "symbolList.h"
#include <stdlib.h>
#include <string.h>

char* type_arr_sl[8]={
                        "error",
                        "void",
                        "char",
                        "int",
                        "float",
                        "char[]",
                        "int[]",
                        "float[]"
                    };

struct symbolListEntry *reverseList(struct symbolListEntry *head){
	return head;
    /*struct symbolListEntry *curr=head;
	struct symbolListEntry *p=NULL, *n = NULL;;
   	while(curr!=NULL){
                 n = curr->nextEntry;
                 curr->nextEntry = p;

                 p = curr;
                 curr = n;
        }

 	return p;	
    */ 
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


struct symbolListEntry* getSymbolListOnlyPar(struct symbolListEntry *head) {
    if(head==NULL) {
        return NULL;
    }
    struct symbolListEntry *parList = NULL;
    struct symbolListEntry *rev = head;//reverseList(head);
    int flag = 0;
    while(rev!=NULL) {
        if(rev->symbol.kind == parameter){
		    if(flag==0) {
                flag = 1;
                struct symbolListEntry *temp = rev;
                temp->nextEntry = NULL;
                parList = temp;
            }else {
                struct symbolListEntry *temp = rev;
                temp->nextEntry = NULL;
                struct symbolListEntry *parListEnd = parList;
                while(parListEnd->nextEntry) parListEnd=parListEnd->nextEntry;
                parListEnd->nextEntry = temp;
            }
        
	}
        rev = rev->nextEntry;
    }
    
    return parList;
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

int symbolList_findEntry_Overload(struct symbolListEntry *head, struct symbol sym) {
    while(head!=NULL && symbolCheckId(head->symbol, sym.id)) {
        head = head->nextEntry;
    }
    if( head!=NULL && (head->symbol.kind == function1) && (sym.kind == function1) )
    {
        return 1;
    }

    return 0;
}

struct symbol* symbolList_getSymbol(struct symbolListEntry *head,  const char *id) {
    struct symbolListEntry *entry = symbolList_findEntry(head, id);
    if(entry==NULL) {
        return NULL;
    }
    return &(entry->symbol);
}

struct symbol* symbolList_getSymbol1(struct symbolListEntry *head,  struct symbol sym) {
    struct symbolListEntry *entry = head;
    while(entry!=NULL && symbolcmpover(entry->symbol, sym)) {
        entry = entry->nextEntry;
    }
    return &(entry->symbol);
}

struct symbolListEntry* symbolList_insertEntry(struct symbolListEntry *head, struct symbol symbol,char* fname, int lineno) {
    int possible_overload_flag = 0;
   
    struct symbolListEntry *found_samename_symbolListEntry = symbolList_findEntry(head, symbol.id);
    if(found_samename_symbolListEntry!=NULL) { //Matching symbols are found
        if(found_samename_symbolListEntry->symbol.kind != symbol.kind)    //both are different kind
        {
            fprintf(stderr,"Error in file %s line %d \n\t local variable %s already declared as:\n\t %s %s (near line %d) \n",fname,lineno,symbol.id,type_arr_sl[found_samename_symbolListEntry->symbol.type],found_samename_symbolListEntry->symbol.id,found_samename_symbolListEntry->symbol.lineno);
	        exit(1);
        }else if(found_samename_symbolListEntry->symbol.kind == symbol.kind) // both are same kind
        {
                if(symbol.kind!=function1) //both are non-function
                {
                fprintf(stderr,"Error in file %s line %d \n\t local variable %s already declared as:\n\t %s %s (near line %d) \n",fname,lineno,symbol.id,type_arr_sl[found_samename_symbolListEntry->symbol.type],found_samename_symbolListEntry->symbol.id,found_samename_symbolListEntry->symbol.lineno);
	            exit(1);
                } else possible_overload_flag = 1;
        } 
    }

    //Insert at the beginning of the list
    struct symbolListEntry *temp = initializeEntry(symbol);
    temp->nextEntry = NULL;

    if(!head) { // empty list becomes the new node
        head = temp;
    } else { // find last and link the new node
        struct symbolListEntry* last = head;
        while(last->nextEntry) last=last->nextEntry;
        last->nextEntry = temp;
    }
    return head;
}

