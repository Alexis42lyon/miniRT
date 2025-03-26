/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:00:59 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/25 15:12:02 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_h
# define WINDOW_h

# include <mlx.h>

# define HEIGHT 420
# define WIDTH 720

# define SHOW_WIN 0

/* ----------------------------------- MLX ---------------------------------- */
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_win
{
	char	*name;
	int		width;
	int		height;

	void	*win_ptr;
	void	*mlx_ptr;
	t_data	img;
}	t_win;

int		create_img(t_win *win);
void	set_pixel(t_data *data, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);

void	init_win(t_win *win);

#endif
