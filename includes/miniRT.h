/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:24:45 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/31 14:18:28 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft/vector.h"
# include "libft/link_list.h"
# include "libft/io.h"
# include "libft/memory.h"
# include "libft/string.h"
# include <stdbool.h>

# define ESC 65307
# define SIZE_WIN 0.5
# define SHOW_SRUCT 1

typedef struct s_win	t_win;

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
	int		fov;
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

/* ---------------------------------- SCENE --------------------------------- */

typedef struct s_scene
{
	int				fd;
	char			*line;
	char			**tokens;
	t_list			*map;
	t_vec3			sky_color;
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

void	free_arr(void **arr);
void	free_all(t_prog *prog_set);
void	check_mem(t_info info, void *mem, void **res, t_prog *prog);
void	print_exit(t_prog *prog, char *str);

#endif
