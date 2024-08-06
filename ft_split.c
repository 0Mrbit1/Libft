/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <acharik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 06:49:49 by acharik           #+#    #+#             */
/*   Updated: 2024/08/06 06:50:48 by acharik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	is_delimiter(char c, char *delimiters)
{
	int	i;

	i = 0;
	while (delimiters[i])
	{
		if (c == delimiters[i])
			return (1);
		i++;
	}
	return (0);
}

static int	words_count(char *str, char *delimiters)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (is_delimiter(str[i], delimiters))
		i++;
	while (str[i])
	{
		if (is_delimiter(str[i], delimiters) || !str[i + 1])
		{
			while (is_delimiter(str[i], delimiters))
				i++;
			words++;
		}
		i++;
	}
	return (words);
}

static void	store_data(char **dest, char *src, int str_size, char *delimiters)
{
	*dest = malloc(sizeof(char) * (str_size + 1));
	ft_memmove(*dest, src, str_size);
	(*dest)[str_size] = '\0';
}

char	**ft_split(char *str, char *delimiters)
{
	int		i;
	int		j;
	int		str_size;
	int		start;
	char	**split;

	i = 0;
	j = 0;
	split = malloc(sizeof(char *) * (words_count(str, delimiters) + 1));
	start = skip_delimiters(str, i, delimiters);
	while (str[i])
	{
		if (is_delimiter(str[i], delimiters))
		{
			str_size = i - start;
			store_data(&(split[j]), &(str[start]), str_size, delimiters);
			j++;
			start = skip_delimiters(str, i, delimiters);
		}
		i++;
	}
	str_size = i - start;
	store_data(&(split[j++]), &(str[start]), str_size, delimiters);
	split[j] = NULL;
	return (split);
}
