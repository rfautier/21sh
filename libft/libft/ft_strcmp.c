/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bluff <bluff@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 01:11:03 by bluff             #+#    #+#             */
/*   Updated: 2018/03/09 12:02:39 by bluff            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	if (!lhs || !rhs)
		return (-1);
	while (*lhs == *rhs && *lhs && *rhs)
	{
		lhs++;
		rhs++;
	}
	return ((unsigned char)*lhs - (unsigned char)*rhs);
}
