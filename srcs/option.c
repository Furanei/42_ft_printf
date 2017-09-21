/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 19:35:35 by mbriffau          #+#    #+#             */
/*   Updated: 2017/09/21 16:01:16 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	option(t_printf *pf, int c, size_t n)
{
	char	s[n + 1];
	int 	i;

	i = n;
	if (n)
	{
		s[n] = '\0';
		while(n)
			s[--n] = c;
		buffer(&*pf, s, i);
	}
	return (n);
}
