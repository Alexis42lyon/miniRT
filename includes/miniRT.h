/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:24:45 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/28 16:59:46 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <libft.h>
# include "libft/vector.h"
# include <stdbool.h>

# include "window.h"

# define ESC 65307
# define SIZE_WIN 0.5
# define SHOW_SRUCT 0

typedef struct info
{
	const char	*file;
	int			line;
	const char	*function;
}	t_info;

/* --------------------------------- OBJECT --------------------------------- */
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
	double			radius;
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
	double			radius;
	double			height;
	size_t			color;
}	t_cylinder;

typedef struct ray
{
	t_vec3	origin;
	t_vec3	dir;

	int		lenght;
}	t_ray;

/* ---------------------------------- SCENE --------------------------------- */

typedef struct s_scene
{
	int				fd;
	char			*line;
	t_list			*map;
	int				sky_color;
	t_ambient_light	ambient_light;
	t_camera		camera;
	t_light_source	light;
	size_t			nb_spheres;
	size_t			nb_planes;
	size_t			nb_cylinders;
	t_sphere		*spheres;
	t_plane			*planes;
	t_cylinder		*cylinders;
}	t_scene;

typedef struct s_prog
{
	t_scene		*scene;
	t_win		*win;
	// more ..
}	t_prog;

void	init(t_prog *prog, char **av);
void	free_arr(void **arr);
void	free_all(t_prog *prog_set);
void	check_mem(t_info info, void *mem, void **res, t_prog *prog);
void	print_exit(t_prog *prog, char *str);

// parse.c
void	parse(t_prog *prog);
void	parse_sphere(t_prog *prog, t_sphere *sphere, char **tokens);
void	parse_plane(t_prog *prog, t_plane *plane, char **tokens);
void	parse_cylinder(t_prog *prog, t_cylinder *cylinder, char **tokens);

// parse_utils.c
void	parse_vector(t_prog *prog, t_vec3 *vec, char *str);
void	parse_color(t_prog *prog, size_t *color, char *str);
bool	is_normalized(t_vec3 vec);
void	init_malloc(t_prog *prog);
void	print_scene(const t_scene *scene);

// renderer.c
void	start_renderer(t_prog *prog);
void	render(t_win *win, t_scene *scene);
int		key_hook(int keycode, t_prog *prog);

#endif
