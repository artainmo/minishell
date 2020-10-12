/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:17:44 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 07:21:50 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
** Display all environment variables and shell variables
** mod 1 adds "declare -x " infront of each env_var
*/

void	env_display(char **shenvp, char mod)
{
	int i;

	i = 0;
	if (shenvp && !mod)
	{
		while (shenvp[i])
		{
			if ((ft_printf("%s\n", shenvp[i++])) == -1)
				ft_errnoq();
		}
	}
	else if (shenvp && mod)
	{
		while (shenvp[i])
		{
			if ((ft_printf("declare -x %s\n", shenvp[i++])) == -1)
				ft_errnoq();
		}
	}
}

/*
** Unset builtins deletes a env_var
*/

int		unset(char *env_name, char ***shenvp)
{
	char	**env;
	int		size;

	size = n_env(*shenvp);
	if (!(env = get_env(env_name, *shenvp)))
		return (0);
	free(*env);
	*env = NULL;
	if (!(*shenvp = ft_sralloc_dptr(*shenvp, size)))
		return (0);
	return (1);
}

/*
** EXPORT (env is the address of the env variable we wanna modify)
** Changes the value of an existing ENV VAR, creates a new one otherwise
** env_var FORMAT = NAME=VALUE
*/

int		env_change_value(char *env_var, char ***shenvp)
{
	int		i;
	char	*new_env;
	char	**env;
	char	*env_name;
	char	*new_value;

	if (!(env_name = ft_strduptc(env_var, '=')))
		return (0);
	new_value = env_var + ft_strlentoc(env_var, '=') + 1;
	i = -1;
	if (!(env = get_env(env_name, *shenvp)))
		return (add_new_env(shenvp, env_name, new_value));
	free(env_name);
	if (!(new_env = malloc(ft_strlentoc(*env, '=') + 1
					+ ft_strlen(new_value) + 1)))
		ft_errnoq();
	while ((*env)[++i] != '=')
		new_env[i] = (*env)[i];
	new_env[i++] = '=';
	while (*new_value)
		new_env[i++] = *new_value++;
	new_env[i] = 0;
	free(*env);
	*env = new_env;
	return ((g_dollar_quest = 0) + 1);
}

/*
**  Returns a ptr to the env var you want to MODIFY
*/

char	**get_env(char *env_name, char **envp)
{
	int i;

	i = 0;
	if (!env_name)
		return (NULL);
	while (envp[i])
	{
		if (!strcmptc(envp[i], env_name, '='))
			break ;
		i++;
	}
	if (envp[i])
		return (envp + i);
	return (NULL);
}

/*
**  Returns a ptr to the value of the env var you want to READ
*/

char	*env_get_value(char *env_name, char **envp)
{
	int i;

	i = 0;
	if (!env_name)
		return (NULL);
	while (envp[i])
	{
		if (!strcmptc(envp[i], env_name, '='))
			break ;
		i++;
	}
	if (envp[i])
		return (env_extract_value(envp[i]));
	return (NULL);
}
