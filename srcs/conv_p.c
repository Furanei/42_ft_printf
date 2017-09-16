/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 15:58:06 by achambon          #+#    #+#             */
/*   Updated: 2017/08/28 16:20:49 by achambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"


static t_conv	option_p(t_printf *pf, int n, char c, t_conv *conv, char *s)
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
	buffer(&*pf, tab, n);
	
	return (*conv);
}



void	print_p(t_printf *pf, int len, char *str)
{
	buffer(&*pf, "0x", 2);
	buffer(&*pf, str, len);
	return;
}


int	conv_p_minus(t_printf *pf, t_conv *conv, int len, char *str)
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
		print_p(&*pf, len, str);
		option_p(&*pf, conv->min_width - len - 2, ' ', conv, str);
		return(0);
	}
//JUSTE PRECISION
	if (!conv->min_width && conv->precision)
	{
		buffer(&*pf, "0x", 2);
		option_p(&*pf, conv->precision - len - 2, '0', conv, str);
		return(pf->i_buf);
	}
//LARGEUR MINIMALE ET PRECISION PRESENTES
	if (conv->min_width && conv->precision)
	{
		buffer(&*pf, "0x", 2);
		if(conv->min_width > conv->precision)
		{
			option_p(&*pf, conv->precision - len, '0', conv, str);
			buffer(&*pf, str, len);
			option_p(&*pf, conv->min_width - conv->precision - 2, ' ', conv, str);
			return(0);
		}
		if (conv->min_width <= conv->precision)
		{
			option_p(&*pf, conv->precision - len, '0', conv, str);
		}
	}
	buffer(&*pf, str, len);
	return(0);
}


int	conv_p(t_printf *pf, t_conv *conv)
{
	void *pointer;
	char *str;
	int i;
	int len;
	int	end;

	end = 0;
	i = 0;
	conv->ox = 1;
	if(!(pointer = va_arg(pf->ap, void *)))
	{
		buffer(&*pf, "0x0", 3);
		return(0);
	}
	str = ft_itoa_base((long long)pointer, 16);
	len = ft_strlen(str);
	while (str[i++])
		(ft_isalpha(str[i])) ? str[i] = ft_tolower((int)str[i]): 0;
	if (!(conv->min_width) && !(conv->precision))
	{
		print_p(pf, len ,str);
		return (0);
	}
	if (conv->flag & MINUS)
	{
		(conv_p_minus(&*pf, conv, len, str));
		if (conv->min_width > len)
		{
			
			return (0);
		}
		if(conv->min_width < len )
		{
			print_p(&*pf, len, str);
			return(0);
		}
	}
//JUSTE LARGEUR MINIMALE
	if (conv->min_width && !conv->precision)
	{
		if(conv->min_width < len)
		{
			print_p(&*pf, len, str);
			return(0);
		}
		if(conv->min_width >= len)
		{
			if(conv->flag & ZERO)
			{
				buffer(&*pf, "0x", 2);
				option_p(&*pf, conv->min_width - len - 2, '0', conv, str);
				buffer(&*pf, str, len);
				return(0);
			}
			option_p(&*pf, conv->min_width - len - 2, ' ', conv, str);
			print_p(&*pf, len, str);
			return(pf->i_buf);
		}
	}
//JUSTE PRECISION
	if (!conv->min_width && conv->precision && conv->flag & MINUS)
	{
		buffer(&*pf, str, len);
		return(0);
	}
	if (!conv->min_width && conv->precision && !(conv->flag & MINUS))
	{
		buffer(&*pf, "0x", 2);
		option_p(&*pf, conv->precision - len, '0', conv, str);
		buffer(&*pf, str, len);
		return(pf->i_buf);
	}
//LARGEUR MINIMALE ET PRECISION PRESENTES
	if (conv->min_width && conv->precision)
	{
		if(conv->min_width > conv->precision)
		{
			option_p(&*pf, conv->min_width - conv->precision - 2, ' ', conv, str);
			buffer(&*pf, "0x", 2);
			option_p(&*pf, conv->precision - len, '0', conv, str);
		}
		if (conv->min_width <= conv->precision)
		{
			buffer(&*pf, "0x", 2);
			option_p(&*pf, conv->precision - len, '0', conv, str);
		}
	}
	buffer(&*pf, str, len);	
	return(0);
}


















// else if(!end && conv->min_width && !conv->precision)
// 	{
// 		if (conv->flag & MINUS)
// 		{
// 			conv->before = 1;
// 			conv->min_width = option(pf, conv->min_width - len - 2, ' ', conv, str);
// 			end += 1;
// 		}
// 		else if (!end && conv->min_width <= len)
// 			return(print_p(pf, len, str));
// 		if (!end)
// 		{
// 			conv->before = 0;
// 			conv->min_width = option(pf, conv->min_width - len - 2, ' ', conv, str);
// 			end += 1;
// 		}
// 	}
// 	else if(!end && !conv->min_width && conv->precision)
// 	{
// 		if (conv->precision <= len)
// 			return(print_p(pf, len, str));
// 		conv->before = 0;
// 		conv->precision_set = 2;
// 		conv->min_width = option(pf, conv->precision - len, '0', conv, str);
// 		end += 1;
// 	}
// 	else if(!end && conv->min_width && conv->precision)
// 	{
// 		if(conv->precision <= len && conv->min_width <= len)
// 		{
// 			print_p(pf, len, str);
// 		}
// 		else if(conv->precision > conv->min_width && conv->precision > len)
// 		{
// 			conv->before = 0;
// 			conv->precision_set = 2;
// 			conv->min_width = option(pf, conv->precision - len, '0', conv, str);
// 			end += 1;
// 		}
// 		else if(!end && (conv->min_width > conv->precision) && (conv->min_width >= len))
// 		{
// 			if(conv->flag & MINUS)
// 			{
// 				conv->before = 1;
// 				conv->min_width = option(pf, conv->min_width - len - 2, ' ', conv, str);
// 				end += 1;
// 			}
// 			if (!end)
// 			{
// 				conv->before = 0;
// 				conv->min_width = option(pf, conv->min_width - len - 2, ' ', conv, str);
// 				end += 1;
// 			}
// 		}
// 	}
// 	return;
