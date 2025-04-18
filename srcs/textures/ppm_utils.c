/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:29:14 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/17 12:30:37 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "libft/io.h"

void	print_ppm_header(t_ppm_header header, const char *name)
{
	ft_printf(GRAY "%s header:\n", name);
	ft_printf("\ttype:......%s\n", header.type);
	ft_printf("\twidth:.....%u\n", header.width);
	ft_printf("\theight:....%u\n", header.height);
	ft_printf("\tvalues:....%u\n", header.max_values);
	ft_printf(RESET "\n");
}


