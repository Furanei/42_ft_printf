/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_d4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 16:08:01 by achambon          #+#    #+#             */
/*   Updated: 2017/09/21 13:21:44 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_conv	option_dbis_convbefore4(t_printf *pf, t_conv *conv, char *s)
{
	buffer(&*pf, "+", 1);
	buffer(&*pf, s, ft_strlen(s));
	return (*conv);
}

t_conv	option_d(t_printf *pf, int n, char c, t_conv *conv)
{
	int		i;
	char	tab[n + 1];

	n ? i = 0 && tab[n] == '\0' : 0;
	if (!n)
		return (*conv);
	while (i < n)
		tab[i++] = c;
	if (conv->before == 4)
	{
		buffer(&*pf, tab, n);
		return (option_dbis_convbefore4(&*pf, conv, pf->str));
	}
	(!(conv->before == 3) && conv->before && pf->str) ?
	buffer(&*pf, pf->str, ft_strlen(pf->str)) : 0;
	(!(conv->flag & MINUS) || (conv->flag & MINUS && conv->min_width >
	conv->precision) || conv->before == 3) ? buffer(&*pf, tab, n) : 0;
	((conv->flag & PLUS) && !(conv->flag & (ZERO + MINUS + MODIFIER_HH))
	&& (conv->flag & 0x26000000) && !(conv->before == 3)) ?
	buffer(&*pf, "+", 1) : 0;
	((conv->before == 0 && pf->str) || conv->before == 3) ?
	buffer(&*pf, &*pf->str, ft_strlen(pf->str)) : 0;
	((conv->flag & MINUS && !(conv->min_width > conv->precision))
	&& !(conv->before == 3)) ? buffer(&*pf, tab, n) : 0;
	return (*conv);
}

int		conv_d_minus_width_only(t_printf *pf, t_conv *conv, int len, char *str)
{
	if (conv->min_width < len)
		return (0);
	else if (conv->min_width > len)
	{
		(conv->flag & SPACE && !(conv->flag & PLUS) &&
		!(conv->flag & MODIFIER_HH)) ?
		minwidth_decr_add_char_2_buff(&*pf, ' ', &*conv) : 0;
		if (conv->flag & PLUS && !(conv->flag & ZERO) && !(conv->flag & SPACE)
			&& !(conv->flag & MODIFIER_HH))
		{
			minwidth_decr_add_char_2_buff(&*pf, '+', &*conv);
			conv->before = 1;
			option_d(&*pf, conv->min_width - len, ' ', conv);
		}
	}
	if (!(conv->flag & PLUS))
	{
		conv->before = 1;
		option_d(&*pf, conv->min_width - len, ' ', conv);
	}
	str = pf->str;
	return (pf->i_buf);
}

int		conv_d_minus_width_and_prec(t_printf *pf, t_conv *conv,
int len, char *str)
{
	if (conv->min_width > conv->precision)
	{
		conv->before = 0;
		if (conv->flag & SPACE && !(conv->flag & PLUS)
		&& !(conv->flag & MODIFIER_HH))
			minwidth_decr_add_char_2_buff(&*pf, ' ', conv);
		if (conv->flag & PLUS && !(conv->flag & MODIFIER_HH))
			minwidth_decr_add_char_2_buff(&*pf, '+', conv);
		str[0] == '-' ? special_hhd_reverse_0_n_minus(&*pf, str, '-') : 0;
		option_d(&*pf, conv->precision - len, '0', conv);
		while ((conv->min_width-- - conv->precision))
			buffer(&*pf, " ", 1);
		return (0);
	}
	if (conv->min_width <= conv->precision)
	{
		str[0] == '-' ? special_hhd_reverse_0_n_minus(&*pf, str, '-') : 0;
		if (conv->flag & PLUS && !(conv->flag & MODIFIER_HH))
			minwidth_decr_add_char_2_buff(&*pf, '+', conv);
		if (conv->flag & SPACE && !(conv->flag & PLUS + MODIFIER_HH))
			minwidth_decr_add_char_2_buff(&*pf, ' ', conv);
		conv->before = 3;
		option_d(&*pf, conv->precision - len, '0', conv);
	}
	return (0);
}
