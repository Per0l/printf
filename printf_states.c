/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 00:49:38 by aperol-h          #+#    #+#             */
/*   Updated: 2021/08/12 20:57:08 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

const char	*state_flags_checks(const char *fmt,
								t_modifiers *mods)
{
	char	c_flags[6];
	char	*flag;

	ft_strcpy(c_flags, "-+ #0");
	flag = ft_strchr(c_flags, *fmt);
	if (flag)
	{
		mods->flag = *flag;
		fmt++;
	}
	return (fmt);
}

const char	*state_width_checks(const char *fmt,
								t_modifiers *mods,
								va_list argp)
{
	int	width;

	width = 0;
	if (ft_isdigit(*fmt))
	{
		while (ft_isdigit(*fmt))
		{
			width *= 10;
			width += *fmt - '0';
			fmt++;
		}
		mods->width = width;
	}
	else if (*fmt == '*')
	{
		mods->width = va_arg(argp, int);
		fmt++;
	}
	return (fmt);
}

const char	*state_precision_checks(const char *fmt,
								t_modifiers *mods,
								va_list argp)
{
	int	precision;

	precision = 0;
	if (*fmt == '.')
	{
		fmt++;
		if (ft_isdigit(*fmt))
		{
			while (ft_isdigit(*fmt))
			{
				precision *= 10;
				precision += *fmt - '0';
				fmt++;
			}
			mods->precision = precision;
		}
		else if (*fmt == '*')
		{
			mods->precision = va_arg(argp, int);
			fmt++;
		}
		else
			mods->precision = 0;
	}
	return (fmt);
}

const char	*state_length_checks(const char *fmt,
								t_modifiers *mods)
{
	char	length[3];

	if (*fmt == 'h' || *fmt == 'l')
	{
		length[0] = *fmt++;
		if (*fmt == length[0])
			length[1] = *fmt++;
		else
			length[1] = '\0';
		length[2] = '\0';
		ft_strcpy(mods->length, length);
	}
	return (fmt);
}

const char	*state_specifier_checks(const char *fmt,
								t_modifiers *mods,
								va_list argp,
								int *chars_printed)
{
	char	c_specifier[9];
	char	*specifier;

	ft_strcpy(c_specifier, "cspdiuxX");
	specifier = ft_strchr(c_specifier, *fmt);
	if (specifier)
	{
		mods->specifier = *specifier;
		fmt++;
		ft_printarg(mods, argp, chars_printed);
	}
	else if (*fmt == '%')
	{
		ft_putchar(*fmt++);
		*chars_printed += 1;
	}
	return (fmt++);
}
