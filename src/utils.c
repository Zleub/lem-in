/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 21:28:11 by adebray           #+#    #+#             */
/*   Updated: 2016/03/13 14:17:25 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

void	free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i += 1;
	}
	free(array);
}

extern struct s_stack *stack;

struct s_stack *make_stack(char *name)
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
		stack = make_stack(name);
	else
	{
		s = make_stack(name);
		s->next = stack;
		stack = s;
	}
}

void pop_stack()
{
	stack = stack->next;
}

void print_stack(struct s_stack *s)
{
	if (!s)
		return ;
	ft_printf("%s", s->name);
	if (s->next)
		ft_printf(", ", s->name);
	else
		ft_printf("\n");
	print_stack(s->next);
}

int		is_in_stack(struct s_stack *s, char *name)
{
	if (!ft_strcmp(s->name, name))
		return (1);
	else if (s->next)
		return is_in_stack(s->next, name);
	else
		return (0);
}
