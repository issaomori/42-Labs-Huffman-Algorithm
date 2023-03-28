/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:39:40 by gissao-m          #+#    #+#             */
/*   Updated: 2023/01/15 02:17:15 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It removes the first node of the tree.
 * 
 * @return The first node of the tree.
 */
tree *remove_first_node_init()
{
	tree *temp = NULL;

	if(g_data.tree_huffman)
	{
		temp = g_data.tree_huffman;
		g_data.tree_huffman = temp->next;
		temp->next = NULL;
		g_data.size_tree--;
	}
	return (temp);
}

/**
 * It removes the first two nodes from the tree, creates a new node with the sum of the frequencies of
 * the two nodes, and inserts the new node into the tree
 * 
 * @return The tree is being returned.
 */
tree *make_tree()
{
	tree *first, *second, *new;
	printf("Generating tree...\n");
	while(g_data.size_tree > 1)
	{
		first = remove_first_node_init();
		second = remove_first_node_init();
		new = malloc(sizeof(tree));
		if(new)
		{
			new->c = '+';
			new->frequency = first->frequency + second->frequency;
			new->left = first;
			new->right = second;
			new->next = NULL;
			insert_sorted(new);
		}
		else
		{
			printf("Error to alocate memory, when building the tree.\n");
			break ;
		}
	}
	return (g_data.tree_huffman);
}

/**
 * If the parent is NULL, return -1, otherwise return the height of the left subtree plus 1 if it's
 * greater than the height of the right subtree plus 1, otherwise return the height of the right
 * subtree plus 1
 * 
 * @param parent the parent node of the tree
 * 
 * @return The height of the tree.
 */
int	height_tree(tree *parent)
{
	if(parent == NULL)
		return (-1);
	else
	{
		int left, right;
		left = height_tree(parent->left) + 1;
		right = height_tree(parent->right) + 1;
		if(left > right)
			return left;
		else
			return right;
	}
}
