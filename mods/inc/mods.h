#ifndef MODS_H
# define MODS_H

#include <stdlib.h>
#include <stdio.h>

enum e_type {
	NIL,
	DOUBLE,
	FLOAT,
	POINTER
};

union u_value {
	double	d;
	float	f;
	void	*p;
};

struct s_value {
	char			*k;
	union u_value	u;
	enum e_type		e;
	struct s_value	*n;
};

struct s_table {
	unsigned int	size;
	struct s_value	**array;
};

typedef struct s_value t_value;
typedef struct s_table t_table;

t_table	*init(int size);
t_value	*set(t_table *t, char *key, t_value *v);
t_value	*value(int e, union u_value u);
union u_value *get(t_table *t, char *key);

#endif
