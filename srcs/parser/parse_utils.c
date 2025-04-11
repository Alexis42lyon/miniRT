/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:22:42 by abidolet          #+#    #+#             */
/*   Updated: 2025/04/11 10:22:43 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <math.h>
#include <parser.h>
#include "libft/is.h"

void	parse_vector(t_prog *prog, t_vec3 *vec, char *str)
{
	check_mem((t_info){__FILE__, __LINE__, __func__},
		ft_split(str, ','), (void **)&prog->parser->tokens, prog);
	if (ft_arrlen(prog->parser->tokens) != 3)
		free_all(prog);
	vec->x = check_atof(prog, prog->parser->tokens[0]);
	vec->y = check_atof(prog, prog->parser->tokens[1]);
	vec->z = check_atof(prog, prog->parser->tokens[2]);
	free_arr((void **)prog->parser->tokens);
	prog->parser->tokens = NULL;
}

void	parse_color(t_prog *prog, t_vec3 *color, char *str)
{
	check_mem((t_info){__FILE__, __LINE__, __func__},
		ft_split(str, ','), (void **)&prog->parser->tokens, prog);
	if (ft_arrlen(prog->parser->tokens) != 3)
		print_exit(prog, "Invalid color format");
	color->x = check_atof(prog, prog->parser->tokens[0]);
	color->y = check_atof(prog, prog->parser->tokens[1]);
	color->z = check_atof(prog, prog->parser->tokens[2]);
	free_arr((void **)prog->parser->tokens);
	prog->parser->tokens = NULL;
	if (color->x != (unsigned char)(color->x)
		|| color->y != (unsigned char)(color->y)
		|| color->z != (unsigned char)(color->z))
		print_exit(prog, "Color values must be in range [0, 255]");
	color->x /= 255.0;
	color->y /= 255.0;
	color->z /= 255.0;
}

void	get_atof(char **nptr, double *res)
{
	double	fraction;

	(*nptr)++;
	fraction = 0.1;
	while (ft_isdigit(**nptr))
	{
		*res += (**nptr - '0') * fraction;
		(*nptr)++;
		fraction *= 0.1;
	}
}

double	check_atof(t_prog *prog, const char *nptr)
{
	int		sign;
	double	res;

	sign = 1;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	res = 0.0;
	if (!ft_isdigit(*nptr))
		print_exit(prog, "Invalid number format");
	while (ft_isdigit(*nptr))
	{
		res = res * 10 + *nptr++ - '0';
		if (res * sign != (int)(res * sign))
			print_exit(prog, "Invalid number format");
	}
	if (*nptr == '.')
		get_atof((char **)&nptr, &res);
	if (*nptr)
		print_exit(prog, "Invalid number format");
	return (res * sign);
}
