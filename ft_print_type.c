/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:06:22 by ppimchan          #+#    #+#             */
/*   Updated: 2023/03/27 14:06:46 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(t_list *tp)
{
	char	c;

	c = va_arg(tp->ap, int);
	ft_putchar_fd(c, 1);
	return (1);
}

int	print_str(t_list *tp)
{
	char	*s;
	int		len;

	s = va_arg(tp->ap, char *);
	if (s)
	{
		len = ft_strlen(s);
		ft_putstr_fd(s, 1);
	}
	else
	{
		ft_putstr_fd("(null)", 4);
		len = 6;
	}
	return (len);
}

int	print_ptr_to_str(t_list *tp)
{
	size_t	address;
	char	*address_str;
	int		len;

	address = va_arg(tp->ap, size_t);
	address_str = ptr_to_str(address);
	ft_putstr_fd(address_str, 1);
	len = (int)ft_strlen(address_str);
	free(address_str);
	return (len);
}

int	print_nbr_to_str(t_list *tp)
{
	int		nbr;
	char	*s;
	int		len;

	nbr = va_arg(tp->ap, int);
	s = nbr_to_str_dec(nbr);
	len = ft_strlen(s);
	ft_putstr_fd(s, 1);
	free(s);
	return (len);
}

int	print_uint_to_strbase(t_list *tp, char type, unsigned int base)
{
	unsigned int	nbr;
	char			*s;
	int				len;

	nbr = va_arg(tp->ap, unsigned int);
	s = uint_to_str_base(nbr, type, base);
	len = ft_strlen(s);
	ft_putstr_fd(s, 1);
	free(s);
	return (len);
}
