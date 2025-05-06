/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:12:29 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/06 14:05:14 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_BONUS_H
# define TEXTURE_BONUS_H

# define DEFAULT_RENDER_PATH "./"

# include "libft/vector.h"
# include "miniRT_bonus.h"
# include "raytracer_bonus.h"

# include <stdint.h>
# include <sys/types.h>

t_ppm_header	parse_header(int fd);
int				header_assert(t_ppm_header header, t_prog *prog);

t_vec3			*parse_image(t_ppm_header *header, int fd);
t_ppm_image		ppm_image(char *path, t_prog *prog);
t_ppm_header	invalid_header(void);

t_vec3			get_px(float u, float v, t_ppm_image *image);
void			print_ppm_header(t_ppm_header header, const char *name);
int				is_header_valid(t_ppm_header *header);

void			save_image_to_ppm(t_win_scene *win);

// uv.h
void			get_uv(t_scene *scene, t_hit hit, float *u, float *v);

#endif // !TEXTURE_H
