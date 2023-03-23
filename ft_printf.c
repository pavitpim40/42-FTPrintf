/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:41:29 by ppimchan          #+#    #+#             */
/*   Updated: 2023/03/23 20:25:26 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	write (fd, s, ft_strlen(s));
}

int	ft_printf(const char *format, ...)
{
	int	i;
	int total_len;
	va_list ap; // ap : argument process
	char c;
	char *s;

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
			else if(*(format + i) == 's')
			{
				s = va_arg(ap, char *);
				if(s)
				{
					total_len += ft_strlen(s);
				ft_putstr_fd(s,1);
				} 
				else
				{
					total_len += 6;
					ft_putstr_fd("(null)",4);
				}
				
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

	// # MAN-CHAR
	// printf("%c", '0');
	// ft_printf(" %c ", '0');
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