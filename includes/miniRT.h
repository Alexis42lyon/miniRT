/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:24:45 by abidolet          #+#    #+#             */
/*   Updated: 2025/03/23 23:28:06 by abidolet         ###   ########.fr       */
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
# define INVALID_COLOR 0xFFFFFFFF

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
	unsigned int	color;
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
	unsigned int	color;
}	t_light_source;

typedef struct sphere
{
	t_vec3			origin;
	double			diameter;
	unsigned int	color;
	struct sphere	*next;
}	t_sphere;

typedef struct plane
{
	t_vec3			origin;
	t_vec3			normal;
	unsigned int	color;
	struct plane	*next;
}	t_plane;

typedef struct cylinder
{
	t_vec3			origin;
	t_vec3			normal;
	double			diameter;
	double			height;
	unsigned int	color;
	struct cylinder	*next;
}	t_cylinder;

typedef struct s_scene
{
	t_ambient_light	ambient_light;
	t_camera		camera;
	t_light_source	light;
	t_sphere		*spheres;
	t_plane			*planes;
	t_cylinder		*cylinders;
	void			*mlx;
	int				width;
	int				height;
	void			*win;
}	t_scene;

void	init(t_scene *scene, char **av);
void	free_arr(char **arr);
void	free_all(t_scene *scene, char *msg);
int		close_window(void *mlx);
void	start(t_scene *scene, char **av);

// parse.c
void	parse(t_scene *scene, int fd);
void	parse_sphere(t_scene *scene, char *line);
void	parse_plane(t_scene *scene, char *line);
void	parse_cylinder(t_scene *scene, char *line);

// parse_utils.c
bool	parse_vector(t_vec3 *vec, char *str);
int		parse_color(char *str);
int		is_normalized(t_vec3 vec);

#endif
