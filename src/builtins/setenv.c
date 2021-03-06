/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 13:25:54 by vbaudot           #+#    #+#             */
/*   Updated: 2018/04/07 01:34:31 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int		builtin_setenv_2(t_env_var *e_var, char **args, int i,
	t_wait_el *el)
{
	e_var->key = ft_strdup(args[1]);
	while (e_var->key[i])
	{
		if (check_if_key_ok(*e_var, i, el) == 1)
			return (1);
		i++;
	}
	e_var->value = ft_strdup(args[2]);
	return (0);
}

int				builtin_setenv(char **args, t_list **env, t_wait_el *el, int i)
{
	t_env_var	e_var;
	char		*tmp;

	el->pid = -2;
	tmp = NULL;
	if (!args[1] || (args[1] && !(tmp = ft_strchr(args[1], '=')) && !args[2]))
		return (ft_printf("Usage: setenv KEY[=VALUE] [VALUE]\n") && 1);
	if (tmp)
	{
		e_var.key = ft_strsub(args[1], 0, (int)(tmp - args[1]));
		while (e_var.key[++i])
			if (check_if_key_ok(e_var, i, el) == 1)
				return (1);
		if (!(tmp[1]) && args[2])
			e_var.value = ft_strdup(args[2]);
		else
			e_var.value = ft_strdup(tmp + 1);
	}
	else
	{
		if (builtin_setenv_2(&e_var, args, 0, el) != 0)
			return (0);
	}
	param_ins_or_rep(env, &e_var);
	return (0);
}

int				builtin_unsetenv(char **args, t_list **env, t_wait_el *el)
{
	t_list	*tmp;

	el->pid = -2;
	if (!args[1])
	{
		return (ft_printf("Usage: unsetenv KEY\n") && 1);
	}
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(((t_env_var*)tmp->content)->key, args[1]))
		{
			if (tmp == *env)
				*env = (*env)->next;
			ft_lstdelone(&tmp, free_env_var);
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}
