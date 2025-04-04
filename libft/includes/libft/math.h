/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:16:11 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/04 10:23:28 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

typedef unsigned int uint;

int		overflow_check(const char *s, void (*f)(int, void *), void *param);

int		ft_abs(float n);
int		ft_max(float a, float b);
int		ft_min(float a, float b);

uint	pcg_hash(uint input);
float	random_float(uint input);
float	ft_clamp(float f, float min, float max);


#endif
