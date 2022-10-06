/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 00:34:35 by aperol-h          #+#    #+#             */
/*   Updated: 2021/08/10 01:47:06 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# ifdef __APPLE__
#  define IS_APPLE 1
# else
#  define IS_APPLE 0
# endif
typedef struct s_modifiers
{
	char	flag;
	int		width;
	int		precision;
	char	length[3];
	char	specifier;
	int		c;
}	t_modifiers;
enum	e_STATES
{
	STATE_NORMAL,
	STATE_FLAGS,
	STATE_WIDTH,
	STATE_PRECISION,
	STATE_LENGHT,
	STATE_SPECIFIER
};
const char	*state_flags_checks(const char *fmt,
				t_modifiers *mods);
const char	*state_width_checks(const char *fmt,
				t_modifiers *mods,
				va_list argp);
const char	*state_precision_checks(const char *fmt,
				t_modifiers *mods,
				va_list argp);
const char	*state_length_checks(const char *fmt,
				t_modifiers *mods);
const char	*state_specifier_checks(const char *fmt,
				t_modifiers *mods,
				va_list argp,
				int *chars_printed);
void		ft_printarg(t_modifiers *mods,
				va_list argp,
				int *chars_printed);
void		ft_putchar(char c);
void		ft_putstr(char *s, int c);
char		*ft_itoa_hex(unsigned long n, int uppercase);
int			ft_print_mod(char *s, t_modifiers *mods);
int			ft_printf(const char *fmt, ...);
#endif