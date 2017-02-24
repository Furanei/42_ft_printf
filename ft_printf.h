/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 03:52:30 by mbriffau          #+#    #+#             */
/*   Updated: 2017/02/24 06:24:36 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define MAX(a, b)			b & ((a - b) >> 31) | a & (~(a - b) >> 31)
# define MIN(a, b)			a & ((a - b) >> 31) | b & (~(a - b) >> 31)
# define ABS(a)				(a < 0) ? -a : a
# define COLOR(s,n)			ft_putstr(s), (format += n)
# define PF_RED				"\033[31m"
# define PF_GREEN			"\033[32m"
# define PF_YELLOW			"\033[33m"
# define PF_BLUE			"\033[34m"
# define PF_PURPLE			"\033[35m"
# define PF_CYAN			"\033[36m"
# define PF_EOC				"\033[36m"

# include "libft/libft.h"
# include <stdarg.h>
# include <errno.h>

typedef struct				s_printf
{
	char			*content;
	size_t			*size;
}							t_printf;

/*
** refer to parsing.c for description of variables in below structures
*/

int				ft_printf(char *format, ...);

#endif