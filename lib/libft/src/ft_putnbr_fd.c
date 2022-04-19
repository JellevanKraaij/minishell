/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-kra <jvan-kra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:44:24 by jvan-kra          #+#    #+#             */
/*   Updated: 2021/10/19 15:44:24 by jvan-kra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		len;
	long	nb_long;

	nb_long = n;
	if (nb_long < 0)
	{
		ft_putchar_fd('-', fd);
		nb_long *= -1;
	}
	len = ft_nrlen(nb_long);
	while (len > 0)
	{
		ft_putchar_fd(((long)(nb_long / ft_pow(10, len - 1)) % 10) + '0', fd);
		len--;
	}
}
