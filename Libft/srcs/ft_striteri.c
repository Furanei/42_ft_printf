/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 17:46:40 by mbriffau          #+#    #+#             */
/*   Updated: 2016/12/07 12:25:15 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t		i;
	size_t		y;

	if (!s || !f)
		return ;
	i = 0;
	y = ft_strlen(s);
	if (s != NULL)
		while (i < y)
			f(i++, s++);
}
