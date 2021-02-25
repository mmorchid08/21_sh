/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:04:24 by youarzaz          #+#    #+#             */
/*   Updated: 2020/03/09 15:04:29 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

t_var	*ft_new_env_var(char *key, char *value)
{
	t_var *var;

	if (!(var = (t_var *)malloc(sizeof(t_var))))
		exit(1);
	var->key = key;
	var->value = value;
	var->next = NULL;
	return (var);
}

void	ft_add_env_var(t_var **head, t_var *new)
{
	t_var *tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = new;
		return ;
	}
	ft_add_env_var(&(tmp->next), new);
}

t_var	*ft_load_env(char **envp)
{
	t_var	*var;
	char	*str;
	int		i;
	int		shlvl;

	var = NULL;
	i = -1;
	g_env.home = "";
	while (envp[++i])
		if ((str = ft_strchr(envp[i], '=')))
		{
			if (!(*str = '\0') && ft_strequ(envp[i], "SHLVL"))
			{
				shlvl = ft_atoi(str + 1);
				ft_add_env_var(&var, ft_new_env_var(ft_strdup(envp[i]),
				ft_itoa((ABS(shlvl) <= 999 && shlvl > 0) ? (shlvl + 1) : 1)));
			}
			else
			{
				(ft_strequ(envp[i], "HOME")) && (g_env.home = str + 1);
				ft_add_env_var(&var, ft_new_env_var(ft_strdup(envp[i]),
							ft_strdup(str + 1)));
			}
		}
	return (var);
}

char	*ft_get_var_value(t_var *head, char *key)
{
	if (!head)
		return (NULL);
	else if (ft_strequ(head->key, key))
		return (head->value);
	return (ft_get_var_value(head->next, key));
}

void	ft_free_var(t_var **head)
{
	t_var	*var;
	t_var	*tmp;

	var = *head;
	while (var)
	{
		free(var->key);
		free(var->value);
		tmp = var->next;
		free(var);
		var = tmp;
	}
}
