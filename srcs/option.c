/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achambon <achambon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 19:35:35 by mbriffau          #+#    #+#             */
/*   Updated: 2017/08/15 19:20:40 by achambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_conv	*option_print(int print_size, char c, t_conv *conv, char *s)
{
	int			i;
	char		tab[(conv->min_width - print_size) + 1];
	int 		size;

	size = (conv->min_width - print_size);
	i = 0;
	tab[size] = '\0';
	if (size)
	{
		if (s && conv->before && !(conv->before == 3))
		{
			conv->ox == 1 ? ft_putstr("0x") : 0;
			ft_putstr(s);
		}
		if (conv->precision_set == 2)
		{
			ft_putstr("0x");
			conv->ox = 0;
		}
		if(!(conv->flag & MINUS) || (conv->flag & MINUS && size > conv->precision) || conv->before == 3)
		{
			while (i < size)
				tab[i++] = c;
			write(1, tab, size);
		}
		if((conv->flag & PLUS) && !(conv->flag & ZERO) && !(conv->flag & MINUS) && (conv->flag & (TYPE_D + TYPE_U + TYPE_O)))
		{
			ft_putchar('+');
		}
			if ((conv->before == 0 && s) || conv->before == 3)
		{
			if(conv->ox == 1)
				ft_putstr("0x");
			ft_putstr(s);
		}
		if((conv->flag & MINUS && !(size > conv->precision)) && !(conv->before == 3))
		{
			while (i < size)
				tab[i++] = c;
			write(1, tab, size);
		}
	}
	conv->min_width = 0;
	return (conv);
}

// Le N c'est simplement conv->min_width donc inutile en revanche on a besoin de soustraire la taille de ce qu'il y a a print.
// donc n devient print_size a soustraire.
// J'ai garde ta version ici
int	option(t_printf *pf, int n, char c, t_conv *conv, char *s)
{
	int		i;
	char	tab[n + 1];

	i = 0;
	tab[n] = '\0';
	if (!n)
		return(0);
	if (conv->before == 4)
	{
		while (i < n)
			tab[i++] = c;
		buffer(&*pf, tab, n);
		// write(1, tab, n);
		// ft_putchar('+');
		buffer(&*pf, "+", 1);
		buffer(&*pf, s, ft_strlen(s));
		// ft_putstr(s);
		return(0);
	}
	if (!(conv->before == 3) && conv->before && s)
	{
		if(conv->ox == 1)
			buffer(&*pf, "0x0", 3);
		buffer(&*pf, s, ft_strlen(s));
	}
	if (conv->precision_set == 2)
	{
		buffer(&*pf, "0x", 2);
		// ft_putstr("0x");
		conv->ox = 0;
	}
	if(!(conv->flag & MINUS) || (conv->flag & MINUS && conv->min_width > conv->precision) || conv->before == 3)
	{
		while (i < n)
			tab[i++] = c;
		buffer(&*pf, tab, n);
		// write(1, tab, n);
	}
	if(((conv->flag & PLUS) && !(conv->flag & ZERO) && !(conv->flag & MINUS) && (conv->flag & (TYPE_D + TYPE_U + TYPE_O)) && !(conv->before == 3) && !conv->flag & MODIFIER_HH))
		buffer(&*pf, "+", 1);
	if ((conv->before == 0 && s) || conv->before == 3)
	{
		if(conv->ox == 1)
			buffer(&*pf, "0x", 2);
		buffer(&*pf, s, ft_strlen(s));
	}
	if((conv->flag & MINUS && !(conv->min_width > conv->precision)) && !(conv->before == 3))
	{
		while (i < n)
			tab[i++] = c;
		buffer(&*pf, tab, n);
		// write(1, tab, n);
	}
	
	return (n - i);
}
