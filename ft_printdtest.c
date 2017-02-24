/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdtest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 03:44:35 by mbriffau          #+#    #+#             */
/*   Updated: 2017/02/24 09:40:34 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


void	parse(char	*format, va_list ap)
{
	if (*format == 'c')
	ft_putchar(va_arg(ap, unsigned));
	if (*format == 'd')
		ft_putnbr(va_arg(ap, int));
	else if (*format == 's')
	{
		pf_putstr(va_arg(ap, char *));
		// ft_putnbr(va_arg(ap, int));
	}
}

int		ft_printf(char *format, ...)
{
	va_list		ap;
	t_printf	p;

	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			if (*format == '%')
				parse(++format, ap);
					// break ;
			// else if (!(pf_buf_add(&buf, (void*)(&(format[i++])), 1)))
			// 	return (-1);
		}
		format++;
	}
	va_end(ap);
	return (0);
}

// char	*conversion_specifier(char *format, va_list ap, t_printf *p)
// {
// 	(ft_strchr("CDSUOB", *format)) ? p->lm.llong = 1 : 0;
// 	p->cs.upcase = (*format == 'X') ? 1 : 0;
// 	(*format == 'x' || *format == 'X') ? pf_putnb_base(16, ap, p) : 0;
// 	(*format == 'u' || *format == 'U') ? pf_putnb_base(10, ap, p) : 0;
// 	(*format == 'o' || *format == 'O') ? pf_putnb_base(8, ap, p) : 0;
// 	(*format == 'b' || *format == 'B') ? pf_putnb_base(2, ap, p) : 0;
// 	(ft_strchr("dDi", *format)) ? pf_putnb(ap, p) : 0;
// 	(*format == 'c' || *format == 'C') ? pf_character(ap, p) : 0;
// 	(*format == 's' && !p->lm.llong) ? p->len += pf_string(ap, p) : 0;
// 	if (*format == 'S' || (*format == 's' && p->lm.llong))
// 		p->len += pf_wide_string(ap, p);
// 	(*format == 'p') ? p->len += print_pointer_address(ap, p) : 0;
// 	(*format == 'n') ? *va_arg(ap, int *) = p->len : 0;
// 	(*format == 'm') ? p->len += ft_printf_putstr(strerror(errno), p) : 0;
// 	(*format == 'f' || *format == 'F') ? pf_putdouble(ap, p) : 0;
// 	if (*format == '{')
// 		return (color(format, p));
// 	if (!ft_strchr("sSpdDibBoOuUxXcC%nmfF", *format))
// 		cs_not_found(format, p);
// 	return (format);
// }