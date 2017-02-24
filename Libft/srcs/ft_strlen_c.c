/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 21:49:52 by mbriffau          #+#    #+#             */
/*   Updated: 2017/02/24 09:33:09 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_c(char const *str, char cmp)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 32768;
	while (str[i])
	{
		if (str[i] == cmp)
			return (i);
		if (str[i + n])
			i += n;
		else
		{
			n >>= 1;
			i++;
		}
	}
	return (i);
}
