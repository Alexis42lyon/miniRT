/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:18:24 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/05 16:23:43 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "libft/memory.h"
#include "libft/vector.h"
#include "miniRT.h"
#include "mlx.h"

int	window_close(void *prog)
{
	free_all(prog);
	return (0);
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

void	init_win(t_prog *prog)
{
	t_win_scene	*win;

	setup_win(prog);
	win = prog->win_scene;
	win->win_ptr = mlx_new_window(win->mlx_ptr, WIDTH,
			HEIGHT, "miniRT");
	if (!win->win_ptr)
		print_exit(prog, "Mlx new_window failed");
	if (create_img(win) == -1)
		print_exit(prog, "Mlx create img failed");
	mlx_loop_hook(prog->win_scene->mlx_ptr, new_frame, prog);
	mlx_hook(win->win_ptr, ON_DESTROY, 1L<<2, window_close, prog);
	check_mem((t_info){__FILE__, __LINE__, __func__},
		ft_calloc((win->height) * (win->width), sizeof(t_vec3)),
		(void **)&win->accumulation_data, prog);
	check_mem((t_info){__FILE__, __LINE__, __func__},
		ft_calloc(win->height * win->width, sizeof(t_render_pass)),
		(void **)&win->pass, prog);
	init_button_window(prog);
	mlx_hook(win->win_ptr, ON_MOUSEDOWN, 1L<<2, mouse_down, prog);
	mlx_hook(win->win_ptr, ON_MOUSEUP, 1L<<3, mouse_up, prog);
	mlx_hook(win->win_ptr, ON_KEYDOWN, 1L<<0, key_down, prog);
	mlx_hook(win->win_ptr, ON_KEYUP, 1L<<1, key_up, prog);
	mlx_loop(win->mlx_ptr);
}
