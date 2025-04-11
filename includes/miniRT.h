/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:18:34 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/11 15:18:35 by mjuncker         ###   ########.fr       */
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
# include "camera.h"

# define ESC 65307
# define LEFT_ARR 65361
# define UP_ARR 65362
# define RIGHT_ARR 65363
# define DOWN_ARR 65364
# define PAGE_UP 65365
# define PAGE_DOWN 65366

typedef struct s_parser		t_parser;
typedef struct s_win_scene	t_win_scene;
typedef struct s_win_button	t_win_button;

typedef struct info
{
	const char	*file;
	int			line;
	const char	*function;
}	t_info;

typedef struct material
{
	t_vec3	albedo;

	float	roughtness;
	float	emission_power;
}	t_mat;

/* --------------------------------- OBJECT --------------------------------- */
typedef struct ambient_light
{
	double			ratio;
	t_vec3			color;
}	t_ambient_light;

typedef struct light
{
	t_vec3			origin;
	double			ratio;
	t_mat			material;
}	t_light_source;

typedef struct sphere
{
	t_vec3			origin;
	double			radius;
	t_mat			material;
	struct sphere	*next;
}	t_sphere;

typedef struct plane
{
	t_vec3			origin;
	t_vec3			normal;
	t_mat			material;
}	t_plane;

typedef struct cylinder
{
	t_vec3			origin;
	t_vec3			normal;
	double			radius;
	double			height;
	t_mat			material;
}	t_cylinder;

typedef struct s_ray_cylinder
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray_cylinder;

/* ---------------------------------- SCENE --------------------------------- */

typedef struct s_scene
{
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

	short			vp_flags;

	t_uint			frame_count;
	t_uint			total_render_time;
	t_uint			min_render_time;
	t_uint			max_render_time;
}	t_scene;

typedef struct s_prog
{
	t_parser		*parser;
	t_scene			*scene;
	t_win_scene		*win_scene;
	t_win_button	*win_button;
}	t_prog;

// utils.c
void	check_mem(t_info info, void *mem, void **res, t_prog *prog);
void	show_progress(int current, int max);

// free.c
void	free_arr(void **arr);
void	free_parser(t_parser *parser);
void	free_all(t_prog *prog_set);
void	print_exit(t_prog *prog, char *str);

// ?.c
void	print_cam(const t_camera *cam);
t_mat	default_mat(void);

#endif
