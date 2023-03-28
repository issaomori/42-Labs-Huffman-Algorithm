#include "encoder.h"

/**
 * It takes a file and a size, and returns a shared memory block
 * 
 * @param file The file that will be used to generate the key.
 * @param size The size of the shared memory block.
 * 
 * @return The return value is the shared memory id.
 */
int take_shared_block(char *file, int size)
{
	key_t key;

	key = ftok(file, 23);
	if (key == IPC_ERR)
		return (IPC_ERR);
	 return (shmget(key, size, 0644 | IPC_CREAT));
}

/**
 * It creates a shared memory block and returns a pointer to it
 * 
 * @param file the name of the file that will be used to create the shared memory block.
 * @param size the size of the shared memory block
 * 
 * @return A pointer to a shared memory block.
 */
shared_memory *attach_memory_block(char *file, int size)
{
	int id_block_sh = take_shared_block(file, size);
	if (id_block_sh == IPC_ERR)
	{
		printf ("Error: to creating shared memory IPC\n");
		exit(3);
	}
	shared_memory *result;
	result = (shared_memory *) shmat(id_block_sh, (void*)0, 0);
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
 * It prints the result of the decoder.
 * 
 * @param block is the shared memory block
 */
void    print_return_descompact(shared_memory *block)
{
	printf("\t\tText Result of Decoder:\n%s", block->ret_txt_desc);
	printf("\n\n");
	printf("Total bytes of Text Original: %d bytes\n", g_data.size_char);
	printf("Text compacted: %d bytes\n", block->compacted_bytes);
	printf("Text descompacted: %d bytes\n", block->size_char);
	printf("Time to descompact: %d ms\n", block->time_to_decode);
	printf("Compact to: %.2f%% of Text Original\n", (float)(block->compacted_bytes*100/(float)g_data.size_char));
}

/**
 * It takes a tree and an array and an index and it puts the tree into the array at the index
 * 
 * @param parent The root of the tree to be serialized.
 * @param arr The array in which the tree is to be serealized.
 * @param index This is the index of the array where the next character will be stored.
 * 
 * @return a pointer to the root of the tree.
 */
void    serealize_tree(tree *parent, long int *arr, int *index)
{
	if(!parent)
	{
		arr[(*index)++] = -1;
		return;
	}
	arr[(*index)++] = parent->c;
	serealize_tree(parent->left, arr, index);
	serealize_tree(parent->right, arr, index);
	serealize_tree(parent->next, arr, index);
}

/**
 * It creates a shared memory block, serializes the tree, copies the compacted data and waits for the
 * decoder to finish
 */
void    generate_memory_shared()
{
	int i;
	int j;

	printf("Encoder Finished! Room decoder...\n");
	shared_memory *block_mem = (shared_memory*)attach_memory_block(FILE_NAME, sizeof(shared_memory) + (256*256) + 10000000);
	bzero(block_mem, sizeof(shared_memory));
	j = 0;
	serealize_tree(g_data.tree_huffman, block_mem->tree_serialize, &j);
	for (i = 0; i < g_data.sh_mem->compacted_bytes;i++)
		block_mem->compact_data[i] = g_data.sh_mem->compact_data[i];
	block_mem->time_to_decode = -1;
	block_mem->total_bytes = g_data.sh_mem->total_bytes;
	block_mem->size_tree = g_data.size_tree;
	block_mem->size_char = g_data.size_char;
	block_mem->compacted_bytes = g_data.sh_mem->compacted_bytes;

	while (block_mem->time_to_decode == -1);
	print_return_descompact(block_mem);
	detach_memory_block(block_mem);
	memory_destroy(FILE_NAME);
}
