/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digits_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtorregr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 16:39:54 by dtorregr          #+#    #+#             */
/*   Updated: 2026/06/13 16:39:56 by dtorregr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_num(long n)
{
	int		out;
	char	c;

	out = 0;
	if (n > 9)
		out += print_num(n / 10);
	c = (n % 10) + '0';
	out += write(1, &c, 1);
	return (out);
}

int	print_uint(unsigned int n)
{
	return (print_num((long)n));
}

int	print_dec(int n)
{
	int		out;
	long	current_n;

	out = 0;
	current_n = n;
	if (current_n < 0)
		out += write(1, "-", 1);
	current_n *= ((n >= 0) * 2) - 1;
	out += print_num(current_n);
	return (out);
}
