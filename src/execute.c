/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaudot <vbaudot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:40:03 by vbaudot           #+#    #+#             */
/*   Updated: 2018/03/02 11:51:01 by vbaudot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_list	*ft_lstcopy(t_list **head)
{
	t_list	*copy;
	t_list	*curr_copy;
	t_list	*tmp;
	t_list	*curr_head;

	curr_head = *head;
	if (*head == NULL)
		return (NULL);
	curr_copy = ft_lstnew(curr_head->content, curr_head->content_size);
	copy = curr_copy;
	curr_head = curr_head->next;
	while (curr_head)
	{
		tmp = ft_lstnew(curr_head->content, curr_head->content_size);
		curr_copy->next = tmp;
		curr_copy = tmp;
		curr_head = curr_head->next;
	}
	return (copy);
}

int		execute_env(char **args, t_list **head)
{
	t_list	*copy;

	if (!args[0])
		return (1);
	if (ft_strcmp(args[0], "help") == 0)
		return (mini_help(args));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (mini_echo(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (mini_cd(args, head));
	else if (ft_strcmp(args[0], "env") == 0)
	{
		copy = ft_lstcopy(head);
		mini_env(args, &copy);
		ft_lsterase(&copy);
		return (1);
	}
	return (launch(args, head));
}

int		execute(t_parser parser, t_list **head)
{
	t_list	*copy;

	if (!parser.cmd[0])
		return (1);
	if (ft_strcmp(parser.cmd[0], "help") == 0)
		return (mini_help(parser.cmd));
	else if (ft_strcmp(parser.cmd[0], "exit") == 0)
		return (mini_exit(parser.cmd));
	else if (ft_strcmp(parser.cmd[0], "echo") == 0)
		return (mini_echo(parser.cmd));
	else if (ft_strcmp(parser.cmd[0], "unsetenv") == 0)
		return (mini_unsetenv(parser.cmd, head));
	else if (ft_strcmp(parser.cmd[0], "setenv") == 0)
		return (mini_setenv(parser.cmd, head));
	else if (ft_strcmp(parser.cmd[0], "cd") == 0)
		return (mini_cd(parser.cmd, head));
	else if (ft_strcmp(parser.cmd[0], "env") == 0)
	{
		copy = ft_lstcopy(head);
		mini_env(parser.cmd, &copy);
		ft_lsterase(&copy);
		return (1);
	}
	return (launch(parser.cmd, head));
}
