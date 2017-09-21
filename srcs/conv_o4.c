/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_o4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 21:01:23 by achambon          #+#    #+#             */
/*   Updated: 2017/09/19 21:02:56 by achambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_conv		option_o3(t_printf *pf, char *tab, char c, t_conv *conv)
{
	if ((conv->before == 0 && pf->str) || conv->before == 3)
	{
		if (conv->ox == 1)
			buffer(&*pf, "0x", 2);
		if (conv->flag & SHARP)
			buffer(&*pf, "0", 1);
		buffer(&*pf, pf->str, pf->len);
	}
	if ((conv->flag & MINUS && !(conv->min_width > conv->precision))
	&& !(conv->before == 3))
		fill_tab_with_c(&*pf, tab, c);
	return (*conv);
}

t_conv		option_o2(t_printf *pf, int i, char c, t_conv *conv)
{
	char	tab[pf->n + 1];

	tab[pf->n] = '\0';
	if (!(conv->before == 3) && conv->before && pf->str)
	{
		if (conv->ox == 1)
			buffer(&*pf, "0x", 2);
		buffer(&*pf, pf->str, pf->len);
	}
	(conv->precision_set == 2) ? (buffer(&*pf, "0x", 2)) && (conv->ox = 0) : 0;
	if (!(conv->flag & MINUS) || (conv->flag & MINUS
	&& conv->min_width > conv->precision) || conv->before == 3)
	{
		while (i < pf->n)
			tab[i++] = c;
		buffer(&*pf, tab, pf->n);
	}
	if (((conv->flag & PLUS) && !(conv->flag & ZERO) && !(conv->flag & MINUS)
	&& (conv->flag & (TYPE_D + TYPE_U + TYPE_O)) && !(conv->before == 3)
	&& !conv->flag & MODIFIER_HH))
		buffer(&*pf, "+", 1);
	return (*conv);
}

t_conv		option_o(t_printf *pf, int n, char c, t_conv *conv)
{
	int		i;
	char	tab[n + 1];
	int		len;

	pf->n = n;
	len = ft_strlen(pf->str);
	i = 0;
	tab[n] = '\0';
	if (!n)
		return (*conv);
	if (conv->before == 4)
	{
		while (i < n)
			tab[i++] = c;
		buffer(&*pf, tab, n);
		buffer(&*pf, " ", 1);
		buffer(&*pf, pf->str, len);
		return (*conv);
	}
	option_o2(&*pf, i, c, conv);
	option_o3(&*pf, tab, c, conv);
	return (*conv);
}
