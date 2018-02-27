/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_selection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-roy <fle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 11:18:55 by fle-roy           #+#    #+#             */
/*   Updated: 2018/02/27 15:50:16 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		move_select(unsigned long touch)
{
	t_ft_sh *sh;
	int		tmp;

	sh = get_ft_shell();
	if ((sh->cursor == 0 && touch == T_ALT_LEFT) || (sh->cursor == sh->buf.cursor && touch == T_ALT_RIGHT))
		return ;
	if (!sh->select_size)
		sh->select_start = sh->cursor;
	tmp = sh->select_size + (touch == T_ALT_LEFT ? -1 : 1);
	ft_fprintf(sh->debug_tty, "Start : %u\nSize : %d\nCursor : %u\nTest : %d\n", sh->select_start, sh->select_size, sh->cursor, tmp);
	if (sh->select_start + tmp - 1 != sh->cursor)
		move_in_terminal((touch == T_ALT_LEFT ? T_LARR : T_RARR), 1);
	else
		ft_fprintf(sh->debug_tty, "BAM\n");
	if (ABS(tmp) > ABS(sh->select_size) && sh->cursor != sh->select_start)
		exec_term_command(TC_REVERSEVIDEO);
	ft_putchar(sh->buf.buf[sh->cursor]);
	if (sh->cursor == 0)
		exec_term_command(TC_MOVELEFT);
	else
		move_in_terminal(T_LARR, 0);
	 if (sh->select_start + tmp - 1 == sh->cursor)
	 	move_in_terminal(T_RARR, 1);
	exec_term_command(TC_RESETGRAPHICS);
	sh->select_size += (touch == T_ALT_LEFT ? -1 : 1);
}
