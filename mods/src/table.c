#include <mods.h>

size_t	ft_strlen(const char *s)
{
	char	*tmp;

	tmp = (char*)s;
	if (s == 0)
		return (0);
	while (*tmp)
		++tmp;
	return (tmp - s);
}

int			ft_strcmp(const char *s1, const char *s2)
{
	size_t	lenght;

	lenght = ft_strlen(s2);
	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (*s2);
	else if (!s2)
		return (*s1);
	while (*s1 == *s2)
	{
		if (lenght-- == 0)
			return (0);
		s1++;
		s2++;
	}
	if (*s1 - *s2 < -127)
		return (1);
	return (*s1 - *s2);
}

void	ft_bzero(void *s, size_t n)
{
	while (n) {
		(((char *)s))[n] = 0;
		n -= 1;
	}
}

t_value	*value(int e, union u_value u)
{
	t_value *val = malloc(sizeof(t_value));
	ft_bzero(val, sizeof(t_value));

	val->e = e;
	val->u = u;
	return val;
}

unsigned int hash(unsigned int size, char *line)
{
	unsigned int	hashich;
	int				c;

	hashich = 5381;
	while ((c = *line++))
		hashich = ((hashich << 5) + hashich) ^ c;
	if (hashich > size)
		return (hashich % size);
	return (hashich);
}

t_value *assign(t_value **v, t_value *nv)
{
	if ((*v) && (*v)->e != NIL) {
		if (!ft_strcmp((*v)->k, nv->k))
		{
			free((*v)->k);
			free(*v);
			*v = nv;
			return (*v);
		}
		else
		if (!(*v)->n) {
			(*v)->n = malloc(sizeof(t_value));
			ft_bzero((*v)->n, sizeof(t_value));
		}
		assign(&(*v)->n, nv);
	}
	else
		(*v) = nv;
	return (*v);
}

t_value	*set(t_table *t, char *key, t_value *v)
{
	unsigned int h;

	h = hash(t->size, key);
	v->k = key;
	// printf("%p\n", t->array[h]);
	return (assign(&t->array[h], v));
}

union u_value NILL = {
	.p = NULL
};

union u_value *solve_collision(t_value *v, char *key)
{
	if (!v)
		return (&NILL);
	else if (!ft_strcmp(v->k, key))
		return (&v->u);
	else if (v->n)
		return (solve_collision(v->n, key));
	else
		return (&NILL);
}

union u_value *get(t_table *t, char *key)
{
	unsigned int h;

	h = hash(t->size, key);
	return (solve_collision(t->array[h], key));
}

t_table	*init(int size)
{
	t_table *t;

	if (!(t = malloc(sizeof(t_table))))
		return (NULL);
	else if (!(t->array = malloc(sizeof(t_value *) * size)))
		return (NULL);

	t->size = size;
	int i = 0;
	while (i < size)
	{
		t->array[i] = NULL;
		i += 1;
	}
	// ft_bzero(t->array, sizeof(t_value) * size);
	return (t);
}
