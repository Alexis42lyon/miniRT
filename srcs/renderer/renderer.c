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

t_vec3	random_vec(uint seed)
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


t_vec3	phong_shading(t_scene *scene, t_hit hit, t_mat mat)
{
	t_vec3	diffuse;
	t_vec3	specular;
	t_vec3	ambient;

	t_vec3	light_dir;

	light_dir = vec3_sub(hit.point, scene->light.origin);
	light_dir = vec3_mult(light_dir, -1);

	// Diffuse = Kd * DOT(N, L) * Od * Ld
	// Kd = reflection coef
	// N = normal
	// L = light
	// Od = mat albeado
	// Ld = light color
	diffuse = vec3_mult(mat.albedo, mat.roughtness * ft_clamp(ft_dot(hit.normal, light_dir), 0, 1));
	diffuse = vec3_multv(diffuse, scene->light.material.albedo);
	diffuse = vec3_divide(diffuse, vec3_lenght_square(light_dir));
	diffuse = vec3_mult(diffuse, scene->light.ratio * 5);

	// R = 2 * DOT(N, L) * N - L
	// specular = Ks * (DOT(V, R))^roughness * Od * Ld
	// ks = obj specular coef
	// V = view vector
	float specular_coef = 01.0f;

	t_vec3	view_vec = vec3_normalize(vec3_sub(scene->camera.origin, hit.point));
	t_vec3 R = vec3_sub(vec3_mult(hit.normal, 2 * ft_clamp(ft_dot(hit.normal, light_dir), 0, 1)), light_dir); 
	float	specular_intensity = specular_coef * pow(ft_clamp(ft_dot(view_vec, R), 0, 1), mat.roughtness);
	specular = vec3_multv(vec3_mult(mat.albedo, specular_intensity), scene->light.material.albedo);

	// Ambient = Ka * Od * Ld
	ambient = vec3_multv( mat.albedo, scene->ambient_light.color);
	ambient = vec3_mult(ambient, scene->ambient_light.ratio);

	// return specular;
	return vec3_clamp(vec3_add(vec3_add(ambient, diffuse), specular), 0, 1);
}

t_vec3	get_px_col(int i, int j, t_viewport vp, t_scene *scene)
{
	t_ray	ray;
	t_hit	hit;
	t_mat	mat;
	// t_vec3	ambiant_color;

	t_vec3	final_color;
	float	mutiplier = 1.0f;
	t_vec3	ray_color;

	ray_color = vec3_mult(scene->ambient_light.color, scene->ambient_light.ratio);
	final_color = (t_vec3){0.0, 0.0, 0.0};

	ray = get_ray(i, j, vp);

	uint seed = i + j * vp.win->width;
	seed *= scene->frame_count;

	for (int i = 0; i < BOUNCES; i++)
	{
		hit = trace_ray(ray, scene);
		if (hit.distance == -1)
		{
			// return ((t_vec3){0,0,0});
			final_color = vec3_mult(vec3_add(final_color, scene->sky_color), mutiplier);
			break;
		}


		if (hit.type == SPHERE)
			mat = scene->spheres[hit.obj_index].material;
		else if (hit.type == PLANE)
			mat = scene->planes[hit.obj_index].material;
		else if (hit.type == CYLINDER)
			mat = scene->cylinders[hit.obj_index].material;

		mat.roughtness = 0.1f;
		final_color = vec3_mult(mat.albedo, mutiplier);
		// final_color = vec3_mult(normal_color(hit), mutiplier);

		// Phong shading model
		final_color = phong_shading(scene, hit, mat);
		// final_color = 
		mutiplier *= 0.5f;

		ray.origin = vec3_add(hit.point, vec3_mult(hit.normal, 0.0001));
		ray.dir = vec3_reflect(ray.dir,
			vec3_add(hit.normal, vec3_mult(random_vec(seed), mat.roughtness)));
		
	}

	return (vec3_clamp(final_color, 0 ,1));
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
			set_pixel(&vp.win->img, i, j, convert_to_rgba(accumulation));
			i++;
		}
		show_progress(vp.win->width * j + i, vp.win->width * vp.win->height);
		j++;
	}
	scene->frame_count++;
}

void	add_to_log(t_scene *scene, uint render_time)
{
	// print_cam(&scene->camera);
	ft_printf(GRAY "\n[LOG]: render time:%dms\n" RESET, render_time);
	ft_printf(GRAY "[LOG]: frame_count:%d\n" RESET,
		scene->frame_count);
	ft_printf(GREEN "done rendering!\n\n" RESET);

	scene->total_render_time += render_time;
	if (scene->min_render_time == (uint)-1)
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

int	run_pipeline(t_prog *prog)
{
	int			msec;
	clock_t		before;
	clock_t		difference;
	t_viewport	vp;

	prog->scene->sky_color = (t_vec3){0.8, 0.9, 0.95};
	prog->scene->sky_color = (t_vec3){0,0,0};
	vp = viewport(prog->win_scene, prog->scene);
	msec = 0;
	before = clock();
	render(vp, prog->scene);
	mlx_put_image_to_window(prog->win_scene->mlx_ptr, prog->win_scene->win_ptr,
		prog->win_scene->img.img, 0, 0);
	difference = clock() - before;
	msec = difference * 1000 / CLOCKS_PER_SEC;
	add_to_log(prog->scene, msec);
	return (0);
}

void	start_renderer(t_prog *prog)
{
	t_win_scene	*win;
	t_scene	*scene;

	win = prog->win_scene;
	scene = prog->scene;

	scene->min_render_time = -1;
	scene->max_render_time = -1;
	scene->total_render_time = 0;

	init_win(prog);
	mlx_key_hook(win->win_ptr, key_hook, prog);
	if (win->mlx_ptr == NULL)
		return ;
	run_pipeline(prog);
	init_button_window(prog);
	mlx_loop(win->mlx_ptr);
}
