/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 20:30:23 by bluff             #+#    #+#             */
/*   Updated: 2017/11/06 12:12:09 by fle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	int	res;

	if (s1 == NULL || s2 == NULL)
		return (0);
	res = ft_strcmp(s1, s2);
	return (!res ? 1 : 0);
}
