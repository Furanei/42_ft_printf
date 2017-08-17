/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 17:30:50 by achambon          #+#    #+#             */
/*   Updated: 2017/08/11 00:54:05 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/ft_printf.h"

void		print_conv_x(t_conv *conv, int len, char *str)
{
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
return;
}

void		conv_x(t_printf *pf, t_conv *conv, char height)
{

	unsigned int pointer_x;
	char *str;
	int i;
	int len;
	i = 0;

	if(!(pointer_x = va_arg(pf->ap, unsigned int)))
		return(ft_putstr("0x0"));
	str = ft_itoa_base((long long)pointer_x, 16);
	len = ft_strlen(str);

	if (height == 'x')
	{
		while (str[i])
		{
			if (ft_isalpha(str[i]))
			{
				str[i] = ft_tolower((int)str[i]);
			}
			i++;
		}
	}
	print_conv_x(conv, len, str);
	return;
}
