/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambgus.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:45:15 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/12 10:58:48 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_ambigus(t_list *lst, t_env *env)
{
	t_list	*tmp;
	char	*varaib;
	//int		spc_at_bgn;
	//int		spc_at_end;
	
	tmp = lst;
	while(tmp && tmp->type != space  && tmp->type > 4)
	{
		if (tmp->type == var)
		{
			varaib = ft_getenv(tmp->content + 1, env);
			if (count_words(varaib) > 1)
				return (1);
			else if (count_words(varaib) == 0)
			{
				
			}
		}
		tmp = tmp->next;
	}
	while(tmp && tmp->type != space  && tmp->type > 4)
	{
		if (tmp->type == var)
		{
			varaib = ft_getenv(tmp->content + 1, env);
			if (count_words(varaib) > 1)
				return (1);
		}
		tmp = tmp->next;
	}
	tmp = lst;
	return (0);
}

void	flag_ambigus(t_list *lst, t_env *env)
{
	t_list	*tmp;
	int		ambg;
	
	tmp = lst;
	while(tmp && tmp->next)
	{
		ambg = 0; 
		if (tmp->type == red_out || tmp->type == red_in || tmp->type == append)
		{
			tmp = tmp->next;
			if (tmp->type == space)
				tmp = tmp->next;
			ambg = check_ambigus(tmp, env);
			while(tmp && tmp->type != space  && tmp->type > 4)
			{
				if (ambg && tmp->type == var)
					tmp->type = ambigus;
				tmp = tmp->next;
			}
		}
		tmp && (tmp->type != red_out) && tmp->type != red_in && tmp->type != append && (tmp = tmp->next);
	}
}