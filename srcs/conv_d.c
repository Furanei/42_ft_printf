/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 15:10:00 by mbriffau          #+#    #+#             */
/*   Updated: 2017/09/16 18:30:45 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*ft_itoa_pf(long long n)
{
	int			i;
	long long	a;
	int			neg;
	char		*str;

	i = 1;
	neg = (n < 0) ? 1 : 0;
	if (n > 0)
		n = n * -1;
	a = n;
	while ((a = a / 10) < 0)
		i++;
	str = (char *)malloc((sizeof(char) * i) + neg + 1);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, i + neg + 1);
	if (neg == 1)
		str[0] = '-';
	i -= 1 - neg;
	while (i-- >= neg)
	{
		str[i + 1] = (-(n % 10) + '0');
		n = n / 10;
	}
	return (str);
}


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

static int	conv_d_minus(t_printf *pf, t_conv *conv, int len, char *str)
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
				minwidth_decr_add_char_2_buff(&*pf, ' ', &*conv);
			}
			if(conv->flag & PLUS && !(conv->flag & ZERO) && !(conv->flag & SPACE) && !(conv->flag & MODIFIER_HH))
			{
				minwidth_decr_add_char_2_buff(&*pf, '+', &*conv);
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
				minwidth_decr_add_char_2_buff(&*pf, ' ', conv);
			if(conv->flag & PLUS && !(conv->flag & MODIFIER_HH))
				minwidth_decr_add_char_2_buff(&*pf, '+', conv);
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
				minwidth_decr_add_char_2_buff(&*pf, '+', conv);
			if(conv->flag & SPACE && !(conv->flag & PLUS + MODIFIER_HH))
				minwidth_decr_add_char_2_buff(&*pf, ' ', conv);
			conv->before = 3;
			option_d(&*pf, conv->precision - len, '0', conv, str);
			return(0);
		}
	}
	buffer(&*pf, str, len);
	return(0);
}

static int		conv_d_hh_nominus(t_printf *pf, t_conv *conv, char *str, int len)
{

//JUSTE LARGEUR MINIMALE
	if (conv->min_width && !conv->precision)
	{
		if(conv->min_width < len)
		{
			if(conv->flag & PLUS && str[0] != '-')
				return(add_char_and_string_2_buff(&*pf, '+', str, len));
			if(conv->flag & SPACE && !(conv->flag & ZERO))
				return(add_char_and_string_2_buff(&*pf, ' ', str, len));
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
					return(add_char_and_string_2_buff(&*pf, '-', str, len));
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
	uintmax_t		apint;
	char	*str;
	int		flag_hh;
	int		width_temp;
	// (intmax_t)((short)va_arg(*ap, int))
	(conv->flag & MODIFIER_H ? apint = (intmax_t)((short)va_arg(pf->ap, int)) : 0); /*short */
	(conv->flag & MODIFIER_HH ? apint = (intmax_t)((char)va_arg(pf->ap, int)) : 0); /*char */
	conv->flag & MODIFIER_L ? apint = va_arg(pf->ap, long) : 0;
	(conv->flag & MODIFIER_LL ? apint = va_arg(pf->ap, long long) : 0);
	(conv->flag & MODIFIER_Z ? apint = (intmax_t)(va_arg(pf->ap, ssize_t)) : 0);
	(conv->flag & MODIFIER_J ? apint = va_arg(pf->ap, uintmax_t) : 0);
	!(conv->flag & 2016) ? apint = va_arg(pf->ap, int) : 0;
	// !apint ? ft_error_pf(INFO, "error_conv_d\n"): 0;
	
	len = ft_strlen(str = ft_itoa_pf((long long)apint));
	
	if(!conv->precision && conv->precision_tick)
	{
			if(conv->min_width)
				while(conv->min_width--)
					buffer(&*pf, " ", 1);
			if(!(ft_strncmp("0", str, len)))
			{
			 return(pf->i_buf);
			}
	}
	if (!conv->min_width && !conv->precision)
	{
		if(conv->flag & PLUS && str[0] != '-')
			return(add_char_and_string_2_buff(&*pf, '+', str, len));
		if(conv->flag & SPACE && !(conv->flag & PLUS) && str[0] != '-')
			return(add_char_and_string_2_buff(&*pf, ' ', str, len));
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
				return(add_char_and_string_2_buff(&*pf, '+', str, len));
			}
			if(conv->flag & SPACE || ((conv->flag & MODIFIER_HH) && !(conv->flag & ZERO)))
			{
				return(add_char_and_string_2_buff(&*pf, ' ', str, len));
			}
			buffer(&*pf, str, len);
			return(0);
		}
		if(conv->min_width >= len || width_temp >= len)
		{
			if(conv->flag & SPACE && !(conv->flag & PLUS))
			{
				minwidth_decr_add_char_2_buff(&*pf, ' ', &*conv);
						//	conv->min_width--;
			}
			if(conv->flag & PLUS && !(conv->flag & ZERO + MODIFIER_HH))
				conv->min_width--;
			else if(conv->flag & PLUS && conv->flag & ZERO && !(conv->flag & MODIFIER_HH))
			{
				if(str[0] == '-')
				{
					str[0] = '0';
					buffer(&*pf, "-", 1);
					while(conv->min_width-- - len - 1)
							buffer(&*pf, "0", 1);
					buffer(&*pf, str, len);
					return(pf->i_buf);
				}
				buffer(&*pf, "+", 1);
							option_d(&*pf, conv->min_width - 1 - len, '0', &*conv, str);
				return(pf->i_buf);
			}
			else if(conv->flag & ZERO)
			{
				if(str[0] == '-')
				{
					str[0] = '0';
					buffer(&*pf, "-", 1);
					while(conv->min_width-- - len - 1)
							buffer(&*pf, "0", 1);
					buffer(&*pf, str, len);
					// return(add_char_and_string_2_buff(&*pf, '-', str, len));
					return(pf->i_buf);
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
		if(str[0] == '-')
			{
				str[0] = '0';
				buffer(&*pf, "-", 1);
				while(conv->precision-- - len)
						buffer(&*pf, "0", 1);
				buffer(&*pf, str, len);
				// return(add_char_and_string_2_buff(&*pf, '-', str, len));
				return(pf->i_buf);
			}
		if (conv->flag & SPACE && !(conv->flag & PLUS) && !(conv->flag & MODIFIER_HH))
			buffer(&*pf, " ", 1);
		if (conv->flag & PLUS && !(conv->flag & MODIFIER_HH))
			buffer(&*pf, "+", 1);
		if(!(conv->flag & MODIFIER_HH))
		{
			if (conv->precision > len)
				option_d(&*pf, conv->precision - len, '0', &*conv, str);
			else
				buffer(&*pf, str, len);
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
				minwidth_decr_add_char_2_buff(&*pf, ' ', &*conv);
			}
			if(conv->flag & PLUS)
				conv->min_width--;
			if(conv->flag & ZERO && str[0] == '-')
			{
				str[0] = '0';
				buffer(&*pf, "-", 1);
				while(conv->min_width-- - len - 1)
						buffer(&*pf, "0", 1);
				buffer(&*pf, str, len);
				return (pf->i_buf);
			}
			// printf("%d\n", conv->min_width);
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
				minwidth_decr_add_char_2_buff(&*pf, ' ', &*conv);
			}
			conv->before = 3;
			option_d(&*pf, conv->precision - len, '0', &*conv, str);
			return(0);
		}
	}
	// printf("%ld at the end\n", apint);
	// printf("%s at the end\n", str);
	buffer(&*pf, str, len);	
	return(0);
}
