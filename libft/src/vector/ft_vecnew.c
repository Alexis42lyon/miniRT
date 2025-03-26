/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:58:12 by mjuncker          #+#    #+#             */
/*   Updated: 2025/03/24 16:59:39 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/vector.h"
#include "stdio.h"

t_vec3	ft_vec3new(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

void	print_vec(t_vec3 vec)
{
	printf("vec: (x: %lf, y: %lf, z: %lf)\n", vec.x, vec.y, vec.z);
}

