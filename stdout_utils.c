/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aperol <aperol@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 00:35:05 by aperol-h          #+#    #+#             */
/*   Updated: 2021/08/12 20:53:09 by aperol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (c != -1)
			ft_putchar(c);
		else
			ft_putchar(s[i]);
		i++;
	}
}

char	*ft_itoa_hex(unsigned long n, int uppercase)
{
	char	hexchars[17];
	char	s_out[17];
	int		i;

	if (uppercase)
		ft_strcpy(hexchars, "0123456789ABCDEF");
	else
		ft_strcpy(hexchars, "0123456789abcdef");
	i = 0;
	if (n == 0)
		s_out[i++] = '0';
	while (n != 0)
	{
		s_out[i++] = hexchars[n % 16];
		n /= 16;
	}
	s_out[i] = '\0';
	ft_strrev(s_out);
	return (ft_strdup(s_out));
}
