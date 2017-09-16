/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 23:26:26 by mbriffau          #+#    #+#             */
/*   Updated: 2017/08/28 17:18:17 by achambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		conv_b(t_printf *pf, t_conv *conv)
{

	unsigned int ptr;
	char *str;
	int i;
	int len;
	i = 0;

	if(conv)
		i = 0;
	ptr = va_arg(pf->ap, unsigned int);
	str = ft_itoa_base((long long)ptr, 2);
	len = ft_strlen(str);
	while((i + len) < 8)
	{
		write(1, "0", 1);
		i++;
	}
	write(1, str, len);
	return;
}
