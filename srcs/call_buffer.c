/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 09:53:49 by achambon          #+#    #+#             */
/*   Updated: 2017/09/21 16:06:33 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		minwidth_decr_add_char_2_buff(t_printf *pf, char c, t_conv *conv)
{
	conv->min_width--;
	buffer(pf, &c, 1);
	return(pf->i_buf);
}

int		special_hhd_reverse_0_n_minus(t_printf *pf, char *str, char c)
{
	str[0] = '0';
	buffer(pf, &c, 1);
	return(pf->i_buf);
}
