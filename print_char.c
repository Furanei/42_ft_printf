/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 07:02:27 by mbriffau          #+#    #+#             */
/*   Updated: 2017/02/24 09:45:41 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// int		print_char(char c)
// {

// 	write
// }

void		pf_putstr(char *s)
{
	int n = 0;
	printf("%d - ", n = ft_strlen(s));
	write(1, s, ft_strlen(s));
}
