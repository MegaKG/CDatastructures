#include <stdio.h>
#include <stdlib.h>


typedef struct llst_listNodeStruct {
    struct llst_listNodeStruct* before;
    struct llst_listNodeStruct* after;

    void* data;

} llst_node;

typedef struct llst_listStruct {
    llst_node* head;
    llst_node* tail;

    long int length;
} llst_list;


//Make a new node and configure it
llst_node* _llst_newNode(void* dataPtr, llst_node* before, llst_node* after){
    llst_node* newNode = (llst_node*)malloc(sizeof(llst_node));
    newNode->before = before;
    newNode->after = after;

    newNode->data = dataPtr;

    return newNode;
}

//Place a node after another
void _llst_appendNodeToNode(llst_node* after, llst_node* head){
    head->after = after;
    after->before = head;
}

//Place a node before another
void _llst_pushNodeToNode(llst_node* before, llst_node* head){
    head->before = before;
    before->after = head;
}

//Insert a node iterating forward
void _llst_insertAtDepthFwd(llst_node* toInsert, llst_node* head, long int position){
    llst_node* working = head;
    for (long int index = 0; index < position; index++){
        if (working == NULL){
            return;
        }

        working = working->after;
    }

    llst_node* beforeInsert = working->before;
    llst_node* afterInsert = working; 

    //Stitch it together
    beforeInsert->after = toInsert;
    afterInsert->before = toInsert;
    toInsert->before = beforeInsert;
    toInsert->after = afterInsert;
}

//Insert a node iterating backward
void _llst_insertAtDepthRev(llst_node* toInsert, llst_node* tail, long int position){
    llst_node* working = tail;
    for (long int index = -1; index >= position; index--){
        if (working == NULL){
            return;
        }
        working = working->before;
    }

    llst_node* beforeInsert = working->before;
    llst_node* afterInsert = working; 

    //Stitch it together
    beforeInsert->after = toInsert;
    afterInsert->before = toInsert;
    toInsert->before = beforeInsert;
    toInsert->after = afterInsert;
}

//Get a node iterating forward
llst_node* _llst_getFwd(llst_node* head, long int position){
    llst_node* working = head;
    for (long int index = 0; index < position; index++){
        if (working == NULL){
            return NULL;
        }
        working = working->after;
    }

    return working;
}

//Get a node iterating backward
llst_node* _llst_getRev(llst_node* tail, long int position){
    llst_node* working = tail;
    for (long int index = -1; index >= position+1; index--){
        working = working->before;
    };

    return working;
}

//Get a value iterating forward
void* _llst_getValueFwd(llst_node* head, long int position){
    return _llst_getFwd(head,position)->data;
}



//Get a value iterating backward
void* _llst_getValueRev(llst_node* tail, long int position){
    return _llst_getRev(tail,position)->data;
}


//Make a new Linked List 
llst_list* llst_newList(){
    llst_list* newList = (llst_list*)malloc(sizeof(llst_list));

    newList->length = 0;
    newList->head = NULL;
    newList->tail = NULL;

    return newList;
}

//Append to the end of the list
void llst_append(void* data, llst_list* myList){
    if (myList->length == 0){
        llst_node* firstNode = _llst_newNode(data,NULL,NULL);
        myList->head = firstNode;
        myList->tail = firstNode;
        myList->length = 1;
    }
    else {
        llst_node* newNode = _llst_newNode(data,NULL,NULL);
        _llst_appendNodeToNode(newNode,myList->tail);
        myList->tail = newNode;
        myList->length += 1;
    }
}

//Push to the start of the list
void llst_push(void* data, llst_list* myList){
    if (myList->length == 0){
        llst_node* firstNode = _llst_newNode(data,NULL,NULL);
        myList->head = firstNode;
        myList->tail = firstNode;
        myList->length = 1;
    }
    else {
        llst_node* newNode = _llst_newNode(data,NULL,NULL);
        _llst_pushNodeToNode(newNode,myList->head);
        myList->head = newNode;
        myList->length += 1;
    }
}

//absolute value integer
long int _llst_abs(long int input){
    return (input < 0) ? input*-1: input;
}

//determine closest circular index
long int _llst_getClosestIndex(long int index, long int length){
    //Determine the closest point
    long int realIndex = index;
    
    //If Reverse Index
    if (index < 0){
        if ((length + index) < _llst_abs(index)){
            realIndex = length + index;
        }
    }
    //If Forward index
    else {
        if (_llst_abs(index-length) < index){
            realIndex = index - length;
        }
    }

    return realIndex;
}

//Get value at position
void* llst_get(long int index, llst_list* myList){
    if (myList->length == 0){
        return NULL;
    }

    long int closestIndex = _llst_getClosestIndex(index,myList->length);

    if (closestIndex < 0){
        return _llst_getValueRev(myList->tail, closestIndex);
    }
    else {
        return _llst_getValueFwd(myList->head, closestIndex);
    }
}

long int llst_length(llst_list* myList){
    return myList->length;
}

//Insert into the linked list - will place data at the exact place mentioned
void llst_insertAt(long int index, void* data, llst_list* myList){
    if (myList->length == 0){
        llst_node* firstNode = _llst_newNode(data,NULL,NULL);
        myList->head = firstNode;
        myList->tail = firstNode;
        myList->length = 1;
    }
    else {
        if (index < 0){
            //Get the node to insert after
            if (index == -1){
                llst_append(data,myList);
            }
            else {
                //Get the node to insert after
                llst_node* toInsertAfter = _llst_getRev(myList->head,index);
                
                //Stitch it
                llst_node* newNode = _llst_newNode(data,NULL,NULL);
                llst_node* evenAfterThat = toInsertAfter->after;

                evenAfterThat->before = newNode;
                newNode->after = evenAfterThat;
                toInsertAfter->after = newNode;
                newNode->before = toInsertAfter;

                myList->length += 1;

            }
            
        }
        else {
            if (index == 0){
                llst_push(data,myList);
            }
            else {
                //Get the node to insert before
                llst_node* toInsertBefore = _llst_getFwd(myList->head,index);

                //Stitch it
                llst_node* newNode = _llst_newNode(data,NULL,NULL);
                llst_node* evenBeforeThat = toInsertBefore->before;
                
                evenBeforeThat->after = newNode;
                newNode->before = evenBeforeThat;
                toInsertBefore->before = newNode;
                newNode->after = toInsertBefore;

                myList->length += 1;
                
            }
            

        }
    }
    
}



//Pop the first element
void* llst_pop(llst_list* myList){
    if (myList->length == 0){
        return NULL;
    }

    llst_node* first = myList->head;
    llst_node* next = first->after;
    void* toReturn = first->data;
    free(first);
    myList->head = next;
    myList->length -= 1;
    return toReturn;
}

//Dequeue the last element
void* llst_dequeue(llst_list* myList){
    if (myList->length == 0){
        return NULL;
    }

    llst_node* last = myList->tail;
    llst_node* next = last->before;
    void* toReturn = last->data;
    free(last);
    myList->tail = next;
    myList->length -= 1;
    return toReturn;
}


//Delete from the linked list - will delete the exact element listed
void llst_delete(long int index, llst_list* myList){
    if (myList->length == 0){
        return;
    }
    else {
        long int closestIndex = _llst_getClosestIndex(index,myList->length);

        llst_node* toDelete = NULL;
        if (closestIndex == -1){
               llst_dequeue(myList);
        }
        else if (closestIndex == 0){
                llst_pop(myList);
        }
        else {
            if (closestIndex < 0){
                //Get the node to insert after
                toDelete = _llst_getRev(myList->head,closestIndex);
            }
            else {
                //Get the node to insert before
                toDelete = _llst_getFwd(myList->head,closestIndex);                
            }

            //Stitch it
            llst_node* before = toDelete->before;
            llst_node* after = toDelete->after;

            before->after = after;
            after->before = before;

            free(toDelete);
            myList->length -= 1;
        }
    }
    
}

//Clear a list
void llst_clear(llst_list* myList){
    long int oldLength = myList->length;
    for (long int index = 0; index < oldLength; index++){
        llst_pop(myList);
    }
}

//Tear down
void llst_destroy(llst_list* myList){
    llst_clear(myList);
    //printf("Kill %p\n",myList);
    free(myList); //This is an issue
}

//The memory safe variants of the above delete statements.
//These will deallocate the data pointer as well
//Pop the first element
void* llst_popSafe(llst_list* myList){
    if (myList->length == 0){
        return NULL;
    }

    llst_node* first = myList->head;
    llst_node* next = first->after;
    void* toReturn = first->data;
    free(first->data);
    free(first);
    myList->head = next;
    myList->length -= 1;
    return toReturn;
}

//Dequeue the last element
void* llst_dequeueSafe(llst_list* myList){
    if (myList->length == 0){
        return NULL;
    }

    llst_node* last = myList->tail;
    llst_node* next = last->before;
    void* toReturn = last->data;
    free(last->data);
    free(last);
    myList->tail = next;
    myList->length -= 1;
    return toReturn;
}


//Delete from the linked list - will delete the exact element listed
void llst_deleteSafe(long int index, llst_list* myList){
    if (myList->length == 0){
        return;
    }
    else {
        long int closestIndex = _llst_getClosestIndex(index,myList->length);

        llst_node* toDelete = NULL;
        if (closestIndex == -1){
               llst_dequeueSafe(myList);
        }
        else if (closestIndex == 0){
                llst_popSafe(myList);
        }
        else {
            if (closestIndex < 0){
                //Get the node to insert after
                toDelete = _llst_getRev(myList->head,closestIndex);
            }
            else {
                //Get the node to insert before
                toDelete = _llst_getFwd(myList->head,closestIndex);                
            }

            //Stitch it
            llst_node* before = toDelete->before;
            llst_node* after = toDelete->after;

            before->after = after;
            after->before = before;

            free(toDelete->data);
            free(toDelete);
            myList->length -= 1;
        }
    }
    
}

//Clear a list
void llst_clearSafe(llst_list* myList){
    long int oldLength = myList->length;
    for (long int index = 0; index < oldLength; index++){
        llst_popSafe(myList);
    }
}

//Tear down
void llst_destroySafe(llst_list* myList){
    llst_clearSafe(myList);
    free(myList);
}
