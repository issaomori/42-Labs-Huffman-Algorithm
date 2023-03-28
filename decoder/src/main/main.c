#include "decoder.h"

/**
 * It returns the current time in milliseconds
 * 
 * @return The time in milliseconds.
 */
static int long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	printf("Initialization of Decoder!\n");
	setlocale(LC_ALL, "C.UTF-8");
	shared_memory *block_mem = attach_memory_block(FILE_NAME, sizeof(shared_memory));
	if (block_mem == NULL)
	{
		printf("Error in the process of reading the shared memory\n");
		exit(3);
	}
	int size_char = block_mem->size_char;
	int i = 0;
	tree *tree_huffman = deserialize_tree(block_mem->tree_serialize, &i);
	int initial = get_time();
	block_mem->compacted_bytes = descompacted(tree_huffman, block_mem);
	int final = get_time();
	block_mem->time_to_decode = final - initial;
	block_mem->size_char = size_char;
	detach_memory_block(block_mem);
	printf("Decoder Finished! Look at the other terminal!\n");
	return (0);
}
