/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnasered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 10:15:00 by nnasered          #+#    #+#             */
/*   Updated: 2025/08/28 09:24:10 by nnasered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if (size > SIZE_MAX / nmemb)
		return (NULL);
	p = malloc(nmemb * size);
	if (p != NULL)
		ft_bzero(p, nmemb * size);
	return (p);
}
