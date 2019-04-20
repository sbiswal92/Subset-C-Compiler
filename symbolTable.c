#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>

char* type_arr_inn[8]={
                        "error",
                        "void",
                        "char",
                        "int",
                        "float",
                        "char[]",
                        "int[]",
                        "float[]"
                    };

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

int diffParamTypes(enum type* par_types1, enum type* par_types2,int nPar) {

	for(int i=0;i<nPar;i++)
	{
		if(par_types1[i]!=par_types2[i])
			return 1;
	}
	
return 0; // no mismatch

}

int diffParamTypesRev(enum type* par_types1, enum type* par_types2,int nPar) {

	for(int i=0;i<nPar;i++)
	{
		if(par_types1[i]!=par_types2[nPar-i-1])
			return 1;
	}
	
return 0; // no mismatch

}

int coercionPossibleParamTypes(enum type* par_typesFun, enum type* par_typesExp,int nPar) {

	for(int i=0;i<nPar;i++)
	{
		if(par_typesFun[i]<par_typesExp[i])
			return 0;
	}

	return 1; // no mismatch

}
int coercionPossibleParamTypesRev(enum type* par_typesFun, enum type* par_typesExp,int nPar) {

	for(int i=0;i<nPar;i++)
	{
		if(par_typesFun[i]<par_typesExp[nPar-1-i])
			return 0;
	}

	return 1; // no mismatch

}


struct symbolTable* symbolTable_getParent(struct symbolTable* symbolTable) {
        return symbolTable->parentSymbolTable;
}

struct symbolTable* symbolTable_addChild(struct symbolTable* symbolTable,struct symbol parentSymbol) {

	//create a new child table
    struct symbolTableListEntry *childSymbolTableListEntry;
    childSymbolTableListEntry = symbolTableListEntry_initializeEntry();
    struct symbolTable *childSymbolTable = (struct symbolTable*)childSymbolTableListEntry->entry;
	childSymbolTable->symbolListHead = NULL;
	childSymbolTable->parentSymbolTable = symbolTable;
	childSymbolTable->parentSymbolTableEntrySymbol = parentSymbol;
	childSymbolTable->local_num = -1;
	childSymbolTable->param_num = -1;
	childSymbolTable->fun_num = -1;

	//insert at end
	/****/
	if(!symbolTable->childSymbolTableListHead) { // empty list becomes the new node
         symbolTable->childSymbolTableListHead = childSymbolTableListEntry;
    } else { // find last and link the new node
        struct symbolTableListEntry* last = symbolTable->childSymbolTableListHead;
        while(last->nextEntry) last=last->nextEntry;
        last->nextEntry = childSymbolTableListEntry;
    }
	/****/
     
	//insert at start 
    	//childSymbolTableListEntry->nextEntry = symbolTable->childSymbolTableListHead;
    	//symbolTable->childSymbolTableListHead = childSymbolTableListEntry;


    return childSymbolTable;
}

struct symbolTable* symbolTable_getMainChild(struct symbolTable* symbolTable, struct symbol parentSymbol) {

	//obtain the first child of this symbolTable
	
	struct symbolTableListEntry *iter = symbolTable->childSymbolTableListHead;
    struct symbolTable *mainchildSymbolTable = NULL;
	
	
	iter = symbolTable->childSymbolTableListHead;
	while(iter!=NULL)
	{
	  mainchildSymbolTable = (struct symbolTable*)iter->entry;
	  struct symbol sym1 = mainchildSymbolTable->parentSymbolTableEntrySymbol;
	  struct symbol sym2 = parentSymbol;
	  
	  if(symbolcmpover(sym1, sym2)==0)
	  {  
	  	return mainchildSymbolTable;
	  }
	  iter = iter->nextEntry;
	}
		return NULL;
	  
}

struct symbolTable* symbolTable_getChild(struct symbolTable* symbolTable, struct symbol* parentSymbol) {
	//iterate through children of this symbolTable
	//basically  meant to iterate in glocal symbol table looking for duplicate functions

	struct symbolTableListEntry *currChildTableE = symbolTable->childSymbolTableListHead;
	struct symbolTable *currChildTable = (struct symbolTable*)currChildTableE->entry;
	//Check for the child symbolTable whose parentSymbolTableEntry->symbol matches parentEntrySymbol
	while(symbolcmpover(currChildTable->parentSymbolTableEntrySymbol,*parentSymbol)!=0)
	{
		currChildTableE = currChildTableE->nextEntry;
		currChildTable = (struct symbolTable*)currChildTableE->entry;
	}
	return currChildTable;
}


struct symbol* symbolTable_getSymbol(struct symbolTable *symbolTable,  const char *id) {
    return symbolList_getSymbol(symbolTable->symbolListHead, id);
}

struct symbol* symbolTable_getSymbol1(struct symbolTable *symbolTable,  struct symbol symbol) {
    return symbolList_getSymbol1(symbolTable->symbolListHead, symbol);
}

void symbolTable_insertSymbol(struct symbolTable *symbolTable, struct symbol symbol, char* fname, int lineno) {
  	if(symbol.kind==variable)
	{
		symbolTable->symbolListHead = symbolList_insertEntry(symbolTable->symbolListHead, symbol, fname, lineno, (symbolTable->param_num>=0)?symbolTable->param_num+symbolTable->local_num+1:symbolTable->local_num);
		symbolTable->local_num +=1; 
	} 
	
	else if(symbol.kind==parameter) 
	{ 
		symbolTable->symbolListHead = symbolList_insertEntry(symbolTable->symbolListHead, symbol, fname, lineno, symbolTable->param_num );
		symbolTable->param_num +=1; 
	}
	else 
	{ 
		symbolTable->symbolListHead = symbolList_insertEntry(symbolTable->symbolListHead, symbol, fname, lineno, symbolTable->fun_num );
		symbolTable->fun_num +=1; 
	}
}


struct symbol* lookup(struct symbolTable *symbolTable, const char *id, char* fname, int lineno) {
    struct symbolTable *symbolTableIter = symbolTable;
    struct symbol *symbol = symbolTable_getSymbol(symbolTableIter, id);
    while(symbol==NULL) {
        symbolTableIter = symbolTable_getParent(symbolTableIter);
        if(symbolTableIter==NULL) {
            break;
        }
        symbol = symbolTable_getSymbol(symbolTableIter, id); // find the symbol in table symbolTableIter
    }
    if(symbol==NULL) {
        fprintf(stderr,"Error in %s line %d:\n \t Identifier %s is not defined \n",fname,lineno,id);
		exit(1);
    }
	if(strcmp(symbolTableIter->parentSymbolTableEntrySymbol.id,"0")==0)
		symbol->whatTable = 'G';
	else
		symbol->whatTable = 'L';
    return symbol;
}



struct symbol* lookup1(struct symbolTable *symbolTable, struct symbol sym,char* fname, int lineno) {
    struct symbolTable *symbolTableIter = symbolTable;
    struct symbol *symbol = symbolList_getSymbol1(symbolTable->symbolListHead, sym);
    while(symbol==NULL) {
        symbolTableIter = symbolTable_getParent(symbolTableIter);
        if(symbolTableIter==NULL) {
            break;
        }
        symbol = symbolTable_getSymbol1(symbolTableIter, sym);
    }
    if(symbol==NULL) {
     	fprintf(stderr,"Error in %s line %d:\n \t Identifier %s is not defined\n",fname,lineno,sym.id);
		exit(1);
    }
    return symbol;
}

struct symbolTable* enter_scope(struct symbolTable* symbolTable, struct symbol parentSymbol, int isNew) {
	if(isNew)	return symbolTable_addChild(symbolTable, parentSymbol);
	else return symbolTable_getMainChild(symbolTable, parentSymbol);
}

int fixSymInSymTable(struct symbolTable* symbolTable, struct symbol symbol, int nPar, enum type *par_types,char* fname, int lineno)
{	

		
		struct symbolListEntry *curr = symbolTable->symbolListHead; 
		struct symbolListEntry *lastMatch = NULL;
		int myflag = 1;
		
		while(curr!=NULL) //iterate through the table and look for symbols with same name P.S: cannot be non-function because that case is handled
		{
			if(symbolcmp_id(curr->symbol, symbol)==0) // find the matching symbol
			{
				lastMatch = curr;
				if( (curr->symbol.n==nPar) && !diffParamTypes(curr->symbol.par_types,par_types,nPar) ) // exact same par num & types exists
				{
					if(curr->symbol.type != symbol.type) // diff return types
						{
							fprintf(stderr,"Error in file %s line %d:\n\t Redeclaration function %s %s:\n\t  Function already defined as %s %s (near line %d)",fname,lineno,type_arr_inn[symbol.type],symbol.id,type_arr_inn[curr->symbol.type],curr->symbol.id,curr->symbol.lineno);
							 exit(1);
						}
					if(curr->symbol.type == symbol.type) // same return types OK to have!
						{
							 if(curr->symbol.isDefined==1)
							 {
							 	myflag = -1; //delete this new child table created for this symbol
								break;
							 }
							 else{
							 	myflag = 2; //delete the old child?
								break;	
							 }
						}
				}
				if( (curr->symbol.n!=-1) && ( (curr->symbol.n!=nPar) || ( (curr->symbol.n==nPar) && diffParamTypes(curr->symbol.par_types,par_types,nPar) )) ) // overlaoding conditions
				{
					fprintf(stderr,"Error in file %s line %d:\n\t Function overloading is not allowed:\n \t   Function %s %s(",fname,lineno,type_arr_inn[curr->symbol.type],curr->symbol.id);
						if(curr->symbol.n>0)
						{
						for(int m = 0;m<curr->symbol.n-1;m++)
							fprintf(stderr,"%s, ",type_arr_inn[curr->symbol.par_types[m]]);
						fprintf(stderr,"%s) is already defined(near line %d) \n",type_arr_inn[curr->symbol.par_types[curr->symbol.n-1]],curr->symbol.lineno);
						} else
							fprintf(stderr,") is already defined(near line %d) \n",curr->symbol.lineno);
					exit(1);
				}
			}
			curr=curr->nextEntry;
		}

		//So, nothing matched. So lets overload
		struct symbolListEntry *curr1 = symbolTable->symbolListHead;
		
		if(lastMatch!=NULL)
		{
			lastMatch->symbol.n=nPar;
			lastMatch->symbol.par_types=par_types;
		
		}
		
		return myflag;//ok added an entry in the symTable and updated its values

}


struct symbolTable* exit_scope(struct symbolTable* symbolTable, int* isDef, char* fname, int lineno) {
	//Two kinds of fixing : 1. set the number parameters and their types

	struct symbolTable* parentSymbolTable = symbolTable->parentSymbolTable;
	int to_do = 0;
	if(*isDef) // if the table is already defined, get the parent table , assign the function's isDef = 1 and return the table 
	 {
		 struct symbolListEntry *curr = parentSymbolTable->symbolListHead;
			while(curr!=NULL)
			{
				if(symbolcmp(curr->symbol,symbolTable->parentSymbolTableEntrySymbol))
				{	curr->symbol.isDefined = 1; break; }
				curr = curr->nextEntry;
			} 
		return parentSymbolTable;
	 }
	
	int nPar = 0;
	enum type *par_types = (enum type *)malloc(sizeof(enum type));
		
	if(strcmp(symbolTable->parentSymbolTableEntrySymbol.id,"0")!=0) // function's table
	{
		
		//traverse the symbolListHead to find number of parameters
	
		struct symbolListEntry *curr = symbolTable->symbolListHead;

		
		while(curr!=NULL)
		{
			
			if(curr->symbol.kind ==  parameter)
			{
				par_types[nPar] = curr->symbol.type;
				nPar = nPar+1;
				par_types = (enum type *)realloc(par_types,(nPar+1)*sizeof(enum type));
			}
			curr = curr->nextEntry;
		}
		//Go ahead and put in the parameter details of the function
		to_do = fixSymInSymTable(parentSymbolTable, symbolTable->parentSymbolTableEntrySymbol, (nPar == 0? 0 : nPar),(nPar == 0? NULL : par_types),fname,  lineno);
	} else { 
		symbolTable->parentSymbolTableEntrySymbol.par_types = NULL;
		symbolTable->parentSymbolTableEntrySymbol.n = 0;
		to_do = fixSymInSymTable(parentSymbolTable, symbolTable->parentSymbolTableEntrySymbol, 0, NULL, fname,  lineno); // adding local block
	    }
		
	   struct symbol controlSymbol;
	
		if(to_do==-1){ // definition already exists, delete current entry
			struct symbolListEntry *parentTableList = parentSymbolTable->symbolListHead;
			struct symbolListEntry *parentTableList_lastMatch = NULL;
			struct symbol badSymbol = symbolTable->parentSymbolTableEntrySymbol;
			while(parentTableList!=NULL)
			{
				if((symbolcmpover(parentTableList->symbol,badSymbol)==0) && (parentTableList->symbol.n==nPar) && !diffParamTypes(parentTableList->symbol.par_types,par_types,nPar) )
				{
					parentTableList_lastMatch=parentTableList;
				}
				parentTableList = parentTableList->nextEntry;
			}
			parentTableList_lastMatch = NULL;
			*isDef = -1;
		}else if(to_do == 2){ // definition does not exist, retain current entry, delete older entry
			
			struct symbolListEntry *parentTableList = parentSymbolTable->symbolListHead; // what symbols
			struct symbol keepSymbol = symbolTable->parentSymbolTableEntrySymbol;
			struct symbolListEntry *parentTableList_prevMatch = NULL;
			
			//struct symbol keepSymbol = symbolTable->parentSymbolTableEntrySymbol;
			while(parentTableList!=NULL)
			{
				if((symbolcmpover(parentTableList->symbol,keepSymbol)==0)  && (parentTableList->symbol.n==nPar) && !diffParamTypes(parentTableList->symbol.par_types,par_types,nPar) ) //not-to-lineno
				{
					controlSymbol = keepSymbol;
					struct symbolListEntry *temp = parentTableList;
					if(parentTableList_prevMatch){
						parentTableList_prevMatch->nextEntry = parentTableList->nextEntry;
					}
					else{
						parentSymbolTable->symbolListHead = parentTableList->nextEntry;
					}
					temp = NULL;
					break;
				}
				parentTableList_prevMatch = parentTableList;
				parentTableList = parentTableList->nextEntry;
				
			}
			*isDef = 2;
		}else if(to_do == 1) *isDef = 1;
		else *isDef = 0;

	
		if(*isDef==2) //  I have removed the symbol from the table but the childTable for that symbol is yet to be removed 
			{

				struct symbolTableListEntry *parentTableChildrenList = parentSymbolTable->childSymbolTableListHead; // what tables
				struct symbolTableListEntry *parentTableChildrenList_prevMatch = NULL;
				struct symbolTable* myTable = NULL;
				while(parentTableChildrenList!=NULL)
				{
					myTable = (struct symbolTable*)parentTableChildrenList->entry;
					if(symbolcmpover(myTable->parentSymbolTableEntrySymbol,controlSymbol)==0) //not-to-lineno
					{
					struct symbolTableListEntry *tempTable = parentTableChildrenList;
					if(parentTableChildrenList_prevMatch){
						struct symbolTable* moxi = (struct symbolTable*)parentTableChildrenList_prevMatch->entry;
						struct symbolTable* toxi = (struct symbolTable*)parentTableChildrenList->nextEntry->entry;
						
						parentTableChildrenList_prevMatch->nextEntry = parentTableChildrenList->nextEntry;
					}
					else{
						parentSymbolTable->childSymbolTableListHead = parentTableChildrenList->nextEntry;
					}
					tempTable = NULL;
					break;
				}
				parentTableChildrenList_prevMatch = parentTableChildrenList;
				parentTableChildrenList = parentTableChildrenList->nextEntry;
				
				}
			}

	
	
	return parentSymbolTable;
}

/*void check_return(struct symbolTable* symbolTable, enum type ret_type, char* fname, int lineno) {

	if(symbolTable->parentSymbolTableEntrySymbol!=NULL) // function's table
	{
	
		enum type fun_ret_type = symbolTable->parentSymbolTableEntrySymbol.type;
		if(fun_ret_type != ret_type)
		{
			fprintf(stderr,"Error in %s line %d:\n \t Function %s should return a value of type %s function %s \n", fname, lineno, symbolTable->parentSymbolTableEntrySymbol.id, type_arr_inn[symbolTable.type],type_arr_inn[ret_type] );
			exit(1);
		}
		
	}
	
	return;
}*/




struct symbolTableListEntry * reverseTableList(struct symbolTableListEntry *head){
	return head;
	/*struct symbolTableListEntry *curr=head;
        struct symbolTableListEntry *p=NULL, *n = NULL;;
        while(curr!=NULL){
		
                 n = curr->nextEntry;
                 curr->nextEntry = p;

                 p = curr;
                 curr = n;
        }

        return p;
	*/
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

struct symbolListEntry* getMatchesinSymTable(struct symbolTable *symbolTable, const char *id) {
    struct symbolListEntry *symbolTableIter = symbolTable->symbolListHead;
	struct symbolListEntry *matchSymbolListHead = NULL;
	struct symbolListEntry *matchSymbolList = NULL;

	int ctr = 0;
	while(symbolTableIter!=NULL)
	{
		if(strcmp(symbolTableIter->symbol.id,id)==0)
		{
			struct symbolListEntry *temp = (struct symbolListEntry*) malloc(sizeof(struct symbolListEntry));
    		temp->symbol = symbolTableIter->symbol;
    		temp->nextEntry = NULL;

			if(matchSymbolListHead==NULL)
				{
					matchSymbolList = temp;	
					matchSymbolListHead = matchSymbolList;
				}
			else
				{
					matchSymbolList->nextEntry = temp;
					matchSymbolList = matchSymbolList->nextEntry;
				}

		}
		symbolTableIter = symbolTableIter->nextEntry;		
	}
    return matchSymbolListHead;
}

int nooMatchesinSymTable(struct symbolTable *symbolTable, const char *id) {
    struct symbolListEntry *symbolTableIter = symbolTable->symbolListHead;
	struct symbolListEntry *matchSymbolList = NULL;

	int ctr = 0;
	while(symbolTableIter!=NULL)
	{
		if(strcmp(symbolTableIter->symbol.id,id)==0)
		{
			ctr+=1;
		}
		symbolTableIter = symbolTableIter->nextEntry;
		
	}
	return ctr;
}