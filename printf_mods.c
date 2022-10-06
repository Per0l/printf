/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_mods.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 18:01:35 by aperol            #+#    #+#             */
/*   Updated: 2021/08/12 20:50:39 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"
#include <stdlib.h>

void	ft_width_padding(char *out, char *ori, int n, char flag)
{
	char	pad;

	if (!out)
		return ;
	pad = ' ';
	if (flag == '0')
	{
		if (*ori == '-' || *ori == '+')
			*out++ = *ori++;
		pad = '0';
	}
	else if (flag == '-')
	{
		ft_strcpy(out, ori);
		out += ft_strlen(ori);
	}
	while (n > 0)
	{
		*out++ = pad;
		n--;
	}
	if (flag != '-')
		ft_strcpy(out, ori);
}

char	*ft_precision_padding(char *out, char *ori, t_modifiers *mods, int *len)
{
	if (mods->precision != -1)
	{
		if (mods->specifier != 's' && mods->precision >= *len)
		{
			mods->width = mods->precision;
			mods->flag = '0';
			if (ft_strchr(ori, '-') || ft_strchr(ori, '+'))
				mods->width++;
		}
		else if (mods->specifier == 's')
		{
			if (out)
				free(out);
			out = (char *)ft_calloc((*len + 10), sizeof(char));
			if (!out)
				return (NULL);
			ft_strcpy(out, ori);
			out[mods->precision] = '\0';
		}
		*len = ft_strlen(out);
	}
	return (out);
}

char	*ft_plus_flag(char *out, char *ori, t_modifiers *mods, int *len)
{
	char	valid[4];

	ft_strcpy(valid, "cdi");
	if (ft_strchr(valid, mods->specifier)
		&& (mods->flag == '+' || mods->flag == ' ') && !ft_strchr(ori, '-'))
	{
		if (out)
			free(out);
		out = (char *)ft_calloc((*len + 2), sizeof(char));
		if (!out)
			return (NULL);
		*out = mods->flag;
		ft_strcpy(out + 1, ori);
		ori = out;
		*len = ft_strlen(out);
	}
	return (out);
}

char	*ft_sharp_flag(char *out, char *ori, t_modifiers *mods, int *len)
{
	char	valid[3];

	ft_strcpy(valid, "xX");
	if (mods->flag == '#' && ft_strchr(valid, mods->specifier) && *ori != '0')
	{
		if (out)
			free(out);
		out = (char *)ft_calloc((*len + 3), sizeof(char));
		if (!out)
			return (NULL);
		out[0] = '0';
		out[1] = mods->specifier;
		ft_strcpy(out + 2, ori);
		ori = out;
		*len = ft_strlen(out);
	}
	return (out);
}

int	ft_print_mod(char *s, t_modifiers *mods)
{
	int		len;
	char	*out;

	if (!s)
		return (0);
	out = ft_strdup(s);
	len = ft_strlen(s);
	out = ft_plus_flag(out, s, mods, &len);
	out = ft_sharp_flag(out, s, mods, &len);
	out = ft_precision_padding(out, s, mods, &len);
	if (mods->width != -1 && mods->width > len)
	{
		if (out)
			free(out);
		out = (char *)ft_calloc((len + (mods->width - len) + 1), sizeof(char));
		if (!out)
			return (0);
		ft_width_padding(out, s, mods->width - len, mods->flag);
		len = ft_strlen(out);
	}
	if (!out)
		return (0);
	ft_putstr(out, mods->c);
	free(out);
	return (len);
}
