/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:09:16 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/11 17:04:11 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "miniRT.h"
# include <math.h>

# define BOUNCES 4
# define DEFAULT_EMMI_POWER 5

# define SPECULAR 0b0100
# define DIFFUSE 0b0010
# define AMBIENT 0b0001

# define LIGHT_RANGE 10
# define SPECULAR_COEF 0.6f
# define SHINY_POWER 32 // 32 = plastic // 256 = glass

enum	e_object_type
{
	NONE = 0,
	PLANE,
	SPHERE,
	CYLINDER,
};

typedef struct ray
{
	t_vec3	origin;
	t_vec3	dir;

	int		length;
}	t_ray;

typedef struct hit_info
{
	t_vec3				point;
	t_vec3				normal;
	double				distance;

	size_t				obj_index;
	enum e_object_type	type;

}	t_hit;

typedef struct viewport
{
	t_win_scene		*win;

	double			vp_height;
	double			vp_width;

	t_vec3			px_up_left;

	t_camera		*cam;

	t_vec3			vertical;
	t_vec3			horizontal;

	int				witdh;
	int				height;
}	t_viewport;

struct s_light_info
{
	t_light_source	light;
	t_vec3			light_dir;
	float			attenuation;

	t_mat			mat;

	t_hit			hit;
	t_ray			ray;
};

struct s_objs_data
{
	void	*objs;
	size_t	n_obj;
	size_t	size;
};

// colors.c
t_vec3		normal_color(t_hit hit);
t_uint		vec_to_int(const t_vec3 color);
t_vec3		int_to_vec(t_uint color);

// ray.c
t_ray		get_ray(float u, float v, t_viewport vp);
t_hit		hit_fail(void);
t_vec3		ray_to_vec(t_ray r);

// intersection.c
t_hit		trace_ray(t_ray ray, t_scene *scene);

// renderer.c
t_vec3		get_px_col(int i, int j, t_viewport vp, t_scene *scene);
void		render(t_viewport vp, t_scene *scene);
t_viewport	viewport(t_win_scene *win, t_scene *scene);

// sphere.c
double		sphere_hit(void *p_sphere, const t_ray ray);
t_hit		hit_result(const t_vec3 origin, const t_ray r, const double t,
				const size_t idx);

// place.c
double		plane_hit(void *p_plane, const t_ray ray);
double		cylinders_hit(void *p_cy, t_ray r);

// lighting.c
t_vec3		phong_shading(t_scene *scene, t_hit hit, t_mat mat, t_ray ray);

// phong_model.c
t_vec3		phong_diffuse(struct s_light_info info);
t_vec3		phong_ambient(t_scene *scene, t_mat mat);
t_vec3		phong_specular(struct s_light_info info);

// anti_aliasing.c
void	anti_aliaser(t_viewport	vp, t_scene *scene);

#endif
