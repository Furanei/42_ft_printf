/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 18:34:23 by mbriffau          #+#    #+#             */
/*   Updated: 2017/09/16 15:04:55 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../libft/srcs/libft.h"
# include <stdarg.h>
# include <errno.h>
# include <unistd.h>
# include <wchar.h> 

# include <stdio.h>// to delete

# define INFO __FILE__, (char *)__FUNCTION__, __LINE__

# define BUFFER_SIZE	1000

# define TYPE_S			(1 << 31)
# define TYPE_C			(1 << 30)
# define TYPE_D			(1 << 29)
# define TYPE_P			(1 << 28)
# define TYPE_X			(1 << 27)
# define TYPE_U			(1 << 26)
# define TYPE_O			(1 << 25)
# define TYPE_B			(1 << 24)
# define TYPE_PERCENT 	(1 << 23)

# define PRECISION		(1 << 11)

# define MODIFIER_H		(1 << 10)
# define MODIFIER_HH	(1 << 9)
# define MODIFIER_L		(1 << 8)
# define MODIFIER_LL	(1 << 7)
# define MODIFIER_J		(1 << 6)
# define MODIFIER_Z		(1 << 5)

# define MINUS			(1 << 4)
# define PLUS			(1 << 3)
# define SHARP			(1 << 2)
# define ZERO			(1 << 1)
# define SPACE			(1 << 0)

# define LOG_CLEAR		\033[2K
# define LOG_UP			\033[A
# define LOG_NOCOLOR	\033[0m
# define LOG_BOLD		\033[1m
# define LOG_UNDERLINE	\033[4m
# define LOG_BLINKING	\033[5m
# define LOG_BLACK		\033[1;30m
# define LOG_RED		\033[1;31m
# define LOG_GREEN		\033[1;32m
# define LOG_YELLOW		\033[1;33m
# define LOG_BLUE		\033[1;34m
# define LOG_VIOLET		\033[1;35m
# define LOG_CYAN		\033[1;36m
# define LOG_WHITE		\033[1;37m

typedef struct			s_conv
{
	int					min_width;
	int					precision;
	int					precision_set;
	int					precision_tick;
	int					ox;
	int					before;
	char				modif;
	char				sign;
	int					flag;
}						t_conv;

typedef struct			s_printf
{
	char 				*format;
	va_list				ap;
	int					i;
	char				*buffer;
	int 				i_buf;
	int					subtract_buffer;
}						t_printf;

void		ft_error_pf(char *file, char *func, int line, char *s);

int			ft_printf(char *format, ...);
t_printf	*parse_conversion(t_printf *pf);
t_conv		*init_conv(void);
t_printf	*print_wint(t_printf *pf, wint_t wint);
void		print_p(t_printf *pf, int len, char *str);
int			option(t_printf *pf, int n, char c, t_conv *conv, char *s);
t_conv		*option_print(int print_size, char c, t_conv *conv, char *s);
t_printf	*buffer(t_printf *pf, char *saved, int len);

t_printf	*conversion_specifier(t_printf *pf, t_conv *conv);
void		conv_c(t_printf *pf, t_conv *conv);
void		conv_s(t_printf *pf, t_conv *conv);
int			conv_d(t_printf *pf, t_conv *conv);
int			conv_d_l(t_printf *pf, t_conv *conv);
int			conv_d_h(t_printf *pf, t_conv *conv);
void		conv_f(t_printf *pf, t_conv *conv);
void		conv_f_L(t_printf *pf, t_conv *conv);
int			conv_p(t_printf *pf, t_conv *conv);
void		conv_mx(t_printf *pf, t_conv *conv);
void		conv_x(t_printf *pf, t_conv *conv, char height);
void		conv_o(t_printf *pf, t_conv *conv);
void		conv_u(t_printf *pf, t_conv *conv);
void		conv_b(t_printf *pf, t_conv *conv);
void		conv_percent(t_printf *pf, t_conv *conv);
void		no_conv(t_printf *pf, t_conv *conv);
int			add_char_and_string_2_buff(t_printf *pf, char c, char *str, int len);
int			minwidth_decr_add_char_2_buff(t_printf *pf, char c, t_conv *conv);
int			special_hhd_reverse_0_n_minus(t_printf *pf, char *str, char c);
