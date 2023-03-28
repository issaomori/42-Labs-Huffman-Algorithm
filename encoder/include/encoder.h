/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:40:05 by gissao-m          #+#    #+#             */
/*   Updated: 2023/01/15 10:09:10 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCODER_H
# define ENCODER_H

//This is importing the libraries that are needed for the program to run.
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <unistd.h>
# include <locale.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/time.h>
# include <stdbool.h>

//Defining the size of the array, the name of the file and the error of the IPC.
#define SIZE 256
#define FILE_NAME "Makefile"
#define IPC_ERR -1


//Creating a struct called tree_huffman.
typedef struct tree_huffman
{
	unsigned char c;
	int frequency;
	struct tree_huffman *left;
	struct tree_huffman *right;
	struct tree_huffman *next;
}   tree;

//Creating a struct called shared_memory.
typedef struct shared_memory
{
	unsigned char compact_data[10000000];
	int				total_bytes;
	int				compacted_bytes;
	int				time_to_decode;
	long int		tree_serialize[100000];
	int				size_tree;
	int				size_char;
	unsigned char	ret_txt_desc[10000000];
}   shared_memory;

//Creating a struct called encoder, which will be the global variable.
typedef struct encoder
{
	unsigned char	*txt;
	unsigned int	*frequency_list;
	int				size_tree;
	char			**dic;
	unsigned char	*c_encode;
	int				size_char;
	tree			*tree_huffman;
	shared_memory	*sh_mem;

}	encoder;

//Main:
void	checking_arguments(int argc, char **argv);
//Compact:
void	compact();
//Dicionary:
void	make_dicionary();
void	generate_dicionary(tree *parent, char *path);
char	**alloc_dicionary(int height);
//Encode:
char	*encode();
//Make_List:
void	init_list();
void	fill_frequency_list();
void	insert_sorted(tree *node);
void	fill_list();
//Make_tree:
tree	*remove_first_node_tree();
void	build_tree();
void	print_tree(tree *parent, int size);
tree	*make_tree();
int		height_tree(tree *node);
//Read_text:
int		count_txt(char *argv);
void	read_txt();
//Init:
void	init_global(unsigned int *frequency_list);
void	free_all();
//Memory_shared:
void	generate_memory_shared();
// Utils:
char	*str_join(char *s1, char *s2);

extern encoder g_data;
#endif
