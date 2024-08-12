/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:43:52 by lamhal            #+#    #+#             */
/*   Updated: 2024/08/12 10:39:16 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <stdio.h>
# include <fcntl.h>

typedef enum
{
	Pipe,
	red_out,
	red_in,
	herdoc,
	append,
	dquot,
	squot,
	var,
	space,
	word,
	limtr,
	limtr_qt,
	ambigus
}	t_type;

typedef struct s_list
{
	char			*content;
	t_type			type;
	struct s_list	*next;
}	t_list;

typedef struct s_cmds
{
	t_list	*red;
	char	**av;
	int		fdin;
	int		fdout;
	struct s_cmds *next;	
}t_cmds;


typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	int				printed;
}	t_env;

size_t	ft_strlen(const	char *str);
t_list	*ft_lstnew(char *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **l, t_list *new);
void	ft_remove_node(t_list **lst);
void	ft_lstclear(t_list **lst);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
t_cmds	*proccess_line(char *line, t_list **lst, t_env *env);
int		check_syntaxe_error(t_list *lst);
t_env	*ft_lstnew_env(char *env);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void	ft_lstadd_midl(t_list **lst, t_list *new);
void	ft_lstadd_front_env(t_env **l, t_env *new);
void	ft_lstclear_env(t_env **lst);
t_env	*ft_env(char **env);
void	 remove_quotes(t_list *list);
char   *ft_getenv(char *key, t_env *env);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free(char *str1, char *str2);
char	*ft_strchr(const char *s, int c);
void	expand(t_list *lst, t_env *env);
t_cmds	*ft_lstnew_cmd(t_list **lst);
void	ft_lstadd_back_cmd(t_cmds **lst, t_cmds *new);
void	ft_lstclear_cmd(t_cmds **lst);
t_cmds	*list_cmds(t_list *lst);
int		count_words(char *str);
char	**ft_split(char *str);
void	ft_lst_join(t_list **lst);
void	remove_empty_node(t_list **lst);
void	*get_token(char *line, int *i);
void	flag_ambigus(t_list *lst, t_env *env);
// void	*get_token_var(char *line, int *i);
void	expand_var(char *var, t_env *env, t_list **lst);


#endif