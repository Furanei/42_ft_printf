/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 15:58:06 by achambon          #+#    #+#             */
/*   Updated: 2017/08/11 00:55:18 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/ft_printf.h"

void	print_p(char *str)
{
	ft_putstr("0x");
	ft_putstr(str);
	return;
}


void	conv_p(t_printf *pf, t_conv *conv)
{
	void *pointer;
	char *str;
	int i;
	int len;
	int	end = 0;

	i = -1;
	conv->ox = 1;
	if(!(pointer = va_arg(pf->ap, void *)))
		return (ft_putstr("0x0"));
	str = ft_itoa_base((long long)pointer, 16);
	len = ft_strlen(str);
	while (str[++i])
		(ft_isalpha(str[i])) ? str[i] = ft_tolower((int)str[i]): 0;
	if (!(conv->min_width) && !(conv->precision))
		return (print_p(str));
	else if(!end && conv->min_width && !conv->precision)
	{
		if (conv->flag & MINUS)
		{
			conv->before = 1;
			conv->min_width = option(conv->min_width - len - 2, ' ', conv, str);
			end += 1;
		}
		else if (!end && conv->min_width <= len)
			return(print_p(str));
		if (!end)
		{
			conv->before = 0;
			conv->min_width = option(conv->min_width - len - 2, ' ', conv, str);
			end += 1;
		}
	}
	else if(!end && !conv->min_width && conv->precision)
	{
		if (conv->precision <= len)
			return(print_p(str));
		conv->before = 0;
		conv->precision_set = 2;
		conv->min_width = option(conv->precision - len, '0', conv, str);
		end += 1;
	}
	else if(!end && conv->min_width && conv->precision)
	{
		if(conv->precision <= len && conv->min_width <= len)
		{
			print_p(str);
		}
		else if(conv->precision > conv->min_width && conv->precision > len)
		{
			conv->before = 0;
			conv->precision_set = 2;
			conv->min_width = option(conv->precision - len, '0', conv, str);
			end += 1;
		}
		else if(!end && (conv->min_width > conv->precision) && (conv->min_width >= len))
		{
			if(conv->flag & MINUS)
			{
				conv->before = 1;
				conv->min_width = option(conv->min_width - len - 2, ' ', conv, str);
				end += 1;
			}
			if (!end)
			{
				conv->before = 0;
				conv->min_width = option(conv->min_width - len - 2, ' ', conv, str);
				end += 1;
			}
		}
	}
	return;
}



