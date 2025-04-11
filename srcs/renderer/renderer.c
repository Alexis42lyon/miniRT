#include "libft/math.h"
#include "libft/vector.h"
#include "miniRT.h"
#include "mlx.h"
#include "window.h"
#include "raytracer.h"
#include <limits.h>
#include <time.h>

//! TO REMOVE
#include <stdio.h>

void	show_progress(int current, int max)
{
	int		i;
	float	progress;

	printf("\033[?25lprogress: [");
	progress = ((double)current / (double)max) * 100;
	i = 0;
	while (i * 5 < progress)
	{
		printf(RESET "#");
		i++;
	}
	while (i < 20)
	{
		printf(GRAY "-");
		i++;
	}
	printf(RESET "]\033[?25h\r");
}

t_viewport viewport(t_win_scene *win, t_scene *scene)
{
	t_viewport vp;
	vp.win = win;
	vp.cam = &scene->camera;

	vp.witdh = win->width;
	vp.height = win->height;

	float focal_length = 1.0f;

	vp.vp_height = 2 * tan(vp.cam->fov/2 * 3.1415/ 180) * focal_length;
	vp.vp_width = vp.vp_height * win->aspect_ratio;

	vp.px_up_left = vec3_add(vp.cam->origin,
		vec3_add(
			vec3_sub(
				vec3_mult(vp.cam->forward, focal_length),
				vec3_mult(vp.cam->right, vp.vp_width/2)
				),
			vec3_mult(vp.cam->up, vp.vp_height/2)));

	vp.horizontal = vec3_mult(vp.cam->right, vp.vp_width);
	vp.vertical = vec3_mult(vec3_mult(vp.cam->up, -1), vp.vp_height);

	return vp;
}

t_vec3	random_vec(t_uint seed)
{
	return ((t_vec3){
		random_float(seed ^ 0x1F1F1F1F),
		random_float(seed ^ 0x2E2E2E2E),
		random_float(seed ^ 0x3D3D3D3D)
	});
}

int get_sp_inter(const t_sphere sphere, const t_ray ray)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	disc;

	oc = vec3_sub(sphere.origin, ray.origin);
	a = ft_dot(ray.dir,ray.dir);
	b = -2.0 * ft_dot(ray.dir, oc);
	c = ft_dot(oc, oc) - sphere.radius * sphere.radius;
	disc = b*b - 4*a*c;
	if (disc < 0)
		return (-1);
	return (disc);
}

int exposed_to_light(t_sphere sphere, t_vec3 point, t_vec3 light)
{
	(void)sphere;
	(void)point;
	(void)light;

	t_ray	ray;
	ray.origin = point;
	ray.dir = vec3_add(point, light);
	return (get_sp_inter(sphere, ray) == 0);
}


t_vec3	get_px_col(int i, int j, t_viewport vp, t_scene *scene)
{
	t_ray	ray;
	t_hit	hit;
	t_mat	mat;

	t_vec3	final_color;
	float	mutiplier = 1.0f;

	final_color = vec3_zero();

	ray = get_ray((float)(i) / ((float)vp.witdh), (float)(j) / (float)(vp.height), vp);

	t_uint seed = i + j * vp.win->width;

	seed *= scene->frame_count;
	for (int i = 0; i < BOUNCES; i++)
	{
		seed *= i + 1;
		hit = trace_ray(ray, scene);
		if (hit.distance == -1)
		{
			final_color = vec3_mult(vec3_add(final_color, scene->sky_color), mutiplier);
			break;
		}

		if (hit.type == SPHERE)
			mat = scene->spheres[hit.obj_index].material;
		else if (hit.type == PLANE)
			mat = scene->planes[hit.obj_index].material;
		else if (hit.type == CYLINDER)
			mat = scene->cylinders[hit.obj_index].material;

		mat.roughtness = 0.8f;
		final_color = vec3_mult(mat.albedo, mutiplier);

		// Phong shading model
		final_color = phong_shading(scene, hit, mat, ray);
		mutiplier *= 0.5f;

		ray.origin = vec3_add(hit.point, vec3_mult(hit.normal, 0.0001));
		ray.dir = vec3_reflect(ray.dir,
			vec3_add(hit.normal, vec3_mult(random_vec(seed), mat.roughtness)));

	}
	// printf("%d %d\n", i, j);
	return (vec3_clamp(final_color, 0, 1));
}

void	render(t_viewport vp, t_scene *scene)
{
	int		i;
	int		j;
	t_vec3	color;
	t_vec3	*accumulation_data;

	accumulation_data = vp.win->accumulation_data;

	j = 0;
	while (j < vp.win->height)
	{
		i = 0;
		while (i < vp.win->width)
		{
			color = get_px_col(i, j, vp, scene);
			accumulation_data[i + j * vp.win->width] = vec3_add(accumulation_data[i + j * vp.win->width], color);
			t_vec3	accumulation = accumulation_data[i + j * vp.win->width];
			accumulation = vec3_divide(accumulation, scene->frame_count);
			accumulation = vec3_clamp(accumulation, 0, 1);
			set_pixel(&vp.win->img, i, j, vec_to_int(accumulation));
			i++;
		}
		show_progress(vp.win->width * j + i, vp.win->width * vp.win->height);
		j++;
	}
}

void	add_to_log(t_scene *scene, t_uint render_time)
{
	ft_printf(GRAY "\n[LOG]: render time:%dms\n" RESET, render_time);
	ft_printf(GRAY "[LOG]: frame_count:%d\n" RESET,
		scene->frame_count);
	// print_cam(&scene->camera);
	ft_printf(GREEN "done rendering!\n\n" RESET);

	scene->total_render_time += render_time;
	if (scene->min_render_time == (t_uint)-1)
	{
		scene->min_render_time = render_time;
		scene->max_render_time = render_time;
		return ;
	}
	if (render_time > scene->max_render_time)
		scene->max_render_time = render_time;
	if (render_time < scene->min_render_time)
		scene->min_render_time = render_time;
}
