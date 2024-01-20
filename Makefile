$(CC) = gcc
all:
	$(CC) testLinkedLists.c -O3 -o lltests
	$(CC) testHashTable.c -O3 -o httests
