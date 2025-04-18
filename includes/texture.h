/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:12:29 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/17 13:49:22 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
#define TEXTURE_H

#include "libft/vector.h"
#include "miniRT.h"

# include <stdint.h>
#include <sys/types.h>

typedef struct ppm_header
{

	char	type[2];

	uint	width;
	uint	height;

	uint	max_values;

}	t_ppm_header;

typedef struct ppm_image
{
	t_ppm_header	header;
	t_vec3			*values;

}	t_ppm_image;

t_ppm_header	parse_header(int fd);
int				header_assert(t_ppm_header header, t_prog *prog);

t_vec3			*parse_image(t_ppm_header *header, int fd, t_prog *prog);
t_ppm_image		ppm_image(char *path, t_prog *prog);

t_ppm_header	get_px(int x, int y, t_ppm_image *image);
void			print_ppm_header(t_ppm_header header, const char *name);
uint				get_next_value(char **line, int fd);

#endif // !TEXTURE_H
