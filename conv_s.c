/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 16:07:37 by mbriffau          #+#    #+#             */
/*   Updated: 2017/08/17 18:17:17 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/ft_printf.h"

int		ft_wstrlen(wchar_t *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int		count_wchars(t_conv *conv, wchar_t *wstr, int size)
{
	int		i;
	int		add;
	int		total;

	i = 0;
	add = 0;
	total = 0;
	while (i < size)
	{
		if (wstr[i] <= 0x7F)
			add = 1;
		else if (wstr[i] <= 0x7FF)
			add = 2;
		else if (wstr[i] <= 0xFFFF)
			add = 3;
		else if (wstr[i] <= 0x10FFFF)
			add = 4;
		if (conv->precision_set && conv->type == 's'
			&& (total + add) > conv->precision)
			break ;
		total += add;
		i++;
	}
	size = i;
	return (total);
}
static void	print_wstring(t_conv *conv, wchar_t *wstr, int size)
{
	int i = 0;

	count_wchars(conv, wstr, size);
	while (i < size)
	{
		print_wint(wstr[i]);
		i++;		
	}
}

static t_conv	*option_s(t_printf *pf, int print_size, char c, t_conv *conv, char *s)
{
	int			i;
	char		tab[(conv->min_width - print_size) + 1];
	int 		size;

	size = (conv->min_width - print_size);
	i = 0;
	tab[size] = '\0';
	if (!size)
		return (conv);
	if (size)
	{
		if(!(conv->flag & MINUS) || (conv->flag & MINUS && size > conv->precision) || conv->before == 3)
		{
			while (i < size)
				tab[i++] = c;
			// write(1, tab, size);
			buffer(&*pf, tab, size);
		}
		if((conv->flag & MINUS && !(size > conv->precision)) && !(conv->before == 3))
		{
			while (i < size)
				tab[i++] = c;
			// write(1, tab, size);
			buffer(&*pf, tab, size);
		}
	}
	conv->min_width = 0;
	return (conv);
}

void	conv_s(t_printf *pf, t_conv *conv)
{
	void *str;
	int len;

	conv->flag & MODIFIER_L ? (str = va_arg(pf->ap, wchar_t *)) : (str = va_arg(pf->ap, unsigned char *));
	len = (conv->flag & MODIFIER_L ? count_wchars(conv, str ,ft_wstrlen(str)) : ft_strlen(str));
	if ((conv->flag & ZERO) && !(conv->flag & MINUS))
		option_s(&*pf, len, '0', &*conv, 0);
	else if (conv->flag & SPACE && conv->min_width > len)
		option_s(&*pf, len, ' ', &*conv, 0);
	else if (conv->min_width > len && !(conv->flag & MINUS))
		option_s(&*pf, len, ' ', &*conv, 0);
	else if ((conv->flag & MINUS))
	{
		conv->flag & MODIFIER_L ? print_wstring(conv, str, ft_wstrlen(str)) : buffer(&*pf, str, len);
		option_s(&*pf, len, ' ', &*conv, 0);
		return;
	}
	if (conv->flag & MODIFIER_L)
		print_wstring(conv, str, ft_wstrlen(str));
	else
		buffer(&*pf, str, len);
}

// if (conv->flag & MODIFIER_L)
// 	{	
// 		if (MB_CUR_MAX == 1)
// 			return;
// 		c = va_arg(pf->ap, wint_t);
// 		len = count_wint(c);
// 		conv->flag & ZERO && !(conv->flag & MINUS) ? option_c(len, '0', &*conv, 0) : 0;
// 		conv->flag & SPACE ? option_c(len, ' ', &*conv, 0) : 0;
// 		conv->min_width > len && !(conv->flag & MINUS) ? option_c(len, ' ', &*conv, 0) : 0;
// 		conv->flag & MINUS ? print_wint(c) : 0 ;
// 		conv->flag & MINUS ? option_c(len, ' ', &*conv, 0) : print_wint(c);
// 	}
// 	else
// 	{
// 		c = va_arg(pf->ap, unsigned);
// 		(conv->flag & ZERO && !(conv->flag & MINUS)) ?
// 		option_c(1, '0', &*conv, 0) : 0;
// 		conv->flag & SPACE ? option_c(1, ' ', &*conv, 0) : 0;
// 		conv->min_width > 1 && !(conv->flag & MINUS) ? option_c(1, ' ', &*conv, 0) : 0;
// 		conv->flag & MINUS ? option_c(1, ' ', &*conv, c) : ft_putchar(c);
// 	}