/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:55:22 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/12 10:56:33 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_list	*lst;
	t_env	*env_lst;
	t_cmds	*cmds;
	char	*line;

	(void)ac;
	(void)av;
	lst = NULL;
	env_lst = ft_env(env);
	line = readline("minishell:  ");
	while (line && ft_strncmp(line, "exit", 5))
	{
		//printf("line = %s\n", line);
		if (ft_strlen(line) > 0)
			add_history(line);
		system("leaks minishell");
		cmds = proccess_line(line, &lst, env_lst);
		free(line);
		ft_lstclear(&lst);
		line = readline("minishell:  ");
	}
}
