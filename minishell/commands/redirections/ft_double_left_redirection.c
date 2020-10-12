/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_left_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:43:43 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/04 23:07:20 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char		*after_double_redir_args(char *command)
{
	int		i;
	char	*ret;
	t_shell shell;

	i = 0;
	if (!(ret = ft_strtrim(command, " ")))
		ft_errnoq();
	zero_that(&shell.bsq, &shell.bdq, &shell.benc);
	if (!ft_strchr(ret, '"') && !ft_strchr(ret, '\\') && !ft_strchr(ret, '\''))
	{
		while (ret[i] != ' ' && ret[i])
			i++;
		ret[i] = '\0';
	}
	else
		ret = parse_quotes(ret, &shell, 1);
	return (ret);
}

char		*double_left_redirection_ml(char *fw)
{
	char	*line;
	char	*buf;
	int		i;

	i = 0;
	if (!(buf = ft_strdup(""))
		|| !(line = ft_strdup("")))
		ft_errnoq();
	while (!ft_strcmp(fw, line) && !g_ctrl_d)
	{
		if (i++ > 0)
			line = addonec(line, '\n');
		if (!(buf = ft_strjoin_f(buf, line)))
			ft_errnoq();
		free(line);
		if (ft_printf("> ") == -1)
			ft_errnoq();
		if (get_next_line(0, &line) == -1)
			ft_errnoq();
	}
	free(line);
	return (buf);
}

void		double_left_redirection(char *command, char *next_command
		, t_shell *shell, char **arg)
{
	char	**comm_betw_redirec;
	char	*buff;
	char	*tmp;
	int		fd;
	int		la;

	if (!(comm_betw_redirec = ft_split(next_command, '<')))
		ft_errnoq();
	la = ft_count_words(comm_betw_redirec) - 1;
	tmp = after_double_redir_args(comm_betw_redirec[la]);
	if (!(arg = ft_split(comm_betw_redirec[0], ' ')))
		ft_errnoq();
	buff = double_left_redirection_ml(tmp);
	if ((fd = open("/tmp/.drltmp", O_RDWR | O_CREAT | O_TRUNC, 0666)) < 0)
		ft_errno();
	write(fd, buff, ft_strlen(buff));
	free(buff);
	ft_left_redirection(command, "/tmp/.drltmp", shell);
	free_dlr(tmp, comm_betw_redirec, arg);
}
