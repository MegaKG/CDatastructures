#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct htbl_keyPairStruct {
    void* dataValue;
    char* keyValue;
} htbl_keyPair;

typedef struct htbl_tableStruct {
    llst_list** hashTable;
    int tableWidth;
    int keyCount;
} htbl_table;

//This is the FNV-0 Basic Hash system
int htbl_hashString(char* key, int maxWidth){
    //A magic number!
    const unsigned long long int FNV_prime = 1099511628211L;
    unsigned long long int Output = 0;
    int index = 0;
    while (1){
        if (key[index] == '\x00'){
            break;
        }
        else {
            Output = Output * FNV_prime;
            Output = Output ^ key[index];
            index += 1;
        }
    }

    return Output % maxWidth;
}

//Compare two strings
int compareString(char* A, char* B){
    int index = 0;
    while (1){
        if (A[index] != B[index]){
            return 0;
        }
        if ((A[index] == '\x00') || (B[index] == '\x00')){
            break;
        }
        index += 1;
    }
    return 1;
}

int htbl_length(htbl_table* myTable){
    return myTable->keyCount;
}

htbl_table* htbl_newTable(int tableWidth){
    //Create the table in memory
    htbl_table* myNewTable = (htbl_table*)malloc(sizeof(htbl_table));
    myNewTable->tableWidth = tableWidth;

    //Create the array of "buckets"
    myNewTable->hashTable = (llst_list**)malloc(sizeof(llst_list*));

    //Create the sublists for the collisions
    for (int index = 0; index < tableWidth; index++){
        myNewTable->hashTable[index] = llst_newList();
        printf("New List %p\n",myNewTable->hashTable[index]);
    }

    //Return the new table
    return myNewTable;
}



htbl_keyPair* _htbl_searchListForKeypair(char* key, llst_list* targetList){
    //Abuse the internal workings of the linked list to search
    llst_node* working = targetList->head;
    if (working == NULL){
        return NULL;
    }

    //Iterate over the linked list;
    htbl_keyPair* keyPair;
    while (1){
        //Fetch the Keypair
        keyPair = (htbl_keyPair*)working->data;

        //If it is a match to the key, return the data
        if (compareString(keyPair->keyValue,key)){
            return keyPair;
        }

        //If it is the last entry, break the loop
        if (working->after == NULL){
            break;
        }
        //Otherwise iterate to next value
        else {
            working = working->after;
        }
    }
    return NULL;
}

char* _htbl_copyString(char* input){
    char* Output = (char*)malloc((sizeof(char)*strlen(input)) +1);
    memset(Output,0,strlen(input));
    strcpy(Output,input);
    return Output;
}

void* htbl_getValue(char* key, htbl_table* myTable){
    //Hash the String
    int hashTableKey = htbl_hashString(key,myTable->tableWidth);

    //Get the target list
    llst_list* targetList = myTable->hashTable[hashTableKey];

    //Perform a lookup
    htbl_keyPair* result = _htbl_searchListForKeypair(key,targetList);

    //Check if there is a result
    if (result == NULL){
        return NULL;
    }
    
    return result->dataValue;
}

void htbl_setValue(char* key, void* data, htbl_table* myTable){
    //Hash the String
    int hashTableKey = htbl_hashString(key,myTable->tableWidth);

    //Get the target list
    llst_list* targetList = myTable->hashTable[hashTableKey];

    //Perform a lookup
    htbl_keyPair* result = _htbl_searchListForKeypair(key,targetList);

    //Check if we actually found something
    if (result == NULL){
        return;
    }

    result->dataValue = data;
}

void htbl_deleteValue(char* key, htbl_table* myTable){
    //Hash the String
    int hashTableKey = htbl_hashString(key,myTable->tableWidth);

    //Get the target list
    llst_list* targetList = myTable->hashTable[hashTableKey];

    //Abuse the internal workings of the linked list to search
    llst_node* working = targetList->head;
    if (working == NULL){
        return;
    }

    //Iterate over the linked list;
    htbl_keyPair* keyPair;
    int index = 0;
    while (1){
        //Fetch the Keypair
        keyPair = (htbl_keyPair*)working->data;

        //If it is a match to the key, return the data
        if (compareString(keyPair->keyValue,key)){
            free(keyPair->keyValue);
            free(keyPair);
            llst_delete(index,targetList);
            myTable->keyCount -= 1;
            break;
        }

        //If it is the last entry, break the loop
        if (working->after == NULL){
            break;
        }
        //Otherwise iterate to next value
        else {
            working = working->after;
        }
    }
}


void htbl_insertValue(char* key, void* value, htbl_table* myTable){
    //Copy the Key
    char* myKey = _htbl_copyString(key);

    //Create the keypair
    htbl_keyPair* newKeypair = (htbl_keyPair*)malloc(sizeof(htbl_keyPair));
    newKeypair->keyValue = myKey;
    newKeypair->dataValue = value;

    //Hash the String
    int hashTableKey = htbl_hashString(myKey,myTable->tableWidth);

    //Get the target list
    llst_list* targetList = myTable->hashTable[hashTableKey];

    //Perform a lookup to ensure that there isn't a collision
    //If no value found, insert it
    if (_htbl_searchListForKeypair(myKey,targetList) == NULL){
        llst_push(newKeypair,targetList);
        myTable->keyCount += 1;
    }
    //Otherwise, do nothing
}

//Empty the dictionary
void htbl_clear(htbl_table* myTable){
    htbl_keyPair* workingPair;
    for (int tableIndex = 0; tableIndex < myTable->tableWidth; tableIndex++){
        for (int listIndex = 0; listIndex < myTable->hashTable[tableIndex]->length; listIndex++){
            workingPair = (htbl_keyPair*)llst_pop(myTable->hashTable[tableIndex]);
            if (workingPair != NULL){
                free(workingPair->keyValue);
                free(workingPair);
            }
        }
    }
}

//Tear down the hashTable
void htbl_destroy(htbl_table* myTable){
    htbl_clear(myTable);

    int oldLength =  myTable->tableWidth;
    for (int tableIndex = 0; tableIndex < oldLength; tableIndex++){
        llst_destroy(myTable->hashTable[tableIndex]);
    }
    free(myTable->hashTable);
    free(myTable);
}


//Duplicate modes with memory safety
//These call "free" on each data pointer
void htbl_setValueSafe(char* key, void* data, htbl_table* myTable){
    //Hash the String
    int hashTableKey = htbl_hashString(key,myTable->tableWidth);

    //Get the target list
    llst_list* targetList = myTable->hashTable[hashTableKey];

    //Perform a lookup
    htbl_keyPair* result = _htbl_searchListForKeypair(key,targetList);

    //Check if we actually found something
    if (result == NULL){
        return;
    }

    free(result->dataValue);
    result->dataValue = data;
}

void htbl_deleteValueSafe(char* key, htbl_table* myTable){
    //Hash the String
    int hashTableKey = htbl_hashString(key,myTable->tableWidth);

    //Get the target list
    llst_list* targetList = myTable->hashTable[hashTableKey];

    //Abuse the internal workings of the linked list to search
    llst_node* working = targetList->head;
    if (working == NULL){
        return;
    }

    //Iterate over the linked list;
    htbl_keyPair* keyPair;
    int index = 0;
    while (1){
        //Fetch the Keypair
        keyPair = (htbl_keyPair*)working->data;

        //If it is a match to the key, return the data
        if (compareString(keyPair->keyValue,key)){
            free(keyPair->keyValue);
            free(keyPair->dataValue);
            free(keyPair);
            llst_delete(index,targetList);
            myTable->keyCount -= 1;
            break;
        }

        //If it is the last entry, break the loop
        if (working->after == NULL){
            break;
        }
        //Otherwise iterate to next value
        else {
            working = working->after;
        }
    }
}

//Empty the dictionary
void htbl_clearSafe(htbl_table* myTable){
    htbl_keyPair* workingPair;
    for (int tableIndex = 0; tableIndex < myTable->tableWidth; tableIndex++){
        for (int listIndex = 0; listIndex < myTable->hashTable[tableIndex]->length; listIndex++){
            workingPair = (htbl_keyPair*)llst_pop(myTable->hashTable[tableIndex]);
            if (workingPair != NULL){
                free(workingPair->keyValue);
                free(workingPair->dataValue);
                free(workingPair);
            }
        }
    }
}

//Tear down the hashTable
void htbl_destroySafe(htbl_table* myTable){
    htbl_clearSafe(myTable);

    for (int tableIndex = 0; tableIndex < myTable->tableWidth; tableIndex++){
        llst_destroy(myTable->hashTable[tableIndex]);
    }
    free(myTable->hashTable);
    free(myTable);
}