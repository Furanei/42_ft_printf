/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_specifier.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 18:00:23 by mbriffau          #+#    #+#             */
/*   Updated: 2017/09/15 14:09:36 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_printf	*conversion_specifier(t_printf *pf, t_conv *conv)
{
	if (conv->flag & (TYPE_D + TYPE_S + TYPE_C + TYPE_P + TYPE_X + TYPE_O + TYPE_U + TYPE_B + TYPE_PERCENT))
	{
		conv->flag & TYPE_D ? conv_d(&*pf, &*conv) : 0;
		conv->flag & TYPE_S ? conv_s(&*pf, &*conv) : 0;
		conv->flag & TYPE_C ? conv_c(&*pf, &*conv) : 0;
		conv->flag & TYPE_P ? conv_p(&*pf, &*conv) : 0;
		((conv->flag & TYPE_X) && !(conv->flag & MODIFIER_L)) ? conv_x(&*pf, &*conv, 'x') : 0;
		((conv->flag & TYPE_X) && (conv->flag & MODIFIER_L)) ? conv_x(&*pf, &*conv, 'X') : 0;
		conv->flag & TYPE_O ? conv_o(&*pf, &*conv) : 0;
		conv->flag & TYPE_U ? conv_u(&*pf, &*conv) : 0;
		conv->flag & TYPE_B ? conv_b(&*pf, &*conv) : 0;
		conv->flag & TYPE_PERCENT ? conv_percent(&*pf, &*conv) : 0;
		pf->i++;
	}
	else if (!(conv->flag & (TYPE_S + TYPE_C + TYPE_D + TYPE_P + TYPE_X + TYPE_U + TYPE_O + TYPE_B + TYPE_PERCENT)))
	{
		if ((conv->flag & (MINUS + PLUS + SHARP + ZERO + SPACE)) && conv->min_width)
		{
			no_conv(&*pf, &*conv);
			pf->i++;
		}
	}
	return(pf);
}
