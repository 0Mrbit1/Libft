/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <acharik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 10:35:26 by acharik           #+#    #+#             */
/*   Updated: 2023/11/27 08:50:46 by acharik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_updated(const char *str, char c)
{
	size_t	i;

	i = 0;
	while ((str[i] != '\0') && (str[i] != c))
	{
		i++;
	}
	return (i);
}

static size_t	ft_words_count(const char *str, char c)
{
	size_t	i;
	size_t	end;
	size_t	word_count;

	i = 0;
	word_count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			word_count += 1;
			end = ft_strlen_updated(&str[i], c);
			i += end - 1;
		}
		i++;
	}
	return (word_count);
}

static void	fill_up_ptr(const char *str, char *ptr, size_t start, size_t end)
{
	size_t	j;

	j = 0;
	while (j < end)
	{
		ptr[j] = str[start];
		j++;
		start++;
	}
	ptr[j] = '\0';
}

static char	**get_start_end_fill(char *ptr, char **split, const char *str,
		char c)
{
	size_t	end;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			end = ft_strlen_updated(&str[i], c);
			ptr = (char *)malloc(end + 1);
			if (!ptr)
			{
				while (j)
					free(split[--j]);
				return (NULL);
			}
			fill_up_ptr(str, ptr, i, end);
			split[j++] = ptr;
			i += end - 1;
		}
		i++;
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	char	*ptr;
	size_t	words;

	if (!s)
		return (NULL);
	words = ft_words_count(s, c);
	ptr = 0;
	split = (char **)malloc(sizeof(ptr) * (words + 1));
	if (!split)
		return (NULL);
	if (!get_start_end_fill(ptr, split, s, c))
	{
		free(split);
		return (NULL);
	}
	split[words] = NULL;
	return (split);
}
