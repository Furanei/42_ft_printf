/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 02:36:34 by mbriffau          #+#    #+#             */
/*   Updated: 2017/02/24 09:39:59 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		main(int argc, char const *argv[])
{
	printf("\n\n-----\n%s\n", "bonjour");
	ft_printf("%s\n", "bonjour");
	printf("\n\n-----\n%d\n", 123456);
	ft_printf("%d\n", 123456);
	printf("\n\n-----\n%c\n", 'c');
	ft_printf("%c\n", 'c');
	printf("\n\n-----\n%s\n", "你好봉쥬르");
	ft_printf("%s\n", "你好봉쥬르");

	printf("\n\n\n");
	printf("\n\n-----\n%s\n", "sa");
	ft_printf("%s\n", "sa");
	return 0;
}
