/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_o3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 20:59:56 by achambon          #+#    #+#             */
/*   Updated: 2017/09/19 21:01:10 by achambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		conv_ominus_width_only2(t_printf *pf, t_conv *conv, int len)
{
	(conv->flag & SHARP) ? (conv->min_width--) && (buffer(&*pf, "0", 1)) : 0;
	if (conv->flag & PLUS && !(conv->flag & ZERO) && !(conv->flag & SPACE))
	{
		conv->before = 1;
		option_o(&*pf, conv->min_width - len, ' ', conv);
		return (0);
	}
	(conv->flag & PLUS && !(conv->flag & ZERO)) ? conv->min_width-- : 0;
	if (conv->flag & PLUS && conv->flag & ZERO && !(conv->flag & MODIFIER_HH))
	{
		conv->before = 1;
		option_o(&*pf, conv->min_width - len, ' ', conv);
		return (0);
	}
	else if (conv->flag & ZERO)
	{
		conv->before = 1;
		option_o(&*pf, conv->min_width - len, ' ', conv);
		return (0);
	}
	return (1);
}

int		conv_ominus_width_only(t_printf *pf, t_conv *conv, int len)
{
	if (conv->min_width && !conv->precision)
	{
		if (conv->min_width < len)
		{
			if (conv->flag & SHARP && !(conv->flag & SPACE + PLUS))
				buffer(&*pf, "0", 1);
			return (0);
		}
		else if (conv->min_width > len)
			if (!(conv_ominus_width_only2(&*pf, conv, len)))
				return (0);
		if (!(conv->flag & PLUS))
		{
			conv->before = 1;
			option_o(&*pf, conv->min_width - len, ' ', conv);
			return (0);
		}
		option_o(&*pf, conv->min_width - len, ' ', conv);
		return (0);
	}
	return (1);
}

int		conv_ominus_prec_only(t_printf *pf, t_conv *conv, int len, char *str)
{
	if (!conv->min_width && conv->precision)
	{
		if (conv->flag & SHARP)
		{
			conv->precision--;
		}
		conv->before = 3;
		if (str[0] == '-')
		{
			special_hhd_reverse_0_n_minus(pf, str, '-');
		}
		option_o(&*pf, conv->precision - len, '0', conv);
		return (0);
	}
	return (1);
}

int		conv_ominus_width_and_prec(t_printf *pf, t_conv *conv, int len,
char *str)
{
	if (conv->min_width && conv->precision)
	{
		if (conv->min_width > conv->precision)
		{
			if (conv->flag & SHARP)
			{
				conv->precision--;
				conv->min_width--;
			}
			conv->before = 0;
			if (str[0] == '-')
			{
				special_hhd_reverse_0_n_minus(&*pf, str, '-');
			}
			option_o(&*pf, conv->precision - len, '0', conv);
			while ((conv->min_width-- - conv->precision))
				buffer(&*pf, " ", 1);
			return (0);
		}
	}
	return (1);
}

int		conv_o_minus(t_printf *pf, t_conv *conv, int len, char *str)
{
	if (!conv->min_width && !conv->precision)
		return (pf->i_buf);
	if (!(conv_ominus_width_only(&*pf, conv, len)))
		return (pf->i_buf);
	if (!(conv_ominus_prec_only(&*pf, conv, len, str)))
		return (pf->i_buf);
	if (!(conv_ominus_width_and_prec(&*pf, conv, len, str)))
		return (pf->i_buf);
	if (conv->min_width <= conv->precision)
	{
		if (str[0] == '-')
			special_hhd_reverse_0_n_minus(&*pf, str, '-');
		conv->before = 3;
		option_o(&*pf, conv->precision - len, '0', conv);
		return (0);
	}
	buffer(&*pf, str, len);
	return (0);
}
