/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:40:43 by ppimchan          #+#    #+#             */
/*   Updated: 2023/03/25 01:33:50 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return;
	// printf("S in put:%s:\n",s);
	// printf("Len in put:%zu\n",ft_strlen(s));
	write (fd, s, ft_strlen(s));
}