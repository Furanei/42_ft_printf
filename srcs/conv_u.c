/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 13:05:40 by achambon          #+#    #+#             */
/*   Updated: 2017/09/21 13:25:21 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"

// static char	*ft_itoa_pf(unsigned long long n)
// {
// 	int			i;
// 	uintmax_t	a;
// 	char		*str;

// 	i = 1;
// 	a = n;
// 	while ((a = a / 10) > 0)
// 		i++;
// 	if (!(str = (char *)malloc((sizeof(char) * i) + 1)))
// 		return (0);
// 	ft_bzero(str, i + 1);
// 	str[i] = '\0';
// 	while (i-- >= 0)
// 	{
// 		str[i] = ((n % 10) + '0');
// 		n = n / 10;
// 	}
// 	return (str);
// }

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
		buffer(&*pf, tab, n);
		buffer(&*pf, " ", 1);
		buffer(&*pf, s, len);
		return(*conv);
	}
	if (!(conv->before == 3) && conv->before && s)
	{
		if(conv->ox == 1)
			buffer(&*pf, "0x", 2);
		buffer(&*pf, s, len);
	}
	if (conv->precision_set == 2)
	{
		buffer(&*pf, "0x", 2);
		conv->ox = 0;
	}
	if(!(conv->flag & MINUS) || (conv->flag & MINUS && conv->min_width > conv->precision) || conv->before == 3)
	{
		while (i < n)
			tab[i++] = c;
		buffer(&*pf, tab, n);
	}
	if(((conv->flag & PLUS) && !(conv->flag & ZERO) && !(conv->flag & MINUS) && (conv->flag & (TYPE_D + TYPE_U + TYPE_O)) && !(conv->before == 3) && !conv->flag & MODIFIER_HH))
		buffer(&*pf, "+", 1);
	if ((conv->before == 0 && s) || conv->before == 3)
	{
		if(conv->ox == 1)
			buffer(&*pf, "0x", 2);
		buffer(&*pf, &*s, len);
	}
	if((conv->flag & MINUS && !(conv->min_width > conv->precision)) && !(conv->before == 3))
	{
		while (i < n)
			tab[i++] = c;
		buffer(&*pf, tab, n);
	}
	
	return (*conv);
}

int	conv_u_minus(t_printf *pf, t_conv *conv, int len, char *str)
{
	if (!conv->min_width && !conv->precision)
			return(pf->i_buf);
	if (conv->min_width && !conv->precision)
	{
		if(conv->min_width < len)
			return(0);
		else if(conv->min_width > len)
		{
			if(conv->flag & PLUS && !(conv->flag & ZERO) && !(conv->flag & SPACE) /*&& !(conv->flag & MODIFIER_HH)*/)
			{
				conv->before = 1;
				option_u(&*pf, conv->min_width - len, ' ', conv, str);
				return(pf->i_buf);
			}
			if(conv->flag & PLUS && !(conv->flag & ZERO))
				conv->min_width--;
			else if(conv->flag & PLUS && conv->flag & ZERO && !(conv->flag & MODIFIER_HH))
			{
				conv->before = 1;
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
	if (!conv->min_width && conv->precision)
	{
		conv->before = 3;
		if(str[0] == '-')
			special_hhd_reverse_0_n_minus(pf, str, '-');
		option_u(&*pf, conv->precision - len, '0', conv, str);
		return(pf->i_buf);
	}
	if (conv->min_width && conv->precision)
	{
		if(conv->min_width > conv->precision)
		{
			conv->before = 0;
			if (str[0] == '-')
				special_hhd_reverse_0_n_minus(&*pf, str, '-');
			option_u(&*pf, conv->precision - len, '0', conv, str);
			while((conv->min_width-- - conv->precision))
				buffer(&*pf, " ", 1);
			return(0);
		}
		if (conv->min_width <= conv->precision)
		{
			if(str[0] == '-')
				special_hhd_reverse_0_n_minus(&*pf, str, '-');
			conv->before = 3;
			option_u(&*pf, conv->precision - len, '0', conv, str);
			return(0);
		}
	}
	buffer(&*pf, str, len);
	return(0);
}


int	print_conv_u(t_printf *pf, char *str, t_conv *conv)
{
	int len ;
	int	width_temp;

	len = ft_strlen(str);
	width_temp = conv->min_width;
	if (conv->flag & MINUS)
	{
		(conv_u_minus(&*pf, conv, len, str));
		if (conv->min_width > len || width_temp > len)
		{
			if (str[0] == '-')
			{
				width_temp--;
				if (conv->flag & PLUS && !(conv->flag & SPACE + ZERO))
					width_temp++;
			}
			return (0);
		}
		if(conv->min_width < len && !(conv->flag & SPACE) && !(conv->flag & PLUS) && !conv->precision)
		{
			buffer(&*pf, str, len);
			return(0);
		}
	}
	if(str[0] == '-' && conv->flag & MINUS)
	{
		conv->min_width--;
	}
	if (conv->min_width && !conv->precision)
	{
		if(conv->min_width < len)
		{
			buffer(&*pf, str, len);
			return(0);
		}
		if(conv->min_width >= len || width_temp >= len)
		{
			if(conv->flag & SPACE && !(conv->flag & PLUS))
			{
				if (conv->flag & ZERO)
					minwidth_decr_add_char_2_buff(&*pf, '0', &*conv);
				else
					minwidth_decr_add_char_2_buff(&*pf, ' ', &*conv);
			}
			if(conv->flag & PLUS && !(conv->flag & ZERO + MODIFIER_HH))
				conv->min_width--;
			else if(conv->flag & PLUS && conv->flag & ZERO && !(conv->flag & MODIFIER_HH))
			{
				option_u(&*pf, conv->min_width - len, '0', &*conv, str);
				return(pf->i_buf);
			}
			else if(conv->flag & ZERO)
			{
				if(str[0] == '-')
				{
					str[0] = '0';
					return(add_char_and_string_2_buff(&*pf, '-', str, len));
				}
				option_u(&*pf, conv->min_width - len, '0', &*conv, str);
				return(pf->i_buf);
			}
			if(conv->flag & MODIFIER_HH)
			{
				while(conv->min_width-- - len)
					buffer(&*pf, " ", 1);
				buffer(&*pf, str, len);
				return(0);
			}
			if(conv->flag & PLUS && !(conv->flag & ZERO) && !(conv->flag & SPACE))
				conv->before = 4;
			option_u(&*pf, conv->min_width - len, ' ', &*conv, str);
			return(pf->i_buf);
		}
	}
	if (!conv->min_width && conv->precision && conv->flag & MINUS)
		return(0);
	if (!conv->min_width && conv->precision && !(conv->flag & MINUS))
	{
		conv->before = 3;
			option_u(&*pf, conv->precision - len, '0', &*conv, str);
			return(pf->i_buf);
	}
	if (conv->min_width && conv->precision)
	{
		if(conv->min_width > conv->precision)
		{
			conv->before = 0;
			if(conv->flag & SPACE && !(conv->flag & PLUS))
				minwidth_decr_add_char_2_buff(&*pf, ' ', &*conv);
			if(conv->flag & PLUS)
				conv->min_width--;
			while((conv->min_width-- - conv->precision))
				buffer(&*pf, " ", 1);
			if(conv->flag & PLUS)
			{
				conv->before = 3;
				buffer(&*pf, " ", 1);
			}
			option_u(&*pf, conv->precision - len, '0', &*conv, str);
			return(0);
		}
		if (conv->min_width <= conv->precision)
		{
			option_u(&*pf, conv->precision - len, '0', &*conv, str);
			return(0);
		}
	}
	buffer(&*pf, str, len);	
	return(0);
}

void	conv_u(t_printf *pf, t_conv *conv)
{
	unsigned long int ptr;

	ptr = 0;
	if (conv->flag & MODIFIER_L)
		ptr = (unsigned long int)ptr;
	else if (conv->flag & MODIFIER_LL)
		ptr = (unsigned long long int)ptr;
	else if (conv->flag & MODIFIER_H)
		ptr = (uint16_t)ptr;
	else if (conv->flag & MODIFIER_HH)
		ptr = (uint8_t)ptr;
	else if (conv->flag & MODIFIER_Z)
		ptr = (size_t)ptr;
	else if (conv->flag & MODIFIER_J)
		ptr = (uintmax_t)ptr;
	else 
	{
		ptr = (unsigned int)ptr;
		ptr = va_arg(pf->ap, unsigned int);
		print_conv_u(pf, ft_uitoa_pf(ptr), conv);
		return;
	}
	ptr = va_arg(pf->ap, uintmax_t);
	print_conv_u(pf, ft_uitoa_pf((uintmax_t)ptr), conv);
	return;
}
