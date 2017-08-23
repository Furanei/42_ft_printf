/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 15:49:25 by mbriffau          #+#    #+#             */
/*   Updated: 2017/08/23 19:10:36 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static t_conv		*parse_flags(t_printf *pf, t_conv *conv)
{
	while (ft_strchr("#0-+ ", pf->format[pf->i]))
	{ 	
		pf->format[pf->i] == '-' ? conv->flag += MINUS : 0;
		pf->format[pf->i] == '+' ? conv->flag += PLUS : 0;
		pf->format[pf->i] == '#' ? conv->flag += SHARP : 0;
		pf->format[pf->i] == '0' ? conv->flag += ZERO : 0;
		pf->format[pf->i] == ' ' ? conv->flag += SPACE : 0;
		if (pf->format[pf->i] == '\0')
			break;
		pf->i++;
	}
	return (conv);
}

static t_conv	*parse_minimal_width(t_printf *pf, t_conv *conv)
{
	conv->min_width = atoi(&pf->format[pf->i]);
	while (ft_isdigit(pf->format[pf->i]))
		pf->i++;
	if (!(pf->format))
		ft_error_pf(INFO, "error_parse_minimal_width");
	return (conv);
}

static t_conv	*parse_precision(t_printf *pf, t_conv *conv)
{
	conv->precision = atoi(&pf->format[++pf->i]);
	conv->precision > 0 ? conv->precision_set = 1 : 0 ;
	while (ft_isdigit(pf->format[pf->i]))
		pf->i++;
	if (!pf->format[pf->i]) 
		ft_error_pf(INFO, "Invalid format. (After Precision)");
	return (conv);
}

static t_conv	*parse_modifier(t_printf *pf, t_conv *conv)
{	
	if (ft_strchr("CSDUOX", pf->format[pf->i]))
		conv->flag += MODIFIER_L;
	else if (ft_strchr("hljz", pf->format[pf->i]))
	{
		if (pf->format[pf->i] == 'h')
			(pf->format[pf->i + 1] == 'h') ? (conv->flag += MODIFIER_HH) && (pf->i++) : (conv->flag += MODIFIER_H);
		if (pf->format[pf->i] == 'l')
			(pf->format[pf->i + 1] == 'l') ? (conv->flag += MODIFIER_LL) && (pf->i++) : (conv->flag += MODIFIER_L);
		(pf->format[pf->i + 1] == 'j') ? (conv->flag += MODIFIER_J) : 0;
		(pf->format[pf->i + 1] == 'z') ? (conv->flag += (1 << 5)) : 0;
		pf->i++;
	}
	return (conv);
}

static int parse_type(char c)
{
	int ret;

	ret = 0;
	c == 'd' || c == 'D' || c == 'i' ? ret = TYPE_D : 0;
	c == 's' || c == 'S' ? ret = TYPE_S : 0;
	c == 'c' || c == 'C' ? ret = TYPE_C : 0;
	c == 'x' || c == 'X' ? ret = TYPE_X : 0;
	c == 'o' || c == 'O'? ret = TYPE_O : 0;
	c == 'p' ? ret = TYPE_P : 0;
	c == 'u' ? ret = TYPE_U : 0;
	c == 'b' ? ret = TYPE_B : 0;
	return (ret);
}

t_printf	*parse_conversion(t_printf *pf)
{
	t_conv		*conv;

	conv = init_conv();
	parse_flags(&*pf, &*conv);
	parse_minimal_width(&*pf, &*conv);
	(pf->format[pf->i] == '.' ? parse_precision(&*pf, &*conv) : 0);
	conv = parse_modifier(&*pf, conv);
	(!pf->format[pf->i]) ? ft_error_pf(INFO, "error_format_type") : 0;
	conv->flag += parse_type(pf->format[pf->i]);// si il ny a rien apres -> option
	while (!(ft_strchr("cCsSdDipxXuUoO", conv->type)))
		pf->i += 1;
	conversion_specifier(&*pf, &*conv);
	return (pf);
}

