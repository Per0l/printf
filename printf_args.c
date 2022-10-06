/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 01:32:35 by aperol-h          #+#    #+#             */
/*   Updated: 2021/08/12 20:46:57 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include <stdlib.h>

void	ft_printint(t_modifiers *mods,
					va_list argp,
					int *chars_printed)
{
	int		i_toprint;
	char	*s_toprint;

	i_toprint = va_arg(argp, int);
	if (mods->specifier == 'c')
	{
		s_toprint = (char *)malloc(2 * sizeof(char));
		if (!s_toprint)
			return ;
		if (i_toprint == 0)
		{
			mods->c = 0;
			i_toprint++;
		}
		s_toprint[0] = i_toprint;
		s_toprint[1] = '\0';
		*chars_printed += ft_print_mod(s_toprint, mods);
	}
	else
	{
		s_toprint = ft_itoa(i_toprint);
		*chars_printed += ft_print_mod(s_toprint, mods);
	}
	free(s_toprint);
}

void	ft_printuint(t_modifiers *mods,
					va_list argp,
					int *chars_printed)
{
	unsigned int	ui_toprint;
	char			*s_toprint;

	ui_toprint = va_arg(argp, unsigned int);
	s_toprint = NULL;
	if (mods->specifier == 'u')
		s_toprint = ft_itoa(ui_toprint);
	else if (mods->specifier == 'x')
		s_toprint = ft_itoa_hex(ui_toprint, 0);
	else if (mods->specifier == 'X')
		s_toprint = ft_itoa_hex(ui_toprint, 1);
	if (!s_toprint)
		return ;
	*chars_printed += ft_print_mod(s_toprint, mods);
	free(s_toprint);
}

void	ft_printptr(t_modifiers *mods,
					va_list argp,
					int *chars_printed)
{
	char	*s_toprint;
	char	*tmp;
	void	*ptr;

	ptr = va_arg(argp, void *);
	if (ptr || IS_APPLE)
	{
		s_toprint = ft_itoa_hex((unsigned long)ptr, 0);
		if (!s_toprint)
			return ;
		tmp = ft_strjoin("0x", s_toprint);
		*chars_printed += ft_print_mod(tmp, mods);
		free(tmp);
		free(s_toprint);
	}
	else
	{
		ft_putstr("(nil)", -1);
		*chars_printed += 5;
	}
}

void	ft_printstring(t_modifiers *mods,
					va_list argp,
					int *chars_printed)
{
	char	*s_toprint;

	s_toprint = va_arg(argp, char *);
	if (s_toprint)
		*chars_printed += ft_print_mod(s_toprint, mods);
	else
		*chars_printed += ft_print_mod("(null)", mods);
}

void	ft_printarg(t_modifiers *mods,
					va_list argp,
					int *chars_printed)
{
	if (ft_strchr("cdi", mods->specifier))
		ft_printint(mods, argp, chars_printed);
	else if (ft_strchr("uxX", mods->specifier))
		ft_printuint(mods, argp, chars_printed);
	else if (mods->specifier == 'p')
		ft_printptr(mods, argp, chars_printed);
	else if (mods->specifier == 's')
		ft_printstring(mods, argp, chars_printed);
}
