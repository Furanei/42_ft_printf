/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 16:07:37 by mbriffau          #+#    #+#             */
/*   Updated: 2017/09/24 18:31:02 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		ft_wstrlen(wchar_t *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int		count_wchars(t_conv *conv, wchar_t *wstr, int size)
{
	int		i;
	int		add;
	int		total;

	i = 0;
	add = 0;
	total = 0;
	while (i < size)
	{
		if (wstr[i] <= 0x7F)
			add = 1;
		else if (wstr[i] <= 0x7FF)
			add = 2;
		else if (wstr[i] <= 0xFFFF)
			add = 3;
		else if (wstr[i] <= 0x10FFFF)
			add = 4;
		if (conv->precision_set && conv->flag & TYPE_S
			&& (total + add) > conv->precision)
			break ;
		total += add;
		i++;
	}
	size = i;
	return (total);
}

static void		print_wstring(t_printf *pf, t_conv *conv, wchar_t *wstr, int n)
{
	int i;

	i = 0;
	count_wchars(conv, wstr, n);
	while (i < n)
	{
		print_wint(&*pf, wstr[i]);
		i++;
	}
}

static t_conv	*option_s(t_printf *pf, int print_size, char c, t_conv *conv)
{
	int			i;
	char		tab[(conv->min_width - print_size) + 1];
	int			size;

	size = (conv->min_width - print_size);
	i = 0;
	tab[size] = '\0';
	if (!size)
		return (conv);
	else
	{
		while (i < size)
			tab[i++] = c;
		buffer(&*pf, tab, size);
	}
	conv->min_width = 0;
	return (conv);
}

void	conv_s_file(t_printf *pf)
{
	int		fd;
	char	*s;
	char	array[32];
	int	ret;

	s = va_arg(pf->ap, char *);
	fd = open(s, O_RDONLY);
	if (fd == -1 || -1 == read(fd, array, 1))
		exit(-1);
	close(fd);
	fd = open(s, O_RDONLY);
	while ((ret = read(fd, array, 32)))
		buffer(&*pf, array, ret);

}

void			conv_s(t_printf *pf, t_conv *conv)
{
	void	*str;
	int		len;

	if (conv->flag & MODIFIER_F)
	{
		conv_s_file(&*pf);
		return ;
	}
	if (conv->flag & MODIFIER_L)
	{
		str = va_arg(pf->ap, wchar_t *);
		!(MB_CUR_MAX > 1) ? exit (-1) : 0;
	}
	(!(conv->flag & MODIFIER_L))
	? str = va_arg(pf->ap, unsigned char *) : 0;
	(str == NULL) ? (str = ft_strdup("(null)")) : 0;
	len = (conv->flag & MODIFIER_L ? count_wchars(conv, str, ft_wstrlen(str)) :
	ft_strlen(str));
	if (conv->precision && conv->precision < len)
		len = conv->precision;
	if (conv->min_width > len && (conv->flag & ZERO) && !(conv->flag & MINUS))
		option_s(&*pf, len, '0', &*conv);
	else if (conv->min_width > len && conv->flag & SPACE)
		option_s(&*pf, len, ' ', &*conv);
	else if (conv->min_width > len && !(conv->flag & MINUS))
		option_s(&*pf, len, ' ', &*conv);
	conv->flag & MODIFIER_L ? print_wstring(&*pf, conv, str, ft_wstrlen(str))
	: buffer(&*pf, str, len);
	(conv->min_width > len && conv->flag & MINUS)
	? option_s(&*pf, len, ' ', &*conv) : 0;
}
