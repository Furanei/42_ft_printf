/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 09:53:49 by achambon          #+#    #+#             */
/*   Updated: 2017/08/17 11:30:04 by achambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		add_char_and_string_2_buf(t_printf *pf, char c, char *str, int len)
{
	buffer(pf, &c, 1);
	buffer(pf, str, len);
	return(pf->i_buf);
}

int		minwidth_decr_add_char_2_buf(t_printf *pf, char c, t_conv *conv)
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
