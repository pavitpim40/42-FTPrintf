/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:41:29 by ppimchan          #+#    #+#             */
/*   Updated: 2023/03/27 14:22:15 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_type(t_list *tp, char type)
{
	int	print_len;

	print_len = 0;
	if (type == 'c')
		print_len += print_char(tp);
	else if (type == 's')
		print_len += print_str(tp);
	else if (type == 'p')
		print_len += print_ptr_to_str(tp);
	else if (type == 'd' || type == 'i')
		print_len += print_nbr_to_str(tp);
	else if (type == 'u')
		print_len += print_uint_to_strbase(tp, 'd', 10);
	else if (type == 'x')
		print_len += print_uint_to_strbase(tp, 'x', 16);
	else if (type == 'X')
		print_len += print_uint_to_strbase(tp, 'X', 16);
	else if (type == '%')
		print_len += write(1, "%", 1);
	return (print_len);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		total_len;
	va_list	ap;
	t_list	*tp;

	i = 0;
	total_len = 0;
	tp = (t_list *)calloc(sizeof(t_list), 1);
	if (!tp)
		return (-1);
	va_start(tp->ap, format);
	while (*(format + i))
	{
		if (*(format + i) == '%')
		{
			i++;
			total_len += ft_print_type(tp, *(format + i));
		}
		else
			total_len += write(1, format + i, 1);
		i++;
	}
	va_end(ap);
	return (total_len);
}
