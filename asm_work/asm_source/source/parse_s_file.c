/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:27:35 by rabougue          #+#    #+#             */
/*   Updated: 2016/12/18 17:43:14 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	ignore_comment(int *fd)
{
	char	*line;
	int		nb;

	while (get_next_line_lseek(*fd, &line, &nb) > 0)
	{
		ft_fprintf(1, YELLOW"%s\n"END, line);
		if (line[0] == COMMENT_CHAR || line[0] == '\0')
			continue ;
		else
		{
			lseek(*fd, -ft_strlen(line) -nb , SEEK_CUR);
			ft_strdel(&line);
			break ;
		}
		ft_strdel(&line);
	}
}

int8_t	parse_s_file(char *file, t_header *header)
{
	int	fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (EXIT_FAILURE);
	parse_name(&fd, header);
	parse_comment(&fd, header);
	return (EXIT_SUCCESS);
}
