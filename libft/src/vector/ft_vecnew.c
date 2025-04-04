/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:58:12 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/04 08:51:09 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/vector.h"
#include "stdio.h"

t_vec3	new_vec3(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec3	vec3_zero(void)
{
	return ((t_vec3){0.0f, 0.0f, 0.0f});
}

void	print_vec(t_vec3 vec)
{
	printf("(x: %lf, y: %lf, z: %lf)\n", vec.x, vec.y, vec.z);
}

