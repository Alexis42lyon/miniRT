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

#include "libft/io.h"
#include "libft/memory.h"
#include "libft/vector.h"
#include "raytracer.h"
#include "libft/string.h"
#include <math.h>
#include <stdint.h>

bool is_negative_zero(double x)
{
    uint64_t bits;

    ft_memcpy(&bits, &x, sizeof(double));
    return bits == 0x8000000000000000ULL;
}

void	print_double(uint64_t x)
{
	for ( int i = 63; i >= 0; i-- )
{
    ft_printf( "%d", (x >> i ) & 1 );
}
ft_printf("\n");
}


t_vec3	checker_color(t_hit	hit, t_mat mat)
{
	int	x;
	int	y;
	int	z;

	// if (fabs(hit.point.x) < 0.00001)
	// 	hit.point.x = 0;
	// if (fabs(hit.point.y) < 0.00001)
	// 	hit.point.y = 0;
	// if (fabs(hit.point.z) < 0.00001)
	// 	hit.point.z = 0;
	hit.point.x = round(hit.point.x * 100.0) / 100.0;
	hit.point.y = round(hit.point.y * 100.0) / 100.0;
	hit.point.z = round(hit.point.z * 100.0) / 100.0;
	x = floor(hit.point.x);
	y = floor(hit.point.y);
	z = floor(hit.point.z);
	// print_vec(hit.point);
	// ft_log(LOG, "X:%d, y:%d, z:%d", x, y, z);
	if ((x + y + z) % 2 == 0)
		return ((t_vec3){0,0,0});
	return (mat.albedo);
}
