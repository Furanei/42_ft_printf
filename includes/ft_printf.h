/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbriffau <mbriffau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 18:34:23 by mbriffau          #+#    #+#             */
/*   Updated: 2017/09/21 14:08:27 by mbriffau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../libft/srcs/libft.h"
# include <stdarg.h>
# include <errno.h>
# include <unistd.h>
# include <wchar.h>
# include "macros_pf.h"

# include <stdio.h>// to delete

typedef struct			s_conv
{
	int					min_width;
	int 				width_temp;
	int					precision;
	int					precision_set;//////////
	int					precision_tick;////////////
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
	char 				*str;
	int 				len;
	int 				n;
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

/*
**conv_c
*/
void		conv_c(t_printf *pf, t_conv *conv);

/*
**conv_s
*/
void		conv_s(t_printf *pf, t_conv *conv);

/*
**conv_d
*/
int			conv_d(t_printf *pf, t_conv *conv);

/*
**conv_x
*/
void		conv_x(t_printf *pf, t_conv *conv);
/*
**number.c
*/
intmax_t	ptr_number_base(t_printf *pf, int f);
uintmax_t	ptr_number(t_printf *pf, int f);
char		*ft_uitoa_pf(uintmax_t n);




int 		conv_d_bis(t_printf *pf, t_conv *conv, char *str, int len);
int			conv_d_l(t_printf *pf, t_conv *conv);
int			conv_d_h(t_printf *pf, t_conv *conv);
int			conv_d_prec_only(t_printf *pf, t_conv *conv, int len, char *str);
int			conv_d_width_only(t_printf *pf, t_conv *conv, int width_temp, char *str);
int			conv_d_width_only2(t_printf *pf, t_conv *conv, int len, char *str);
int			conv_d_width_only3(t_printf *pf, t_conv *conv, int len, char *str);
int			conv_d_minus2(t_printf *pf, t_conv *conv, int width_temp, char *str);
int			conv_d_width_only3(t_printf *pf, t_conv *conv, int len, char *str);
int			conv_d_width_only2(t_printf *pf, t_conv *conv, int len, char *str);
int			conv_d_width_only(t_printf *pf, t_conv *conv, int width_temp, char *str);
int			conv_d_prec_only(t_printf *pf, t_conv *conv, int len, char *str);
int			conv_d_minus(t_printf *pf, t_conv *conv, int len, char *str);
int			conv_d_hh_nominus_width_only2(t_printf *pf, t_conv *conv, char *str, int len);
int			conv_d_hh_nominus_width_only(t_printf *pf, t_conv *conv, char *str, int len);
int			conv_d_hh_nominus_width_and_prec(t_printf *pf, t_conv *conv, char *str, int len);
int			conv_d_hh_nominus(t_printf *pf, t_conv *conv, char *str, int len);
t_conv		option_dbis_convbefore4(t_printf *pf, t_conv *conv, char *s);
t_conv		option_d(t_printf *pf, int n, char c, t_conv *conv);
int			conv_d_minus_width_only(t_printf *pf, t_conv *conv, int len, char *str);
int			conv_d_minus_width_and_prec(t_printf *pf, t_conv *conv, int len, char *str);
char		*ft_itoa_printf(long long n);

void		conv_f(t_printf *pf, t_conv *conv);
void		conv_f_L(t_printf *pf, t_conv *conv);
int			conv_p(t_printf *pf, t_conv *conv);

void		conv_mx(t_printf *pf, t_conv *conv);
int			conv_x_minus(t_printf *pf, t_conv *conv, int len, char *str);
int			conv_x_nowidth_noprec(t_printf *pf, t_conv *conv, char *str, int len);
int			conv_x_minus2(t_printf *pf, t_conv *conv, char *str, int len);
int 		conv_x_width_only3(t_printf *pf, t_conv *conv, int len, char *str);
int			conv_x_width_only2(t_printf *pf, t_conv *conv, int len, char *str);
t_conv		option_x(t_printf *pf, int n, char c, t_conv *conv);
t_printf	*add_0x(t_printf *pf, t_conv *conv);
int			conv_x_minus_width_sup_len(t_printf *pf, t_conv *conv, int len);
int			conv_x_minus_width_only(t_printf *pf, t_conv *conv, int len);
int			conv_x_minus_width_and_prec(t_printf *pf, t_conv *conv, int len, char *str);
char		*ft_str_tolower(char *s);
int			fill_tab_with_c(t_printf *pf, char *tab, char c);
t_conv		option_x3(t_printf *pf, char *tab, char c, t_conv *conv);
t_conv		option_x2(t_printf *pf, int n, char c, t_conv *conv);

void		conv_o(t_printf *pf, t_conv *conv);
int			conv_o_nowidth_noprec(t_printf *pf, t_conv *conv, char *str, int len);
int			conv_o_minus2(t_printf *pf, t_conv *conv, int len, char *str);
int			conv_o_width_only3(t_printf *pf, t_conv *conv, int len, char *str);
int			conv_o_width_only2(t_printf *pf, t_conv *conv, int len, char *str);
int			conv_o_width_only(t_printf *pf, t_conv *conv, int len, char *str);
int			conv_ominus_width_only2(t_printf *pf, t_conv *conv, int len);
int			conv_ominus_width_only(t_printf *pf, t_conv *conv, int len);
int 		conv_ominus_prec_only(t_printf *pf, t_conv *conv, int len, char *str);
int 		conv_ominus_width_and_prec(t_printf *pf, t_conv *conv, int len, char *str);
int			conv_o_minus(t_printf *pf, t_conv *conv, int len, char *str);
t_conv		option_o(t_printf *pf, int n, char c, t_conv *conv);
t_conv		option_o2(t_printf *pf, int i, char c, t_conv *conv);
t_conv		option_o3(t_printf *pf, char *tab, char c, t_conv *conv);

void		conv_u(t_printf *pf, t_conv *conv);
void		conv_b(t_printf *pf, t_conv *conv);
void		conv_percent(t_printf *pf, t_conv *conv);
void		no_conv(t_printf *pf, t_conv *conv);

int			add_char_and_string_2_buff(t_printf *pf, char c, char *str, int len);
int			minwidth_decr_add_char_2_buff(t_printf *pf, char c, t_conv *conv);
int			special_hhd_reverse_0_n_minus(t_printf *pf, char *str, char c);
// int			if_tick_but_no_prec(t_printf *pf, t_conv *conv);
