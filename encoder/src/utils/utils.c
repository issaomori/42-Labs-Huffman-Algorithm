/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:40:33 by gissao-m          #+#    #+#             */
/*   Updated: 2023/01/15 01:28:31 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It takes two strings, joins them together, and returns the result
 * 
 * @param s1 The first string to be joined.
 * @param s2 The string to be appended to s1.
 * 
 * @return A pointer to a string.
 */
char	*str_join(char *s1, char *s2)
{
	int		count_s1;
	int		count_s2;
	char	*join;
	size_t	lenght;

	count_s1 = -1;
	count_s2 = -1;
	if (s1 == 0 || s2 == 0)
		return (NULL);
	lenght = strlen(s1) + strlen(s2) + 1;
	join = (char *)malloc(lenght);
	if (join == 0)
		return (NULL);
	while (s1[++count_s1] != '\0')
		join[count_s1] = s1[count_s1];
	while (s2[++count_s2] != '\0')
		join[count_s1 + count_s2] = s2[count_s2];
	join[count_s1 + count_s2] = '\0';
	free (s1);
	return (join);
}
