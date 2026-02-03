/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:07:47 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/28 09:16:23 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("a is alpha : %d\n", ft_isalpha('a'));
	printf("l is alpha : %d\n", ft_isalpha('l'));
	printf("z is alpha : %d\n", ft_isalpha('z'));
	printf("A is alpha : %d\n", ft_isalpha('A'));
	printf("R is alpha : %d\n", ft_isalpha('R'));
	printf("Z is alpha : %d\n", ft_isalpha('Z'));
	printf("9 is alpha : %d", ft_isalpha('9'));
	return (0);
}*/
