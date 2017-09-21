/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_o2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 20:52:17 by achambon          #+#    #+#             */
/*   Updated: 2017/09/19 20:58:51 by achambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		conv_o_nowidth_noprec(t_printf *pf, t_conv *conv, char *str, int len)
{
	if (!conv->min_width && !conv->precision)
	{
		(conv->flag & SHARP) ? (buffer(&*pf, "0", 1))
			&& (conv->min_width--) : 0;
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
	}
	return (1);
}

int		conv_o_minus2(t_printf *pf, t_conv *conv, int len, char *str)
{
	if (conv->flag & MINUS)
	{
		(conv_o_minus(&*pf, conv, len, str));
		if (conv->min_width > len || conv->width_temp > len)
		{
			if (str[0] == '-')
			{
				conv->width_temp--;
				if (conv->flag & PLUS && !(conv->flag & SPACE + ZERO))
					conv->width_temp++;
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

int		conv_o_width_only3(t_printf *pf, t_conv *conv, int len, char *str)
{
	if (conv->flag & PLUS && conv->flag & ZERO
			&& !(conv->flag & MODIFIER_HH))
	{
		option_o(&*pf, conv->min_width - len, '0', &*conv);
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
		option_o(&*pf, conv->min_width - len, '0', &*conv);
		return (0);
	}
	if (conv->flag & MODIFIER_HH)
	{
		while (conv->min_width-- - len)
			buffer(&*pf, " ", 1);
		buffer(&*pf, str, len);
		return (0);
	}
	return (1);
}

int		conv_o_width_only2(t_printf *pf, t_conv *conv, int len, char *str)
{
	if (conv->min_width >= len || conv->width_temp >= len)
	{
		if (conv->precision_tick && conv->precision_set == 0
				&& !ft_strcmp("0", str))
		{
			while (conv->min_width--)
				buffer(&*pf, " ", 1);
			return (0);
		}
		(conv->flag & SHARP) ? conv->min_width-- : 0;
		if (conv->flag & SPACE && !(conv->flag & PLUS)
				&& !(conv->flag & SHARP))
		{
			if (conv->flag & ZERO)
				minwidth_decr_add_char_2_buff(&*pf, '0', &*conv);
			else
				minwidth_decr_add_char_2_buff(&*pf, ' ', &*conv);
		}
		(conv->flag & PLUS && !(conv->flag & SHARP)
		&& !(conv->flag & ZERO + MODIFIER_HH)) ? conv->min_width-- : 0;
		if (!(conv_o_width_only3(&*pf, conv, len, str)))
			return (0);
	}
	return (1);
}

int		conv_o_width_only(t_printf *pf, t_conv *conv, int len, char *str)
{
	if (conv->min_width && !conv->precision)
	{
		if (conv->min_width < len)
		{
			(conv->flag & SHARP) ? (buffer(&*pf, "0", 1))
				&& (conv->min_width--) : 0;
			buffer(&*pf, str, len);
			return (0);
		}
		if (!(conv_o_width_only2(&*pf, conv, len, str)))
			return (0);
		(conv->flag & PLUS && !(conv->flag & SHARP)
		&& !(conv->flag & ZERO) && !(conv->flag & SPACE))
			? conv->before = 4 : 0;
		option_o(&*pf, conv->min_width - len, ' ', &*conv);
		return (0);
	}
	return (1);
}
