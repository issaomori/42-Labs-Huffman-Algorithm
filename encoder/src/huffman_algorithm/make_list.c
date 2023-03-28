#include "encoder.h"

/**
 * It fills the frequency list with the number of times each character appears in the text. Creating a table with the ASCII size, so don't need search, optimizing the execution of the program, because makes direct access in the table.
 */

void	fill_frequency_list()
{
	int i;
	for(i = 0; i < SIZE; i++)
		g_data.frequency_list[i] = 0;
	int j;
	for(j = 0; g_data.txt[j]; j++)
		g_data.frequency_list[g_data.txt[j]]++;
	fill_list();
}

/**
 * It inserts a new node into the linked list of trees in ascending order of frequency
 * 
 * @param new the new node to be inserted
 */
void	insert_sorted(tree *new)
{
	if(g_data.tree_huffman == NULL)
		g_data.tree_huffman = new;
	else if (new->frequency < g_data.tree_huffman->frequency)
	{
		new->next = g_data.tree_huffman;
		g_data.tree_huffman = new;
	}
	else
	{
	tree *temp;
	temp = g_data.tree_huffman;
	while(temp->next && temp->next->frequency <= new->frequency)
		temp = temp->next;
	new->next = temp->next;
	temp->next = new;
	}
	g_data.size_tree++;
}

/**
 * This function creates a new node for each character that appears in the file, and inserts it into a sorted linked list.
 **/
void	fill_list()
{
	for(int i = 0; i < SIZE; i++)
	{
		if(g_data.frequency_list[i] > 0)
		{
			tree *new;
			new = malloc(sizeof(tree));
			if(new)
			{
				new->c = i;
				new->frequency = g_data.frequency_list[i];
				new->right = NULL;
				new->left = NULL;
				new->next = NULL;
				insert_sorted(new);
			}
			else
			{
				printf("Error to alocate memory, when the tree was filled.\n");
				break ;
			}
		}
	}
}
