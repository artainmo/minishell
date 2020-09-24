/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 09:28:05 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/04 23:30:20 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		quotes_parse_arg(char **words, int i, t_shell *shell)
{
	int j;

	j = i;
	while (words[j])
	{
		words[j] = parse_quotes(words[j], shell, ((!words[j + 1]) ? 1 : 0));
		j++;
	}
}

char		*too_much_left(char *command)
{
	int i;

	i = 0;
	if (ft_strnstr(command, "<<<", ft_strlen(command)))
	{
		while (command[i] && command[i] != '<')
			i++;
		command[i] = '\0';
		return (command);
	}
	return (0);
}

void		too_much_right(char *command, char *next_command, t_shell *shell)
{
	if (ft_strnstr(next_command, ">>>", ft_strlen(next_command)))
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
	else
		ft_right_redirection(command, next_command, shell);
}

char		*ft_strchr_wquotes(char *s, char *ch, t_shell shell)
{
	int i;

	i = 0;
	while (s[i])
	{
		toggle_quotesb(s[i], &shell);
		if (!shell.bsq && !shell.bdq && !shell.benc
				&& (s[i] == ch[0] || s[i] == ch[1] || (
						i > 0 && s[i - 1] != '\\' && s[i] == ch[2])))
			return (s + i);
		i++;
	}
	return (0);
}

int			is_token_edq(char c)
{
	return (c == '\\' || c == '\'' || c == '<'
	|| c == '>' || c == '|' || c == ';');
}
