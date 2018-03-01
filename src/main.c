/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:40:09 by fle-roy           #+#    #+#             */
/*   Updated: 2018/03/01 11:06:24 by rfautier         ###   ########.fr       */
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

void main_routine(void)
{
	char *cmd;
	t_ft_sh *shell;
	t_parser *parser;

	shell = get_ft_shell();
	ft_fprintf(shell->debug_tty, "YAY\n");
	load_history(shell, 0);
	ft_fprintf(shell->debug_tty, "%p\n", shell->history);
	cmd = read_command(NULL, NULL);
	parser = get_parser(cmd);
	//Tu peux faire joue-joue ici victor
	add_to_history(shell, cmd);
	load_history(shell, 1);
	ft_fprintf(shell->debug_tty, "YAY\n");
	ft_printf("%s%s\n", (!shell->is_a_tty ? "" : "\nTyped : "),cmd);
	free_parser(parser);
	free(cmd);
}

int		main(int argc, const char **argv, const char **environ)
{
	t_ft_sh *shell;

	(void)environ;
	shell = get_ft_shell();
	shell->debug_tty = -1;
	if (argc == 3 && !ft_strcmp("-d", argv[1]))
		init_debug(shell, argv[2]);
	if (!is_env_correct())
		return (1);
	cli_loader(0);
	main_routine();
	cli_loader(1);
	if (shell->debug_tty > 0)
		close(shell->debug_tty);
	free(shell->select);
	return (0);
}
