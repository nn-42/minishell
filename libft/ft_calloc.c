/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:01:50 by nfaronia          #+#    #+#             */
/*   Updated: 2025/09/03 13:45:23 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			total_size;

	if (count != 0 && size != 0)
	{
		total_size = count * size;
		if (total_size / count != size)
			return (NULL);
	}
	else
		total_size = 1;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}

/*
#include <stdio.h>

int	main(void)
{
	int *ptr;
	size_t count = 2;
	size_t size = sizeof(int);
	size_t i;

	ptr = (int *)ft_calloc(count, size);
	if (!ptr)
		return(0);
	i = 0;
	while (i < count)
	{
		printf("ptr[%zu] = %d\n", i, ptr[i]);
		i++;
	}
	free(ptr);
	printf("original calloc \n");
	ptr = (int *)calloc(count, size);
	if (!ptr)
		return(0);
	i = 0;
	while (i < count)
	{
		printf("ptr[%zu] = %d\n", i, ptr[i]);
		i++;
	}
	free(ptr);
	return (0);
}*/
