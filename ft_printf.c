/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:41:29 by ppimchan          #+#    #+#             */
/*   Updated: 2023/03/23 22:28:28 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	len1;
	size_t	len2;

	i = 0;
	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!res)
		return (0);
	while (i < len1)
	{
		res[i] = s1[i];
		i ++;
	}
	while (i < len1 + len2)
	{
		res[i] = s2[i - len1];
		i ++;
	}
	res[i] = '\0';
	return (res);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count * size < count && count * size < size)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == 0)
		return (ptr);
	ft_bzero(ptr, count * size);
	return (ptr);
}

static size_t	ft_intlen(size_t nb, int div)
{
	int		i;
	size_t	number;

	i = 0;
	if (!nb)
		return (1);
	number = nb;
	while (number)
	{
		number /= div;
		i++;
	}
	return (i);
}

char	*get_hexaddr_str(size_t x, char format)
{
	char	*hex;
	char	*res;
	// int		i;
	size_t	len;
	char	*res2;

	if (format == 'x')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	// i = 0;
	len = ft_intlen(x, 16);
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

char	*p_type_str(size_t p)
{
	char	*str;

	str = get_hexaddr_str(p, 'x');
	if (str == NULL)
		return (NULL);
	return (str);
}


// MINE

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

int ft_print_p(va_list *ap)
{
	size_t address;
	char	*address_str;
	int len;

	len = 0;
	address = va_arg(*ap,size_t);
	address_str = p_type_str(address);
	ft_putstr_fd(address_str,1);
	len += (int)ft_strlen(address_str);
	free(address_str);
	return (len);
}
int	ft_printf(const char *format, ...)
{
	int	i;
	int total_len;
	va_list ap; // ap : argument process
	// char *s;
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