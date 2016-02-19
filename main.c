/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 13:25:15 by adebray           #+#    #+#             */
/*   Updated: 2016/02/19 19:43:27 by adebray          ###   ########.fr       */
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

int		resolve(struct s_lem_in *lemin, char *name)
{
	ft_printf("-- %s\n", name);
	char *tmp = get_container(lemin, name)->name;

	resolve(lemin, tmp);
	return (1);
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
	resolve(&lemin, lemin.end->name);
	return (0);
}
