/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:27:35 by rabougue          #+#    #+#             */
/*   Updated: 2016/12/19 17:33:24 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

int8_t	parse_s_file(char *file, t_header *header)
{
	int	fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	parse_name(&fd, header);
	parse_comment(&fd, header);
	return (EXIT_SUCCESS);
}
