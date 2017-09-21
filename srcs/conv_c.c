/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 15:10:00 by mbriffau          #+#    #+#             */
/*   Updated: 2017/09/18 17:59:05 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		count_wint(wint_t c)
{
	if (c <= 0x7F)
		return (1);
	else if (c <= 0x7FF)
		return (2);
	else if (c <= 0xFFFF)
		return (3);
	else if (c <= 0x10FFFF)
		return (4);
	return (0);
}

t_printf		*print_wint(t_printf *pf, wint_t wint)
{
	char	str[4];
	int		lock;
	int		i;

	i = 0;
	lock = 1;
	wint <= 0x7F ? (str[i] = wint) && (lock--) : 0;
	lock && wint <= 0x7FF ? (str[i] = (((wint & 0x07c0) >> 6) + 0xc0))
	&& (str[++i] = ((wint & 0x003F) + 0x80)) && (lock--) : 0;
	lock && wint <= 0xFFFF ? (str[i] = (((wint & 0xF000) >> 12) + 0xE0))
	&& (str[++i] = (((wint & 0x0Fc0) >> 6) + 0x80))
	&& (str[++i] = ((wint & 0x003F) + 0x80)) && (lock--) : 0;
	lock && wint <= 0x10FFFF ? (str[i] = (((wint & 0x1c0000) >> 18) + 0xF0))
	&& (str[++i] = (((wint & 0x03F000) >> 12) + 0x80))
	&& (str[++i] = (((wint & 0x0Fc0) >> 6) + 0x80))
	&& (str[++i] = ((wint & 0x003F) + 0x80)) && (lock--) : 0;
	buffer(&*pf, str, ++i);
	return (pf);
}

static t_conv	*option_c(t_printf *pf, int print_size, char c, t_conv *conv)
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

static void		conv_c_wint(t_printf *pf, t_conv *conv)
{
	char	c;
	int		len;

	if (MB_CUR_MAX == 1)
		return ;
	c = va_arg(pf->ap, wint_t);
	len = count_wint(c);
	conv->min_width > len && conv->flag & ZERO && !(conv->flag & MINUS)
	? option_c(&*pf, len, '0', &*conv) : 0;
	conv->min_width > len && conv->flag & SPACE
	? option_c(&*pf, len, ' ', &*conv) : 0;
	conv->min_width > len && !(conv->flag & MINUS)
	? option_c(&*pf, len, ' ', &*conv) : 0;
	print_wint(&*pf, c);
	(conv->min_width > len && conv->flag & MINUS)
	? option_c(&*pf, len, ' ', &*conv) : 0;
}

void			conv_c(t_printf *pf, t_conv *conv)
{
	char	c;

	if (conv->flag & MODIFIER_L && MB_CUR_MAX > 1)
		conv_c_wint(&*pf, &*conv);
	else
	{
		c = va_arg(pf->ap, unsigned);
		if (c == 0)
		{
			conv->min_width > 1 && !(conv->flag & MINUS)
			? option_c(&*pf, 1, ' ', &*conv) : 0;
			buffer(*&pf, "^@", 2);
			pf->subtract_buffer += 1;
			return ;
		}
		(conv->flag & ZERO && !(conv->flag & MINUS))
		? option_c(&*pf, 1, '0', &*conv) : 0;
		conv->flag & SPACE ? option_c(&*pf, 1, ' ', &*conv) : 0;
		conv->min_width > 1 && !(conv->flag & MINUS)
		? option_c(&*pf, 1, ' ', &*conv) : 0;
		buffer(&*pf, ((char*)&c), 1);
		(conv->min_width > 1 && conv->flag & MINUS)
		? option_c(&*pf, 1, ' ', &*conv) : 0;
	}
	return ;
}
