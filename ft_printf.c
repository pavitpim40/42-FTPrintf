/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:41:29 by ppimchan          #+#    #+#             */
/*   Updated: 2023/03/23 21:51:08 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


int ft_print_char(va_list *ap)
{
	char c;
	
	c = va_arg(*ap, int);
	ft_putchar_fd(c,1);
	return (1);
	
}

int ft_print_str(va_list *ap)
{
	char *s;
	int len;
	
	len = 0;
	s = va_arg(*ap, char *);
	if(s)
	{
		len += ft_strlen(s);
		ft_putstr_fd(s,1);
	} 
	else
	{
		ft_putstr_fd("(null)",4);
		len = 6;
	}
	return (len);
}
int	ft_printf(const char *format, ...)
{
	int	i;
	int total_len;
	va_list ap; // ap : argument process

	i = 0;
	total_len = 0;
	va_start(ap, format);
	while(*(format + i))
	{
		if(*(format + i) == '%')
		{
			i++;
			if(*(format + i) == 'c')
				total_len += ft_print_char(&ap);	
			else if(*(format + i) == 's')
				total_len += ft_print_str(&ap);		
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

	// # MAN-CHAR
	// printf("%c", '0');
	// printf("%d",ft_printf(" %c ", '0'));
	// printf(" %c", '0' - 256);
	// printf("%c ", '0' + 256);
	// printf(" %c %c %c ", '0', 0, '1');
	// printf(" %c %c %c ", ' ', ' ', ' ');
	// printf(" %c %c %c ", '1', '2', '3');
	// printf(" %c %c %c ", '2', '1', 0);
	// printf(" %c %c %c ", 0, '1', '2');

	// # MAN-STRING
	// char *s2 = "Mussum Ipsum, cacilds vidis litro abertis. Posuere libero varius. Nullam a nisl ut ante blandit hendrerit. Aenean sit amet nisi. Atirei o pau no gatis, per gatis num morreus.";
	
	// ft_printf("%s", "");
	// ft_printf(" %s", "");
	// ft_printf("%s ", "");
	// ft_printf(" %s ", "");
	// ft_printf(" %s ", "-");
	// ft_printf(" %s %s ", "", "-");
	// ft_printf(" %s %s ", " - ", "");
	// ft_printf(" %s %s %s %s %s", " - ", "", "4", "", s2);
	// ft_printf(" %s %s %s %s %s ", " - ", "", "4", "", "2 ");
	// ft_printf(" NULL %s NULL ", NULL);
// }