#include "libft/math.h"
#include "libft/vector.h"
#include "miniRT.h"
#include "mlx.h"
#include "window.h"
#include "raytracer.h"
#include <limits.h>
#include <time.h>

#define BOUNCES 2

//! TO REMOVE
#include <stdio.h>

t_viewport viewport(t_win_scene *win, t_scene *scene)
{
	t_viewport vp;
	vp.win = win;
	vp.cam = &scene->camera;

	vp.cam->foward = vec3_normalize(vp.cam->direction);
	t_vec3 world_up = (t_vec3){0, -1, 0}; // World up direction
	vp.cam->right = vec3_normalize(vec3_cross(vp.cam->foward, world_up));
	vp.cam->up = vec3_cross(vp.cam->right, vp.cam->foward);

	vp.vp_height = 2;
	vp.vp_width = vp.vp_height * ((double)win->width / win->height);

	vp.vp_u = vec3_mult(vp.cam->right, vp.vp_width);
	vp.vp_v = vec3_mult(vp.cam->up, vp.vp_height);

	vp.px_delta_u = vec3_divide(vp.vp_u, win->width);
	vp.px_delta_v = vec3_divide(vp.vp_v, win->height);

	t_vec3 view_center = vec3_sub(vp.cam->origin, vec3_mult(vp.cam->foward, vp.cam->fov));
	vp.vp_up_left = vec3_sub(
						vec3_sub(view_center, vec3_divide(vp.vp_u, 2)),
						vec3_divide(vp.vp_v, 2)
						);

	vp.px_00 = vec3_add(vp.vp_up_left,
						vec3_mult(vec3_add(vp.px_delta_u, vp.px_delta_v), 0.5));
						
	return vp;
}

t_vec3	get_px_col(int i, int j, t_viewport vp, t_scene *scene)
{
	t_vec3	light_dir;
	t_ray	ray;
	t_hit	hit;

	t_vec3	final_color;
	float	mutiplier = 1.0f;

	final_color = (t_vec3){0.0, 0.0, 0.0};

	light_dir = vec3_normalize((t_vec3){-1, -1, -1}); // FAKE LIGHT
	ray = get_ray(i, j, vp, scene->sample_count);

	for (int i = 0; i < BOUNCES; i++)
	{
		hit = trace_ray(ray, scene);
		if (hit.hit_distance == -1)
		{
			final_color = vec3_mult(vec3_add(final_color, scene->sky_color), mutiplier);
			break;
		}

		float	light_intensity = ft_dot(hit.hit_normal, vec3_mult(light_dir, -1));
		if (light_intensity < 0)
			light_intensity = 0;
		t_vec3	color = scene->spheres[hit.obj_index].material.albedo;
		color = vec3_mult(color, light_intensity);

		final_color = vec3_mult(vec3_add(final_color, color), mutiplier);
		mutiplier *= 0.5f;

		ray.origin = vec3_add(hit.hit_point, vec3_mult(hit.hit_normal, 0.0001));
		ray.dir = vec3_reflect(ray.dir, hit.hit_normal);
	}

	return (final_color);
}
void    show_progress(int current, int max);

void	render(t_viewport vp, t_scene *scene)
{
	int		i;
	int		j;
	t_vec3	col;

	j = 0;
	while (j < vp.win->height)
	{
		i = 0;
		while (i < vp.win->width)
		{
			col = get_px_col(i, j, vp, scene);
			set_pixel(&vp.win->img, i, j, convert_to_rgba(col));
			i++;
		}
		show_progress(vp.win->width * j + i, vp.win->width * vp.win->height);
		j++;
	}
	printf("\033[?25h\n");
	scene->frame_count++;
}

void    show_progress(int current, int max)
{
        int             i;
        float   progress;

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
        printf(RESET "] (%d%%)\r", (int)progress);

}

void	run_pipeline(t_prog *prog)
{
	int			msec;
	clock_t		before;
	clock_t		difference;
	t_viewport	vp;

	print_cam(&prog->scene->camera);
	prog->scene->sky_color = (t_vec3){0.8, 0.9, 0.95};
	vp = viewport(prog->win_scene, prog->scene);
	msec = 0;
	before = clock();
	render(vp, prog->scene);
	mlx_put_image_to_window(prog->win_scene->mlx_ptr, prog->win_scene->win_ptr,
		prog->win_scene->img.img, 0, 0);
	difference = clock() - before;
	msec = difference * 1000 / CLOCKS_PER_SEC;
	ft_dprintf(2, GRAY "[LOG]: render time:%dms \n" RESET, msec % 1000);
	ft_dprintf(2, GRAY "[LOG]: frame_count:%d \n" RESET,
		prog->scene->frame_count);
	ft_dprintf(2, GREEN "done rendering!\n\n" RESET);
}

void	start_renderer(t_prog *prog)
{
	t_win_scene	*win;
	t_scene	*scene;

	win = prog->win_scene;
	scene = prog->scene;
	scene->sample_count = 0;
	init_win(prog);
	mlx_key_hook(win->win_ptr, key_hook, prog);
	if (win->mlx_ptr == NULL)
		return ;
	run_pipeline(prog);
	init_button_window(prog);
	mlx_loop(win->mlx_ptr);
}
