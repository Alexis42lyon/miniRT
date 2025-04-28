/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:12:29 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/25 11:49:10 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
#define TEXTURE_H

# define DEFAULT_RENDER_PATH "./"

# include "libft/vector.h"
# include "miniRT.h"

# include <stdint.h>
# include <sys/types.h>

t_ppm_header	parse_header(int fd);
int				header_assert(t_ppm_header header, t_prog *prog);

t_vec3			*parse_image(t_ppm_header *header, int fd);
t_ppm_image		ppm_image(char *path, t_prog *prog);
t_ppm_header	invalid_header(void);

t_vec3	get_px(float u, float v, t_ppm_image *image);
void			print_ppm_header(t_ppm_header header, const char *name);

void	save_image_to_ppm(t_win_scene *win);

#endif // !TEXTURE_H
