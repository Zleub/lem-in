/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 17:52:15 by adebray           #+#    #+#             */
/*   Updated: 2016/02/19 19:12:12 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

int		consume_nbr(char *line, struct s_lem_in *lemin, int *state)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			return (0);
		i += 1;
	}
	*state = ROOM;
	lemin->nbr = ft_atoi(line);
	return (lemin->nbr);
}

int		consume_room(char *line, struct s_lem_in *lemin, int *state)
{
	static struct s_room **forward_alloc;
	char	**split;

	split = ft_strsplit(line, ' ');
	if (!ft_strcmp("##start", line))
		forward_alloc = &lemin->start;
	else if (!ft_strcmp("##end", line))
		forward_alloc = &lemin->end;
	else if (forward_alloc != 0 && arraylen(split) == 3)
	{
		*forward_alloc = alloc_room(split[0]);
		lemin_push_room(lemin, *forward_alloc);
		forward_alloc = 0;
	}
	else if (arraylen(split) == 3)
		lemin_push_room(lemin, alloc_room(split[0]));
	else
	{
		*state = TUBE;
		consume_tube(line, lemin, state);
	}
	return (0);
}

int		consume_tube(char *line, struct s_lem_in *lemin, int *state)
{
	struct s_room	*s1;
	struct s_room	*s2;
	char			**split;

	(void)state;
	split = ft_strsplit(line, '-');
	if (arraylen(split) == 2)
	{
		s1 = get_room(lemin, split[0]);
		s2 = get_room(lemin, split[1]);

		if (s1 && s2 && ft_strcmp(split[0], split[1]))
			room_push_room(s1, s2);
	}
	else
	{
		ft_printf("else %s\n", line);
	}

	return (0);
}
