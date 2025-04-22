/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:29:14 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/22 12:24:03 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/vector.h"
#include "texture.h"
#include "libft/io.h"

void	print_ppm_header(t_ppm_header header, const char *name)
{
	ft_log(LOG, "%s header:", name);
	ft_log(LOG, "   type:........%s", header.type);
	ft_log(LOG, "   width:.......%u", header.width);
	ft_log(LOG, "   height:......%u", header.height);
	ft_log(LOG, "   values:......%u", header.max_values);
}

#include <stdio.h>
t_vec3	get_px(float u, float v, t_ppm_image *image)
{
	int x;
	int y;

	x = image->header.width * u;
	y = image->header.height * v;
	return (image->values[x + image->header.width * y]);
}
