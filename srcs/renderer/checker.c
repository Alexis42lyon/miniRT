/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abidolet <abidolet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:17:24 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/16 23:55:07 by abidolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/vector.h"
#include "raytracer.h"
#include <math.h>

t_vec3	checker_color(t_hit	hit, t_mat mat)
{
	int	x;
	int	y;
	int	z;

	(void)mat;
	x = floor(hit.point.x);
	y = floor(hit.point.y);
	z = floor(hit.point.z);
	if ((x + y + z) % 2 == 0)
		return ((t_vec3){0,0,0});
	return (mat.albedo);
}
