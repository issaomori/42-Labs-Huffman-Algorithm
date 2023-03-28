/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:40:17 by gissao-m          #+#    #+#             */
/*   Updated: 2023/01/15 01:15:37 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It initializes the global data structure
 * 
 * @param frequency_list This is the array of frequencies that we will be using to generate the sound.
 */
void    init_global(unsigned int *frequency_list)
{
	bzero(&g_data, 1);
	g_data.txt = strdup("");
	g_data.frequency_list = calloc(sizeof (unsigned int), SIZE);
	g_data.sh_mem = calloc(sizeof(shared_memory), 1);
	bzero(g_data.sh_mem, sizeof(shared_memory));
	bzero(g_data.frequency_list, SIZE);
}

/**
 * It initializes the global variable g_data.tree_huffman to NULL, initializes the global variable
 * g_data.size_tree to 0, and calls the function fill_frequency_list().
 */
void	init_list()
{
	g_data.tree_huffman = NULL;
	g_data.size_tree = 0;
	fill_frequency_list();
}

/**
 * It frees the memory allocated to the matrix
 * 
 * @param s The matrix to be freed.
 */
void	free_matrix(char **s)
{
	int	count;

	count = 0;
	while (count < SIZE)
	{
		if(s[count])
			free(s[count++]);
	}
	free(s);
}

/**
 * It frees the memory allocated for the tree.
 * 
 * @param root the root of the tree
 * 
 * @return The root of the tree.
 */
void    freeTree(tree* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

/**
 * It frees all the memory allocated in the program
 */
void	free_all()
{
	int i = 0;
	if (g_data.dic)
		free_matrix(g_data.dic);
	if (g_data.txt)
		free(g_data.txt);
	if (g_data.frequency_list)
		free(g_data.frequency_list);
	if (g_data.c_encode != NULL)
		free(g_data.c_encode);
	if(g_data.tree_huffman != NULL)
		freeTree(g_data.tree_huffman);
}