#include <libft.h>
#include <ft_printf.h>

typedef struct s_hash_table t_table;
struct s_hash_table {
	size_t id;
	size_t size;
	t_table *children;
};

void print_table(t_table *t)
{
	size_t i = 0;

	ft_printf("== %d [%p] ==\n", t->id, t);
	while (t->children && i < t->size) {
		ft_printf("-> %d\n", t->children[i].id);
		i += 1;
	}
}

typedef struct s_lem_in t_lem_in;
struct s_lem_in {
	int nbr;
	t_table *start;
	t_table *end;

	t_table *g;
};

// void alloc_table()

void *add_room(t_lem_in *main, char *str) {
	(void)main; (void)str;

	ft_printf("new room, current size: %d\n", main->g->size);

	char **_ = ft_strsplit(str, ' ');

	t_table *tmp;
	main->g->size += 1;
	tmp = main->g->children;
	main->g->children = malloc(sizeof(t_table) * main->g->size);
	ft_memcpy(main->g->children, tmp, sizeof(t_table) * (main->g->size - 1));
	ft_bzero(&main->g->children[main->g->size - 1], sizeof(t_table));
	main->g->children[main->g->size - 1].id = ft_atoi(_[0]);
	free(tmp);
	return (&main->g->children[main->g->size - 1]);
}

int get_nbr(t_lem_in *main, char *str) {
	main->nbr = ft_atoi(str);
	ft_printf("I got %d ants\n", main->nbr);
	return (1);
}

int get_room(t_lem_in *main, char *str) {
	(void)main; (void)str;

	static t_table **p;

	int i = 0;
	while (str[i]) {
		if (str[i] == '-')
			return (-1);
		i += 1;
	}

	if (!ft_strcmp(str, "##start")) {
		p = &main->start;
		return (0);
	}
	else if (!ft_strcmp(str, "##end")) {
		p = &main->end;
		return (0);
	}

	if (p)
		*p = add_room(main, str);
	else
		add_room(main, str);

	if (p == &main->start)
		p = 0;
	else if (p == &main->end)
		p = 0;

	return (0);
}

int get_path(t_lem_in *main, char *str) {
	(void)main; (void)str;

	ft_printf("get-path: %s\n", str);
	return (0);
}

static int(*states[])(t_lem_in *main, char *str) = {
	get_nbr, get_room, get_path
};

char *handle_comment(char *str) {
	int i = 0;
	while (str[i]) {
		if (str[i] == '#' && str[i + 1] != '#')
			break;
		else if (str[i] == '#' && str[i + 1] == '#')
			i += 1;
		i += 1;
	}

	if (str[i])
		str[i] = '\0';
	return ft_strtrim(str);
}

void parse(t_lem_in *main, char *str) {
	static int state;
	int res = 0;

	str = handle_comment(str);
	if (states[state])
		res = states[state](main, str);

	if (res == 1)
		state += 1;
	else if (res == -1) {
		state += 1;
		parse(main, str);
	}
}

int main(void) {
	t_lem_in main;

	ft_bzero(&main, sizeof(t_lem_in));
	main.g = (t_table*)malloc(sizeof(t_table));
	ft_bzero(main.g, sizeof(t_table));
	main.g->id = -1;

	char *str;
	while (get_next_line(0, &str) > 0) {
		parse(&main, str);
		free(str);
	}

	ft_printf("main:\n");
	ft_printf("\tnbr: %d\n", main.nbr);
	ft_printf("start: %d\n", main.start->id);
	ft_printf("end: %d\n", main.end->id);
	print_table(main.g);
	return (0);
}
