/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 00:31:52 by aperol-h          #+#    #+#             */
/*   Updated: 2021/08/10 01:16:12 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

void	reset_modifiers(t_modifiers *mods)
{
	mods->flag = '\0';
	mods->width = -1;
	mods->precision = -1;
	ft_bzero(mods->length, 3);
	mods->specifier = '\0';
	mods->c = -1;
}

const char	*state_normal_checks(const char *fmt,
								int *state,
								int *chars_printed,
								t_modifiers *mods)
{
	reset_modifiers(mods);
	if (*fmt == '%')
	{
		fmt++;
		return (fmt);
	}
	else
	{
		ft_putchar(*fmt++);
		*chars_printed += 1;
		*state = -1;
		return (fmt);
	}
}

int	ft_printf(const char *fmt, ...)
{
	va_list		argp;
	t_modifiers	mods;
	int			state;
	int			chars_printed;

	state = STATE_NORMAL;
	chars_printed = 0;
	va_start(argp, fmt);
	while (*fmt != '\0')
	{
		if (state == STATE_NORMAL)
			fmt = state_normal_checks(fmt, &state, &chars_printed, &mods);
		else if (state == STATE_FLAGS)
			fmt = state_flags_checks(fmt, &mods);
		else if (state == STATE_WIDTH)
			fmt = state_width_checks(fmt, &mods, argp);
		else if (state == STATE_PRECISION)
			fmt = state_precision_checks(fmt, &mods, argp);
		else if (state == STATE_LENGHT)
			fmt = state_length_checks(fmt, &mods);
		else if (state == STATE_SPECIFIER)
			fmt = state_specifier_checks(fmt, &mods, argp, &chars_printed);
		state = (state + 1) % 6;
	}
	return (chars_printed);
}
