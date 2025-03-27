#include "libft/vector.h"
#include "miniRT.h"
#include "window.h"
#include <stdio.h>
t_sphere	sphere = {{-50,-1,0}, 0.5, 0, NULL};

int	sphere_hit(const t_sphere sphere, const t_ray ray)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec3_sub(sphere.origin, ray.origin);
	a = ft_dot(ray.dir, ray.dir);
	b = -2.0 * ft_dot(ray.dir, oc);
	c = ft_dot(oc, oc) - sphere.radius * sphere.radius;
	discriminant = b*b - 4 * a * c;
	return (discriminant >= 0);
}


int	draw_background(t_ray r)
{

	if (sphere_hit(sphere, r))
		return (0x000000);

	return (0x8ad2ff);
}

//int	render_test_sphere(t_win *win)
//{
//}

void	render(t_win *win, t_scene *scene)
{
	t_camera	cam;

	cam = scene->camera;
	cam.fov = 1; // TODO a changer
	// camera viewport
	double vp_height = 2;
	double vp_width = vp_height * (win->width / win->height);
	
	// viewport vectors
	t_vec3 vp_u = new_vec3(vp_width, 0, 0);
	t_vec3 vp_v = new_vec3(0, -vp_height, 0);

	// delta between each pixel
	t_vec3 px_delta_u = vec3_divide(vp_u, win->width);
	t_vec3 px_delta_v = vec3_divide(vp_v, win->height);

	// calculate loc of upper left px
	t_vec3	vp_up_left = vec3_sub(vec3_sub(vec3_sub(cam.origin, new_vec3(0, 0, cam.fov)),
			vec3_divide(vp_u, 2)), vec3_divide(vp_v, 2));
	t_vec3	px_00 = vec3_add(vp_up_left, vec3_mutl(vec3_add(px_delta_u, px_delta_v), 0.5));

	// Rendering:
	for (int j = 0; j < win->height; j++)
	{
		for (int i = 0; i < win->width; i++)
		{
			t_vec3 px_center = vec3_add(px_00, vec3_add(vec3_mutl(px_delta_u, i), vec3_mutl(px_delta_v, j)));
			t_vec3 ray_dir = vec3_sub(px_center, cam.origin);

			t_ray	ray;
			ray.dir = ray_dir;
			ray.origin = cam.origin;

			set_pixel(&win->img, i, j, draw_background(ray));
		}
	}
	printf(GREEN "done rendering!\n" RESET);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img, 0, 0);
}

void	start_renderer(t_prog *prog)
{
	t_win	*win;
	t_scene	*scene; 
	
	win = prog->win;
	scene = prog->scene;
	scene->sky_color = 0x8ad2ff;
	init_win(win);
	mlx_key_hook(win->win_ptr, key_hook, prog);
	if (win->mlx_ptr == NULL)
		return ;
	render(win, scene);
	mlx_loop(win->mlx_ptr);
}
