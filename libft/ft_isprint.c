/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:17:05 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/28 09:40:24 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if ((c >= 32 && c <= 126))
		return (1);
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("'a' is printable : %d\n", ft_isprint('a'));
	printf("'l' is printable : %d\n", ft_isprint('l'));
	printf("'z' is printable : %d\n", ft_isprint('z'));
	printf("'A' is printable : %d\n", ft_isprint('A'));
	printf("'R' is printable : %d\n", ft_isprint('R'));
	printf("'Z' is printable : %d\n", ft_isprint('Z'));
	printf("'0' is printable : %d\n", ft_isprint('0'));
	printf("'5' is printable : %d\n", ft_isprint('5'));
	printf("'9' is printable : %d\n", ft_isprint('9'));
	printf("' ' (space) is printable : %d\n", ft_isprint(' '));
	printf("'&' is printable : %d\n", ft_isprint('&'));
	printf("'\\n' is printable : %d\n", ft_isprint('\n'));
	printf("127 is printable : %d\n", ft_isprint(127));
	printf("31 is printable : %d\n", ft_isprint(31));
	return (0);
}*/
