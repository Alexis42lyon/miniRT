#include "window.h"
#include "raytracer.h"
#include <limits.h>

t_hit	sp_hit_result(const t_sphere *sp, const t_ray r, const double t)
{
	t_hit	hit;

	hit.hit_point = vec3_add(r.origin, vec3_mult(r.dir, t));
	hit.hit_normal = unit_vec3(vec3_sub(hit.hit_point, sp->origin));
	hit.hit_distance = t;
	return (hit);
}

t_hit	sphere_hit(const t_sphere *sphere, const t_ray ray)
{
	t_vec3	oc;
	double	a;
	double	h;
	double	c;
	double	t;

	oc = vec3_sub(sphere->origin, ray.origin);
	a = vec3_lenght_square(ray.dir);
	h = ft_dot(ray.dir, oc);
	c = vec3_lenght_square(oc) - sphere->radius * sphere->radius;
	t = h * h - a * c;

	if (t < 0)
		return ((t_hit){{0 ,0 ,0}, {0, 0, 0}, -1, 0});
	return (sp_hit_result(sphere, ray, ((h - sqrt(t)) / a)));
}

t_vec3	draw_background(t_ray r, t_sphere *sphere, t_scene *scene)
{
	t_hit	hit;
	t_hit	tmp;
	size_t	i;

	hit.hit_distance = INT_MIN;
	i = 0;
	while (i < scene->nb_spheres)
	{
		tmp = sphere_hit(&sphere[i], r);
		if (tmp.hit_distance > hit.hit_distance)
		{
			hit = tmp;
		}
		i++;
	}

	if (hit.hit_distance > 0)
	{
		return (normal_color(hit));
	}
	t_vec3	unit_dir = unit_vec3(r.dir);
	double	a = 0.5f * (unit_dir.y + 1.0f);
	return (vec3_add(vec3_mult(new_vec3(1, 1, 1), (1.0 - a)), vec3_mult(new_vec3(0.5, 0.7, 1.0), a)));
}

void	render(t_win *win, t_scene *scene)
{
	t_camera	cam;
	cam = scene->camera;

	// camera viewport
	double vp_height = 2;
	double vp_width = vp_height * ((double)win->width / win->height);

	// viewport vectors
	t_vec3 vp_u = (t_vec3){vp_width, 0, 0};
	t_vec3 vp_v = (t_vec3){0, -vp_height, 0};

	// delta between each pixel
	t_vec3 px_delta_u = vec3_divide(vp_u, WIDTH);
	t_vec3 px_delta_v = vec3_divide(vp_v, HEIGHT);

	// calculate loc of upper left px
	t_vec3	vp_up_left = vec3_sub(vec3_sub(vec3_sub(cam.origin, (t_vec3){0, 0, cam.fov}),
			vec3_divide(vp_u, 2)), vec3_divide(vp_v, 2));
	t_vec3	px_00 = vec3_add(vp_up_left, vec3_mult(vec3_add(px_delta_u, px_delta_v), 0.5));

	// Rendering:
	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			t_vec3 px_center = vec3_add(px_00, vec3_add(vec3_mult(px_delta_u, i), vec3_mult(px_delta_v, j)));
			t_vec3 ray_dir = vec3_sub(px_center, cam.origin);

			t_ray	ray;
			ray.dir = ray_dir;
			ray.origin = cam.origin;

			t_vec3	col = draw_background(ray, scene->spheres, scene);

			set_pixel(&win->img, i, j, convert_to_rgba(col));
		}
	}
	ft_printf(GREEN "done rendering!\n" RESET);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img, 0, 0);
}

void	start_renderer(t_prog *prog)
{
	t_win	*win;
	t_scene	*scene;

	win = prog->win;
	scene = prog->scene;
	scene->sky_color = 0x8ad2ff;
	init_win(prog);
	mlx_key_hook(win->win_ptr, key_hook, prog);
	if (win->mlx_ptr == NULL)
		return ;
	render(win, scene);
	mlx_loop(win->mlx_ptr);
}
