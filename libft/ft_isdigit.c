/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:10:03 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/28 09:23:52 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("a is digit : %d\n", ft_isdigit('a'));
	printf("l is digit : %d\n", ft_isdigit('l'));
	printf("z is digit : %d\n", ft_isdigit('z'));
	printf("A is digit : %d\n", ft_isdigit('A'));
	printf("R is digit : %d\n", ft_isdigit('R'));
	printf("Z is digit : %d\n", ft_isdigit('Z'));
	printf("0 is digit : %d\n", ft_isdigit('0'));
	printf("5 is digit : %d\n", ft_isdigit('5'));
	printf("9 is digit : %d\n", ft_isdigit('9'));
	return (0);
}*/
