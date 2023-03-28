#ifndef DECODER_H
# define DECODER_H

//This is importing the libraries that are needed for the program to run.
# include <stdio.h>
# include <stdlib.h>
# include <string.h> 
# include <unistd.h>
# include <locale.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/time.h>
# include <stdbool.h>

//This is defining the file name and the IPC error.
#define FILE_NAME "Makefile"
#define IPC_ERR -1

//This is creating a binary tree, struct.
typedef struct tree_huffman
{
    unsigned char c;
    int frequency;
    struct tree_huffman *left;
    struct tree_huffman *right;
    struct tree_huffman *next;
}   tree;

//This is creating a struct for memory shared.
typedef struct shared_memory
{
    unsigned char compact_data[10000000];
    int total_bytes;
    int compacted_bytes;
    int time_to_decode;
    long int tree_serialize[100000];
    int size_tree;
    int size_char;
    unsigned char ret_txt_desc[10000000];
}   shared_memory;

//Descompact:
int	descompacted(tree *node, shared_memory *block);
//Make_Tree:
tree *deserialize_tree(long int *arr, int *index);
//Shared_Memory:
shared_memory *attach_memory_block(char *file, int size);
bool detach_memory_block(shared_memory *block);

#endif