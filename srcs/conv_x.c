/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 17:30:50 by achambon          #+#    #+#             */
/*   Updated: 2017/09/21 14:08:19 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		conv_x_width_only(t_printf *pf, t_conv *conv, int len, char *str)
{
	if (conv->min_width && !conv->precision)
	{
		if (conv->min_width < len)
		{
			if (conv->flag & SHARP && !(conv->flag & MINUS))
				add_0x(&*pf, &*conv);
			buffer(&*pf, str, len);
			return (0);
		}
		if (conv->min_width >= len || conv->width_temp >= len)
		{
			(conv->flag & PLUS && !(conv->flag & ZERO + MODIFIER_HH + SHARP))
				? conv->min_width-- : 0;
			if (!(conv_x_width_only2(&*pf, conv, len, str)))
				return (0);
			(conv->flag & PLUS && !(conv->flag & ZERO) && !(conv->flag & SPACE))
				? conv->before = 4 : 0;
			(conv->flag & SHARP) ? (conv->ox = 1)
				&& (conv->min_width = conv->min_width - 2) : 0;
			option_x(&*pf, conv->min_width - len, ' ', &*conv);
			return (0);
		}
	}
	return (1);
}

int		print_conv_x3(t_printf *pf, t_conv *conv, int len)
{
	if (!conv->min_width && conv->precision && conv->precision > len
			&& !(conv->flag & MINUS))
	{
		conv->before = 3;
		(conv->flag & SHARP) ? buffer(&*pf, "0x", 2) : 0;
		option_x(&*pf, conv->precision - len, '0', &*conv);
		return (0);
	}
	return (1);
}

int		print_conv_x2(t_printf *pf, t_conv *conv, int len, char *str)
{
	if (!(print_conv_x3(&*pf, conv, len)))
		return (0);
	if (conv->min_width && conv->precision)
	{
		if (conv->min_width > conv->precision)
		{
			conv->before = 0;
			(conv->flag & PLUS) ? conv->min_width-- : 0;
			(conv->flag & SHARP) ? (conv->ox = 2)
				&& (conv->min_width = conv->min_width - 2) : 0;
			while ((conv->min_width-- - len))
				buffer(&*pf, " ", 1);
			(conv->flag & PLUS) ? (conv->before = 3)
				&& (buffer(&*pf, " ", 1)) : 0;
			buffer(&*pf, str, len);
			return (0);
		}
		if (conv->min_width <= conv->precision)
		{
			(conv->flag & SHARP) ? buffer(&*pf, "0x", 2) : 0;
			option_x(&*pf, conv->precision - len, '0', &*conv);
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

int		print_conv_x(t_printf *pf, t_conv *conv, int len, char *str)
{
	conv->width_temp = conv->min_width;
	if (!conv->precision && conv->precision_tick)
	{
		if_tick_but_no_prec(&*pf, conv);///////////tick
		if (!(ft_strncmp("0", str, len)))
			return (pf->i_buf);
	}
	if (!(conv_x_nowidth_noprec(&*pf, conv, str, len)))
		return (pf->i_buf);
	if (!(conv_x_minus2(&*pf, conv, str, len)))
		return (pf->i_buf);
	(str[0] == '-' && conv->flag & MINUS) ? conv->min_width-- : 0;
	if (!(conv_x_width_only(&*pf, conv, len, str)))
		return (pf->i_buf);
	if (!conv->min_width && conv->precision && conv->flag & MINUS)
		return (0);
	if (!(print_conv_x2(&*pf, conv, len, str)))
		return (pf->i_buf);
	buffer(&*pf, str, len);
	return (0);
}

void	conv_x(t_printf *pf, t_conv *conv)
{
	uintmax_t	va_ptr;
	char		*str;

	va_ptr = 1;
	conv->flag & MODIFIER_L ? ((va_ptr = (unsigned long int)va_ptr) &&
			(va_ptr = va_arg(pf->ap, unsigned long int))) : 0;
	conv->flag & MODIFIER_LL ? ((va_ptr = (unsigned long long int)va_ptr) &&
			(va_ptr = va_arg(pf->ap, unsigned long long int))) : 0;
	conv->flag & MODIFIER_H ? ((va_ptr = (uint16_t)va_ptr) &&
			(va_ptr = va_arg(pf->ap, unsigned int))) : 0;
	conv->flag & MODIFIER_HH ? ((va_ptr = (uint8_t)va_ptr) &&
			(va_ptr = va_arg(pf->ap, unsigned int))) : 0;
	conv->flag & MODIFIER_Z ? ((va_ptr = (size_t)va_ptr) &&
			(va_ptr = va_arg(pf->ap, size_t))) : 0;
	conv->flag & MODIFIER_J ? ((va_ptr = (uintmax_t)va_ptr) &&
			(va_ptr = va_arg(pf->ap, uintmax_t))) : 0;
	!(conv->flag & 0x7E0) ? ((va_ptr = (unsigned int)va_ptr) &&
			(va_ptr = va_arg(pf->ap, unsigned int))) : 0;
	str = ft_itoa_base((long long)va_ptr, 16);
	pf->str = str;
	conv->flag & MODIFIER_X ? 0 : (str = ft_str_tolower(str));
	print_conv_x(pf, conv, ft_strlen(str), str);
	return ;
}
