/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:51:00 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/15 21:48:05 by rabougue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static char	*check_if_label_exist(char *line)
{
	int		i; // variable qui stocke le nombre de caractere d'indentation.
	int		count_car_label; // compte le nombre de caractere d'une label.
	char	*label; // stock la premiere chaine de caractere j'usqu'au caractere blanc (' ' ou '\t')

	i = skip_blank(line); // skip les espaces
	count_car_label = 0;
	label = NULL;
	ft_fprintf(1, CYAN"\nline = %s\n"END, line);
	while (line[i] != '\0' && ft_isspace(line[i]) == false) // boucle jusqua la fin du label
	{
		++count_car_label;
		++i;
	}
	label = ft_strndup(&line[skip_blank(line)], count_car_label); // stock le label
	ft_fprintf(1, RED"\nlabel = %s\n"END, label);
	ft_fprintf(1, PURPLE"\nchar =  %c\n"END, label[count_car_label - 1]);
	/*if (ft_strchr(LABEL_CHARS, label[count_car_label -1]) == NULL) */
	if (label[count_car_label -1] == ':') 
		return (label);
	return (NULL);
}

bool	check_if_label_good_formatted(char *label)
{
	ft_fprintf(1, "label = %s\n", label);
	int	i;
	int	len_label; // longeur du label

	i = 0;
	len_label = ft_strlen(label);
	if (label[len_label -1] != ':') // si le dernier caractere du label est != de ':' alors error
		return (false);
	while (i < len_label -1) // verification que le label contient que des caracteres autorise
	{
		if (ft_strchr(LABEL_CHARS, label[i]) == NULL)
			return (false);
		++i;
	}
	return (true);
}

void	get_instruction(char *line)
{
	
}

void	parse_instructions(int *fd)
{
	char	*line;
	char	*label;

	while (get_next_line(*fd, &line) > 0)
	{
		if (is_cmt(line) == true) // Verifie si la ligne est un commentaire
		{
			ft_strdel(&line);
			continue ;
		}
		if ((label = check_if_label_exist(line)) != NULL)
		{
			if (check_if_label_good_formatted(label) == false)
				error(BAD_LABEL_FORMAT);
		}
		// verifier si il y a une instruction apres le label et la parser.
		get_instruction(line);
		ft_fprintf(1, YELLOW"line = %s\n"END, line);
		ft_strdel(&line);
	}
}
