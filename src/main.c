/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:40:09 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/19 16:56:39 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_ft_sh	*get_ft_shell(void)
{
	static t_ft_sh shell;

	return (&shell);
}

void	init_debug(t_ft_sh *shell, const char *path)
{
	if ((shell->debug_tty = open(path, O_WRONLY)) < 0)
		return ;
	ft_fprintf(shell->debug_tty, "-------------------------------------\n");
}

void main_routine(t_list **head, int status)
{
	char *cmd;
	t_ft_sh *shell;
	t_parser *parser;
	int		x;
	int 	nb;
	int		should_exit;
	t_dup	r_dup;
	int		fb;

	fb = 0;
	init_r_dup(&r_dup);
	shell = get_ft_shell();
	should_exit = 0;
	while (42)
	{
		cmd = read_command(NULL, status, 0, (!fb ? fb++ : fb));
		if (cmd && cmd[0] == '\0')
		{
			fb = 0;
			free(cmd);
			continue ;
		}
		add_to_history(shell, cmd);
		if ((parser = get_parser(cmd)))
		{
			nb = parser[0].nb;
			x = 0;
			while (x < nb)
			{
				if (!(check_dup(parser, x)))
					break ;
				if (!(parser[x].close_stdout))
					check_pipe(parser, x, &r_dup);
				status = execute(parser[x], head, &should_exit);
				if (should_exit)
					break;
				if (parser[x].close_stdout)
				{
					while ((parser[x].input.pipe || parser[x].output.pipe) && x < nb)
						x++;
				}
				init_dup(&r_dup);
				x++;
			}
			ft_fprintf(shell->debug_tty, "YAY\n");
			//ft_printf("%s%s\n", (!shell->is_a_tty ? "" : "\nTyped : "),cmd);
			free_parser(parser);
		}
		free(cmd);
		if (should_exit)
			break;
	}
}

static void ignore_signal(int sig)
{
	(void)sig;
}

int		main(int argc, const char **argv, char **env)
{
	t_ft_sh *shell;
	t_list	*head;

	shell = get_ft_shell();
	signal(SIGINT, ignore_signal);
	shell->debug_tty = -1;
	if (argc == 3 && !ft_strcmp("-d", argv[1]))
		init_debug(shell, argv[2]);
	if (!is_env_correct())
		return (1);
	head = create_list_from_env(env);
	//ft_lstprint(&head);
	cli_loader(0);
	main_routine(&head, 1);
	cli_loader(1);
	ft_lsterase(&head);
	if (shell->debug_tty > 0)
		close(shell->debug_tty);
	free(shell->select);
	return (0);
}
