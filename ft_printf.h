/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:41:23 by ppimchan          #+#    #+#             */
/*   Updated: 2023/03/24 02:00:40 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include	<stdlib.h>
# include	<limits.h>
# include	<stdarg.h>
# include	<unistd.h>
# include	<stdio.h>

int		ft_printf(const char *format, ...);


// MEM
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

// PUT
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);


// LEN
size_t	ft_strlen(const char *s);
size_t	ft_intlen_base(size_t nb, int div);
size_t	ft_uint_len(unsigned int nb, int div);

// N->STRING
char	*ptr_to_str(size_t p);
char	*ulong_to_str_hex(size_t x, char format);
char	*nbr_to_str_dec(int d);
char	*uint_to_str_base(unsigned int x, char type,unsigned int base);
char	*ft_itoa(int n);

// STR MASTER
char	*ft_strjoin(char const *s1, char const *s2);

#endif