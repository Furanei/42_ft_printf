/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 15:10:00 by mbriffau          #+#    #+#             */
/*   Updated: 2017/08/17 18:13:46 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static int		count_wint(wint_t c)
{
	int		size;

	size = 0;
	if (c <= 0x7F)
		size = 1;
	else if (c <= 0x7FF)
		size = 2;
	else if (c <= 0xFFFF)
		size = 3;
	else if (c <= 0x10FFFF)
		size = 4;
	return (size);
}

void	print_wint(wint_t wint)
{
	char	str[4];

	if (wint <= 0x7F)
		write(1, (unsigned*)&wint, 1);
	else if (wint <= 0x7FF)
	{
		str[0] = (((wint & 0x07c0) >> 6) + 0xc0);
		str[1] = ((wint & 0x003F) + 0x80);
		write(1, str, 2);
	}
	else if (wint <= 0xFFFF)
	{
		str[0] = (((wint & 0xF000) >> 12) + 0xE0);
		str[1] = (((wint & 0x0Fc0) >> 6) + 0x80);
		str[2] = ((wint & 0x003F) + 0x80);
		write(1, str, 3);
	}
	else if (wint <= 0x10FFFF)
	{
		str[0] = (((wint & 0x1c0000) >> 18) + 0xF0);
		str[1] = (((wint & 0x03F000) >> 12) + 0x80);
		str[2] = (((wint & 0x0Fc0) >> 6) + 0x80);
		str[3] = ((wint & 0x003F) + 0x80);
		write(1, str, 4);
	}
}

static t_conv	*option_c(t_printf *pf, int print_size, char c, t_conv *conv, char print)
{
	int			i;
	char		tab[(conv->min_width - print_size) + 1];
	int 		size;

	size = (conv->min_width - print_size);
	i = 0;
	tab[size] = '\0';
	if (print)
	{
		conv->flag & MODIFIER_L ?
		print_wint(c) : buffer(&*pf, &c, 1);
	}
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


void	conv_c(t_printf *pf, t_conv *conv)
{
	int len;
	wint_t c;

	c = 0;
	if (conv->flag & MODIFIER_L)
	{	
		if (MB_CUR_MAX == 1)
			return;
		c = va_arg(pf->ap, wint_t);
		len = count_wint(c);
		conv->flag & ZERO && !(conv->flag & MINUS) ? option_c(&*pf, len, '0', &*conv, 0) : 0;
		conv->flag & SPACE ? option_c(&*pf, len, ' ', &*conv, 0) : 0;
		conv->min_width > len && !(conv->flag & MINUS) ? option_c(&*pf, len, ' ', &*conv, 0) : 0;
		conv->flag & MINUS ? print_wint(c) : 0 ;
		conv->flag & MINUS ? option_c(&*pf, len, ' ', &*conv, 0) : print_wint(c);
	}
	else
	{
		c = (char)c;
		c = va_arg(pf->ap, unsigned);
		(conv->flag & ZERO && !(conv->flag & MINUS)) ?
		option_c(&*pf, 1, '0', &*conv, 0) : 0;
		conv->flag & SPACE ? option_c(&*pf, 1, ' ', &*conv, 0) : 0;
		conv->min_width > 1 && !(conv->flag & MINUS) ? option_c(&*pf, 1, ' ', &*conv, 0) : 0;
		if (conv->flag & MINUS)
			option_c(&*pf, 1, ' ', &*conv, c);
		else
			(buffer(&*pf, ((char*)&c), 1));
	}
	return ;
}
