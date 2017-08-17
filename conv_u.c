/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 13:05:40 by achambon          #+#    #+#             */
/*   Updated: 2017/08/11 14:57:31 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/ft_printf.h"


void	print_conv_u(char *str, t_conv *conv)
{
	int len ;

	len = ft_strlen(str);
	if (!(conv->min_width) && !(conv->precision))
		return (ft_putstr(str));

	if(conv->min_width && !(conv->precision))
	{
		if (conv->flag & MINUS)
		{
			conv->before = 1;
			option(conv->min_width - len , ' ', conv, str);
			return;
		}
		if (conv->min_width <= len)
			return(ft_putstr(str));
		conv->before = 0;
		option(conv->min_width - len, ' ', conv, str);
		return;
	}

	if(!(conv->min_width) && conv->precision)
	{
		if (conv->precision <= len)
			return(ft_putstr(str));
		conv->before = 0;
		option(conv->precision - len, '0', conv, str);
		return;
	}

	if(conv->min_width && conv->precision)
	{
		if(conv->precision <= len && conv->min_width <= len)
		{
			ft_putstr(str);
		}
			if(conv->precision > conv->min_width && conv->precision > len)
		{
			conv->before = 0;
			option(conv->precision - len, '0', conv, str);
			return;
		}
		if(conv->min_width > conv->precision && conv->min_width >= len)
		{
			if(conv->flag & MINUS)
			{
				while (conv->precision-- - len)
					ft_putchar('0');
				conv->before = 1;
				option(conv->min_width - len, ' ', conv, str);
				return;
			}
			conv->before = 0;
			while (conv->min_width-- - conv->precision)
				ft_putchar(' ');
			option(conv->precision - len, '0', conv, str);
			return;
		}

}
}
void	conv_u(t_printf *pf, t_conv *conv)
{
	unsigned int ptr;

	ptr = 0;
	conv->flag & MODIFIER_L ? ptr = (unsigned long int)ptr : 0 ;
	conv->flag & MODIFIER_LL ? ptr = (unsigned long long int)ptr : 0;
	conv->flag & MODIFIER_H ? ptr = (uint16_t)ptr : 0;
	conv->flag & MODIFIER_HH ? ptr = (uint8_t)ptr : 0;
	conv->flag & MODIFIER_Z ? ptr = (size_t)ptr : 0;
	conv->flag & MODIFIER_J ? ptr = (uintmax_t)ptr : 0;
	ptr = va_arg(pf->ap, uintmax_t);
	print_conv_u(ft_itoa_base((long long)ptr, 10), conv);
	return;
}
