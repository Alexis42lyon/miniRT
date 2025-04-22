/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:48:28 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/17 12:45:41 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "libft/memory.h"
#include "miniRT.h"
#include "texture.h"
#include "libft/io.h"
#include "libft/string.h"
#include "libft/is.h"

#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

t_ppm_header	invalid_header(void)
{
	return ((t_ppm_header){
			.type[0] = -1,
			.type[1] = -1,
			.width = -1,
			.height = -1,
			.max_values = -1,
			});
}

uint	get_next_value(int fd)
{
	uint	val;

	int		nb_read;
	char	c[1];

	nb_read = read(fd, c, 1);
	while (is_whitespace(c[0]) && nb_read != 0)
	{
		nb_read = read(fd, c, 1);

	}
	if (c[0] == '#')
	{
		while (c[0] != '\n' && nb_read != 0)
		{
			nb_read = read(fd, c, 1);
		}
	}

	val = 0;
	while ((c[0] >= '0' && c[0] <= '9') && nb_read != 0)
	{
		val *= 10;
		val += c[0] - '0';
		nb_read = read(fd, &c, 1);
	}
	return (val);
}

int	header_assert(t_ppm_header header, t_prog *prog)
{
	if (ft_strcmp(header.type, "P6") != 0)
		print_exit(prog, "invalid format");
	if (header.width < 1)
		print_exit(prog, "invalid width");
	if (header.height < 1)
		print_exit(prog, "invalid height");
	if (header.max_values < 1)
		print_exit(prog, "invalid color values");
	return (0);
}

t_ppm_header parse_header(int fd)
{
	t_ppm_header	header;
	char			buff[2];

	ft_bzero(&header, sizeof(t_ppm_header));

	read(fd, buff, 2);
	header.type[0] = buff[0];
	header.type[1] = buff[1];
	header.width = get_next_value(fd);
	header.height = get_next_value(fd);
	header.max_values = get_next_value(fd);
	return (header);
}


