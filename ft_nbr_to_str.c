/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:56:58 by ppimchan          #+#    #+#             */
/*   Updated: 2023/03/27 13:46:11 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*nbr_to_str_dec(int d)
{
	char	*str;

	str = ft_itoa(d);
	if (str == NULL)
		return (NULL);
	return (str);
}

char	*uint_to_str_base(unsigned int x, char type, unsigned int base)
{
	char	*set;
	char	*res;
	int		len;

	if (type == 'x')
		set = "0123456789abcdef";
	else if (type == 'X')
		set = "0123456789ABCDEF";
	else if (type == 'd')
		set = "0123456789";
	len = ft_uint_len(x, base);
	res = (char *)ft_calloc(sizeof(char), len + 1);
	if (res == NULL)
		return (NULL);
	while (x >= base)
	{
		*(res + len - 1) = set[x % base];
		x /= base;
		len--;
	}
	*(res) = set[x];
	return (res);
}

char	*ulong_to_str_hex(size_t x, char format)
{
	char	*hex;
	char	*res;
	size_t	len;
	char	*res2;

	if (format == 'x')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	len = ft_intlen_base(x, 16);
	res = (char *)ft_calloc(sizeof(char), len + 1);
	if (res == NULL)
		return (0);
	while (x >= 16)
	{
		*(res + len - 1) = hex[x % 16];
		x /= 16;
		len--;
	}
	*(res) = hex[x];
	res2 = ft_strjoin("0x", res);
	free(res);
	return (res2);
}

char	*ptr_to_str(size_t p)
{
	char	*str;

	str = ulong_to_str_hex(p, 'x');
	if (str == NULL)
		return (NULL);
	return (str);
}
