/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:10:34 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/11 09:13:10 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	 remove_quotes(t_list *list)
{
	t_list	*tmp;
    char    *tmp_var;

	if (!list)
		return ;
	tmp = list;
	while (tmp)
	{
		if(tmp->type == squot || tmp->type == dquot)
		{
			tmp_var = tmp->content;
			tmp->content = ft_substr(tmp->content, 1, ft_strlen(tmp->content) - 2);
            free(tmp_var);
		}
		tmp = tmp->next;
	}
}

void	remove_empty_node(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	while(tmp && tmp->next)
	{
	
		if(tmp->next->content == NULL)
			ft_remove_node(&tmp->next);
		else
			tmp = tmp->next;
	}
	tmp = *lst;
	while(tmp && tmp->next)
	{
	
		if(tmp->type == space && tmp->next->type == space)
			ft_remove_node(&tmp->next);
		else
			tmp = tmp->next;
	}
}