Note:
All data pointers are expected to be externally managed (created / destroyed) unless otherwise stated.
In other words, bytes at the pointer locations WILL NOT BE copied, only referenced.
The "safe" functions will call free() on the data pointer.

Array indexing works for both positive and negative indexes.
Iterating positively, 0 maps to the first element, 1 to the seconds etc....
By using negative indexes, data can be accessed from the end of the list.
In this case, iterating negatively, -1 maps to the last element, -2 maps to the second-last etc...

When accessing a value, the get functions will automatically determine which end of the array is closest to the index before iterating.


# llst_list* llst_newList();
Creates a new linked list and returns a pointer object.


# void llst_append(void* data, llst_list* myList);
Appends a pointer to the end of the list.
Data is inserted at index after last element. 

# void llst_push(void* data, llst_list* myList);
Places a new data pointer at the beginning of the list.
Data is inserted at the zero position.


# void* llst_get(long int index, llst_list* myList);
Gets a value at a specific position.
Zero and positive indexes start from the beginning of the array.
Negative index will work back from the end of the array.
Function is optimised to determine closest list entry point.


# long int llst_length(llst_list* myList);
Returns the apparent length of the list.


# void llst_insertAt(long int index, void* data, llst_list* myList);
Places a new pointer at the exact index such that calling "get" will return its value.
For positive indexes, this is before the existing data.
For negative indexes, this is after the existing data.


# void* llst_pop(llst_list* myList);
Will return the first (index=0) data pointer, then remove it from the array.
This function will not call free() on the data pointer.


# void* llst_dequeue(llst_list* myList);
Will return the last (index=-1) data pointer, then remove it from the array.
This function will not call free() on the data pointer.


# void llst_delete(long int index, llst_list* myList);
Deletes an element at a specific index. 
This function will not call free() on the data pointer.


# void llst_clear(llst_list* myList);
Erases every element in the list and returns it to zero length.
This function will not call free() on the data pointers.


# void llst_destroy(llst_list* myList);
Erases every existing element in the list, then deallocates the memory held by the list.
This function will not call free() on the data pointers.


# void* llst_popSafe(llst_list* myList);
Will return the first (index=0) data pointer, then remove it from the array.
The memory for the data pointer is cleared with free().


# void* llst_dequeueSafe(llst_list* myList);
Will return the last (index=-1) data pointer, then remove it from the array.
The memory for the data pointer is cleared with free().


# void llst_deleteSafe(long int index, llst_list* myList);
Deletes an element at a specific index. 
The memory for the data pointer is cleared with free().


# void llst_clearSafe(llst_list* myList);
Erases every element in the list and returns it to zero length.
The memory allocations for all data pointers are cleared with free().


# void llst_destroySafe(llst_list* myList);
Erases every existing element in the list, then deallocates the memory held by the list.
The memory allocations for all data pointers are cleared with free().