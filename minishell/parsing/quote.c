/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:11:34 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/04 23:32:34 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*addonec(char *s1, char c)
{
	char	*nstr;
	int		i;

	i = 0;
	if (!(nstr = malloc(ft_strlen(s1) + 2)))
		ft_errnoq();
	while (s1[i])
	{
		nstr[i] = s1[i];
		i++;
	}
	free(s1);
	nstr[i++] = c;
	nstr[i] = '\0';
	return (nstr);
}

void	zero_that(char *bsq, char *bdq, char *benc)
{
	*bsq = 0;
	*bdq = 0;
	*benc = 0;
}

int		toggle_quotesb(char c, t_shell *shell)
{
	if (c == '\\' && !shell->benc && !shell->bsq && (shell->benc = 1))
		return (1);
	else if (c == '\"' && !shell->bsq && !shell->benc)
	{
		shell->bdq = (shell->bdq) ? 0 : 1;
		return (1);
	}
	else if (c == '\'' && !shell->bdq && !shell->benc)
	{
		shell->bsq = (shell->bsq) ? 0 : 1;
		return (1);
	}
	else if (shell->benc)
		shell->benc = 0;
	return (0);
}

/*
** if eol == 1 we are parsing the last elem
*/

char	*parse_quotes(char *line, t_shell *shell, char eol)
{
	int		i;
	char	*ret;

	shell->benc = 0;
	if (!(ret = malloc(1)))
		ft_errnoq();
	*ret = 0;
	i = -1;
	while (line[++i])
		if (!toggle_quotesb(line[i], shell))
			ret = addonec(ret, line[i]);
		else if ((line[i] == '\\' && is_token_edq(line[i + 1]) && shell->bdq))
			ret = addonec(ret, line[i]);
	if (((shell->bsq || shell->bdq) || (shell->benc)) && eol)
	{
		free(ret);
		if (!(ret = ft_strdup("")))
			ft_errnoq();
		ft_putstr_fd("Parse error : multiline commands not supported.\n", 2);
	}
	free(line);
	return (ret);
}

char	*parse_quotes_nof(char *line, t_shell *shell, char eol)
{
	int		i;
	char	*ret;

	shell->benc = 0;
	if (!(ret = malloc(1)))
		ft_errnoq();
	*ret = 0;
	i = -1;
	while (line[++i])
		if (!toggle_quotesb(line[i], shell))
			ret = addonec(ret, line[i]);
		else if ((line[i] == '\\' && is_token_edq(line[i + 1])) && shell->bdq)
			ret = addonec(ret, line[i]);
	if (((shell->bsq || shell->bdq) || (shell->benc)) && eol)
	{
		free(ret);
		if (!(ret = ft_strdup("")))
			ft_errnoq();
		ft_putstr_fd("Parse error : multiline commands not supported.\n", 2);
	}
	return (ret);
}
