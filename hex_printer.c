#include "ft_printf.h"

static int	print_hex(unsigned long n, int upper)
{
	int				out;
	char			*ref;
	char			c;
	
	out = 0;
	if (upper)
		ref = "0123456789ABCDEF";
	else
		ref = "0123456789abcdef";
	if (n >= 16)
		out += print_hex(n/16, upper);
	c = ref[n % 16];
	out += write(1, &c, 1);
	return out;
}

int print_ptr(void *ptr) {
	unsigned long	n;
	int				out;

	out = 0;
	if (!ptr)
		return (write(1, "(nil)", 5));
	n = (unsigned long)ptr;
	out += write(1, "0x", 2);
	out += print_hex(n, 0);
	return out;
}
