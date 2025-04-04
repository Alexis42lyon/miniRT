/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:16:11 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/04 08:54:25 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# include <sys/types.h>

int		overflow_check(const char *s, void (*f)(int, void *), void *param);

int		ft_abs(float n);
int		ft_max(float a, float b);
int		ft_min(float a, float b);

uint	PCG_Hash(uint input);
float	PCG_Hash_range(float range, uint input);
float	ft_clamp(float f, float min, float max);


#endif
