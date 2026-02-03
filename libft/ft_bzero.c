/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:29:50 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/28 10:10:21 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}

/*
#include <stdio.h>

int	main(void)
{
	char s[] = "noor";
	printf("before ft_bzero : %s \n", s);
	ft_bzero(s, 2);
	printf("after ft_bzero : %s \n", s);
	return (0);
}*/
