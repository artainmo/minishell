/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_left_right_redirec.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:34:00 by sel-melc          #+#    #+#             */
/*   Updated: 2020/03/09 15:34:03 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	split_right_left(char *command, char **exec_left,
							char **right, int *first_left)
{
	int		i;
	int		rem;
	char	*exec;
	char	*left;

	i = 0;
	*first_left = 0;
	while (command[i] != '>')
		i++;
	command[i] = '\0';
	rem = i + 1;
	if (!(exec = ft_strdup(command)))
		ft_errnoq();
	while (command[i] != '<')
		i++;
	command[i] = '\0';
	if (!(*right = ft_strdup(&command[rem])))
		ft_errnoq();
	left = &command[i + 1];
	if (!(*exec_left = ft_strjoin_f(exec, "<")))
		ft_errnoq();
	if (!(*exec_left = ft_strjoin_f(*exec_left, left)))
		ft_errnoq();
}

static void	split_left_right(char *command, char **exec_left,
							char **right, int *first_left)
{
	int i;

	i = 0;
	*first_left = 1;
	while (command[i] != '>')
		i++;
	command[i] = '\0';
	if (!(*exec_left = ft_strdup(command)))
		ft_errnoq();
	if (!(*right = ft_strdup(&command[i + 1])))
		ft_errnoq();
}

static char	*test_errors_norm(int *fd_2, int *fd_0,
	char *exec_left, t_shell *shell)
{
	int i;

	i = 0;
	*fd_2 = dup(2);
	*fd_0 = dup(0);
	close(1);
	close(0);
	while (exec_left[i] != '<')
		i++;
	exec_left[i] = '\0';
	close(2);
	ft_shellparsing(exec_left, shell);
	dup2(*fd_2, 2);
	*fd_2 = i;
	return (exec_left);
}

static int	test_errors(char *exec_left, char *right, int f_l, t_shell *shell)
{
	int		fd_1;
	int		fd_2;
	int		fd_0;

	fd_1 = dup(1);
	exec_left = test_errors_norm(&fd_2, &fd_0, exec_left, shell);
	if (g_error_minishell)
	{
		exec_left[fd_2] = '<';
		ft_right_redirection(exec_left, right, shell);
		dup2(fd_1, 1);
		dup2(fd_0, 0);
		return (-1);
	}
	if (f_l)
		ft_left_redirection(exec_left, &exec_left[fd_2 + 1], shell);
	dup2(fd_1, 1);
	dup2(fd_0, 0);
	if (g_error_minishell)
		return (0);
	return (1);
}

void		mix_right_left_redirec(char *command, t_shell *shell)
{
	char	*exec_left;
	char	*right;
	int		i;
	int		first_left;
	int		ret;

	i = 0;
	shell->right_left = 1;
	while (command[i] != '>' && command[i] != '<')
		i++;
	if (command[i] == '>')
		split_right_left(command, &exec_left, &right, &first_left);
	else
		split_left_right(command, &exec_left, &right, &first_left);
	if ((ret = test_errors(exec_left, right, first_left, shell)) > 0)
	{
		exec_left[i] = '<';
		ft_right_redirection(exec_left, right, shell);
	}
	else if (ret != -1)
		free(exec_left);
	g_error_minishell = 0;
	shell->right_left = 0;
	free(right);
}
