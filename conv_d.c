/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 15:10:00 by mbriffau          #+#    #+#             */
/*   Updated: 2017/08/18 16:43:02 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/ft_printf.h"

static t_conv	option_d(t_printf *pf, int n, char c, t_conv *conv, char *s)
{
	int		i;
	char	tab[n + 1];
	int 	len;

	len = ft_strlen(s);
	i = 0;
	tab[n] = '\0';
	if (!n)
		return(*conv);
	while (i < n)
		tab[i++] = c;
	if (conv->before == 4)
	{
		buffer(&*pf, tab, n);
		buffer(&*pf, "+", 1);
		buffer(&*pf, s, len);
				return(*conv);
	}
	if (!(conv->before == 3) && conv->before && s)
		buffer(&*pf, s, len);
	if(!(conv->flag & MINUS) || (conv->flag & MINUS && conv->min_width > conv->precision) || conv->before == 3)
		buffer(&*pf, tab, n);
	if((conv->flag & PLUS) && !(conv->flag & (ZERO + MINUS + MODIFIER_HH)) && (conv->flag & 0x26000000) && !(conv->before == 3))
		buffer(&*pf, "+", 1);
	if ((conv->before == 0 && s) || conv->before == 3)
		buffer(&*pf, &*s, len);
	if((conv->flag & MINUS && !(conv->min_width > conv->precision)) && !(conv->before == 3))
		buffer(&*pf, tab, n);
	return (*conv);
}

int	conv_d_minus(t_printf *pf, t_conv *conv, int len, char *str)
{
	if (!conv->min_width && !conv->precision)
			return(pf->i_buf);
//JUSTE LARGEUR MINIMALE
	if (conv->min_width && !conv->precision)
	{
		if(conv->min_width < len)
			return(0);
		else if(conv->min_width > len)
		{
			if(conv->flag & SPACE && !(conv->flag & PLUS) && !(conv->flag & MODIFIER_HH))
			{
				minwidth_decr_add_char_2_buf(&*pf, ' ', &*conv);
			}
			if(conv->flag & PLUS && !(conv->flag & ZERO) && !(conv->flag & SPACE) && !(conv->flag & MODIFIER_HH))
			{
				minwidth_decr_add_char_2_buf(&*pf, '+', &*conv);
				conv->before = 1;
				option_d(&*pf, conv->min_width - len, ' ', conv, str);
				return(pf->i_buf);
			}
			if(conv->flag & PLUS && !(conv->flag & ZERO))
			{
				conv->min_width--;
			}
			else if(conv->flag & PLUS && conv->flag & ZERO && !(conv->flag & MODIFIER_HH))
			{
				conv->before = 1;
				buffer(&*pf, "+", 1);
				option_d(&*pf, conv->min_width - 1 - len, ' ', conv, str);
				return(pf->i_buf);
			}
			else if(conv->flag & ZERO)
			{
				conv->before = 1;
				option_d(&*pf, conv->min_width - len, ' ', conv, str);
				return(pf->i_buf);
			}
		}
		if (!(conv->flag & PLUS))
		{
			conv->before = 1;
			option_d(&*pf, conv->min_width - len, ' ', conv, str);
			return(pf->i_buf);
		}
		option_d(&*pf, conv->min_width - len, ' ', conv, str);
		return(0);
	}
//JUSTE PRECISION
	if (!conv->min_width && conv->precision)
	{
		conv->before = 3;
		if (conv->flag & SPACE && !(conv->flag & PLUS) && !(conv->flag & MODIFIER_HH))
			buffer(&*pf, " ", 1);
		if (conv->flag & PLUS && !(conv->flag & MODIFIER_HH))
			buffer(&*pf, "+", 1);
		if(str[0] == '-')
		{
			special_hhd_reverse_0_n_minus(pf, str, '-');
		}
		option_d(&*pf, conv->precision - len, '0', conv, str);
		return(pf->i_buf);
	}
//LARGEUR MINIMALE ET PRECISION PRESENTES
	if (conv->min_width && conv->precision)
	{
		if(conv->min_width > conv->precision)
		{
			conv->before = 0;
			if(conv->flag & SPACE && !(conv->flag & PLUS) && !(conv->flag & MODIFIER_HH))
				minwidth_decr_add_char_2_buf(&*pf, ' ', conv);
			if(conv->flag & PLUS && !(conv->flag & MODIFIER_HH))
				minwidth_decr_add_char_2_buf(&*pf, '+', conv);
			if (str[0] == '-')
				special_hhd_reverse_0_n_minus(&*pf, str, '-');
			option_d(&*pf, conv->precision - len, '0', conv, str);
			while((conv->min_width-- - conv->precision))
				buffer(&*pf, " ", 1);
						return(0);
		}
		if (conv->min_width <= conv->precision)
		{
			if(str[0] == '-')
				special_hhd_reverse_0_n_minus(&*pf, str, '-');
			if(conv->flag & PLUS && !(conv->flag & MODIFIER_HH))
				minwidth_decr_add_char_2_buf(&*pf, '+', conv);
			if(conv->flag & SPACE && !(conv->flag & PLUS + MODIFIER_HH))
				minwidth_decr_add_char_2_buf(&*pf, ' ', conv);
			conv->before = 3;
			option_d(&*pf, conv->precision - len, '0', conv, str);
			return(0);
		}
	}
	buffer(&*pf, str, len);
	return(0);
}
int		conv_d_hh_nominus(t_printf *pf, t_conv *conv, char *str, int len)
{

//JUSTE LARGEUR MINIMALE
	if (conv->min_width && !conv->precision)
	{
		if(conv->min_width < len)
		{
			if(conv->flag & PLUS && str[0] != '-')
				return(add_char_and_string_2_buf(&*pf, '+', str, len));
			if(conv->flag & SPACE && !(conv->flag & ZERO))
				return(add_char_and_string_2_buf(&*pf, ' ', str, len));
			buffer(&*pf, str, len);
			return(0);
		}
		if(conv->min_width >= len)
		{
			if(conv->flag & PLUS && !(conv->flag & ZERO + MODIFIER_HH))
				conv->min_width--;
			else if(str[0] != '-' && conv->flag & PLUS && conv->flag & ZERO && !(conv->flag & MODIFIER_HH))
			{
				buffer(&*pf, "+", 1);
				option_d(&*pf, conv->min_width - 1 - len, '0', conv, str);
				return(pf->i_buf);
			}
			else if(conv->flag & ZERO)
			{
				if(str[0] == '-')
				{
					str[0] = '0';
					return(add_char_and_string_2_buf(&*pf, '-', str, len));
				}
				option_d(&*pf, conv->min_width - len, '0', conv, str);
				return(pf->i_buf);
			}
			option_d(&*pf, conv->min_width - len, ' ', conv, str);
			return(pf->i_buf);
		}
	}
//JUSTE PRECISION
	if (!conv->min_width && conv->precision)
	{
		conv->before = 3;
		if (conv->flag & SPACE && !(conv->flag & PLUS) && !(conv->flag & MODIFIER_HH))
			buffer(&*pf, " ", 1);
		if (conv->flag & PLUS && !(conv->flag & MODIFIER_HH))
			buffer(&*pf, "+", 1);
		if(str[0] == '-')
		{
			special_hhd_reverse_0_n_minus(pf, str, '-');
		}
		option_d(&*pf, conv->precision - len, '0', conv, str);
		return(pf->i_buf);
			return(0);
	}
//LARGEUR MINIMALE ET PRECISION PRESENTES
	if (conv->min_width && conv->precision)
	{
		if(conv->min_width > conv->precision)
		{
			conv->before = 0;
			if(conv->flag & ZERO && !(conv->flag & PLUS))
				conv->min_width--;
			if(conv->flag & SPACE)
			{
				conv->min_width--;
				if(conv->flag & PLUS + ZERO)
					buffer(&*pf, " ", 1);
			}
			if(conv->flag & PLUS)
				conv->min_width--;
			while((conv->min_width-- - conv->precision))
				buffer(&*pf, " ", 1);
			if(conv->flag & PLUS && str[0] != '-')
			{
				conv->before = 3;
				buffer(&*pf, "+", 1);
			}
			if(str[0] == '-')
				special_hhd_reverse_0_n_minus(&*pf, str, '-');
			option_d(&*pf, conv->precision - len, '0', conv, str);
			return(0);
		}
		if (conv->min_width <= conv->precision)
		{
			if(str[0] == '-')
				special_hhd_reverse_0_n_minus(&*pf, str, '-');
			conv->before = 3;
			option_d(&*pf, conv->precision - len, '0', conv, str);
			return(0);
		}
	}
	buffer(&*pf, str, len);	
	return(0);
}

int		conv_d(t_printf *pf, t_conv *conv)
{
	int		len;
	int		apint;
	char	*str;
	int		flag_hh;
	int		width_temp;
	apint = (conv->flag & MODIFIER_H ? va_arg(pf->ap, short) : 0);
	apint = (conv->flag & MODIFIER_HH ? va_arg(pf->ap, char) : 0);
	apint = (conv->flag & MODIFIER_L ? va_arg(pf->ap, long) : 0);
	apint = (conv->flag & MODIFIER_LL ? va_arg(pf->ap, long long) : 0);
	apint = (conv->flag & MODIFIER_Z ? va_arg(pf->ap, size_t) : 0);
	apint = (conv->flag & MODIFIER_J ? va_arg(pf->ap, uintmax_t) : 0);
	apint = !(conv->flag & 2016) ? va_arg(pf->ap, int) : 0;
	!apint ? ft_error_pf(INFO, "error_conv_d\n"): 0;
	len = ft_strlen(str = ft_itoa(apint));
	if (!conv->min_width && !conv->precision)
	{
		if(conv->flag & SPACE && !(conv->flag & PLUS))
			return(add_char_and_string_2_buf(&*pf, ' ', str, len));
		if(conv->flag & PLUS)
			return(add_char_and_string_2_buf(&*pf, '+', str, len));
	}
	width_temp = conv->min_width;
	if (conv->flag & MODIFIER_HH && !(conv->flag & MINUS))
	{
		conv_d_hh_nominus(&*pf, conv, str, len);
		return(0);
	}
	if (conv->flag & MINUS)
	{
		(conv_d_minus(&*pf, conv, len, str));
		if (conv->min_width > len || width_temp > len)
		{
			if (str[0] == '-')
			{
				width_temp--;
				if (conv->flag & PLUS && !(conv->flag & SPACE + ZERO))
					width_temp++;
			}
				if (conv->flag & MODIFIER_HH && !(conv->flag & SPACE + ZERO) && conv->flag & PLUS && !(conv->precision))
				{
					buffer(&*pf, str, len);
					while(width_temp-- - len)
						buffer(&*pf, " ", 1);
									}
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
		flag_hh = 1;
		conv->min_width--;
	}
//JUSTE LARGEUR MINIMALE
	if (conv->min_width && !conv->precision)
	{
		if(conv->min_width < len)
		{
			if(conv->flag & PLUS && width_temp < len)
			{
				return(add_char_and_string_2_buf(&*pf, '+', str, len));
			}
			if(conv->flag & SPACE || ((conv->flag & MODIFIER_HH) && !(conv->flag & ZERO)))
			{
				return(add_char_and_string_2_buf(&*pf, ' ', str, len));
			}
			buffer(&*pf, str, len);
			return(0);
		}
		if(conv->min_width >= len || width_temp >= len)
		{
			if(conv->flag & SPACE && !(conv->flag & PLUS))
			{
				minwidth_decr_add_char_2_buf(&*pf, ' ', &*conv);
						//	conv->min_width--;
			}
			if(conv->flag & PLUS && !(conv->flag & ZERO + MODIFIER_HH))
				conv->min_width--;
			else if(conv->flag & PLUS && conv->flag & ZERO && !(conv->flag & MODIFIER_HH))
			{
				buffer(&*pf, "+", 1);
							option_d(&*pf, conv->min_width - 1 - len, '0', &*conv, str);
				return(pf->i_buf);
			}
			else if(conv->flag & ZERO)
			{
				if(str[0] == '-')
				{
					str[0] = '0';
					return(add_char_and_string_2_buf(&*pf, '-', str, len));
				}
				option_d(&*pf, conv->min_width - len, '0', &*conv, str);
				return(pf->i_buf);
			}
			if(conv->flag & MODIFIER_HH /*&& !(conv->flag & ZERO + PLUS + SPACE)*/)
			{
				while(conv->min_width-- - len)
					buffer(&*pf, " ", 1);
				buffer(&*pf, str, len);
				return(0);
			}
			if(conv->flag & PLUS && !(conv->flag & ZERO) && !(conv->flag & SPACE))
				conv->before = 4;
			option_d(&*pf, conv->min_width - len, ' ', &*conv, str);
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
		if (conv->flag & SPACE && !(conv->flag & PLUS) && !(conv->flag & MODIFIER_HH))
			buffer(&*pf, " ", 1);
		if (conv->flag & PLUS && !(conv->flag & MODIFIER_HH))
			buffer(&*pf, "+", 1);
		if(!(conv->flag & MODIFIER_HH))
		{
			option_d(&*pf, conv->precision - len, '0', &*conv, str);
			return(pf->i_buf);
		}
		else
			return(0);
	}
//LARGEUR MINIMALE ET PRECISION PRESENTES
	if (conv->min_width && conv->precision)
	{
		if(conv->flag & MODIFIER_HH)
			return(0);
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
			if(conv->flag & PLUS)
			{
				conv->before = 3;
				buffer(&*pf, "+", 1);
			}
			option_d(&*pf, conv->precision - len, '0', &*conv, str);
			return(0);
		}
		if (conv->min_width <= conv->precision)
		{
			conv->flag & PLUS ? buffer(&*pf, "+", 1) : 0;
			conv->flag & PLUS ? conv->min_width-- : 0; 
			if(conv->flag & SPACE && !(conv->flag & PLUS))
			{
				minwidth_decr_add_char_2_buf(&*pf, ' ', &*conv);
			}
			conv->before = 3;
			option_d(&*pf, conv->precision - len, '0', &*conv, str);
			return(0);
		}
	}
	buffer(&*pf, str, len);	
	return(0);
}
