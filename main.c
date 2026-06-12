#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//-----------------------------------print_words.c
int print_char(void *p) {
	char c = (char)(long)p;	
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


//-------------------------------- n
static int print_num(long n) {
	int  out;
	char c;

	out = 0;
	if (n > 9)
		out += print_num(n / 10);
	c = (n % 10) + '0';
	out += write(1, &c, 1);
	return (out);
}

int print_uint(unsigned int n) {
	return print_num((long)n);
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

typedef int (*f)(void *);
typedef struct Couple {
	char key;
	f func;
	struct Couple *next;
} Couple;


Couple *add_couple(Couple *head, char key, f func)
{
	Couple *node = malloc(sizeof(Couple));
	if (!node) return head;

	node->key = key;
	node->func = func;
	node->next = head;
	return node;
}

Couple *find_couple(Couple *head, char key)
{
    while (head) {
        if (head->key == key)
            return head;

        head = head->next;
    }
    return 0;
}


void free_list(Couple *head)
{
    while (head) {
        Couple *tmp = head;
        head = head->next;
        free(tmp);
    }
}


int main() {
	Couple *couples;
	Couple *found_couple; 
	
	couples = 0;
	couples = add_couple(couples, 'c', print_char);
	//couples = add_couple(couples, 's', print_string);
	//couples = add_couple(couples, 'd', print_dec);
	found_couple = find_couple(couples, 's');
	if (found_couple)
		found_couple -> func((void *)(long)42);
	free_list(couples);
}
/*
	int negn = -10;
	int posn = 30;
	char *str = "ciao!";
	char *ptr = "ptr!";

	oprintf("d---------------------------------");
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
	printf(" returns %d\n\n", print_string((char[]){'c', 0}));
	
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
}
*/
