/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 13:25:15 by adebray           #+#    #+#             */
/*   Updated: 2016/03/13 14:38:05 by adebray          ###   ########.fr       */
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
		// ft_printf("-> %s\n", line);
		if (line[0] == '#' && line[1] != '#')
			(void)state;
		else
			consumer_array[state](line, lemin, &state);
		free(line);
	}

	if (!lemin->nbr || !lemin->start || !lemin->end)
		return (0);

	// ft_printf("%d\n", lemin->nbr);
	// ft_printf("start %s\n", lemin->start->name);
	// ft_printf("end %s\n", lemin->end->name);
	print_room(lemin->room);
	return (1);
}

struct s_stack *stack = NULL;

struct s_room	*get_container(struct s_lem_in *lemin, char *name)
{
	struct s_room	*r;
	struct s_link	*l;

	r = lemin->room;
	while (r)
	{
		l = r->link;
		while (l)
		{
			// ft_printf("%s -> %s, %s\n", name, r->name, l->room->name);
			if ( !ft_strcmp(name, l->room->name) && !is_in_stack(stack, r->name) )
				return (r);
			l = l->next;
		}
		r = r->next;
	}
	return (0);
}

int		resolve(struct s_lem_in *lemin, char *name)
{
	ft_printf("from %s\n", name);
	print_stack(stack);

	struct s_room *r = get_container(lemin, name);
	if (!r) {
		// ft_printf("no r\n");
		pop_stack();
		return (0);
	}

	char *tmp = r->name;

	ft_printf("-- %s\n", r->link->room->name);
	if (!(ft_strcmp(tmp, lemin->end->name))) {
		ft_printf("clean exit\n");
		return (1);
	}
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
	push_stack(lemin.start->name);
	resolve(&lemin, lemin.start->name);
	push_stack(lemin.end->name);
	ft_printf("--------------\n");
	print_stack(stack);
	return (0);
}
