/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:17:24 by mjuncker          #+#    #+#             */
/*   Updated: 2025/05/02 16:12:26 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/vector.h"
#include "raytracer.h"
#include <math.h>
#include <stdint.h>

t_vec3	checker_color(t_hit	hit, t_mat mat)
{
	int	x;
	int	y;
	int	z;

	hit.point.x = round(hit.point.x * 100.0) / 100.0;
	hit.point.y = round(hit.point.y * 100.0) / 100.0;
	hit.point.z = round(hit.point.z * 100.0) / 100.0;
	x = floor(hit.point.x);
	y = floor(hit.point.y);
	z = floor(hit.point.z);
	if ((x + y + z) % 2 == 0)
		return ((t_vec3){0, 0, 0});
	return (mat.albedo);
}
