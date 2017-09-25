/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 00:09:01 by mbriffau          #+#    #+#             */
/*   Updated: 2017/09/25 01:03:55 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

// t_printf		*print_wint(t_printf *pf, wint_t wint)
// {
// 	char	str[4];
// 	int		lock;
// 	int		i;

// 	i = 0;
// 	lock = 1;
// 	wint <= 0x7F ? (str[i] = wint) && (lock--) : 0;
// 	lock && wint <= 0x7FF ? (str[i] = (((wint & 0x07c0) >> 6) + 0xc0))
// 	&& (str[++i] = ((wint & 0x003F) + 0x80)) && (lock--) : 0;
// 	lock && wint <= 0xFFFF ? (str[i] = (((wint & 0xF000) >> 12) + 0xE0))
// 	&& (str[++i] = (((wint & 0x0Fc0) >> 6) + 0x80))
// 	&& (str[++i] = ((wint & 0x003F) + 0x80)) && (lock--) : 0;
// 	lock && wint <= 0x10FFFF ? (str[i] = (((wint & 0x1c0000) >> 18) + 0xF0))
// 	&& (str[++i] = (((wint & 0x03F000) >> 12) + 0x80))
// 	&& (str[++i] = (((wint & 0x0Fc0) >> 6) + 0x80))
// 	&& (str[++i] = ((wint & 0x003F) + 0x80)) && (lock--) : 0;
// 	buffer(&*pf, str, ++i);
// 	return (pf);
// }

t_printf		*print_wint(t_printf *pf, wint_t wint)
{
	char	str[4];

	if (wint <= 0x7F)
		buffer(&*pf, (char*)&wint, 1);
	else if (wint <= 0x7FF)
	{
		str[0] = (((wint & 0x07c0) >> 6) + 0xc0);
		str[1] = ((wint & 0x003F) + 0x80);
		buffer(&*pf, str, 2);
	}
	else if (wint <= 0xFFFF)
	{
		str[0] = (((wint & 0xF000) >> 12) + 0xE0);
		str[1] = (((wint & 0x0Fc0) >> 6) + 0x80);
		str[2] = ((wint & 0x003F) + 0x80);
		buffer(&*pf, str, 3);
	}
	else if (wint <= 0x10FFFF)
	{
		str[0] = (((wint & 0x1c0000) >> 18) + 0xF0);
		str[1] = (((wint & 0x03F000) >> 12) + 0x80);
		str[2] = (((wint & 0x0Fc0) >> 6) + 0x80);
		str[3] = ((wint & 0x003F) + 0x80);
		buffer(&*pf, str, 4);
	}
	return (pf);
}

t_conv	*option_char(t_printf *pf, int print_size, char c, t_conv *conv)
{
	int			i;
	char		tab[(conv->min_width - print_size) + 1];
	int			size;

	size = (conv->min_width - print_size);
	i = 0;
	tab[size] = '\0';
	if (!size)
		return (conv);
	else
	{
		while (i < size)
			tab[i++] = c;
		buffer(&*pf, tab, size);
	}
	conv->min_width = 0;
	return (conv);
}
