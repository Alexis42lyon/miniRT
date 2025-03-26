#include "libft/vector.h"
#include "miniRT.h"
#include "window.h"
#include <stdio.h>

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
	printf("desc: %lf\n", discriminant);
	return (discriminant >= 0);
}

int	draw_background(int x, int y)
{
	(void)x;
	(void)y;
	t_sphere	sphere;

	sphere.origin = ft_vec3new(0, 0, -1000000000);
	sphere.radius = 0.5;

	t_ray r;

	r.origin = ft_vec3new(0, 0, 0);
	r.dir = ft_vec3new(0, 0, 1);

	if (sphere_hit(sphere, r))
		return (0x000000);

	return (0x8ad2ff);
}

//int	render_test_sphere(t_win *win)
//{
//}

/*void	render(t_win *win, t_scene *scene)
{

	// camera viewport
	double vp_height = 2;
	double vp_width = vp_height * (win->width / win->height);
	
	// viewport vectors
	t_vec3 vp_u = ft_vec3new(vp_width, 0, 0);
	t_vec3 vp_v = ft_vec3new(0, -vp_height, 0);

	// delta between each pixel
	t_vec3 px_delta_u = vec3_divide(vp_u, win->width);
	t_vec3 px_delta_v = vec3_divide(vp_v, win->height);

	// calculate loc of upper left px
	t_vec3	vp_up_left

	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img, 0, 0);
}*/

void	start_renderer(t_prog *prog)
{
	t_win	*win;
	t_scene	*scene; 

	win = prog->win;
	scene = prog->scene;
	scene->sky_color = 0x8ad2ff;
	init_win(win);
	if (win->mlx_ptr == NULL)
		return ;
//	render(win, scene);
	mlx_loop(win->mlx_ptr);
}
