/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artainmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 07:25:21 by artainmo          #+#    #+#             */
/*   Updated: 2020/03/01 07:27:12 by artainmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		strcmptc(const char *s1, const char *s2, char limit)
{
	size_t i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] != limit && s1[i] == s2[i])
		i++;
	if (s1[i] == limit)
		return (0);
	return (s1[i] - s2[i]);
}

int		ft_strlentoc(char *s, char stop)
{
	size_t i;

	i = 0;
	while (s[i] && s[i] != stop)
		i++;
	return (i);
}

char	*env_extract_value(char *env)
{
	while (*env && *env != '=')
		env++;
	return (env + 1);
}

/*
** Adds one more char * to your char **
*/

char	**ft_realloc_dptr(char **ptr, int size)
{
	int		i;
	char	**new_ptr;

	if (!(new_ptr = malloc(sizeof(char *) * (size + 2))))
		ft_errnoq();
	i = 0;
	while (i < size)
	{
		if (!(new_ptr[i] = ft_strdup(ptr[i])))
			return (free_prev_str(new_ptr, i));
		free(ptr[i]);
		i++;
	}
	new_ptr[i] = NULL;
	new_ptr[i + 1] = NULL;
	free(ptr);
	return (new_ptr);
}

/*
** Shenv will copy all the env_var from envp
** we'll then be able to delete/add any env_var
*/

char	**initialize_shenv(char **envp)
{
	int		i;
	char	**shenvp;

	i = 0;
	while (envp[i])
		i++;
	if (!(shenvp = malloc(sizeof(char *) * (i + 1))))
		ft_errnoq();
	i = 0;
	while (envp[i])
	{
		if (!(shenvp[i] = ft_strdup(envp[i])))
			return (free_prev_str(shenvp, i));
		i++;
	}
	shenvp[i] = NULL;
	env_change_value("SHELL=minishell", &shenvp);
	return (shenvp);
}
