/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:05:16 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/12 11:00:51 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.c"

void	expand_var(char *var, t_env *env, t_list **lst)
{
    char    *tmp;    
	char	**strs;
	int		i;
	t_list	*node;
	
	i = 0;
	tmp = var;
	var = ft_getenv(var + 1, env);
    if(!var)
	{
		(*lst)->content = NULL;
		//ft_remove_node(lst);
		free(tmp); 
    	return ;
	}
	free(tmp);
	strs = ft_split(var);
	if (!strs)
		return ;
	if (var[0] == ' ' || var[0] == '\t')
	{
		(*lst)->content = ft_strdup(" ");
	}
	else
	{
		if (!strs[0])
			return ;
		(*lst)->content = strs[i++];
	}
	while(strs[i])
	{
		if (i == 0)
		{
			node = ft_lstnew(ft_strdup(" "));
			node->type = space;
			ft_lstadd_midl(lst, node);
			(*lst) = (*lst)->next;
		}
		node = ft_lstnew(strs[i++]);
		node->type = word;
		ft_lstadd_midl(lst, node);
		(*lst) = (*lst)->next;
	}
	if (var[ft_strlen(var) - 1] == ' ' || var[ft_strlen(var) - 1] == '\t')
	{
		node = ft_lstnew(ft_strdup(" "));
		node->type = space;
		ft_lstadd_midl(lst, node);
		(*lst) = (*lst)->next;
	}

}
