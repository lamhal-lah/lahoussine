/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handl_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:49:15 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/12 10:17:15 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_arg(t_list *lst)
{
	int i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp && tmp->type != Pipe)
	{
		if (tmp->type > 0 &&  tmp->type < 5)
		{
			tmp = tmp->next->next; // < h < f < h
		}
		else
		{
			i++;
			tmp && (tmp = tmp->next);
		}
	}
	return (i);
}

char	**get_args(t_list **lst)
{
	char	**av;
	t_list	*tmp;
	int	i;

	tmp = *lst;
	i = 0;
	av = malloc((count_arg(*lst) + 1)* sizeof(char **));
	while(tmp && tmp->type != Pipe)
	{
		if (tmp->type > 0 && tmp->type < 5)
			tmp = tmp->next->next;
		else
		{
			av[i++] = ft_strdup(tmp->content);
			tmp = tmp->next;
		}
	}
	*lst = tmp;
	av[i] = NULL;
	return (av);
}

t_list	*handll_red(t_list *lst)
{
	t_list	*red;
	t_list	*tmp;
	t_list	*node;
	char	*str;

	red = NULL;
	tmp = lst;
	while (tmp && tmp->next && tmp->type != Pipe)
	{
		if(tmp->type > 0 && tmp->type < 5)
		{
			str = ft_strdup(tmp->next->content);
			node = ft_lstnew(str);
			node->type = tmp->type;
			ft_lstadd_back(&red, node);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (red);
}

t_cmds	*ft_lstnew_cmd(t_list **lst)
{
	t_cmds	*node;
	int		i;

	i = 0;
	node = (t_cmds *)malloc(sizeof(t_cmds));
	if (!node)
		return (NULL);
	// node->av = malloc((count_arg(*lst) + 1)* sizeof(char *));
	// if (!node->av)
	// 	return (NULL);
	node->red = handll_red(*lst);
	node->av = get_args(lst);
	node->fdin = -1337;
	node->fdout = -1337;
	node -> next = NULL;
	return (node);
}

t_cmds    *list_cmds(t_list *lst)
{
	t_cmds  *cmds;
	t_list	*tmp;
	t_cmds	*node;
	int		bgn;

	bgn = 1;
	node = NULL;
	cmds = NULL;
	tmp = lst;
	while (tmp)
	{
		if (tmp && tmp->type != Pipe)
		{
			node = ft_lstnew_cmd(&tmp);
			bgn = 0;
			ft_lstadd_back_cmd(&cmds, node);
		}
		tmp && (tmp = tmp->next);
	}
	return (cmds);
}

void	remove_spaces(t_list **lst)
{
	t_list	*tmp;
	
	tmp = *lst;
	while(tmp && tmp->next)
	{
		if (tmp->next->type == space)
			ft_remove_node(&tmp->next);
		else
			tmp = tmp->next;
	}
}

// void	reflag_limeter(t_list *lst)
// {
// 	t_list	*tmp;
	

// 	tmp = lst;
// 	if (tmp->type != limtr_qt && tmp->next->type == limtr_qt &&
// 		(tmp->next->type == squot || tmp->next->type == dquot))
// 		tmp->type = limtr_qt;
// 	else if (tmp->type != limtr_qt && tmp->type != limtr &&
// 			(tmp->next->type == ambigus || tmp->next->type == var ||
// 			tmp->next->type == word || tmp->type == limtr))
// 		tmp->type = limtr;
// }

void	ft_lst_join(t_list **lst)
{
	t_list	*tmp;
	char	*tmp_content;

	tmp = *lst;
	while(tmp && tmp->next)
	{
		if (tmp->type != space && tmp->type > 4)
		{
			while(tmp && tmp->next && tmp->next->type != space && tmp->next->type > 4)
			{
				tmp_content = tmp->content;
				tmp->content = ft_strjoin(tmp->content, tmp->next->content);
				free(tmp_content);
				ft_remove_node(&tmp->next);
			}
		}
		tmp && (tmp = tmp->next);
	}
	remove_spaces(lst);
}

