/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:59:46 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/02 09:46:09 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_dlr(char *s, char **ds, char **ds2)
{
	free(s);
	double_str_free(ds);
	double_str_free(ds2);
}

void	lredirect_args(char **arg, char *cmd, t_shell *shell)
{
	int i;

	i = 1;
	while (arg[i])
		ft_left_redirection(cmd, arg[i++], shell);
}

char	*sub_arg(char *command)
{
	int i;

	i = 0;
	while (command[i] == ' ')
		i++;
	while (command[i] && command[i] != ' ')
		i++;
	while (command[i] == ' ')
		i++;
	if (!command[i])
		return (ft_strdup(""));
	return (ft_substr(command, i, ft_strlen(command)));
}

char	*mright_redir_parse(char **cmds)
{
	char	*ncmd;
	char	*tmp;
	int		i;

	i = 1;
	if (!(ncmd = ft_strdup(cmds[0])))
		ft_errnoq();
	while (cmds[i])
	{
		if (!(tmp = sub_arg(cmds[i])))
			ft_errnoq();
		if (!(ncmd = ft_strjoin_f(ncmd, tmp)))
			ft_errnoq();
		free(tmp);
		i++;
	}
	return (ncmd);
}

int		comm_red_lenght(char *command, char token)
{
	int		i;
	char	*command_loop;

	i = 0;
	command_loop = command;
	while (get_next_redirection_type(command_loop) == token)
	{
		i++;
		command_loop = goto_next_redirection(command_loop);
	}
	i++;
	return (i);
}
