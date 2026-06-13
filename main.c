#include "ft_printf.h"
int parse_and_print(va_list var, char c)
{
	if (c == '%')
		return print_char('%');
	if (c == 'c')
		return print_char(va_arg(var, int));
	if (c == 's')
		return print_string(va_arg(var, char *));
	if (c == 'i' || c == 'd')
		return print_dec(va_arg(var, int));
	if (c == 'u')
		return print_uint(va_arg(var, unsigned int));
	if (c == 'p')
		return print_ptr(va_arg(var, void *));
	if (c == 'x')
		return print_hex(va_arg(var, unsigned int), 0);
	if (c == 'X')
		return print_hex(va_arg(var, unsigned int), 1);
		
	return 0;
}

int ft_printf(const char *str, ...)
{
	int i;
	int count;
	va_list args;

	count = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			count += parse_and_print(args, str[i+1]);
			i+=2;
		}
		if (!str[i])
			break;
		if (str[i] == '%')
			continue;
		write(1, &str[i], 1);
		count++;
		i++;
	}
	va_end(args);
	return count;
}

int main()
{
	ft_printf("la stringa dice %s", "ciao");
}


//int main() 
//{
//	ft_print(		
	
	/*
	int negn = -10;
	int posn = 30;
	char *str = "ciao!";
	char *ptr = "ptr!";

	printf("d---------------------------------");
	printf("original: \n");
	printf(" returns %d\n", printf("%d", negn));
	printf("mine: \n");
	printf(" returns %d\n\n", print_dec(negn));

	printf("original: \n");
	printf(" returns %d\n", printf("%d", posn));
	printf("mine: \n");
	printf(" returns %d\n\n", print_dec(posn));

	printf("s---------------------------------");
	printf("original: \n");
	printf(" returns %d\n", printf("%s", str));
	printf("mine: \n");
	printf(" returns %d\n\n", print_string(str));
	
	printf("c---------------------------------");
	printf("original: \n");
	printf(" returns %d\n", printf("%c", 'c'));
	printf("mine: \n");
	printf(" returns %d\n\n", print_char('c'));
	
	printf("p---------------------------------");
	printf("original: \n");
	printf(" returns %d\n", printf("%p", &str));
	printf("mine: \n");
	printf(" returns %d\n\n", print_ptr(&str));

	printf("i---------------------------------");
	printf("original: \n");
	printf(" returns %d\n", printf("%i", posn));
	printf("mine: \n");
	printf(" returns %d\n\n", print_dec(posn));

	printf("original: \n");
	printf(" returns %d\n", printf("%i", negn));
	printf("mine: \n");
	printf(" returns %d\n\n", print_dec(negn));
	
	printf("u---------------------------------");
	printf("original: \n");
	printf(" returns %d\n", printf("%u", posn));
	printf("mine: \n");
	printf(" returns %d\n\n", print_dec(posn));

	printf("x---------------------------------");
	printf("original: \n");
	printf(" returns %d\n", printf("%x", 255));
	printf("mine: \n");
	printf(" returns %d\n\n", print_hex(255, 0));

	printf("X---------------------------------");
	printf("original: \n");
	printf(" returns %d\n", printf("%X", 255));
	printf("mine: \n");
	printf(" returns %d\n\n", print_hex(255, 1));
	*/
//}
