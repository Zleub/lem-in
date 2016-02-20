/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 17:49:42 by adebray           #+#    #+#             */
/*   Updated: 2016/02/19 23:28:42 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include <libft.h>
# include <ft_printf.h>

enum {
	NBR,
	ROOM,
	TUBE,
	ELEN
};

struct s_lem_in
{
	int				nbr;
	struct s_room	*start;
	struct s_room	*end;
	struct s_room	*room;
};

struct s_room
{
	char			*name;
	struct s_room	*next;
	struct s_link
	{
		struct s_room	*room;
		struct s_link	*next;
	}				*link;
};

char			*enum_to_string(int e);
int				arraylen(char **split);
struct s_room	*alloc_room(char *name);
struct s_link	*alloc_tube(struct s_room *r);
void			print_room(struct s_room *r);
void			room_push_room(struct s_room *room1, struct s_room *room2);
void			lemin_push_room(struct s_lem_in *lemin, struct s_room *room);

int				consume_nbr(char *line, struct s_lem_in *lemin, int *state);
int				consume_room(char *line, struct s_lem_in *lemin, int *state);
int				consume_tube(char *line, struct s_lem_in *lemin, int *state);

struct s_room	*get_room(struct s_lem_in *lemin, char *name);
struct s_room	*get_container(struct s_lem_in *lemin, char *name);
void			free_array(char **array);

#endif
