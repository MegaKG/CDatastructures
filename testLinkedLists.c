#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include <string.h>


int main(int argc, char** argv){
    //Test the Linked LinkedList
    int tindex = 1;

    //Create a LinkedList
    llst_list* myList = llst_newList();

    //1 Ensure zero length
    if (llst_length(myList) == 0){
        printf("%i Correct Length of Zero\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect Length\n",tindex);
    }
    tindex += 1;

    //2 Attempt get on zero length   
    if (llst_get(0,myList) == NULL){
        printf("%i Correct NULL Return on Zero Length\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect NULL Return on Zero Length\n",tindex);
    }
    tindex += 1;

    //Attempt Push
    llst_push("Hello",myList);

    //3 Ensure Length of 1
    if (llst_length(myList) == 1){
        printf("%i Correct Length of 1 after push\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect Length after push\n",tindex);
    }
    tindex += 1;

    //4 Ensure that I can get the value
    if (strcmp("Hello",llst_get(0,myList)) == 0){
        printf("%i Correct value at index 0 for Hello\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect value at index 0\n",tindex);
        printf("Got %s\n",llst_get(0,myList));
    }
    tindex += 1;

    //Push again
    llst_push("FooBar",myList);

    //5 Ensure Length of 2
    if (llst_length(myList) == 2){
        printf("%i Correct Length of 2 after push\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect Length after push\n",tindex);
    }
    tindex += 1;

    //6 Ensure that I can get the value
    if (strcmp("FooBar",llst_get(0,myList)) == 0){
        printf("%i Correct value at index 0 for FooBar\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect value at index 0\n",tindex);
        printf("Got %s\n",llst_get(0,myList));
    } 
    tindex += 1;  

    //Get End
    //7 Ensure that I can get the value
    if (strcmp("Hello",llst_get(-1,myList)) == 0){
        printf("%i Correct value at index -1 for Hello\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect value at index -1\n",tindex);
        printf("Got %s\n",llst_get(-1,myList));
    }  
    tindex += 1;

    //Append
    llst_append("World",myList);

    //8 Check the length of 3
    if (llst_length(myList) == 3){
        printf("%i Correct Length of 3 after append\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect Length after append\n",tindex);
    }
    tindex += 1;

    //9 Ensure that I can get the value
    if (strcmp("World",llst_get(-1,myList)) == 0){
        printf("%i Correct value at index -1 for World\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect value at index -1\n",tindex);
        printf("Got %s\n",llst_get(-1,myList));
    }  
    tindex += 1;

    //Check middle value
    //10 Ensure that I can get the value
    if (strcmp("Hello",llst_get(-2,myList)) == 0){
        printf("%i Correct value at index -2 for Hello\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect value at index -2\n",tindex);
        printf("Got %s\n",llst_get(-1,myList));
    }  
    tindex += 1;

    //11 Check pop function
    char* popped = llst_pop(myList);
    if (strcmp("FooBar",popped) == 0){
        printf("%i Correct value popped for FooBar\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect value popped\n",tindex);
        printf("Got %s\n",popped);
    }  
    tindex += 1;

    //Insert at second position (1)
    llst_insertAt(1, "123",myList);

    //12 Ensure that I can get the value
    if (strcmp("123",llst_get(1,myList)) == 0){
        printf("%i Correct value at index 1 for 123\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect value at index 1\n",tindex);
        printf("Got %s\n",llst_get(1,myList));
    }  
    tindex += 1;

    //Insert at second position (1)
    llst_insertAt(-2, "456",myList);

    //13 Ensure that I can get the value
    if (strcmp("456",llst_get(-2,myList)) == 0){
        printf("%i Correct value at index -2 for 456\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect value at index -2\n",tindex);
        printf("Got %s\n",llst_get(-2,myList));
    }  
    tindex += 1;

    //14 Attempt Dequeue
    char* dequeued = llst_dequeue(myList);
    if (strcmp("World",dequeued) == 0){
        printf("%i Correct value dequeued for World\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect value dequeued\n",tindex);
        printf("Got %s\n",dequeued);
    }  
    tindex += 1;

    //Delete item at position 1
    llst_delete(1,myList);

    //15 Check both sides
    if ((strcmp("Hello",llst_get(0,myList)) == 0) && (strcmp("456",llst_get(1,myList)) == 0)){
        printf("%i Correct values after delete\n",tindex);
    }
    else {
        printf("%i ** Error,  Incorrect value after delete\n",tindex);
        printf("Got %s\n",llst_get(-2,myList));
    }  
    tindex += 1;

    //Destroy the List
    llst_clear(myList);
    printf("%i Cleared Lists\n",tindex);
    tindex += 1;

    llst_destroy(myList);
    printf("%i Cleaned up success\n",tindex);
}