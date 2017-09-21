/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_x3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 18:34:06 by achambon          #+#    #+#             */
/*   Updated: 2017/09/19 18:35:30 by achambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_conv		option_x(t_printf *pf, int n, char c, t_conv *conv)
{
	int		i;
	char	tab[n + 1];
	int		len;

	len = ft_strlen(pf->str);
	i = 0;
	tab[n] = '\0';
	pf->n = n;
	if (!n)
		return (*conv);
	if (conv->before == 4)
	{
		if (conv->flag & SHARP)
			pf->n--;
		fill_tab_with_c(&*pf, tab, c);
		buffer(&*pf, " ", 1);
		if (conv->flag & SHARP)
			buffer(&*pf, "0x", 2);
		buffer(&*pf, pf->str, len);
		return (*conv);
	}
	option_x2(&*pf, pf->n, c, conv);
	return (*conv);
}

t_printf	*add_0x(t_printf *pf, t_conv *conv)
{
	if (conv->flag & MODIFIER_X)
	{
		buffer(&*pf, "0X", 2);
		return (pf);
	}
	buffer(&*pf, "0x", 2);
	return (pf);
}

int			conv_x_minus_width_sup_len(t_printf *pf, t_conv *conv, int len)
{
	if (conv->min_width > len)
	{
		(conv->flag & SHARP) ? (conv->min_width = conv->min_width - 2)
		&& (buffer(&*pf, "0x", 2)) : 0;
		if (conv->flag & PLUS && !(conv->flag & ZERO) && !(conv->flag & SPACE))
		{
			conv->before = 1;
			option_x(&*pf, conv->min_width - len, ' ', conv);
			return (0);
		}
		(conv->flag & PLUS && !(conv->flag & ZERO)) ? conv->min_width-- : 0;
		if (conv->flag & PLUS && conv->flag & ZERO && !conv->flag & MODIFIER_HH)
		{
			conv->before = 1;
			option_x(&*pf, conv->min_width - len, ' ', conv);
			return (0);
		}
		else if (conv->flag & ZERO)
		{
			conv->before = 1;
			option_x(&*pf, conv->min_width - len, ' ', conv);
			return (0);
		}
	}
	return (1);
}

int			conv_x_minus_width_only(t_printf *pf, t_conv *conv, int len)
{
	if (conv->min_width && !conv->precision)
	{
		if (conv->min_width < len)
		{
			(conv->flag & SHARP) ? buffer(&*pf, "0x", 2) : 0;
			return (0);
		}
		if (!(conv_x_minus_width_sup_len(&*pf, conv, len)))
			return (0);
		if (!(conv->flag & PLUS))
		{
			conv->before = 1;
			option_x(&*pf, conv->min_width - len, ' ', conv);
			return (0);
		}
		option_x(&*pf, conv->min_width - len, ' ', conv);
		return (0);
	}
	return (1);
}

int			conv_x_minus_width_and_prec(t_printf *pf, t_conv *conv,
int len, char *str)
{
	if (conv->min_width && conv->precision)
	{
		if (conv->min_width > conv->precision)
		{
			(conv->flag & SHARP) ? (buffer(&*pf, "0x", 2))
			&& (conv->min_width = conv->min_width - 2) : 0;
			conv->before = 0;
			(str[0] == '-') ? special_hhd_reverse_0_n_minus(&*pf, str, '-') : 0;
			option_x(&*pf, conv->precision - len, '0', conv);
			while ((conv->min_width-- - conv->precision))
				buffer(&*pf, " ", 1);
			return (0);
		}
		if (conv->min_width <= conv->precision)
			(str[0] == '-') ? special_hhd_reverse_0_n_minus(&*pf, str, '-') : 0;
		(conv->flag & SHARP) ? (buffer(&*pf, "0x", 2))
		&& (conv->min_width = conv->min_width - 2) : 0;
		conv->before = 3;
		option_x(&*pf, conv->precision - len, '0', conv);
		return (0);
	}
	return (1);
}
