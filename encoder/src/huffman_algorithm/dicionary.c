/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dicionary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:39:27 by gissao-m          #+#    #+#             */
/*   Updated: 2023/01/15 02:07:12 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It allocates memory for the dictionary.
 * 
 * @param height the height of the dictionary
 * 
 * @return A pointer to a pointer to a char.
 */
char	**alloc_dicionary(int height)
{
	char	**dic;

	dic = malloc(sizeof(char *) * SIZE + 1);
	for(int i = 0; i < SIZE; i++)
		dic[i] = calloc(height, sizeof(char));
	return (dic);
	
}

/**
 * It takes a tree and a path, and if the tree is a leaf, it adds the path to the dictionary, otherwise
 * it recursively calls itself on the left and right children, adding a 0 or 1 to the path
 * 
 * @param parent the root of the tree
 * @param path the path to the current node
 * 
 * @return the number of bits that are needed to represent the character.
 */
void	generate_dicionary(tree *parent, char *path)
{
	if (parent->left == NULL && parent->right == NULL)
	{
		g_data.dic[parent->c] = strdup(path);
		return ;
	}
	char *left = strdup(path);
	char *right = strdup(path);
	left = str_join(left, "0");
	right = str_join(right, "1");
	generate_dicionary(parent->left, left);
	generate_dicionary(parent->right, right);
	free(left);
	free(right);
	return ;
}

/**
 * It allocates a dicionary with the size of the height of the tree plus one, and then generates the dicionary
 **/
void	make_dicionary()
{
	g_data.dic = alloc_dicionary(height_tree(g_data.tree_huffman) + 1);
	printf("Generating dicionary...\n");
	generate_dicionary(g_data.tree_huffman, "");
}