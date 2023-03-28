#include "decoder.h"

/**
 * It checks if the bit at the position str_psc is set in the byte.
 * 
 * @param byte the byte to check
 * @param str_psc The bit position in the byte to be checked.
 * 
 * @return The value of the bit at the position of str_psc in byte.
 */
static unsigned int is_bit(unsigned char byte, int str_psc)
{
	unsigned char mask = (1 << str_psc);
	return (byte & mask);
}

/**
 * It takes a tree and a shared memory block and returns the number of bytes read from the compacted
 * data
 * 
 * @param node the root of the tree
 * @param block is a pointer to a shared_memory struct.
 * 
 * @return The number of bytes read.
 */
int	descompacted(tree *node, shared_memory *block)
{
	tree *temp;
	unsigned char byte = 0;
	int i = 0, dec_i = 0, c_i = 0;

	temp = node;
	while(block->size_char > -1)
	{
		byte = block->compact_data[c_i];
		for(int i = 7; i>= 0; i--)
		{
			if (is_bit(byte, i))
				temp = temp->right;
			else
				temp = temp->left;
			if (temp->left == NULL && temp->right == NULL)
			{
				if (block->size_char < 1)
				{
					return (c_i);
				}
				block->ret_txt_desc[dec_i++] = temp->c;
				temp = node;
				block->size_char--;
			}
		}
		c_i++;
	}
	return(c_i);
}
