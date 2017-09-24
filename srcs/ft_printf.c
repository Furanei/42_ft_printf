/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 15:41:18 by mbriffau          #+#    #+#             */
/*   Updated: 2017/09/24 18:41:21 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		print_buffer(char *s, int size)
{
	write(1, s, size);
}

static t_printf	*print_until(t_printf *pf, char *format, int i, int c)
{
	int		n;

	n = 0;
	while (format[i + n] != '\0' && format[i + n] != c)
	{
		n++;
		if (format[i + n] == '{')
			break ;
	}
	buffer(&*pf, &format[pf->i], n);
	pf->i += n;
	return (pf);
}

int				ft_printf(char *format, ...)
{
	t_printf	pf;
	char		tab[BUFFER_SIZE];

	ft_bzero(&pf, sizeof(pf));
	ft_bzero(&tab[0], BUFFER_SIZE);
	va_start(pf.ap, format);
	pf.format = format;
	pf.buffer = &*tab;
	pf.i_buf = 0;
	while (pf.format[pf.i])
	{
		if (pf.format[pf.i] == '{')
		{
			while (pf.format[pf.i] == '{')
				parsing_color(&pf);
		}

		if (pf.format[pf.i] == '%')
		{
			pf.i++;
			if (pf.format)
				parse_conversion(&pf);
		}
		else if (pf.format[pf.i])
			print_until(&pf, pf.format, pf.i, '%');
	}
	pf.buffer && pf.i_buf ? print_buffer(pf.buffer, pf.i_buf) : 0;
	va_end(pf.ap);
	return (pf.i_buf + pf.add_buffer - pf.subtract_buffer);
}

t_printf		*buffer(t_printf *pf, char *saved, int len)
{
	int			i;

	i = 0;
	if ((pf->i_buf + len) >= BUFFER_SIZE)
	{
		pf->add_buffer += pf->i_buf;
		print_buffer(pf->buffer, pf->i_buf);
		pf->i_buf = 0;
	}
	while (saved && (len - i) && (pf->i_buf < BUFFER_SIZE))
	{
		pf->buffer[pf->i_buf] = saved[i];
		pf->i_buf++;
		i++;
	}
	pf->buffer[pf->i_buf] = '\0';
	return (pf);
}
