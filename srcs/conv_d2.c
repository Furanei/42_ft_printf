/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_d2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 16:04:41 by achambon          #+#    #+#             */
/*   Updated: 2017/09/20 16:32:23 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		conv_d_minus2(t_printf *pf, t_conv *conv, int width_temp,
char *str)
{
	int		len;

	len = ft_strlen(str);
	(conv_d_minus(&*pf, conv, len, str));
	if (conv->min_width > len || width_temp > len)
	{
		if (str[0] == '-')
		{
			width_temp--;
			if (conv->flag & PLUS && !(conv->flag & SPACE + ZERO))
				width_temp++;
		}
		if (conv->flag & MODIFIER_HH && !(conv->flag & SPACE + ZERO) &&
				conv->flag & PLUS && !(conv->precision))
		{
			buffer(&*pf, str, len);
			while (width_temp-- - len)
				buffer(&*pf, " ", 1);
		}
		return (0);
	}
	if (conv->min_width < len && !(conv->flag & SPACE) && !(conv->flag & PLUS)
			&& !conv->precision)
		buffer(&*pf, str, len);
	return (0);
}

int		conv_d_width_only3(t_printf *pf, t_conv *conv, int len, char *str)
{
	if (conv->flag & ZERO)
	{
		if (str[0] == '-')
		{
			str[0] = '0';
			buffer(&*pf, "-", 1);
			while (conv->min_width-- - len - 1)
				buffer(&*pf, "0", 1);
			buffer(&*pf, str, len);
			return (1);
		}
		option_d(&*pf, conv->min_width - len, '0', &*conv);
		return (1);
	}
	if (conv->flag & MODIFIER_HH)
	{
		while (conv->min_width-- - len)
			buffer(&*pf, " ", 1);
		buffer(&*pf, str, len);
		return (1);
	}
	if (conv->flag & PLUS && !(conv->flag & ZERO) && !(conv->flag & SPACE))
		conv->before = 4;
	return (pf->i_buf);
}

int		conv_d_width_only2(t_printf *pf, t_conv *conv, int len, char *str)
{
	if (conv->flag & SPACE && !(conv->flag & PLUS))
		minwidth_decr_add_char_2_buff(&*pf, ' ', &*conv);
	if (conv->flag & PLUS && !(conv->flag & ZERO + MODIFIER_HH))
		conv->min_width--;
	else if (conv->flag & PLUS && conv->flag & ZERO &&
			!(conv->flag & MODIFIER_HH))
	{
		if (str[0] == '-')
		{
			str[0] = '0';
			buffer(&*pf, "-", 1);
			while (conv->min_width-- - len - 1)
				buffer(&*pf, "0", 1);
			buffer(&*pf, str, len);
			return (pf->i_buf);
		}
		buffer(&*pf, "+", 1);
		option_d(&*pf, conv->min_width - 1 - len, '0', &*conv);
		return (pf->i_buf);
	}
	if (conv_d_width_only3(&*pf, conv, len, str) == 1)
		return (pf->i_buf);
	option_d(&*pf, conv->min_width - len, ' ', &*conv);
	return (pf->i_buf);
}

int		conv_d_width_only(t_printf *pf, t_conv *conv, int width_temp, char *str)
{
	int		len;

	len = ft_strlen(str);
	if (conv->min_width < len)
	{
		if (conv->flag & PLUS && width_temp < len)
			return (add_char_and_string_2_buff(&*pf, '+', str, len));
		if (conv->flag & SPACE || ((conv->flag & MODIFIER_HH) &&
					!(conv->flag & ZERO)))
			return (add_char_and_string_2_buff(&*pf, ' ', str, len));
		buffer(&*pf, str, len);
		return (0);
	}
	if (conv->min_width >= len || width_temp >= len)
		return (conv_d_width_only2(&*pf, conv, len, str));
	return (pf->i_buf);
}

int		conv_d_prec_only(t_printf *pf, t_conv *conv, int len, char *str)
{
	conv->before = 3;// ??????????????????????????????
	if (str[0] == '-')
	{
		str[0] = '0';
		buffer(&*pf, "-", 1);
		while (conv->precision-- - len)
			buffer(&*pf, "0", 1);
		buffer(&*pf, str, len);
		return (pf->i_buf);
	}
	if (conv->flag & SPACE && !(conv->flag & PLUS) &&
			!(conv->flag & MODIFIER_HH))
		buffer(&*pf, " ", 1);
	if (conv->flag & PLUS && !(conv->flag & MODIFIER_HH))
		buffer(&*pf, "+", 1);
	if (!(conv->flag & MODIFIER_HH))
	{
		if (conv->precision > len)
			option_d(&*pf, conv->precision - len, '0', &*conv);
		else
			buffer(&*pf, str, len);
		return (pf->i_buf);
	}
	return (0);
}