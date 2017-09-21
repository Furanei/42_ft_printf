/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 15:10:00 by mbriffau          #+#    #+#             */
/*   Updated: 2017/09/21 15:53:59 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		conv_d_width_and_prec2(t_printf *pf, t_conv *conv, int len,
char *str)
{
	conv->before = 0;
	conv->flag & SPACE && !(conv->flag & PLUS) ?
	minwidth_decr_add_char_2_buff(&*pf, ' ', &*conv) : 0;
	conv->flag & PLUS ? conv->min_width-- : 0;
	if (conv->flag & ZERO && str[0] == '-')
	{
		str[0] = '0';
		buffer(&*pf, "-", 1);
		while (conv->min_width-- - len - 1)
			buffer(&*pf, "0", 1);
		buffer(&*pf, str, len);
		return (pf->i_buf);
	}
	while ((conv->min_width-- - conv->precision))
		buffer(&*pf, " ", 1);
	if (conv->flag & PLUS)
	{
		conv->before = 3;
		buffer(&*pf, "+", 1);
	}
	option_d(&*pf, conv->precision - len, '0', &*conv);
	return (0);
}

int		conv_d_width_and_prec(t_printf *pf, t_conv *conv, int len,
char *str)
{
	if (conv->flag & MODIFIER_HH)
		return (0);
	if (conv->min_width > conv->precision)
		return (conv_d_width_and_prec2(&*pf, conv, len, str));
	if (conv->min_width <= conv->precision)
	{
		conv->flag & PLUS ? buffer(&*pf, "+", 1) : 0;
		conv->flag & PLUS ? conv->min_width-- : 0;
		if (conv->flag & SPACE && !(conv->flag & PLUS))
			minwidth_decr_add_char_2_buff(&*pf, ' ', &*conv);
		conv->before = 3;
		option_d(&*pf, conv->precision - len, '0', &*conv);
	}
	return (0);
}

int		conv_d_nowidth_noprec(t_printf *pf, t_conv *conv, char *str, int len)
{
	if (!conv->min_width && !conv->precision)
	{
		if (conv->flag & PLUS && str[0] != '-')
			return (add_char_and_string_2_buff(&*pf, '+', str, len));
		if (conv->flag & SPACE && !(conv->flag & PLUS) && str[0] != '-')
			return (add_char_and_string_2_buff(&*pf, ' ', str, len));
	}
	return (0);
}

int		conv_d_bis(t_printf *pf, t_conv *conv, char *pf->str, int len)
{
	int		width_temp;

	if (conv_d_nowidth_noprec(&*pf, conv, pf->str, len))
		return (pf->i_buf);
	width_temp = conv->min_width;
	if (conv->flag & MODIFIER_HH && !(conv->flag & MINUS))
		return (conv_d_hh_nominus(&*pf, conv, pf->str, len));
	if (conv->flag & MINUS)
		return (conv_d_minus2(&*pf, conv, width_temp, pf->str));
	((pf->str[0] == '-') && (conv->flag & MINUS)) ?
		((conv->min_width--)) : 0;
	if (conv->min_width && !conv->precision)
		return (conv_d_width_only(&*pf, conv, width_temp, pf->str));
	if (!conv->min_width && conv->precision && conv->flag & MINUS)
		return (0);
	if (!conv->min_width && conv->precision && !(conv->flag & MINUS))
		return (conv_d_prec_only(&*pf, conv, len, pf->str));
	if (conv->min_width && conv->precision)
		return (conv_d_width_and_prec(&*pf, conv, len, pf->str));
	buffer(&*pf, pf->str, len);
	return (pf->i_buf);
}

void	conv_d(t_printf *pf, t_conv *conv)
{
	int				len;
	uintmax_t		ptr;

	int		width_temp;

	ptr = ptr_number_base(&*pf, conv->flag);
	pf->str = ft_itoa_printf((long long)ptr);
	len = ft_strlen(pf->str);
	if (!conv->precision && conv->flag & PRECISION && ptr == 0)
	{
		option(&*pf, ' ', conv->min_width);
		return ;
	}
	if (conv_d_nowidth_noprec(&*pf, conv, pf->str, len))
		return ;
	width_temp = conv->min_width;
	if (conv->flag & MODIFIER_HH && !(conv->flag & MINUS))
	{
		conv_d_hh_nominus(&*pf, conv, pf->str, len);
		return ;
	}
	if (conv->flag & MINUS)
	{
		conv_d_minus2(&*pf, conv, width_temp, pf->str);
		return ;
	}
	((pf->str[0] == '-') && (conv->flag & MINUS)) ?
		((conv->min_width--)) : 0;
	if (conv->min_width && !conv->precision)
	{
		conv_d_width_only(&*pf, conv, width_temp, pf->str);
		return ;
	}
	if (!conv->min_width && conv->precision && conv->flag & MINUS)
		return ;
	if (!conv->min_width && conv->precision && !(conv->flag & MINUS))
	{
		conv_d_prec_only(&*pf, conv, len, pf->str);
		return ;
	}
	if (conv->min_width && conv->precision)
	{
		conv_d_width_and_prec(&*pf, conv, len, pf->str);
		return ;
	}
	buffer(&*pf, pf->str, len);
}
