int print_char(int c) {
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
