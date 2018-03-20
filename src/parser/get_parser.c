/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfautier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 13:47:39 by rfautier          #+#    #+#             */
/*   Updated: 2018/03/20 13:47:42 by rfautier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_parser	*get_parser(char *original)
{
	int			stock;
	t_parser	*parser;

	stock = is_correct_talk(original);
	if (stock == 0)
		return (NULL);
	if (stock < 0)
		return (NULL);
	if (stock == 1)
	{
		stock = count_cmd(original);
		if (!(parser = malloc(sizeof(t_parser) * stock)))
			exit(0);
		init_parser(parser, stock);
		split_evoluted(parser, original);
		fill_parser(parser, original);
		return (parser);
	}
	return (NULL);
}
