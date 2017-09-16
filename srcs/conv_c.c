/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 15:10:00 by mbriffau          #+#    #+#             */
/*   Updated: 2017/09/16 15:18:57 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

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

t_printf	*print_wint(t_printf *pf, wint_t wint) ////////////////////////
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

static t_conv	*option_c(t_printf *pf, int print_size, char c, t_conv *conv)//(char)c useless
{
	int			i;
	char		tab[(conv->min_width - print_size) + 1];
	int 		size;

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


void	conv_c(t_printf *pf, t_conv *conv)
{
	int len;
	wint_t c;

	c = 0;
	if (conv->flag & MODIFIER_L && MB_CUR_MAX > 1)
	{	
		if (MB_CUR_MAX == 1)
			return;
		c = va_arg(pf->ap, wint_t);
		len = count_wint(c);
		conv->min_width > len && conv->flag & ZERO && !(conv->flag & MINUS) ? option_c(&*pf, len, '0', &*conv) : 0;
		conv->min_width > len && conv->flag & SPACE ? option_c(&*pf, len, ' ', &*conv) : 0;
		conv->min_width > len && !(conv->flag & MINUS) ? option_c(&*pf, len, ' ', &*conv) : 0;
		if (conv->min_width > len && conv->flag & MINUS)
		{
			print_wint(&*pf, c);
			option_c(&*pf, len, ' ', &*conv);
		}
		else
			print_wint(&*pf, c);
	}
	else
	{
		c = (char)c;
		c = va_arg(pf->ap, unsigned);
		len = 1;
		if (c == 0)
		{
			conv->min_width > len && !(conv->flag & MINUS) ? option_c(&*pf, len, ' ', &*conv) : 0;
			buffer(*&pf, "^@", 2);// taille 2 mais 1 pour return buff
			pf->subtract_buffer += 1;
			return;
		}
		(conv->flag & ZERO && !(conv->flag & MINUS)) ?
		option_c(&*pf, len, '0', &*conv) : 0;
		conv->flag & SPACE ? option_c(&*pf, len, ' ', &*conv) : 0;
		conv->min_width > len && !(conv->flag & MINUS) ? option_c(&*pf, len, ' ', &*conv) : 0;
		if (conv->min_width > len && conv->flag & MINUS)
		{
			(buffer(&*pf, ((char*)&c), len));
			option_c(&*pf, len, ' ', &*conv);
		}
		else
			(buffer(&*pf, ((char*)&c), len));
	}
	return ;
}
