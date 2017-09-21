/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 19:35:35 by mbriffau          #+#    #+#             */
/*   Updated: 2017/09/21 14:08:05 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		conv_o_prec_only(t_printf *pf, t_conv *conv, int len)
{
	if (!conv->min_width && conv->precision && !(conv->flag & MINUS))
	{
		if (conv->flag & SHARP)
			conv->precision--;
		conv->before = 3;
		option_o(&*pf, conv->precision - len, '0', &*conv);
		return (0);
	}
	return (1);
}

int		conv_o_width_and_prec(t_printf *pf, t_conv *conv, int len)
{
	if (conv->min_width && conv->precision)
	{
		if (conv->min_width > conv->precision)
		{
			(conv->flag & SHARP) ? (conv->precision--)
				&& (conv->min_width--) : 0;
			conv->before = 0;
			(conv->flag & SPACE && !(conv->flag & PLUS))
				? minwidth_decr_add_char_2_buff(&*pf, ' ', &*conv) : 0;
			(conv->flag & PLUS) ? conv->min_width-- : 0;
			while ((conv->min_width-- - conv->precision))
				buffer(&*pf, " ", 1);
			(conv->flag & PLUS) ? (conv->before = 3)
				&& (buffer(&*pf, " ", 1)) : 0;
			option_o(&*pf, conv->precision - len, '0', &*conv);
			return (0);
		}
		if (conv->min_width <= conv->precision)
		{
			(conv->flag & SHARP) ? conv->precision-- : 0;
			option_o(&*pf, conv->precision - len, '0', &*conv);
			return (0);
		}
	}
	return (1);
}

static int		if_tick_but_no_prec(t_printf *pf, t_conv *conv)//delete
{
	if(conv->min_width)
		while(conv->min_width--)
			buffer(&*pf, " ", 1);
	return(pf->i_buf);
}

int		conv_o_tick_noprec(t_printf *pf, t_conv *conv, char *str, int len)
{
	if (!conv->precision && conv->precision_tick && !conv->min_width)
	{
		if_tick_but_no_prec(&*pf, conv);//////////////////////tick
		if ((!(ft_strncmp("0", str, len)) && conv->flag & SHARP))
		{
			buffer(&*pf, str, len);
			return (0);
		}
	}
	return (1);
}

int		print_conv_o(t_printf *pf, char *str, t_conv *conv)
{
	int len;

	len = ft_strlen(str);
	pf->len = len;
	conv->width_temp = conv->min_width;
	if (!(conv_o_tick_noprec(&*pf, conv, str, len)))
		return (pf->i_buf);
	if (!(conv_o_nowidth_noprec(&*pf, conv, str, len)))
		return (pf->i_buf);
	if (!(conv_o_minus2(&*pf, conv, len, str)))
		return (pf->i_buf);
	(str[0] == '-' && conv->flag & MINUS) ? conv->min_width-- : 0;
	if (!(conv_o_width_only(&*pf, conv, len, str)))
		return (pf->i_buf);
	if (conv->precision_tick && conv->precision_set == 0
	&& !ft_strcmp("0", str))
		return (pf->i_buf);
	if (!conv->min_width && conv->precision && conv->flag & MINUS)
		return (0);
	if (!(conv_o_prec_only(&*pf, conv, len)))
		return (pf->i_buf);
	if (!(conv_o_width_and_prec(&*pf, conv, len)))
		return (pf->i_buf);
	buffer(&*pf, str, len);
	return (0);
}

void	conv_o(t_printf *pf, t_conv *conv)
{
	uintmax_t ptr;

	ptr = 0;
	ptr = ptr_number(&*pf, conv->flag);
	pf->str = ft_itoa_base((long long)ptr, 8);
	print_conv_o(pf, pf->str, conv);
	return ;
}
