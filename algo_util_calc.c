/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_util_calc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmardin <wmardin@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:40:42 by wmardin           #+#    #+#             */
/*   Updated: 2022/08/08 12:20:30 by wmardin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Returns the number of actions needed to correctly insert a node from 
stack_b into stack_a. Takes into account combo rotation moves.
	-	Calculates how many actions are needed to move the evaluated node
		to the top of stack_b.
	-	Calculates how many actions are needed to move the corresponding
		node in stack_a ("insertion node") to the top of stack_a.
Returns the sum of both actions if no combo moves are detected.
Returns only the higher of both actions if combo moves are detected.
*/
int	ft_calc_actions(t_list **stack_a, t_list **stack_b, t_list *nodefromb)
{
	t_list	*insertionnode_a;
	int		actions_b;
	int		actions_a;

	actions_b = ft_calc_movetotop(stack_b, nodefromb);
	insertionnode_a = ft_getinsertionnode(stack_a, nodefromb->rank);
	actions_a = ft_calc_movetotop(stack_a, insertionnode_a);
	if (actions_a < 0 && actions_b < 0)
	{
		if (actions_a * -1 > actions_b * -1)
			return (actions_a * -1);
		return (actions_b * -1);
	}
	if (actions_a > 0 && actions_b > 0)
	{
		if (actions_a > actions_b)
			return (actions_a);
		return (actions_b);
	}
	if (actions_a < 0)
		actions_a *= -1;
	if (actions_b < 0)
		actions_b *= -1;
	return (actions_a + actions_b);
}

/*
Returns number of actions necessary to move the passed node to the top
of the passed stack.
Returns a positive number for "rotate".
Returns a negative number for "rev_rotate".
*/
int	ft_calc_movetotop(t_list **stack, t_list *node)
{
	t_list	*temp;
	int		counter;
	int		len_list;

	counter = 0;
	len_list = ft_lstsize(*stack);
	temp = *stack;
	while (temp != node)
	{
		temp = temp->next;
		++counter;
	}
	if (counter <= len_list - counter)
		return (counter);
	return ((len_list - counter) * -1);
}
