/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabougue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:51:00 by rabougue          #+#    #+#             */
/*   Updated: 2017/01/16 22:21:46 by rabougue         ###   ########.fr       */
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

void	check_if_instruction_exist(char *instr)
{
	int	i;
	t_op	op;

	i = 0;
	init_op_table(&op);
	ft_fprintf(1, YELLOW"op->instruction_name = %s\n"END, &op.instruction_name[0]);
	ft_fprintf(1, YELLOW"instr = %s\n"END, instr);
	/*while (i < 16)*/
	/*{*/
		/*printf(YELLOW"op->instruction_name = %s\n"END, &op.instruction_name[i]);*/
		/*ft_strncmp(instr, &op.instruction_name[i], ft_strclen(instr, ' '));*/
		/*++i;*/
	/*}*/
	ft_debug();
	(void)instr;
}

void	get_instruction(char *line, bool label_exist)
{
	int	i;

	i = skip_blank(line); // ignore les espaces
	ft_fprintf(1, ORANGE"line = %s\n"END, line);
	if (label_exist == true) // si il y a un label j'avance jusqua l'instruction
	{
		while (line[i] != LABEL_END) // avance jusqu'au ':'
			++i;
		ft_fprintf(1, RED"line = %s\n"END, &line[i]);
			++i; // avance de 1 le curseur (actuellement sur ':')
		if (line[i] == '\0')
			return ;
		i += skip_blank(&line[i]); // ignore les caracteres espaces
		ft_fprintf(1, "line = %s\n", &line[i]);
		check_if_instruction_exist(&line[i]); // erreur argument.
	}

}

void	parse_instructions(int *fd)
{
	char	*line;
	char	*label;
	bool	label_exist;

	label_exist = false;
	while (get_next_line(*fd, &line) > 0)
	{
		if (is_cmt(line) == true) // Verifie si la ligne est un commentaire
		{
			ft_strdel(&line);
			continue ;
		}
		if ((label = check_if_label_exist(line)) != NULL)
		{
			label_exist = true;
			if (check_if_label_good_formatted(label) == false)
				error(BAD_LABEL_FORMAT);
		}
		// verifier si il y a une instruction apres le label et la parser.
		get_instruction(line, label_exist);
		ft_fprintf(1, YELLOW"line = %s\n"END, line);
		ft_fprintf(1, YELLOW"=================================================\n"END, line);
		ft_strdel(&line);
	}
}
