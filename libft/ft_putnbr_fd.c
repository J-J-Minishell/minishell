/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalian- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 11:42:39 by jgalian-          #+#    #+#             */
/*   Updated: 2019/11/25 09:45:32 by jgalian-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = (long int)n;
	if (nb == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (nb < 0)
		{
			ft_putchar_fd('-', fd);
			nb *= -1;
		}
		if (nb > 9)
			ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd((nb % 10 + 48), fd);
	}
}
