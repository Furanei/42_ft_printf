/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 18:17:08 by achambon          #+#    #+#             */
/*   Updated: 2017/08/11 14:54:02 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/ft_printf.h"

void	conv_f_L(t_printf *pf, t_conv *conv)
{
	int		len;
	int		apint;
	char	*str;

	if (!(apint = va_arg(pf->ap, long double)))
		ft_error("error_conv_d\n");
	len = ft_strlen(str = ft_itoa(apint));
	if ((conv->flag & ZERO) && !(conv->flag & MINUS))
		while (conv->min_width-- > 0 + len)
			ft_putchar('0');
	if ((conv->flag & SPACE))
		while ( conv->min_width-- > 0 + len)
			ft_putchar(' ');
	if ((conv->flag & MINUS))
	{
		ft_putnbr(apint);
		while (conv->min_width-- > 0 + len)
			ft_putchar(' ');
		return;
	}
	ft_putnbr(apint);
}

void	conv_f(t_printf *pf, t_conv *conv)
{
	int		len;
	int		apint;
	char	*str;

	if (conv->precision_set == 0)
		conv->precision = 6;
	if(conv->flag & MODIFIER_LL)
		conv_f_L(pf, conv);
	if(!(apint = va_arg(pf->ap, double)))
		ft_error("error_conv_f\n");
	len = ft_strlen(str = ft_itoa(apint));
	if ((conv->flag & ZERO) && !(conv->flag & MINUS))
		while (conv->min_width-- > 0 + len)
			ft_putchar(' ');
	if ((conv->flag & MINUS))
	{
		ft_putnbr(apint);
		while (conv->min_width-- > 0 + len)
			ft_putchar(' ');
		return;
	}
	ft_putnbr(apint);
}

/* Need add precision
 * */
