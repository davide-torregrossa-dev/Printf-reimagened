/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtorregr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:40:34 by dtorregr          #+#    #+#             */
/*   Updated: 2026/06/13 16:40:37 by dtorregr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int	print_ptr(void *ptr);
int	print_uint(unsigned int n);
int	print_dec(int n);
int	print_char(int c);
int	print_string(char *str);
int	print_hex(unsigned long n, int upper);

#endif
