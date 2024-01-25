#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"
#include <string.h>
#include <time.h>

#define maxSize 1000
#define maxVals 20000L
#define maxIntSize 10

double timeAccess(htbl_table* myTable, char* key){
    clock_t start = clock();

    char* retval = htbl_getValue(key,myTable);
    //printf("Got Value\n");

    clock_t end = clock();
    clock_t cTaken = end - start;

    if (retval == NULL){
        printf("Error, null return for %s!\n",key);
    }
    else { 
        if (strcmp(key, retval) != 0){
            printf("Error, strings do not match for %s %s!\n",key,retval);
        }
    }

    return ((double)cTaken) / CLOCKS_PER_SEC;
}

void benchmarkDictSize(long int tsize, long int values){
    //Create a HashTable
    htbl_table* myTable = htbl_newTable(tsize);

    double min;
    double max;
    double avg = 0;

    for (long int index = 0; index < values; index++){
        char* stringBuffer = (char*)malloc(sizeof(char)*maxIntSize);
        char* dataBuffer = (char*)malloc(sizeof(char)*maxIntSize);
        memset(stringBuffer,'\x00',maxIntSize);
        snprintf(stringBuffer, maxIntSize, "%li", index);
        memcpy(dataBuffer, stringBuffer, maxIntSize);
        //printf("%s %s\n",stringBuffer,dataBuffer);

        htbl_insertValue(stringBuffer,dataBuffer,myTable);
        free(stringBuffer);
    }
    //printf("Allocate\n");

    //Initialise the min and max variables
    min = timeAccess(myTable, "0");
    max = min;
    //printf("Min Max\n");

    //Now try to access them
    double accessTime;
    for (long int index = 0; index < values; index++){
        char* stringBuffer = (char*)malloc(sizeof(char)*maxIntSize);
        memset(stringBuffer,'\x00',maxIntSize);
        snprintf(stringBuffer, maxIntSize, "%li", index);
        
        accessTime = timeAccess(myTable, stringBuffer);
        if (accessTime < min){
            min = accessTime;
        }
        if (accessTime > max){
            max = accessTime;
        }
        avg += accessTime;
        free(stringBuffer);
    }

    avg = avg / values;
    printf("Table: %i Size: %i Min: %.10lf Max %.10lf Avg %.10lf\n",tsize,values,min,max,avg);
    


    htbl_destroySafe(myTable);
}

int main(int argc, char** argv){
    for (long int size = 1; size < maxSize; size = size * 2){
        for (long int valcount = size; valcount < maxVals; valcount = valcount * 2){
            benchmarkDictSize(size,valcount);
        }
            
    }
}