/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:24:45 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/24 23:44:16 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <libft.h>
# include <math.h>
# include <stdbool.h>

# define ESC 65307
# define SIZE_WIN 0.5
# define SHOW_SRUCT 1

typedef struct info
{
	const char	*file;
	int			line;
	const char	*function;
}	t_info;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct ambient_light
{
	bool			is_set;
	double			ratio;
	size_t			color;
}	t_ambient_light;

typedef struct camera
{
	bool	is_set;
	t_vec3	origin;
	t_vec3	direction;
	double	fov;
}	t_camera;

typedef struct light
{
	bool			is_set;
	t_vec3			origin;
	double			ratio;
	size_t			color;
}	t_light_source;

typedef struct sphere
{
	t_vec3			origin;
	double			diameter;
	size_t			color;
	struct sphere	*next;
}	t_sphere;

typedef struct plane
{
	t_vec3			origin;
	t_vec3			normal;
	size_t			color;
}	t_plane;

typedef struct cylinder
{
	t_vec3			origin;
	t_vec3			normal;
	double			diameter;
	double			height;
	size_t			color;
}	t_cylinder;

typedef struct s_scene
{
	int				fd;
	char			*line;
	t_list			*map;
	t_ambient_light	ambient_light;
	t_camera		camera;
	t_light_source	light;
	size_t			nb_spheres;
	size_t			nb_planes;
	size_t			nb_cylinders;
	t_sphere		*spheres;
	t_plane			*planes;
	t_cylinder		*cylinders;
	void			*mlx;
	int				width;
	int				height;
	void			*win;
}	t_scene;

void	init(t_scene *scene, char **av);
void	free_arr(void **arr);
void	free_all(t_scene *scene, const char *msg);
int		close_window(void *mlx);
void	start(t_scene *scene, char **av);
t_info	get_info(const char *file, int line, const char *func);
void	check_mem(t_info info, t_scene *scene, void *mem, void **res);

// parse.c
void	parse(t_scene *scene);
void	parse_sphere(t_scene *scene, char **tokens);
void	parse_plane(t_scene *scene, char **tokens);
void	parse_cylinder(t_scene *scene, char **tokens);

// parse_utils.c
void	parse_vector(t_scene *scene, t_vec3 *vec, char *str);
void	parse_color(t_scene *scene, size_t *color, char *str);
bool	is_normalized(t_vec3 vec);
void	init_malloc(t_scene *scene);
void	print_scene(const t_scene *scene);

#endif
