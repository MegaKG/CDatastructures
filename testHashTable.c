#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"
#include <string.h>



int main(int argc, char** argv){
    //Test the Linked LinkedList
    int tindex = 1;

    //Create a LinkedList
    htbl_table* myTable = htbl_newTable(4);

    //1 Ensure zero length
    if (htbl_length(myTable) == 0){
        printf("%i Correct Length of Zero\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect Length\n",tindex);
    }
    tindex += 1;

    //2 Attempt get on zero length of bad key  
    if (htbl_getValue("abc",myTable) == NULL){
        printf("%i Correct NULL Return on Zero Length\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect NULL Return on Zero Length\n",tindex);
    }
    tindex += 1;

    //Attempt Insert
    htbl_insertValue("Hello","World",myTable);

    //3 Ensure Length of 1
    if (htbl_length(myTable) == 1){
        printf("%i Correct Length of 1 after insert\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect Length after insert\n",tindex);
    }
    tindex += 1;

    //4 Ensure that I can get the value
    if (strcmp("World",htbl_getValue("Hello",myTable)) == 0){
        printf("%i Correct value at index Hello for World\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect value at index Hello\n",tindex);
        printf("Got %s\n",htbl_getValue("Hello",myTable));
    }
    tindex += 1;

    //Insert again
    htbl_insertValue("Testing","123",myTable);

    //5 Ensure Length of 2
    if (htbl_length(myTable) == 2){
        printf("%i Correct Length of 2 after insert\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect Length after insert\n",tindex);
    }
    tindex += 1;

    //6 Ensure that I can get the value
    if (strcmp("123",htbl_getValue("Testing",myTable)) == 0){
        printf("%i Correct value at index Testing for 123\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect value at index Testing\n",tindex);
        printf("Got %s\n",htbl_getValue("Testing",myTable));
    } 
    tindex += 1;  

    //Get End
    //7 Ensure that I can get the value
    if (strcmp("World",htbl_getValue("Hello",myTable)) == 0){
        printf("%i Correct value at index Hello for World\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect value at index Hello\n",tindex);
        printf("Got %s\n",htbl_getValue("Hello",myTable));
    }
    tindex += 1;

    //Set a value
    htbl_setValue("Hello","Goodbye",myTable);

    //8 Ensure that value is correct
    if (strcmp("Goodbye",htbl_getValue("Hello",myTable)) == 0){
        printf("%i Correct value at index Hello for Goodbye\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect value at index Hello\n",tindex);
        printf("Got %s\n",htbl_getValue("Hello",myTable));
    }
    tindex += 1;

    //Delete item at position 1
    htbl_deleteValue("Testing",myTable);

    //9 Check the value is deleted
    if (htbl_getValue("Testing",myTable) == NULL){
        printf("%i Correctly Deleted Testing\n",tindex);
    }
    else {
        printf("%i ** Error, Failed to delete value Testing\n",tindex);
    }
    tindex += 1;

    //10 Check the length
    if (htbl_length(myTable) == 1){
        printf("%i Correct Length of 1 after delete\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect Length after delete\n",tindex);
    }
    tindex += 1;

    //Destroy the List
    htbl_clear(myTable);
    printf("%i Cleared the table\n",tindex);
    tindex += 1;

    htbl_destroy(myTable);
    printf("%i Cleaned up success\n",tindex);
}