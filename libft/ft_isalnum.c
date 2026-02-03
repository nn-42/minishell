/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:11:38 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/28 09:33:09 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a'
			&& c <= 'z'))
		return (1);
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("a is alnum : %d\n", ft_isalnum('a'));
	printf("l is alnum : %d\n", ft_isalnum('l'));
	printf("z is alnum : %d\n", ft_isalnum('z'));
	printf("A is alnum : %d\n", ft_isalnum('A'));
	printf("R is alnum : %d\n", ft_isalnum('R'));
	printf("Z is alnum : %d\n", ft_isalnum('Z'));
	printf("0 is alnum : %d\n", ft_isalnum('0'));
	printf("5 is alnum : %d\n", ft_isalnum('5'));
	printf("9 is alnum : %d\n", ft_isalnum('9'));
	printf("  is alnum : %d\n", ft_isalnum(' '));
	printf("& is alnum : %d\n", ft_isalnum('&'));
	printf("\\n is alnum : %d\n", ft_isalnum('\n'));
	return (0);
}*/
