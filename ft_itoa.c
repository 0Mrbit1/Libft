/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <acharik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 08:25:01 by acharik           #+#    #+#             */
/*   Updated: 2023/11/27 08:13:51 by acharik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_power(size_t number, size_t power)
{
	size_t	result;

	result = 1;
	while (power--)
	{
		result = result * number;
	}
	return (result);
}

static int	ft_calculate_number_len(long n)
{
	int	i;

	i = 1;
	n = n / 10;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*get_job_done(int number_len, long n, char *ptr, int i)
{
	int	digit;

	if (!ptr)
		return (NULL);
	while (number_len)
	{
		digit = n / ft_power(10, number_len - 1);
		ptr[i] = digit + '0';
		n = n - digit * ft_power(10, number_len - 1);
		number_len--;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static void	setup_zeroes(size_t *number_len, size_t *flag)
{
	*number_len = 0;
	*flag = 0;
}

char	*ft_itoa(int n)
{
	size_t	number_len;
	size_t	flag;
	size_t	i;
	long	ln;
	char	*ptr;

	ln = n;
	i = 0;
	setup_zeroes(&number_len, &flag);
	if (ln < 0)
	{
		ln *= -1;
		number_len += 1;
		flag = 1;
	}
	number_len += ft_calculate_number_len(ln);
	ptr = malloc(number_len + 1);
	if (!ptr)
		return (NULL);
	if (flag)
	{
		ptr[i++] = '-';
		number_len--;
	}
	return (get_job_done(number_len, ln, ptr, i));
}
