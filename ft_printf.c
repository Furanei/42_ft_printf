/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 03:44:35 by mbriffau          #+#    #+#             */
/*   Updated: 2017/02/23 19:42:42 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


int		ft_printf(char *format, ...)
{
	va_list		ap;
	t_printf	p;

	va_start(ap, format);
	p.len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			if (!format[1] || (format[1] == ' ' && (!format[2]
			|| (!format[3] && format[2] == 'h'))))
				break ;
			p.printed = 0;
			format = parse_optionals(++format, ap, &p);
			if (*format == '%')
				p.len += percent_char(&p);
			format = conversion_specifier(format, ap, &p);
		}
		else
			pf_putchar(*format, &p);
		++format;
	}
	va_end(ap);
	return (p.len);
}