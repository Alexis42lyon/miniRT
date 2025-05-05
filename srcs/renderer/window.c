/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:18:24 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/05 17:03:33 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "libft/memory.h"
#include "libft/vector.h"
#include "miniRT.h"
#include "mlx.h"
#include "button.h"

int	window_close(void *prog)
{
	free_all(prog);
	return (0);
}

void	free_win(t_win_scene *win, t_win_button *win_btn)
{
	if (win->img.img)
		mlx_destroy_image(win->mlx_ptr, win->img.img);
	if (win->final_image.img)
		mlx_destroy_image(win->mlx_ptr, win->final_image.img);
	if (win->win_ptr)
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	if (win->mlx_ptr)
	{
		mlx_destroy_display(win->mlx_ptr);
		free(win->mlx_ptr);
		if (win_btn->mlx_ptr)
			free(win_btn->win_ptr);
	}
	if (win->accumulation_data)
		free(win->accumulation_data);
	if (win->pass)
		free(win->pass);
}

void	setup_win(t_prog *prog)
{
	prog->win_scene->scale_factor = SSAA_FACTOR * SSAA_FACTOR;
	prog->win_scene->height = HEIGHT * prog->win_scene->scale_factor;
	prog->win_scene->width = WIDTH * prog->win_scene->scale_factor;
	prog->win_scene->half_width = HEIGHT / 2;
	prog->win_scene->half_height = WIDTH / 2;
	prog->win_scene->aspect_ratio = (float)WIDTH / (float)HEIGHT;
	prog->win_scene->mlx_ptr = mlx_init();
	if (!prog->win_scene->mlx_ptr)
		print_exit(prog, "Mlx init failed");
}

void	setup_mlx(t_win_scene *win, t_prog *prog)
{
	win->win_ptr = mlx_new_window(win->mlx_ptr, WIDTH,
			HEIGHT, "miniRT");
	if (!win->win_ptr)
		print_exit(prog, "Mlx new_window failed");
	if (create_img(win) == -1)
		print_exit(prog, "Mlx create img failed");
	mlx_loop_hook(prog->win_scene->mlx_ptr, new_frame, prog);
	mlx_hook(win->win_ptr, ON_DESTROY, 1L << 2, window_close, prog);
	check_mem((t_info){__FILE__, __LINE__, __func__},
		ft_calloc((win->height) * (win->width), sizeof(t_vec3)),
		(void **)&win->accumulation_data, prog);
	check_mem((t_info){__FILE__, __LINE__, __func__},
		ft_calloc(win->height * win->width, sizeof(t_render_pass)),
		(void **)&win->pass, prog);
	init_button_window(prog);
	mlx_hook(win->win_ptr, ON_MOUSEDOWN, 1L << 2, mouse_down, prog);
	mlx_hook(win->win_ptr, ON_MOUSEUP, 1L << 3, mouse_up, prog);
	mlx_hook(win->win_ptr, ON_KEYDOWN, 1L << 0, key_down, prog);
	mlx_hook(win->win_ptr, ON_KEYUP, 1L << 1, key_up, prog);
}

void	init_win(t_prog *prog)
{
	setup_win(prog);
	setup_mlx(prog->win_scene, prog);
	ft_log(SUCCESS, "window is setup");
	ft_log(LOG, "rendering at: w:%d h%d",
		prog->win_scene->width, prog->win_scene->height);
	ft_log(LOG, "downscaling at: w:%d h%d (SSAA_FACTOR:%d)",
		WIDTH, HEIGHT, SSAA_FACTOR);
	if (WIDTH * HEIGHT >= 1920 * 1080)
		ft_log(WARNING, "high resulution detected, expect heavy slowdown");
	if (SSAA_FACTOR != 1)
		ft_log(WARNING, "supersampling is enable, expect heavy slowdown");
	mlx_loop(prog->win_scene->mlx_ptr);
}
