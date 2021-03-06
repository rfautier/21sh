/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <rfautier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:42:56 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/23 18:36:35 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int		size_str(t_vari var, char *ori)
{
	int nb;

	nb = 0;
	while (ori[var.i] && (ori[var.i] != ' ' &&
		ori[var.i] != '\n'))
	{
		var.i++;
		nb++;
	}
	return (nb);
}

static char		*search_str(t_vari *var, char *ori)
{
	int		o;
	char	*str;

	o = 0;
	if (!(str = malloc(sizeof(char) * size_str(*var, ori) + 1)))
		ft_perror("malloc", "Mallocation failed. Aborting");
	while (ori[var->i] && (ori[var->i] != ' ' &&
		ori[var->i] != '\n'))
	{
		str[o] = ori[var->i];
		var->i++;
		o++;
	}
	str[o] = '\0';
	return (str);
}

static int		final_heredoc(char *tmp, char *str, char *tmp2, int fd)
{
	while ((ft_strcmp(str, tmp) != 0) && tmp[0] != T_CTRL_D)
	{
		tmp2 = ft_strjoin(tmp, "\n");
		ft_fprintf(fd, tmp2);
		free(tmp2);
		free(tmp);
		if ((tmp = read_command(NULL, 0, 1, 0)) == NULL)
		{
			free(str);
			return (-1);
		}
	}
	free(tmp);
	free(str);
	return (1);
}

static void		open_heredoc_file(char *path_file, int *fd)
{
	if ((*fd = open(path_file, O_WRONLY | O_TRUNC, 0777)) == -1)
		ft_perror("21sh", "Can't open heredoc file /tmp");
	close(*fd);
	if ((*fd = open(path_file, O_RDWR | O_APPEND, 0777)) == -1)
		ft_perror("21sh", "Can't open heredoc file /tmp");
}

int				call_heredoc(t_vari *var, char *ori)
{
	char	*str;
	char	*tmp;
	char	*path_file;
	int		fd;
	char	*tmp2;

	str = search_str(var, ori);
	if ((tmp = read_command(NULL, 0, 1, 0)) == NULL)
	{
		free(str);
		return (-1);
	}
	tmp2 = ft_itoa(var->heredoc);
	path_file = ft_strjoin("/tmp/21sh_heredoc", tmp2);
	free(tmp2);
	if ((fd = open(path_file, O_RDWR | O_CREAT | O_EXCL |
		O_APPEND, 0777)) == -1)
		open_heredoc_file(path_file, &fd);
	free(path_file);
	if ((final_heredoc(tmp, str, tmp2, fd)) == -1)
		return (-1);
	var->i--;
	close(fd);
	return (1);
}
