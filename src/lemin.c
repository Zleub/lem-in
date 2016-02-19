/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 17:51:37 by adebray           #+#    #+#             */
/*   Updated: 2016/02/19 19:09:36 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

char	*enum_to_string(int e)
{
	if (e == NBR) return "NBR" ;
	if (e == ROOM) return "ROOM" ;
	if (e == TUBE) return "TUBE" ;
	else return "NOENUM" ;
}

struct s_room	*alloc_room(char *name)
{
	struct s_room	*r;

	if (!(r = (struct s_room *)malloc(sizeof(struct s_room))))
		exit(-1);
	ft_bzero(r, sizeof(struct s_room));
	r->name = name;
	return (r);
}

struct s_link	*alloc_tube(struct s_room *r)
{
	struct s_link *s;

	s = (struct s_link*)malloc(sizeof(struct s_link));
	s->room = r;
	s->next = 0;
	return (s);
}

void			print_room(struct s_room *r)
{
	struct s_link *l;

	l = r->link;
	ft_printf("ROOM:\n");
	ft_printf("name: %s\n", r->name);
	while (l)
	{
		ft_printf("\t%s\n", l->room->name);
		l = l->next;
	}
	if (r->next)
		print_room(r->next);
}

void			room_push_room(struct s_room *room1, struct s_room *room2)
{
	struct s_link *l;

	l = room1->link;
	if (!room1->link)
		room1->link = alloc_tube(room2);
	else
	{
		while (l->next)
			l = l->next;
		l->next = alloc_tube(room2);
	}
}

void			lemin_push_room(struct s_lem_in *lemin, struct s_room *room)
{
	static struct s_room *last;

	if (!lemin->room)
		lemin->room = room;
	else
		last->next = room;
	last = room;
}

struct s_room	*get_room(struct s_lem_in *lemin, char *name)
{
	struct s_room	*r;

	r = lemin->room;
	while (r)
	{
		if (!ft_strcmp(r->name, name))
			return (r);
		r = r->next;
	}
	return (0);
}

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
			if (!ft_strcmp(l->room->name, name))
				return (r);
			l = l->next;
		}
		r = r->next;
	}
	return (0);
}
