/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_x4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 18:36:31 by achambon          #+#    #+#             */
/*   Updated: 2017/09/19 18:38:30 by achambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char				*ft_str_tolower(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (ft_isalpha(s[i]))
			s[i] = ft_tolower(s[i]);
		i++;
	}
	return (s);
}

int					fill_tab_with_c(t_printf *pf, char *tab, char c)
{
	int i;

	i = 0;
	while (i < pf->n)
		tab[i++] = c;
	buffer(&*pf, tab, pf->n);
	return (pf->i_buf);
}

t_conv				option_x3(t_printf *pf, char *tab, char c, t_conv *conv)
{
	if (!(conv->flag & MINUS) || (conv->flag & MINUS &&
				conv->min_width > conv->precision) || conv->before == 3)
	{
		(conv->flag & SHARP && conv->ox == 2) ? buffer(&*pf, "0x", 2) : 0;
		fill_tab_with_c(&*pf, tab, c);
	}
	(((conv->flag & PLUS) && !(conv->flag & ZERO) && !(conv->flag & MINUS)
	&& (conv->flag & (TYPE_D + TYPE_U + TYPE_O)) && !(conv->before == 3)
	&& !conv->flag & MODIFIER_HH)) ? buffer(&*pf, "+", 1) : 0;
	return (*conv);
}

t_conv				option_x2(t_printf *pf, int n, char c, t_conv *conv)
{
	char	tab[n + 1];
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(pf->str);
	tab[n] = '\0';
	if (!(conv->before == 3) && conv->before && pf->str)
	{
		(conv->ox == 1) ? buffer(&*pf, "0x", 2) : 0;
		buffer(&*pf, pf->str, len);
	}
	(conv->precision_set == 2) ? (buffer(&*pf, "0x", 2)) && (conv->ox = 0) : 0;
	option_x3(&*pf, tab, c, conv);
	if ((conv->before == 0 && pf->str) || conv->before == 3)
	{
		(conv->ox == 1) ? buffer(&*pf, "0x", 2) : 0;
		buffer(&*pf, &*pf->str, len);
	}
	((conv->flag & MINUS && !(conv->min_width > conv->precision))
	&& !(conv->before == 3)) ? fill_tab_with_c(&*pf, tab, c) : 0;
	return (*conv);
}
