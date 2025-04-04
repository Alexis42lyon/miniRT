#ifndef RAYTRACER_H
# define RAYTRACER_H

# include "miniRT.h"
# include <math.h>

typedef struct ray
{
	t_vec3	origin;
	t_vec3	dir;

	int		lenght;
}	t_ray;

typedef struct hit_info
{
	t_vec3	hit_point;
	t_vec3	hit_normal;
	double	hit_distance;

	size_t	obj_index;

}	t_hit;

typedef struct viewport
{
	t_win_scene		*win;

	double		vp_height;
	double		vp_width;

	t_vec3		vp_u;
	t_vec3		vp_v;

	t_vec3		px_delta_u;
	t_vec3		px_delta_v;

	t_vec3		vp_up_left;
	t_vec3		px_00;

	t_camera	*cam;

	t_vec3		color;
}	t_viewport;

typedef struct s_win	t_win;

// colors.c
t_vec3	normal_color(t_hit hit);
uint	convert_to_rgba(const t_vec3 color);

// ray.c
t_ray	get_ray(int i, int j, t_viewport vp);
t_hit	trace_ray(t_ray ray, t_scene *scene);
t_hit	hit_fail(void);
t_vec3	ray_to_vec(t_ray r);

// renderer.c
t_vec3	get_px_col(int i, int j, t_viewport vp, t_scene *scene);
void	start_renderer(t_prog *prog);

// sphere.c
double	sphere_hit(const t_sphere sphere, const t_ray ray);
t_hit	sp_hit_result(const t_vec3 origin, const t_ray r, const double t, const size_t idx);

#endif
