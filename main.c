#include <unistd.h>
#include <stdio.h>

//-----------------------------------print_chars.c
int print_char(char c) {	
	write(1, &c, 1);
	return 1;
}

int print_string(char *str) {
	size_t	i;
	
	i = 0;
	while(str[i]) {
		write(1, &str[i], 1);
		i++;
	}
	return i;
}

//------------------------------print_ptr.c
static int	print_hex(unsigned long n)
{
	int				out;
	char			*ref;
	char			c;
	
	out = 0;
	ref = "0123456789abcdef";
	if (n >= 16)
		out += print_hex(n/16);
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
	out += print_hex(n);
	return out;
}


//-------------------------------- n
static int print_num(long n) {
	int  out;
	char c;

	out = 0;
	if (n > 9)
		out += ft_putnbr_base(n / 10);
	c = (n % 10) + '0';
	out += write(1, &c, 1);
	return (out);
}

int print_uint(unsigned int n)
{
	return (print_num((long)n);
}


int print_dec(int n) {
	int 	out;
	long	current_n;

	out = 0;
	current_n = n;
	if (current_n < 0)
		out+=write(1, "-", 1);
	current_n *= ((n >= 0)*2)-1;
	out+= print_num(current_n);
	return (out);
}

//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
int main() {
	int negn = -10;
	int posn = 30;
	char *str = "ciao!";
	char *ptr = "ptr!";
		


	//char *ptr = "ciao";
	//int amt = print_ptr(&ptr);
	//printf("\n%d", amt);

}
