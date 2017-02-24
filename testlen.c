/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testlen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 09:04:52 by mbriffau          #+#    #+#             */
/*   Updated: 2017/02/24 09:26:00 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		ft_strlen2(int cmp)
{
	int		n;

	n = 32768;
	while (cmp != 0)
		if (cmp - n >= 0)
			cmp -= n;
		else
		{
			n >>= 1;
			cmp--;
		}
	return (cmp);
}

int		ft_strlen(int cmp)
{

	while (cmp != 0)
		cmp--;
	return (cmp);
}

int main(int argc, char const *argv[])
{
	int i;

	i = 80000;
	while (i--)
		ft_strlen2(56);
	return 0;
}

// int		ft_strlen2(char const *str)
// {
// 	int		i;
// 	int		n;

// 	i = 0;
// 	n = 32768;
// 	while (str[i])
// 		if (str[i + n])
// 			i += n;
// 		else
// 		{
// 			n >>= 1;
// 			i++;
// 		}
// 	return (i);
// }

// int		ft_strlen(char const *str)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	return (i);
// }