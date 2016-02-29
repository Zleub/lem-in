/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 11:23:49 by adebray           #+#    #+#             */
/*   Updated: 2016/02/29 11:37:56 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemin.h>

struct s_test
{
	char	*name;
	int		field;
}

struct s_stack
{
	char			*name;
	struct s_stack	*next;
};

struct s_stack *stack = NULL;

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
	ft_printf("%s\n", s->name);
	print_stack(s->next);
}

int main()
{
	push_stack("Hello");
	push_stack("World");
	push_stack("!");

	print_stack(stack);

	pop_stack();
	print_stack(stack);

	push_stack("Hello");
	push_stack("World");
	push_stack("!");

	print_stack(stack);
	pop_stack();
	print_stack(stack);


	while (42) ;
	return 0;
}
