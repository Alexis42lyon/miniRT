#include "raytracer.h"
#include "window.h"

void	run_pipeline(t_prog *prog)
{
	t_viewport	vp;

	vp = viewport(prog->win_scene, prog->scene);
	render(vp, prog->scene);
	// anti aliasing
	// denoiser
	// post processing
	// more ...
}

void display_frame(t_win_scene *win, t_scene *scene)
{
	print_cam(&scene->camera);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img, 0, 0);
	scene->frame_count++;
}

#include <stdio.h>
int new_frame(t_prog *prog)
{
	printf("\n");
	run_pipeline(prog);
	display_frame(prog->win_scene, prog->scene);
	return (0);
}
