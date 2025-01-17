/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 10:05:02 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/12 10:19:23 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handll_qout(char *line, int *i)
{
	char	c;
	int		len;
	
	len = *i;
	c = line[len++];
	while (line[len] && line[len] != c)
		len++;
	len += 1 - *i;

	return (len);
}

int	handell_varaibl(char *line, int *i)
{
	int len;

	len = *i;
	if (line[len] == '$' && line[len + 1] >= '0' && line[len + 1] <= '9')
		return (2);
	else if (line[len] == '$' && line[len + 1] == '$')
	{
		while (line[len] == '$')
			len++;
		len -= *i;
		(len % 2 == 1) && len--;
	}
	else if(line[len] == '$')
	{
		len++;
		while ((line[len] >= 'a' && line[len] <= 'z') ||
			(line[len] >= 'A' && line[len] <= 'Z') || line[len] == '_' ||
			(line[len] >= '0' && line[len] <= '9'))
			len++;
		len -= *i;
	}
	return (len);	
}

int	handell_words(char *line, int *i)
{
	int len;

	len = *i;
	while (line[len] && line [len] != ' ' && line[len] != '\t' && 
			line[len] != '|' && line[len] != '>' && line[len] != '<' &&
			line[len] != '$' && line[len] != '\"' && line[len] != '\'')
			len++;
		len -= *i;
	return (len);
}

void	*get_token(char *line, int *i)
{
	int		len;
	char	*token;
	
	len = *i;
	if (line[len] == 39 || line[len] == 34)
		len = handll_qout(line, i);
	else if ((line[len] == '>' && line[len + 1] == '>') ||
			(line[len] == '<' && line[len + 1] == '<'))
		len = 2;
	else if (line[len] == '|' || line[len] == '>' || line[len] == '<')
		len = 1;
	else if(line[len] == '$')
		len = handell_varaibl(line, i);
	else if (line[len] != ' ' && line[len] != '\t')
		handell_words(line, i);
	token = ft_substr(line, *i, len);
	if (!token)
		return (NULL);
	*i += len;
	return (token);
}

// void	*get_token_var(char *line, int *i)
// {
// 	int		len;
// 	char	*token;
	
// 	len = *i;
// 	if (line[*i] == ' ' || line[*i] == '\t')
// 	{
// 		while (line[len] == ' ' || line[len] == '\t')
// 			len++;
// 		if (line[len])
// 			token = ft_strdup(" ");
// 		*i = len;
// 		return (token);
// 	}
// 	else if(line[len] == '$')
// 		len = handell_varaibl(line, i);
// 	else if (line[len] != ' ' && line[len] != '\t')
// 		handell_words(line, i);
// 	token = ft_substr(line, *i, len);
// 	if (!token)
// 		return (NULL);
// 	*i += len;
// 	return (token);
// }
