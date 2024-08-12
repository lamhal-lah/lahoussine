/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:58:19 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/12 10:50:30 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*expand_var_dqout(char *varaible, t_env *env)
// {
// 	char	*tmp;

// 	if ( varaible && !varaible[1])
// 		return(varaible);
// 	tmp = varaible;
// 	varaible = ft_getenv(varaible + 1, env);
//     if(!varaible)
//         return (NULL);
//     varaible = ft_strdup(varaible);
//     free(tmp);
// 	return varaible;
// }


// char    *get_str(char *str, int *indx, t_env *env)
// {
//     int i;
//     char    *str1;
//     int    k;

//     i = *indx;
//     k = *indx;
//     if (str[i] == '$')
//     {
//         i++;
//         while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') ||
//                 (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_' ||
//             (str[i] >= '0' && str[i] <= '9')))
//             i++;
//     }
//     else
//         while(str[i] && str[i] != '$')
//             i++;
//     str1 = ft_substr(str, k, i - k);
//     if (str1 && str1[0] == '$')
//         str1 = expand_var_dqout(str1, env);
//     *indx = i;
//     return (str1);
// }

// char    *expand_dquot(char *str, t_env *env)
// {
//     char    *str1;
//     char    *str2;
//     int        i;

//     i = 0;
//     str1 = get_str(str, &i, env);
//     while(str[i])
//     {
//         str2 = get_str(str, &i, env);
//         str1 = ft_strjoin_free(str1, str2);
//     }
//     free(str);
//     return (str1);
// }


// void	expand(t_list *lst, t_env *env)
// {
// 	t_list	*tmp;

// 	tmp = lst;
// 	while (tmp)
// 	{
// 		if (tmp->type == var)
// 			expand_var(tmp->content, env, &tmp);
// 		if (tmp->type == dquot)
// 			tmp->content = expand_dquot(tmp->content, env);
// 		tmp && (tmp = tmp->next);
// 	}
// 	remove_empty_node(&lst);
// }


char	*expand_var_dqout(char *varaible, t_env *env)
{
	char	*tmp;

	if ( varaible && !varaible[1])
		return(varaible);
	tmp = varaible;
	varaible = ft_getenv(varaible + 1, env);
    varaible = ft_strdup(varaible);
    free(tmp);
	return varaible;
}

char    *get_str(char *str, int *indx, t_env *env)
{
    int i;
    char    *str1;
    int    k;

    i = *indx;
    k = *indx;
    if (str[i] == '$')
    {
        i++;
        while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') ||
                (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_' ||
            (str[i] >= '0' && str[i] <= '9')))
            i++;
    }
    else
        while(str[i] && str[i] != '$')
            i++;
    str1 = ft_substr(str, k, i - k);
    if (str1 && str1[0] == '$')
        str1 = expand_var_dqout(str1, env);
    *indx = i;
    return (str1);
}


char    *expand_dquot(char *str, t_env *env)
{
    char    *str1;
    char    *str2;
    int        i;

    i = 0;
    str1 = get_str(str, &i, env);
    while(str[i])
    {
        str2 = get_str(str, &i, env);
        str1 = ft_strjoin_free(str1, str2);
    }
    free(str);
    return (str1);
}




void	expand(t_list *lst, t_env *env)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->type == var)
			expand_var(tmp->content, env, &tmp);
		if (tmp->type == dquot)
			tmp->content = expand_dquot(tmp->content, env);
		tmp && (tmp = tmp->next);
	}
	remove_empty_node(&lst);
}
