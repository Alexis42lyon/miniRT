#include <miniRT.h>
#include <math.h>
#include "libft/is.h"

void	parse_vector(t_prog *prog, t_vec3 *vec, char *str)
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

void	parse_color(t_prog *prog, t_vec3 *color, char *str)
{
	check_mem((t_info){__FILE__, __LINE__, __func__},
		ft_split(str, ','), (void **)&prog->scene->tokens, prog);
	if (ft_arrlen(prog->scene->tokens) != 3)
		print_exit(prog, "Invalid color format");
	color->x = ft_atof(prog->scene->tokens[0]);
	color->y = ft_atof(prog->scene->tokens[1]);
	color->z = ft_atof(prog->scene->tokens[2]);
	free_arr((void **)prog->scene->tokens);
	prog->scene->tokens = NULL;
	if (color->x != (unsigned char)(color->x) || color->y != (unsigned char)(color->y) || color->z != (unsigned char)(color->z))
		print_exit(prog, "Color values must be in range [0, 255]");
	color->x /= 255.0;
	color->y /= 255.0;
	color->z /= 255.0;
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

double	check_atof(const char *nptr)
{
	double	res;
	double	fraction;

	res = ft_atoi(nptr);
	fraction = 0.1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
		nptr++;
	if (*nptr++ == '.')
	{
		while (*nptr >= '0' && *nptr <= '9')
		{
			res += (*nptr - '0') * fraction;
			fraction *= 0.1;
			nptr++;
		}
	}
	return (res);
}
