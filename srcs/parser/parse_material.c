/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:00:21 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/17 23:59:19 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parser.h"
#include <fcntl.h>

void	parse_color(t_prog *prog, t_vec3 *color, char *str);

static void	fill_material(t_prog *prog, t_mat *mat, t_list *current)
{
	char	**tokens;
	int		nb_id = prog->parser->nb_id;

	mat = malloc(sizeof(t_mat) * (nb_id));
	if (!mat)
		print_exit(prog, "Material allocation failed");
	int i = 0;
	while (current)
	{
		tokens = (char **)current->content;
		if (ft_arrlen(tokens) != 7)
			print_exit(prog, "Invalid material format");
		mat[i].name = tokens[0];
		parse_color(prog, &mat[i].albedo, tokens[1]);
		mat[i].emission_power = check_atof(prog, tokens[2]);
		mat[i].roughtness = check_atof(prog, tokens[3]);
		mat[i].shyniness = check_atof(prog, tokens[4]);
		mat[i].spec_coef = check_atof(prog, tokens[5]);
		mat[i].use_checker = (bool)check_atof(prog, tokens[6]);
		current = current->next;
		i++;
	}
	prog->scene->materials = mat;
	free_arr((void **)tokens);
	tokens = NULL;
}

void	parse_material(t_prog *prog, t_parser *parser)
{
	t_list	*new_node;

	parser->fd_mat = open("scenes/material.rt", O_RDONLY);
	if (parser->fd_mat == -1)
		print_exit(prog, "material.rt not found");
	parser->line = ft_get_next_line(parser->fd_mat);
	while (parser->line)
	{
		if (ft_strchr(parser->line, '\n'))
			parser->line[ft_strlen(parser->line) - 1] = '\0';
		check_mem((t_info){__FILE__, __LINE__, __func__},
			ft_split(parser->line, ' '),
			(void **)&parser->tokens, prog);
		check_mem((t_info){__FILE__, __LINE__, __func__},
			ft_lstnew(parser->tokens), (void **)&new_node, prog);
		ft_lstadd_back(&parser->mat_chained, new_node);
		parser->nb_id++;
		free(parser->line);
		parser->line = ft_get_next_line(parser->fd_mat);
	}
	if (parser->nb_id == 0)
		print_exit(prog, "No materials found");
	fill_material(prog, prog->scene->materials, parser->mat_chained);
}
