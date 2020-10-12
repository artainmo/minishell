/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 09:29:28 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/02 09:29:56 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** returns -1 if true and 0 if false
*/

int		l_has_empty_cmd(char *line, t_shell shell)
{
	int i;

	i = 0;
	zero_that(&shell.bsq, &shell.bdq, &shell.benc);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == ';')
		return (-1);
	while (line[i])
	{
		if (line[i] == ';' && !shell.bsq && !shell.bdq && !shell.benc)
		{
			i++;
			while (line[i] && ft_isspace(line[i]))
				i++;
			if ((line[i] == ';')
				&& !shell.bsq && !shell.bdq && !shell.benc)
				return (-1);
		}
		else
			toggle_quotesb(line[i], &shell);
		i++;
	}
	return (0);
}

int		is_token(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == ';');
}

/*
** Return 1 if everything was ok
** return -1 if token found with nothing bef4 pipe
** return line[j] (first token) if no other token found
** return line[i]+4 (+4 is arbtary to differentiate from above)
*/

int		parse_err(char *line, t_shell shell)
{
	int ij[2];

	ij[0] = 0;
	while (line[ij[0]] && ft_isspace(line[ij[0]]))
		ij[0]++;
	if (line[ij[0]] == '|')
		return (-1);
	while (line[ij[0]])
	{
		if (is_token(line[ij[0]]) && ((ij[1] = ij[0]) || !ij[1]))
		{
			ij[0]++;
			while (line[ij[0]] && ft_isspace(line[ij[0]]))
				ij[0]++;
			if (!line[ij[0]] && !shell.bsq && !shell.bdq && !shell.benc)
				return (line[ij[1]]);
			if (is_token(line[ij[0]]) && (ij[1] + 1 != ij[0])
				&& !shell.bsq && !shell.bdq && !shell.benc)
				return (line[ij[0]] + 4);
		}
		else
			toggle_quotesb(line[ij[0]], &shell);
		ij[0]++;
	}
	return (1);
}

int		empty_dlredir(char *line, t_shell shell)
{
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	zero_that(&shell.bsq, &shell.bdq, &shell.benc);
	while (line[i] && line[i + 1] && (ret = ft_strncmp(line + i, "<<", 2)))
	{
		toggle_quotesb(line[i], &shell);
		i++;
	}
	i += 2;
	if (!ret)
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (!line[i])
			return (1);
	}
	return (0);
}

void	display_err(int ret, int *i)
{
	if ((ret) == -1 && (*i = -1))
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (ret == '|' && (*i = -1))
		ft_putstr_fd("Parse error : multiline commands not supported.\n", 2);
	else if ((ret == '>' || ret == '<') && (*i = -1))
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n"
				, 2);
	else if (ret == ';' + 4 && (*i = -1))
		ft_putstr_fd("minishell: syntax error near unexpected token `;'\n", 2);
	else if (ret == '|' + 4 && (*i = -1))
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (ret == '<' + 4 && (*i = -1))
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	else if (ret == '>' + 4 && (*i = -1))
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
}
