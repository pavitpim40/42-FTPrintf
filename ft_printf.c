/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:41:29 by ppimchan          #+#    #+#             */
/*   Updated: 2023/03/23 20:07:14 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int	i;
	int total_len;
	va_list ap; // ap : argument process
	char c;

	i = 0;
	total_len = 0;
	va_start(ap, format);
	while(*(format + i))
	{
		if(*(format + i) == '%')
		{
			i++;
			if(*(format + i) == 'c')
			{
				c = va_arg(ap, int);
				total_len += write(1, (unsigned char *)&c,1);

			}
				
		}
		else
			total_len += write(1, format + i, 1);
		i++;
	}
	va_end(ap);
	return (total_len);
}

// int main()
// {
	// printf("%c", '0');
	// ft_printf(" %c ", '0');
	// printf(" %c", '0' - 256);
	// printf("%c ", '0' + 256);
	// printf(" %c %c %c ", '0', 0, '1');
	// printf(" %c %c %c ", ' ', ' ', ' ');
	// printf(" %c %c %c ", '1', '2', '3');
	// printf(" %c %c %c ", '2', '1', 0);
	// printf(" %c %c %c ", 0, '1', '2');
// }