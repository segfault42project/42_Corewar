/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:30:08 by lfabbro           #+#    #+#             */
/*   Updated: 2016/11/23 16:33:38 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_tablen(char **tab)
{
	size_t		len;

	len = 0;
	if (tab)
	{
		while (*tab)
		{
			++tab;
			++len;
		}
	}
	return (len);
}
