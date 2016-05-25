/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 14:21:47 by nflores           #+#    #+#             */
/*   Updated: 2016/01/26 14:09:10 by nflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <wchar.h>
# include <limits.h>

typedef struct	s_printf
{
	va_list		ap;
	int			width;
	int			sharp;
	int			plus;
	int			minus;
	int			space;
	int			zero;
	int			flag;
	int			lng;
	int			modif;
	int			ret;
	int			pct;
	int			impl;
}				t_printf;

int				ft_printf(const char *str, ...);
int				ft_width(const char *str, unsigned int pos, t_printf **ges);
int				ft_prec(const char *str, unsigned int pos, t_printf **ges);
int				ft_modif(const char *str, unsigned int pos, t_printf **ges);
int				ft_setmodif(t_printf **ges);
int				ft_flag(const char *str, unsigned int pos, t_printf **ges);
int				ft_ptr(t_printf **ges);
int				ft_atoi_bin(const char *str);
char			*ft_itoa_base(unsigned long n, unsigned int base);
void			lowercase(char **str);
int				ft_setwidth(int n, t_printf **ges, char **ag);
int				ft_setwidth_c(int n, t_printf **ges);
int				ft_setwidth_o(int n, t_printf **ges, char **ag);
int				ft_setwidth_x(int n, t_printf **ges, char **ag);
int				ft_setwidth_d(int n, t_printf **ges, char **ag);
int				ft_setwidth_p(int n, t_printf **ges, char **ag);
int				ft_setwidth_s(int n, t_printf **ges, char **ag);
int				ft_prec_d(t_printf **ges, char **s);
int				ft_prec_x(t_printf **ges, const char *s);
int				ft_putwchar(wint_t c);
int				ft_putwstr(wint_t *s);
int				ft_ischar(wint_t *s);
size_t			ft_wcharlen(wint_t c);
size_t			ft_strwlen(wint_t *s);
int				ft_printf_d(t_printf **ges);
int				ft_printf_md(t_printf **ges);
int				ft_printf_mmd(t_printf **ges);
int				ft_printf_u(t_printf **ges);
int				ft_printf_mu(t_printf **ges);
int				ft_printf_mmu(t_printf **ges);
int				ft_printf_c(t_printf **ges);
char			*ft_mask(wint_t c);
char			**ft_setoct(t_printf **ges);
char			**ft_setoct_s(wint_t c);
int				ft_print_oct(char **oct);
int				ft_printf_mc(t_printf **ges);
int				ft_printf_s(t_printf **ges);
int				ft_printf_ms(t_printf **ges);
int				ft_printf_p(t_printf **ges);
int				ft_printf_o(t_printf **ges);
int				ft_printf_mo(t_printf **ges);
int				ft_printf_mmo(t_printf **ges);
int				ft_printf_x(t_printf **ges);
int				ft_printf_mx(t_printf **ges);
int				ft_printf_mmx(t_printf **ges);
int				check_pct(const char *str, unsigned int pos, t_printf **ges);
int				ft_printf_pct(t_printf **ges);

#endif
