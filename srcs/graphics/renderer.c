#include "libft/vector.h"
#include "miniRT.h"
#include "window.h"
#include <math.h>
#include <stdio.h>

// t are hit distance (for r = a * bt)
// double	get_closest_hit(double a, double b, double discriminant, t_ray ray)
// {
// 	float	t0;
// 	float	t1;
// 	t_vec3	hit;

// 	t0 = (-b - sqrt(discriminant)) / (2 * a);
// 	t1 = (-b + sqrt(discriminant)) / (2 * a);

// 	hit = vec3_add(ray.origin, vec3_mutl(ray.dir, t0));
	
// }

double	sphere_hit(const t_sphere sphere, const t_ray ray)
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
	discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (-1);
	return ((-b - sqrt(discriminant)) / (2 * a));
}

t_vec3	draw_background(t_ray r, t_sphere *sphere)
{	
	double			t;
	
	t = sphere_hit(*sphere, r);
	// printf("res: %lf\n", result);
	if (t > 0)
	{
		    t_vec3 hit_point = vec3_add(r.origin, vec3_mult(r.dir, t));
		// Calculate normal at the hit point
		t_vec3 normal = unit_vec3(vec3_sub(hit_point, sphere->origin));
		// Map the normal from [-1,1] to [0,1]
		t_vec3 color = vec3_mult(vec3_add(normal, (t_vec3){1, 1, 1}), 0.5);
		return color;

		t_vec3	N = unit_vec3(vec3_sub(ray_to_vec(r), (t_vec3){0, 0, -1}));
		return (vec3_mult((t_vec3){N.x + 1, N.y + 1, N.z + 1}, 0.5));
		// return ((t_vec3){1, 0, 1});
		// return (unit_vec3(vec3_add(r.origin, vec3_mult(r.dir, result))));
	}
	t_vec3	unit_dir = unit_vec3(r.dir);
	double	a = 0.5f * (unit_dir.y + 1.0f);
	return (vec3_add(vec3_mult(new_vec3(1, 1, 1), (1.0 - a)), vec3_mult(new_vec3(0.5, 0.7, 1.0), a)));

	return (new_vec3(0, 0, 0));
}

int convert_to_rgba(const t_vec3 color)
{
	unsigned short r, g, b, a;

	r = (unsigned short)(color.x * 255.999f);
	g = (unsigned short)(color.y * 255.999f);
	b = (unsigned short)(color.z * 255.999f);
	a = (unsigned short)(255.0f);

	return ((a << 24) | (r << 16) | (g << 8) | b);
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

			t_vec3	col = draw_background(ray, scene->spheres);

			set_pixel(&win->img, i, j, convert_to_rgba(col));
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
	init_win(prog);
	mlx_key_hook(win->win_ptr, key_hook, prog);
	if (win->mlx_ptr == NULL)
		return ;
	scene->spheres->origin = (t_vec3){0, 0, 0};
	scene->spheres->radius = 0.5;
	render(win, scene);
	mlx_loop(win->mlx_ptr);
}
