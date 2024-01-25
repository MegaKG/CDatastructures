Note:
Requires the LinkedList.h file to function.

All data pointers are expected to be externally managed (created / destroyed) unless otherwise stated.
In other words, bytes at the pointer locations WILL NOT BE copied, only referenced.
The "safe" functions will call free() on the data pointer.

All keys are expected to be null-terminated character arrays.
Hashing is provided by a modified FNV-0 hash function.

Keys are copied by value into local memory and not associated with initial input.


# htbl_table* htbl_newTable(long int tableWidth);
Creates a new HashTable object pointer.
HashTable "Bucket: count can be configured.
More "Buckets" = Faster lookup / less collisions, but uses more memory.


# long int htbl_length(htbl_table* myTable);
Returns the number of keypairs stored in the hashtable,


# void* htbl_getValue(char* key, htbl_table* myTable);
Fetches a data pointer specified by the key.


# void htbl_setValue(char* key, void* data, htbl_table* myTable);
Updates the value of a data pointer specified by a key.
This will not create a new value if the key does not exist.
Old contents will not be freed from memory.


# void htbl_deleteValue(char* key, htbl_table* myTable);
Removes a keypair from the HashTable.
Contents will not be freed from memory.


# void htbl_insertValue(char* key, void* value, htbl_table* myTable);
Adds a new keypair (key and datapointer).
Key is copied into local memory and not associated to the original data.
If the key exists in memory, it is not updated.


# void htbl_clear(htbl_table* myTable);
Deletes all entries in the hashtable.
This will not free the data pointers stored.


# void htbl_destroy(htbl_table* myTable);
Clears the table and deallocates memory.
This will not free the data pointers stored.


# void htbl_setValueSafe(char* key, void* data, htbl_table* myTable);
Updates the value of a data pointer specified by a key.
This will not create a new value if the key does not exist.
free() is called on old data pointer.

# void htbl_deleteValueSafe(char* key, htbl_table* myTable);
Removes a keypair from the HashTable.
free() is called on data pointer.

# void htbl_clearSafe(htbl_table* myTable);
Deletes all entries in the hashtable.
free() is called on all data pointers stored.

# void htbl_destroySafe(htbl_table* myTable);
Clears the table and deallocates memory.
free() is called on all data pointers stored.