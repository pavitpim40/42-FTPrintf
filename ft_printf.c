/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:41:29 by ppimchan          #+#    #+#             */
/*   Updated: 2023/03/24 00:18:17 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


// FOR HEX
char	*hex_str(size_t x, char format)
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

char	*address_to_str(size_t p)
{
	char	*str;

	str = hex_str(p, 'x');
	if (str == NULL)
		return (NULL);
	return (str);
}

// FOR D
char	*d_to_str(int d)
{
	char	*str;

	str = ft_itoa(d);
	if (str == NULL)
		return (NULL);
	return (str);
}


// FOR U

char	*uint_str(unsigned int d)
{
	char	*str;
	size_t	len;

	len = ft_uint_len(d);
	str = (char *)ft_calloc(sizeof(char), len + 1);
	if (str == NULL)
		return (NULL);
	str[len - 1] = '0'; // why not '\0'
	while(d > 0)
	{
		str[len - 1] = (d % 10) + '0';
		d = d / 10;
		len--;
	}

	return (str);
}

char	*uint_to_str(unsigned int u)
{
	char	*str;

	str = uint_str(u);
	if (str == NULL)
		return (NULL);
	return (str);
}





// MINE PRINT

int ft_print_c(va_list *ap)
{
	char c;
	
	c = va_arg(*ap, int);
	ft_putchar_fd(c,1);
	return (1);
	
}

int ft_print_s(va_list *ap)
{
	char *s;
	int len;
	
	// len = 0;
	s = va_arg(*ap, char *);
	if(s)
	{
		len = ft_strlen(s);
		ft_putstr_fd(s,1);
	} 
	else
	{
		ft_putstr_fd("(null)",4);
		len = 6;
	}
	return (len);
}

int ft_print_p(va_list *ap)
{
	size_t address;
	char	*address_str;
	int len;

	// len = 0;
	address = va_arg(*ap,size_t);
	address_str = address_to_str(address);
	ft_putstr_fd(address_str,1);
	len = (int)ft_strlen(address_str);
	free(address_str);
	return (len);
}

int ft_print_d(va_list *ap)
{
	int	nbr;
	char *s;
	int	len;

	// len = 0;
	nbr = va_arg(*ap, int);
	s = d_to_str(nbr);
	len = ft_strlen(s);
	ft_putstr_fd(s,1);
	free(s);

	return (len);
}

int ft_print_u(va_list *ap)
{
	char *s;
	unsigned int nbr;
	size_t len;

	nbr = va_arg(*ap, unsigned int);
	s = uint_to_str(nbr);
	len = ft_strlen(s);
	ft_putstr_fd(s,1);
	free(s);
	return (len);
}





int	ft_printf(const char *format, ...)
{
	int	i;
	int total_len;
	va_list ap; // ap : argument process
	// char *s;
	// unsigned int nbr;
	// int len;
	// size_t ptr;

	i = 0;
	total_len = 0;
	va_start(ap, format);
	while(*(format + i))
	{
		if(*(format + i) == '%')
		{
			i++;
			if(*(format + i) == 'c')
				total_len += ft_print_c(&ap);	
			else if(*(format + i) == 's')
				total_len += ft_print_s(&ap);
			else if(*(format + i) == 'p')
				total_len += ft_print_p(&ap);
			else if(*(format + i) == 'd' || *(format + i) == 'i')
				total_len += ft_print_d(&ap);
			else if(*(format + i) == 'u')
				total_len += ft_print_u(&ap);
			
			
			
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

	// ft_printf(" %p ",-1);
// }