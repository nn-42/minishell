/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:15:20 by nfaronia          #+#    #+#             */
/*   Updated: 2025/08/28 09:36:58 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if ((c >= 0 && c <= 127))
		return (1);
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("'a' is ascii : %d\n", ft_isascii('a'));
	printf("'l' is ascii : %d\n", ft_isascii('l'));
	printf("'z' is ascii : %d\n", ft_isascii('z'));
	printf("'A' is ascii : %d\n", ft_isascii('A'));
	printf("'R' is ascii : %d\n", ft_isascii('R'));
	printf("'Z' is ascii : %d\n", ft_isascii('Z'));
	printf("'0' is ascii : %d\n", ft_isascii('0'));
	printf("'5' is ascii : %d\n", ft_isascii('5'));
	printf("'9' is ascii : %d\n", ft_isascii('9'));
	printf("' ' (space) is ascii : %d\n", ft_isascii(' '));
	printf("'&' is ascii : %d\n", ft_isascii('&'));
	printf("'\\n' is ascii : %d\n", ft_isascii('\n'));
	printf("200 is ascii : %d\n", ft_isascii(200));

	return (0);
}*/
