/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_x2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 18:31:25 by achambon          #+#    #+#             */
/*   Updated: 2017/09/19 18:33:10 by achambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		conv_x_minus(t_printf *pf, t_conv *conv, int len, char *str)
{
	if (!conv->min_width && !conv->precision)
		return (pf->i_buf);
	if (!(conv_x_minus_width_only(&*pf, conv, len)))
		return (pf->i_buf);
	if (!conv->min_width && conv->precision)
	{
		if (conv->flag & SHARP)
			buffer(&*pf, "0x", 2);
		conv->before = 3;
		if (str[0] == '-')
		{
			special_hhd_reverse_0_n_minus(pf, str, '-');
		}
		option_x(&*pf, conv->precision - len, '0', conv);
		return (pf->i_buf);
	}
	if (!(conv_x_minus_width_and_prec(&*pf, conv, len, str)))
		return (pf->i_buf);
	buffer(&*pf, str, len);
	return (0);
}

int		conv_x_nowidth_noprec(t_printf *pf, t_conv *conv, char *str, int len)
{
	if (!conv->min_width && !conv->precision)
	{
		if (conv->flag & SPACE && !(conv->flag & PLUS))
		{
			(add_char_and_string_2_buff(&*pf, ' ', str, len));
			return (0);
		}
		if (conv->flag & PLUS)
		{
			(add_char_and_string_2_buff(&*pf, '+', str, len));
			return (0);
		}
		(conv->flag & SHARP && str[0] != '0') ? add_0x(&*pf, &*conv) : 0;
	}
	return (1);
}

int		conv_x_minus2(t_printf *pf, t_conv *conv, char *str, int len)
{
	if (conv->flag & MINUS)
	{
		(conv_x_minus(&*pf, conv, len, str));
		if (conv->min_width > len || conv->width_temp > len)
		{
			if (str[0] == '-')
			{
				conv->width_temp--;
				(conv->flag & PLUS && !(conv->flag & SPACE + ZERO))
				? conv->width_temp++ : 0;
			}
			return (0);
		}
		if (conv->min_width < len && !(conv->flag & SPACE)
		&& !(conv->flag & PLUS) && !conv->precision)
		{
			buffer(&*pf, str, len);
			return (0);
		}
	}
	return (1);
}

int		conv_x_width_only3(t_printf *pf, t_conv *conv, int len, char *str)
{
	if (conv->flag & MODIFIER_HH)
	{
		while (conv->min_width-- - len)
			buffer(&*pf, " ", 1);
		buffer(&*pf, str, len);
		return (0);
	}
	return (1);
}

int		conv_x_width_only2(t_printf *pf, t_conv *conv, int len, char *str)
{
	if (conv->flag & PLUS && conv->flag & ZERO && !(conv->flag & MODIFIER_HH))
	{
		(conv->flag & SHARP) ? (buffer(&*pf, "0x", 2))
		&& (conv->min_width = conv->min_width - 2) : 0;
		option_x(&*pf, conv->min_width - len, '0', &*conv);
		return (0);
	}
	else if (conv->flag & ZERO)
	{
		if (str[0] == '-')
		{
			str[0] = '0';
			(add_char_and_string_2_buff(&*pf, '-', str, len));
			return (0);
		}
		(conv->flag & SHARP) ? (buffer(&*pf, "0x", 2))
		&& (conv->min_width = conv->min_width - 2) : 0;
		option_x(&*pf, conv->min_width - len, '0', &*conv);
		return (0);
	}
	if (!(conv_x_width_only3(&*pf, conv, len, str)))
		return (0);
	return (1);
}
