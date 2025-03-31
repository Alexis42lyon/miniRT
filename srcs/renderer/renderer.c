#include "window.h"
#include "raytracer.h"
#include <limits.h>
#include <time.h>

t_vec3	draw_background(t_ray r, t_scene *scene)
{
	t_hit	hit;
	t_hit	tmp;
	size_t	i;

	hit.hit_distance = INT_MIN;
	i = 0;
	while (i < scene->nb_spheres)
	{
		tmp = sphere_hit(scene->spheres[i], r);
		if (tmp.hit_distance > hit.hit_distance)
		{
			hit = tmp;
			hit.obj_index = i;
		}
		i++;
	}
	if (hit.hit_distance > 0)
	{
		return (scene->spheres[hit.obj_index].color);
	}
	return (scene->sky_color);
}

t_viewport	viewport(t_win *win, t_scene *scene)
{
	t_viewport	vp;

	vp.win = win;
	vp.cam = scene->camera;
	vp.vp_height = 2;
	vp.vp_width = vp.vp_height * ((double)win->width / win->height);
	vp.vp_u = (t_vec3){vp.vp_width, 0, 0};
	vp.vp_v = (t_vec3){0, -vp.vp_height, 0};
	vp.px_delta_u = vec3_divide(vp.vp_u, WIDTH);
	vp.px_delta_v = vec3_divide(vp.vp_v, HEIGHT);
	vp.vp_up_left = vec3_sub(vec3_sub(vec3_sub(vp.cam.origin,
					(t_vec3){0, 0, vp.cam.fov}),
				vec3_divide(vp.vp_u, 2)), vec3_divide(vp.vp_v, 2));
	vp.px_00 = vec3_add(vp.vp_up_left, vec3_mult(
				vec3_add(vp.px_delta_u, vp.px_delta_v), 0.5));
	return (vp);
}

void	trace_ray(t_viewport vp, t_scene *scene)
{
	int		i;
	int		j;
	t_vec3	px_center;
	t_ray	ray;
	t_vec3	col;

	j = 0;
	while (j < vp.win->height)
	{
		i = 0;
		while (i < vp.win->width)
		{
			px_center = vec3_add(vp.px_00, vec3_add(
						vec3_mult(vp.px_delta_u, i),
						vec3_mult(vp.px_delta_v, j)));
			ray.dir = vec3_sub(px_center, vp.cam.origin);
			ray.origin = vp.cam.origin;
			col = draw_background(ray, scene);
			set_pixel(&vp.win->img, i, j, convert_to_rgba(col));
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(vp.win->mlx_ptr, vp.win->win_ptr,
		vp.win->img.img, 0, 0);
}

void	render(t_win *win, t_scene *scene)
{
	t_viewport	vp;
	int			msec;
	clock_t		before;
	clock_t		difference;

	msec = 0;
	before = clock();
	vp = viewport(win, scene);
	trace_ray(vp, scene);
	difference = clock() - before;
	msec = difference * 1000 / CLOCKS_PER_SEC;
	ft_printf(GRAY "[LOG]: render time: %dms \n" RESET, msec % 1000);
	ft_printf(GREEN "done rendering!\n\n" RESET);
}

void	start_renderer(t_prog *prog)
{
	t_win	*win;
	t_scene	*scene;

	win = prog->win;
	scene = prog->scene;
	scene->sky_color = (t_vec3){0.8, 0.9, 0.95};
	init_win(prog);
	mlx_key_hook(win->win_ptr, key_hook, prog);
	if (win->mlx_ptr == NULL)
		return ;
	render(win, scene);
	mlx_loop(win->mlx_ptr);
}
