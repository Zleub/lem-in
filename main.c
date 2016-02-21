/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 13:25:15 by adebray           #+#    #+#             */
/*   Updated: 2016/02/21 16:42:49 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

typedef int(*t_consumer)(char *, struct s_lem_in *, int *);

t_consumer	consumer_array[ELEN] = {
	&consume_nbr,
	&consume_room,
	&consume_tube
};


int		get_data(struct s_lem_in *lemin)
{
	char	*line;
	int		state;

	(void)lemin;
	state = NBR;
	while(get_next_line(0, &line) > 0)
	{
		ft_printf("-> %s\n", line);
		if (line[0] == '#' && line[1] != '#')
			(void)state;
		else
			consumer_array[state](line, lemin, &state);
		free(line);
	}

	if (!lemin->nbr || !lemin->start || !lemin->end)
		return (0);

	ft_printf("%d\n", lemin->nbr);
	ft_printf("start %s\n", lemin->start->name);
	ft_printf("end %s\n", lemin->end->name);
	print_room(lemin->room);
	return (1);
}

struct s_stack
{
	char			*name;
	struct s_stack	*next;
};

struct s_stack *stack = NULL;

struct s_stack *allocat_stack(char *name)
{
	struct s_stack *s;

	s = (struct s_stack *)malloc(sizeof(struct s_stack));
	ft_bzero(s, sizeof(struct s_stack));
	s->name = name;
	return (s);
}

void push_stack(char *name)
{
	struct s_stack *s;

	if (!stack)
		stack = allocat_stack(name);
	else
	{
		s = allocat_stack(name);
		s->next = stack;
		stack = s;
	}
}

void pop_stack()
{
	stack = stack->next;
}

struct s_room	*get_container(struct s_lem_in *lemin, char *name)
{
	struct s_room	*r;
	struct s_link	*l;
	struct s_stack	*s;

	r = lemin->room;
	while (r)
	{
		l = r->link;
		while (l)
		{
			s = stack;
			if (s) {
				while (s)
				{
					ft_printf("%s: %s, %s, %s\n", name, r->name, l->room->name, s->name);
					if (!ft_strcmp(l->room->name, name) && ft_strcmp(r->name, s->name) && !ft_strcmp(l->room->name, s->name))
					{
						ft_printf(": %s, %s, %s\n", l->room->name, s->name, name);
						return (r);
					}
					s = s->next;
				}
			}
			else if (!ft_strcmp(l->room->name, name))
			{
				ft_printf("no stack\n");
				return (r);
			}
			l = l->next;
		}
		r = r->next;
	}
	return (0);
}

int		resolve(struct s_lem_in *lemin, char *name)
{
	ft_printf("from %s\n", name);
	struct s_room *r = get_container(lemin, name);
	// if (!r) {
	// 	// pop_stack();
	// 	return (0);
	// }

	char *tmp = r->name;

	ft_printf("-- %s\n", tmp);
	if (!(ft_strcmp(tmp, lemin->start->name)))
		return (1);
	push_stack(tmp);
	resolve(lemin, tmp);
	return (0);
}

int		main(void)
{
	struct s_lem_in		lemin;

	ft_bzero(&lemin, sizeof(struct s_lem_in));
	if (!get_data(&lemin))
	{
		ft_printf("Error\n");
		return (0);
	}
	push_stack(lemin.end->name);
	ft_printf("resolve\n");
	resolve(&lemin, lemin.end->name);
	return (0);
}
