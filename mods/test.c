#include <mods.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void	ft_bzero(void *s, size_t n);
float	get_use(t_table *t);

char *random_string(int size)
{
	char *str = malloc(size + 1);
	ft_bzero(str, size + 1);

	while (size)
	{
		str[size - 1] = arc4random_uniform(10) + 65;
		size -= 1;
	}
	return str;
}

int main(void)
{
	srand(time(NULL));
	t_table *c = init(10);

	int i = 1;
	while (i < 20)
	{
		char *buf = random_string(1);

		set(c, buf, value(DOUBLE, (union u_value)(double)i));
		i += 1;
	}

	set(c, "arno", value(DOUBLE, (union u_value)(double)4242));
	printf("%f\n", get(c, "arno")->d);

	i = 'A';
	while (i <= 'A' + 10) {
		printf("%c: %f\n", i, (double)get(c, (char *)&i)->d);
		i += 1;
	}

	while (42) ;
	return (0);
}
