/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:39:07 by gissao-m          #+#    #+#             */
/*   Updated: 2023/01/15 01:16:51 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It calculates the size of the string that will be returned by the function
 * 
 * @return The size of the string that will be returned.
 */
static int    calculate_size_str()
{
    int    i, size = 0;

    for (i = 0; g_data.txt[i]; i++)
        size+= strlen(g_data.dic[(int)g_data.txt[i]]);
    return (size + 1);
} 

/**
 * It takes the dictionary and the text and generates the encoded string
 * 
 * @return The encoded string.
 */
char	*encode()
{
	int size = calculate_size_str(g_data.dic, g_data.txt);
	g_data.c_encode = calloc(size, sizeof(char));
	int i = 0;

	printf("Generating Encode...\n");
	while(g_data.txt[i] != '\0')
	{
		strcat(g_data.c_encode, g_data.dic[(int)g_data.txt[i]]);
		i++;
	}
	return (g_data.c_encode);
}
