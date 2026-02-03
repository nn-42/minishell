/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:13:59 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/30 12:14:02 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*
void f(unsigned int i, char *c)
{
	(void)i;
	*c = *c - 1;
}
#include <stdio.h>
int main()
{
	char str[] = "bcd";
	ft_striteri(str, f);
	printf("%s", str);
	return (0);
}*/
