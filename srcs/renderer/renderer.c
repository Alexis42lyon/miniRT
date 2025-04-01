#include "window.h"
#include "raytracer.h"
#include <limits.h>
#include <time.h>

//! TO REMOVE
#include <stdio.h>

t_vec3	draw_background(t_ray r, t_scene *scene)
{
	t_hit	hit;
	t_hit	tmp;
	size_t	i;
	t_vec3	light_dir = vec3_normalize((t_vec3){-1, -1, -1}); // FAKE LIGHT
	float	dot;


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
		dot = ft_dot(hit.hit_normal, vec3_mult(light_dir, -1));
		dot *= 0.5f;
		dot += 0.5f;
		return (vec3_mult(scene->spheres[hit.obj_index].color, dot));
	}
	return ((t_vec3){0, 0, 0});
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

t_ray	get_ray(int i, int j, t_viewport vp, uint seed)
{
	t_vec3	offset;
	t_vec3	sample;
	t_ray	ray;

	(void)seed;
	offset = vec3_rand_range(0.5, seed);
	sample = vec3_add(vec3_add(vp.px_00,
			vec3_mult(vp.px_delta_u, i + offset.x)),
			vec3_mult(vp.px_delta_u, j + offset.y));
	sample = vec3_add(vp.px_00, vec3_add(
				vec3_mult(vp.px_delta_u, i + offset.x),
				vec3_mult(vp.px_delta_v, j + offset.y))
				);	
			
	t_vec3 px_center = vec3_add(vp.px_00, vec3_add(
				vec3_mult(vp.px_delta_u, i),
				vec3_mult(vp.px_delta_v, j))
				);

	// printf("px_center: ");
	// print_vec(px_center);
	// printf("sample: ");
	// print_vec(sample);
	// printf("\n");

	ray.origin = vp.cam.origin;
	ray.dir = vec3_sub(px_center, ray.origin); // TODO: change to sample point
	return (ray);
}

void	trace_ray(t_viewport vp, t_scene *scene)
{
	int		i;
	int		j;
	// t_vec3	px_center;
	t_ray	ray;
	t_vec3	col;

	j = 0;
	while (j < vp.win->height)
	{
		i = 0;
		while (i < vp.win->width)
		{
			ray = get_ray(i, j, vp, scene->sample_count);
			scene->sample_count++;
			// ray.dir = vec3_sub(px_center, vp.cam.origin);
			// ray.origin = vp.cam.origin;
			col = draw_background(ray, scene);
			set_pixel(&vp.win->img, i, j, convert_to_rgba(col));
			i++;
		}
		j++;
	}
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
	scene->frame_count++;
	difference = clock() - before;
	msec = difference * 1000 / CLOCKS_PER_SEC;
	ft_dprintf(2, GRAY "[LOG]: render time:%dms \n" RESET, msec % 1000);
	ft_dprintf(2, GRAY "[LOG]: frame_count:%d \n" RESET, scene->frame_count);
	ft_dprintf(2, GREEN "done rendering!\n\n" RESET);
}

void	run_pipeline(t_prog *prog)
{
	render(prog->win, prog->scene);
	mlx_put_image_to_window(prog->win->mlx_ptr, prog->win->win_ptr,
		prog->win->img.img, 0, 0);
	init_buttons(prog->win);
}

void	start_renderer(t_prog *prog)
{
	t_win	*win;
	t_scene	*scene;

	win = prog->win;
	scene = prog->scene;
	scene->sample_count = 0;
	scene->sky_color = (t_vec3){0.8, 0.9, 0.95};
	init_win(prog);
	mlx_key_hook(win->win_ptr, key_hook, prog);
	if (win->mlx_ptr == NULL)
		return ;
	run_pipeline(prog);
	mlx_loop(win->mlx_ptr);
}
