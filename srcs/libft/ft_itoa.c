/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 13:31:37 by jgalian-          #+#    #+#             */
/*   Updated: 2021/04/23 11:58:35 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_intlen(long int n)
{
	long int	len;
	long int	nb;

	nb = n;
	len = 0;
	while (nb)
	{
		nb /= 10;
		len++;
	}
	if (n > 0)
		return (len);
	else
		return (len + 1);
}

char	*put_nb(int nb, int len, char *str)
{
	while (nb > 0)
	{
		str[--len] = (nb % 10) + 48;
		nb /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	len;
	long int	nb;

	nb = (long int)n;
	len = ft_intlen(nb);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	return (put_nb(nb, len, str));
}
