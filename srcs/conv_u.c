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

#include "../includes/ft_printf.h"

static t_conv	option_u(t_printf *pf, int n, char c, t_conv *conv, char *s)
{
	int		i;
	char	tab[n + 1];
	int 	len;

	len = ft_strlen(s);
	i = 0;
	tab[n] = '\0';
	if (!n)
		return(*conv);
	if (conv->before == 4)
	{
		while (i < n)
			tab[i++] = c;
	//	write(1, tab, n);
		buffer(&*pf, tab, n);
		buffer(&*pf, " ", 1);
		buffer(&*pf, s, len);
	//	ft_putchar('+');
	//	ft_putstr(s);
		return(*conv);
	}
	if (!(conv->before == 3) && conv->before && s)
	{
		if(conv->ox == 1)
			buffer(&*pf, "0x", 2);
			//ft_putstr("0x");
		buffer(&*pf, s, len);
	//	ft_putstr(s);
	}
	if (conv->precision_set == 2)
	{
		buffer(&*pf, "0x", 2);
		//ft_putstr("0x");
		conv->ox = 0;
	}
	if(!(conv->flag & MINUS) || (conv->flag & MINUS && conv->min_width > conv->precision) || conv->before == 3)
	{
		while (i < n)
			tab[i++] = c;
		buffer(&*pf, tab, n);
	//	write(1, tab, n);
	}
	if(((conv->flag & PLUS) && !(conv->flag & ZERO) && !(conv->flag & MINUS) && (conv->flag & (TYPE_D + TYPE_U + TYPE_O)) && !(conv->before == 3) && !conv->flag & MODIFIER_HH))
		buffer(&*pf, "+", 1);
	//	ft_putchar('+');
	if ((conv->before == 0 && s) || conv->before == 3)
	{
		if(conv->ox == 1)
			buffer(&*pf, "0x", 2);
		//	ft_putstr("0x");
		buffer(&*pf, &*s, len);
	//	ft_putstr(s);
	}
	if((conv->flag & MINUS && !(conv->min_width > conv->precision)) && !(conv->before == 3))
	{
		while (i < n)
			tab[i++] = c;
		buffer(&*pf, tab, n);
	//	write(1, tab, n);
	}
	
	return (*conv);
}

int	conv_u_minus(t_printf *pf, t_conv *conv, int len, char *str)
{
	if (!conv->min_width && !conv->precision)
			return(pf->i_buf);
//JUSTE LARGEUR MINIMALE
	if (conv->min_width && !conv->precision)
	{
		if(conv->min_width < len)
		{
			return(0);
		}
		else if(conv->min_width > len)
		{
		//	if(conv->flag & SPACE && !(conv->flag & PLUS) && !(conv->flag & MODIFIER_HH))
		//	{
		//		minwidth_decr_add_char_2_buf(&*pf, ' ', &*conv);
		//	}
			if(conv->flag & PLUS && !(conv->flag & ZERO) && !(conv->flag & SPACE) /*&& !(conv->flag & MODIFIER_HH)*/)
			{
			//	minwidth_decr_add_char_2_buf(&*pf, '+', &*conv);
				conv->before = 1;
				option_u(&*pf, conv->min_width - len, ' ', conv, str);
				return(pf->i_buf);
			}
			if(conv->flag & PLUS && !(conv->flag & ZERO))
			{
				conv->min_width--;
			}
			else if(conv->flag & PLUS && conv->flag & ZERO && !(conv->flag & MODIFIER_HH))
			{
				conv->before = 1;
				//buffer(&*pf, "+", 1);
				//ft_putchar('+');
				option_u(&*pf, conv->min_width - len, ' ', conv, str);
				return(pf->i_buf);
			}
			else if(conv->flag & ZERO)
			{
				conv->before = 1;
				option_u(&*pf, conv->min_width - len, ' ', conv, str);
				return(pf->i_buf);
			}
		}
		if (!(conv->flag & PLUS))
		{
			conv->before = 1;
			option_u(&*pf, conv->min_width - len, ' ', conv, str);
			return(pf->i_buf);
		}
		option_u(&*pf, conv->min_width - len, ' ', conv, str);
		return(0);
	}
//JUSTE PRECISION
	if (!conv->min_width && conv->precision)
	{
		conv->before = 3;
		//if (conv->flag & SPACE && !(conv->flag & PLUS) && !(conv->flag & MODIFIER_HH))
		//	buffer(&*pf, " ", 1);
			//ft_putchar(' ');
		//if (conv->flag & PLUS && !(conv->flag & MODIFIER_HH))
		//	buffer(&*pf, "+", 1);
			//ft_putchar('+');
		if(str[0] == '-')
		{
			special_hhd_reverse_0_n_minus(pf, str, '-');
		}
		option_u(&*pf, conv->precision - len, '0', conv, str);
		return(pf->i_buf);
	}
//LARGEUR MINIMALE ET PRECISION PRESENTES
	if (conv->min_width && conv->precision)
	{
		if(conv->min_width > conv->precision)
		{
			conv->before = 0;
			//if(conv->flag & SPACE && !(conv->flag & PLUS) && !(conv->flag & MODIFIER_HH))
			//{
			//	minwidth_decr_add_char_2_buf(&*pf, ' ', conv);
			//}
			//	if(conv->flag & PLUS && !(conv->flag & MODIFIER_HH))
			//{
			//	minwidth_decr_add_char_2_buf(&*pf, '+', conv);
			//}
			if (str[0] == '-')
			{
				special_hhd_reverse_0_n_minus(&*pf, str, '-');
			}
			option_u(&*pf, conv->precision - len, '0', conv, str);
			while((conv->min_width-- - conv->precision))
				buffer(&*pf, " ", 1);
			//	ft_putchar(' ');
			return(0);
		}
		if (conv->min_width <= conv->precision)
		{
			if(str[0] == '-')
			{
				special_hhd_reverse_0_n_minus(&*pf, str, '-');
			}
			//if(conv->flag & PLUS && !(conv->flag & MODIFIER_HH))
			//{
			//	minwidth_decr_add_char_2_buf(&*pf, '+', conv);
			//}
			//if(conv->flag & SPACE && !(conv->flag & PLUS + MODIFIER_HH))
			//{
			//	minwidth_decr_add_char_2_buf(&*pf, ' ', conv);
			//}
			conv->before = 3;
			option_u(&*pf, conv->precision - len, '0', conv, str);
			return(0);
		}
	}
	buffer(&*pf, str, len);
	//ft_putstr(str);
	return(0);
}


int	print_conv_u(t_printf *pf, char *str, t_conv *conv)
{
	int len ;
	int	width_temp;

	len = ft_strlen(str);
	width_temp = conv->min_width;
	if (!conv->min_width && !conv->precision)
	{
		if(conv->flag & SPACE && !(conv->flag & PLUS))
			return(add_char_and_string_2_buf(&*pf, ' ', str, len));
		if(conv->flag & PLUS)
			return(add_char_and_string_2_buf(&*pf, '+', str, len));
	}
	if (conv->flag & MINUS)
	{
		(conv_o_minus(&*pf, conv, len, str));
		if (conv->min_width > len || width_temp > len)
		{
			if (str[0] == '-')
			{
				width_temp--;
				if (conv->flag & PLUS && !(conv->flag & SPACE + ZERO))
					width_temp++;
			}
				//if (conv->flag & MODIFIER_HH && !(conv->flag & SPACE + ZERO) && conv->flag & PLUS && !(conv->precision))
				//{
				//	buffer(&*pf, str, len);
				//	//ft_putstr(str);
				//	while(width_temp-- - len)
				//		buffer(&*pf, " ", 1);
					//	ft_putchar(' ');
				//}
			return (0);
		}
		if(conv->min_width < len && !(conv->flag & SPACE) && !(conv->flag & PLUS) && !conv->precision)
		{
			buffer(&*pf, str, len);
//			ft_putstr(str);
			return(0);
		}
	}
	if(str[0] == '-' && conv->flag & MINUS)
	{
		// flag_hh = 1;
		conv->min_width--;
	}
//JUSTE LARGEUR MINIMALE
	if (conv->min_width && !conv->precision)
	{
		if(conv->min_width < len)
		{
	//		if(conv->flag & PLUS && width_temp < len && !(conv->flag & SPACE))
	//		{
	//						return(add_char_and_string_2_buf(&*pf, '+', str, len));
	//		}
	//		if(conv->flag & SPACE || ((conv->flag & MODIFIER_HH) && !(conv->flag & ZERO)))
	//		{
	//			return(add_char_and_string_2_buf(&*pf, ' ', str, len));
	//		}
			buffer(&*pf, str, len);
			//ft_putstr(str);
			return(0);
		}
		if(conv->min_width >= len || width_temp >= len)
		{
			if(conv->flag & SPACE && !(conv->flag & PLUS))
			{
				if (conv->flag & ZERO)
					minwidth_decr_add_char_2_buf(&*pf, '0', &*conv);
				else
					minwidth_decr_add_char_2_buf(&*pf, ' ', &*conv);
			//	ft_putchar(' ');
			//	conv->min_width--;
			}
			if(conv->flag & PLUS && !(conv->flag & ZERO + MODIFIER_HH))
				conv->min_width--;
			else if(conv->flag & PLUS && conv->flag & ZERO && !(conv->flag & MODIFIER_HH))
			{
//				buffer(&*pf, "+", 1);
			//	ft_putchar('+');
				option_u(&*pf, conv->min_width - len, '0', &*conv, str);
				return(pf->i_buf);
			}
			else if(conv->flag & ZERO)
			{
				if(str[0] == '-')
				{
					str[0] = '0';
					return(add_char_and_string_2_buf(&*pf, '-', str, len));
				}
				option_u(&*pf, conv->min_width - len, '0', &*conv, str);
				return(pf->i_buf);
			}
			if(conv->flag & MODIFIER_HH /*&& !(conv->flag & ZERO + PLUS + SPACE)*/)
			{
				while(conv->min_width-- - len)
					buffer(&*pf, " ", 1);
					//ft_putchar(' ');
				buffer(&*pf, str, len);
				//ft_putstr(str);
				return(0);
			}
			if(conv->flag & PLUS && !(conv->flag & ZERO) && !(conv->flag & SPACE))
				conv->before = 4;
			option_u(&*pf, conv->min_width - len, ' ', &*conv, str);
			return(pf->i_buf);
		}
	}
//JUSTE PRECISION
	if (!conv->min_width && conv->precision && conv->flag & MINUS)
	{
		return(0);
	}
	if (!conv->min_width && conv->precision && !(conv->flag & MINUS))
	{
		conv->before = 3;
//		if (conv->flag & SPACE && !(conv->flag & PLUS) && !(conv->flag & MODIFIER_HH))
//			buffer(&*pf, " ", 1);
			//ft_putchar(' ');
//		if (conv->flag & PLUS && !(conv->flag & MODIFIER_HH))
//			buffer(&*pf, "+", 1);
			//ft_putchar('+');
			option_u(&*pf, conv->precision - len, '0', &*conv, str);
			return(pf->i_buf);
	}
//LARGEUR MINIMALE ET PRECISION PRESENTES
	if (conv->min_width && conv->precision)
	{
	//	if(conv->flag & MODIFIER_HH)
	//		return(0);
		if(conv->min_width > conv->precision)
		{
			conv->before = 0;
			if(conv->flag & SPACE && !(conv->flag & PLUS))
			{
				minwidth_decr_add_char_2_buf(&*pf, ' ', &*conv);
			}
			if(conv->flag & PLUS)
				conv->min_width--;
			while((conv->min_width-- - conv->precision))
				buffer(&*pf, " ", 1);
				//ft_putchar(' ');
			if(conv->flag & PLUS)
			{
				conv->before = 3;
				buffer(&*pf, " ", 1);
				//ft_putchar('+');
			}
			option_u(&*pf, conv->precision - len, '0', &*conv, str);
			return(0);
		}
		if (conv->min_width <= conv->precision)
		{
		//	conv->flag & PLUS ? buffer(&*pf, "+", 1) : 0;
		//	conv->flag & PLUS ? conv->min_width-- : 0; 
		//	if(conv->flag & SPACE && !(conv->flag & PLUS))
		//	{
		//		minwidth_decr_add_char_2_buf(&*pf, ' ', &*conv);
		//	}
		//	conv->before = 3;
			option_u(&*pf, conv->precision - len, '0', &*conv, str);
			return(0);
		}
	}
	buffer(&*pf, str, len);	
	//ft_putstr(str);
	return(0);
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
	print_conv_u(pf, ft_itoa_base((long long)ptr, 10), conv);
	return;
}
