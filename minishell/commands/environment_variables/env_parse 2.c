/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:22:07 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 07:25:04 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** Puts back all the strings that were split
** Now containing the value of a env_var instead of $BLABLA
*/

char	*glue_env_sub(char **env_split)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	if (!(ret = ft_strdup(env_split[0])))
		ft_errno();
	tmp = ret;
	while (env_split[i + 1])
	{
		if (!(ret = ft_strjoin(ret, env_split[i + 1])))
			ft_errnoq();
		free(tmp);
		tmp = ret;
		i++;
	}
	i = 0;
	while (env_split[i])
		free(env_split[i++]);
	free(env_split);
	return (ret);
}

/*
** Returns the number of char in env name before blabla
** str format : cmd_to_env("env_nameblabla") = 8
*/

int		cmd_to_env(char *s, char **shenvp)
{
	int i;

	i = 0;
	while (shenvp[i])
	{
		if (!strcmptc(shenvp[i], s, '='))
			return (ft_strlentoc(shenvp[i], '='));
		i++;
	}
	return (0);
}

int		env_sub2(char **env_split, t_shell shell, int i, int j)
{
	int		k;
	char	*n_tmp;
	char	*v_tmp;

	if (!(k = cmd_to_env(env_split[i], shell.shenvp)))
	{
		free(env_split[i]);
		if (!(env_split[i] = ft_strdup(ft_strchr(env_split[i], '\\'))))
			ft_errnoq();
		return (1);
	}
	j += k;
	if (!(n_tmp = ft_substr(env_split[i], 0, j)))
		ft_errnoq();
	v_tmp = env_get_value(n_tmp, shell.shenvp);
	free(n_tmp);
	k = j;
	j = toggle_bool(&shell, env_split[i], j);
	if (!(n_tmp = ft_substr(env_split[i], k, j - 1)))
		ft_errnoq();
	free(env_split[i]);
	if (!(env_split[i] = ft_strjoin(v_tmp, n_tmp)))
		ft_errnoq();
	free(n_tmp);
	return (1);
}

void	cancel_split_for(char **env_split, int i)
{
	char *tmp;

	tmp = env_split[i];
	if (!(env_split[i] = ft_strjoin("$", env_split[i])))
		ft_errnoq();
	free(tmp);
}

char	*env_substitution(char *line, t_shell shell)
{
	char	**env_split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(env_split = ft_split(line, '$')))
		ft_errnoq();
	while (env_split[i])
	{
		if ((i > 0) && !shell.bsq)
		{
			if (!ft_isalpha(env_split[i][0]) && shell.benc)
				cancel_split_for(env_split, i);
			else if (!env_sub2(env_split, shell, i, j))
				return (0);
		}
		else if ((i > 0) && shell.bsq)
			cancel_split_for(env_split, i);
		toggle_quotesb(env_split[i][j], &shell);
		j = 0;
		i++;
	}
	return (glue_env_sub(env_split));
}
