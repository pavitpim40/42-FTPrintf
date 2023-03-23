/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:41:29 by ppimchan          #+#    #+#             */
/*   Updated: 2023/03/24 01:58:43 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"





// ############################################
// ################## PRINT EACH TYPE -> TO STR
// ############################################

// type c
int print_char(va_list *ap)
{
	char c;
	
	c = va_arg(*ap, int);
	ft_putchar_fd(c,1);
	return (1);
	
}

// type char *
int print_str(va_list *ap)
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

// type unsigned long -> hex
int print_ptr_to_str(va_list *ap)
{
	size_t address;
	char	*address_str;
	int len;

	// len = 0;
	address = va_arg(*ap,size_t);
	address_str = ptr_to_str(address);
	ft_putstr_fd(address_str,1);
	len = (int)ft_strlen(address_str);
	free(address_str);
	return (len);
}

// type int -> str (i,d)
int print_nbr_to_str(va_list *ap)
{
	int	nbr;
	char *s;
	int	len;

	// len = 0;
	nbr = va_arg(*ap, int);
	s = nbr_to_str_dec(nbr);
	len = ft_strlen(s);
	ft_putstr_fd(s,1);
	free(s);

	return (len);
}

// type unsigned int -> hex
int print_uint_to_strbase(va_list *ap, char type,unsigned int base)
{
	unsigned int nbr;
	char *s;
	int	len;
	
	nbr = va_arg(*ap, unsigned int);
	s = uint_to_str_base(nbr, type,base);
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

	i = 0;
	total_len = 0;
	va_start(ap, format);
	while(*(format + i))
	{
		if(*(format + i) == '%')
		{
			i++;
			if(*(format + i) == 'c')
				total_len += print_char(&ap);	
			else if(*(format + i) == 's')
				total_len += print_str(&ap);
			else if(*(format + i) == 'p')
				total_len += print_ptr_to_str(&ap);
			else if(*(format + i) == 'd' || *(format + i) == 'i')
				total_len += print_nbr_to_str(&ap);
			else if(*(format + i) == 'u')
				total_len += print_uint_to_strbase(&ap,'d',10);
			else if(*(format +i) == 'x')
				total_len += print_uint_to_strbase(&ap,'x',16);
			else if(*(format +i) == 'X')
				total_len += print_uint_to_strbase(&ap,'X',16);
			else if(*(format +i) == '%')
				total_len += write(1, "%",1);
			
			
			
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