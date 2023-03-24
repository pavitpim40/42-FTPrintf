/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:41:29 by ppimchan          #+#    #+#             */
/*   Updated: 2023/03/24 16:14:47 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// ##FT_IS
int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}

int is_type(char c)
{
	int	i;

	i = 0;
	while(TYPES[i])
	{
		if (TYPES[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_flags(char c)
{
	int	i;
	
	i = 0;
	while(FLAGS[i])
	{
		if (FLAGS[i] == c)
			return (1);
		i++;
	}
	return (0);	
}


// ####################################

char	*plus_flag_str( t_list *t,char *str)
{
	int	nb;
	char *prefix;
	char *final_str;

	// number type and have + or space
	if((t->type == 'd' || t->type == 'i') && t->f_plus)
	{
		nb = ft_atoi(str);
		if(nb < 0)
			return (str); // เลขลบใช้ print ได้เลย
		prefix = ft_calloc(sizeof(char),2);
		if(prefix == NULL)
			return (NULL);
		if(t->f_plus)
			prefix[0] = '+';
		else
			prefix[0] = ' ';
		final_str = ft_strjoin(prefix,str); // DIFF from original
		if(final_str == NULL)
			return (NULL);
		free(prefix);
		free(str);
		return (final_str);
	}
	return (str);
}



// ############################################
// ################## PRINT EACH TYPE -> TO STR
// ############################################


// type c
int print_char(t_list *tp)
{
	char c;
	
	c = va_arg(tp->ap, int);
	ft_putchar_fd(c,1);
	tp->total_len += 1;
	return (1);
	
}

// type char *
int print_str(t_list *tp)
{
	char *s;
	int len;
	
	// len = 0;
	s = va_arg(tp->ap, char *);
	if(s)
	{
		ft_putstr_fd(s,1);
		len = ft_strlen(s);
	} 
	else
	{
		ft_putstr_fd("(null)",4);
		len = 6;
	}
	tp->total_len += len;
	return (len);
}

// type unsigned long -> hex
int print_ptr_to_str(t_list *tp)
{
	size_t address;
	char	*address_str;
	int len;

	// len = 0;
	address = va_arg(tp->ap,size_t);
	address_str = ptr_to_str(address);
	ft_putstr_fd(address_str,1);
	len = (int)ft_strlen(address_str);
	free(address_str);
	tp->total_len += len;
	return (len);
}

// type d,i -> str (i,d)
int print_nbr_to_str(t_list *tp)
{
	int	nbr;
	char *s;
	int	len;

	// len = 0;
	nbr = va_arg(tp->ap, int);
	s = nbr_to_str_dec(nbr);
	if(tp->f_plus)
	{
		
		s = plus_flag_str(tp,s);
	}


	len = ft_strlen(s);
	ft_putstr_fd(s,1);
	free(s);
	tp->total_len += len;

	return (len);
}

// type unsigned int -> hex
int print_uint_to_strbase(t_list *tp, char type,unsigned int base)
{
	unsigned int nbr;
	char *s;
	int	len;
	
	nbr = va_arg(tp->ap, unsigned int);
	s = uint_to_str_base(nbr, type,base);
	len = ft_strlen(s);
	ft_putstr_fd(s,1);
	free(s);
	tp->total_len += len;
	return (len);
}

int	print_percent(t_list *tp)
{
	tp->total_len += write(1, "%",1);
	return (1);
}
void print_format(t_list *tp)
{
	char 	type;

	type = tp->type;
	if(type == 'c')
		print_char(tp);
	else if(type == 's')
				print_str(tp);
	else if(type == 'p')
			print_ptr_to_str(tp);
	else if(type == 'd' || type == 'i')
			print_nbr_to_str(tp);
	else if(type == 'u')
			print_uint_to_strbase(tp,'d',10);
	else if(type == 'x')
			print_uint_to_strbase(tp,'x',16);
	else if(type == 'X')
			print_uint_to_strbase(tp,'X',16);
	else if(type == '%')
			print_percent(tp);
	
}

// #####################################################################################
// #####################################################################################
// #####################################################################################



// ############################################
// ################## table-print #############
// ############################################


void t_list_start(t_list *tp)
{
	tp->total_len = 0;
	tp->type = 0;
}
void t_list_set_type(t_list *tp,char type)
{
	tp->type = type;
}

void t_list_set_flag(t_list *tp, char flag)
{
	if(flag == '-')
		tp->f_minus = 1;
	else if(flag == '0')
		tp->f_zero = 1;
	else if(flag == '.')
		tp->f_dot = 1;
	else if(flag == '#')
		tp->f_hash = 1;
	else if(flag == ' ')
		tp->f_space = 1;
	else if(flag == '+')
		tp->f_plus = 1;
}
void t_list_reset_flags (t_list *tp)
{
	tp->f_minus = 0;
	tp->f_zero = 0;
	tp->f_dot = 0;
	tp->f_hash = 0;
	tp->f_space = 0;
	tp->f_plus = 1;
}

// FLAGS HANDLE

// DONE : PLUS and SPACE

// ############################################
// ################## core-function #############
// ############################################

int	ft_printf(const char *format, ...)
{
	int	i;
	int total_len;
	va_list ap; // ap : argument process
	t_list *tp;
	char flag;
	char d_str;
	char type;

	i = 0; 
	total_len = 0;
	tp = (t_list *)calloc(sizeof(t_list),1);
	if (!tp)
		return (-1);
	t_list_start(tp);
	va_start(tp->ap, format);

	while(*(format + i))
	{
		if(*(format + i) == '%')
		{
			i++;
			while (tp->type == 0 && !is_type(*(format+i)))
			{
				if(is_flags(*(format+i)))
				{
					flag = *(format + i);
					t_list_set_flag(tp,flag);
				}
				else if(ft_isdigit(*(format + i)))
				{
					d_str = *(format+i);
					if(tp->f_dot)
						tp->precision = (tp->precision * 10) + (d_str - '0');
					else 
						tp->width = (tp->width * 10) + (d_str - '0');
				}
				i++;
			}
			if(is_type(*(format + i)))
			{
				type = *(format + i);
				t_list_set_type(tp,type);
				print_format(tp);	
				t_list_reset_flags(tp);
			}
		}
		else 
			total_len += write(1, format + i, 1);
		i++;
	}
	va_end(ap);
	total_len += tp->total_len;
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