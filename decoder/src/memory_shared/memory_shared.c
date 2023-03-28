#include "decoder.h"

/**
 * It takes a file and a size, and returns a shared memory block
 * 
 * @param file The file name to use for the key.
 * @param size The size of the shared memory block.
 * 
 * @return The shared memory id.
 */
int take_shared_block(char *file, int size)
{
	key_t key;

	key = ftok(file, 23);
	if (key == IPC_ERR)
		return (IPC_ERR);
	 return (shmget(key, size, 0666 | IPC_CREAT));
}

/**
 * It creates a shared memory block and returns a pointer to it
 * 
 * @param file the name of the file that will be used to create the shared memory block.
 * @param size the size of the shared memory block
 * 
 * @return A pointer to a shared_memory struct.
 */
shared_memory *attach_memory_block(char *file, int size)
{
	int shared_block_id = take_shared_block(file, size);
	if (shared_block_id == IPC_ERR)
	{
		printf ("Error: to creating shared memory IPC\n");
		exit(3);
	}
	shared_memory *result;
	result = (shared_memory *) shmat(shared_block_id, (void*)0, 0);
	if (!result)
	{
		printf("Error: Error: to creating shared memory SHMAT");
		exit(3);
	}
	return (result);
}

/**
 * Detach_memory_block() detaches a shared memory block from the current process
 * 
 * @param block The shared memory block to detach.
 * 
 * @return A boolean value.
 */
bool detach_memory_block(shared_memory *block)
{
	return shmdt(block) != IPC_ERR;
}

/**
 * It takes a file name, and destroys the shared memory block associated with it
 * 
 * @param file the name of the file to use as a key.
 * 
 * @return A boolean value.
 */
bool    memory_destroy(char *file)
{
	int id_sh_block;

	id_sh_block = take_shared_block(file, 0);
	if (id_sh_block == IPC_ERR)
		return (NULL);
	return (shmctl(id_sh_block, IPC_RMID, NULL) != IPC_ERR);
}

/**
 * The function deserialize_tree() takes an array of integers and an index as input. It returns a
 * pointer to the root of the tree
 * 
 * @param arr The array of long ints that represent the tree.
 * @param index This is the index of the array that we are currently at.
 * 
 * @return The root of the tree.
 */
tree *deserialize_tree(long int *arr, int *index)
{
	tree *parent;
	if(arr[(*index)] == -1)
	{
		(*index)++;
		return (NULL);
	}
	parent = (tree *) malloc(sizeof(tree));
	parent->c = arr[(*index)++];
	parent->left = deserialize_tree(arr, index);
	parent->right = deserialize_tree(arr, index);
	parent->next = deserialize_tree(arr, index);
	return (parent);
}
