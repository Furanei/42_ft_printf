#include <stdio.h>

int		main(int ac, char **av)
{
	if (ac)
	printf("%- + - +.10f\n", 145.1210);
	printf("%-+12f\n", 145.1);
	printf("%.10f\n", 145.1210);
	printf("%-04d\n", 12);
	return (0);
}
