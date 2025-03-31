/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 18:54:12 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/31 10:46:46 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <math.h>
#include "libft/is.h"

void	check_atoi(t_prog *prog, char *s, int *res)
{
	*res = ft_atoi(s);
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
		if (!ft_isdigit(*s++))
			print_exit(prog, "Invalid number");
}

void	parse_vector(t_prog * prog, t_vec3 *vec, char *str)
{
	check_mem((t_info){__FILE__, __LINE__, __func__},
		ft_split(str, ','), (void **)&prog->scene->tokens, prog);
	if (ft_arrlen(prog->scene->tokens) != 3)
		free_all(prog);
	vec->x = ft_atof(prog->scene->tokens[0]);
	vec->y = ft_atof(prog->scene->tokens[1]);
	vec->z = ft_atof(prog->scene->tokens[2]);
	free_arr((void **)prog->scene->tokens);
	prog->scene->tokens = NULL;
}

void	parse_color(t_prog *prog, size_t *color, char *str)
{
	int		r;
	int		g;
	int		b;

	check_mem((t_info){__FILE__, __LINE__, __func__},
		ft_split(str, ','), (void **)&prog->scene->tokens, prog);
	if (ft_arrlen(prog->scene->tokens) != 3)
		print_exit(prog, "Invalid color format");
	check_atoi(prog, prog->scene->tokens[0], &r);
	check_atoi(prog, prog->scene->tokens[1], &g);
	check_atoi(prog, prog->scene->tokens[2], &b);
	free_arr((void **)prog->scene->tokens);
	prog->scene->tokens = NULL;
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		print_exit(prog, "Color values must be in range [0, 255]");
	*color = (r << 16) + (g << 8) + b;
}

bool	is_normalized(t_vec3 vec)
{
	float	length;

	length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	if (length == 0.0)
		return (0);
	return (fabs(length - 1.0) < 0.0001);
}

void	init_malloc(t_prog *prog)
{
	check_mem((t_info){__FILE__, __LINE__, __func__},
		malloc(sizeof(t_sphere) * (prog->scene->nb_spheres + 1)),
		(void **)&prog->scene->spheres, prog);
	check_mem((t_info){__FILE__, __LINE__, __func__},
		malloc(sizeof(t_plane) * (prog->scene->nb_planes + 1)),
		(void **)&prog->scene->planes, prog);
	check_mem((t_info){__FILE__, __LINE__, __func__},
		malloc(sizeof(t_cylinder) * (prog->scene->nb_cylinders + 1)),
		(void **)&prog->scene->cylinders, prog);
}
