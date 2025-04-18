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

uint	get_next_value(char **line, int fd)
{
	uint	val;
	
	if (*line == NULL)
		return (-1);
	while (is_whitespace((*line)[0]))
		(*line)++;
	if ((*line)[0] == '\n' || (*line)[0] == '#' || (*line)[0] == '\0')
	{
		*line = ft_get_next_line(fd);
		if (!line)
			return (-1);
		return (get_next_value(line, fd));
	}
	val = ft_atoi(*line);
	if ((*line)[0] == '#')
	{
		*line = ft_get_next_line(fd);
		if (!line)
			return (-1);
		return (val);
	}
	while (((*line)[0] >= '0' && (*line)[0] <= '9'))
		(*line)++;
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
	char			*line;

	ft_bzero(&header, sizeof(t_ppm_header));

	line = ft_get_next_line(fd);	
	if (!line)
		return (invalid_header());
	header.type[0] = line[0];
	header.type[1] = line[1];
	line += 2;
	header.width = get_next_value(&line, fd);
	header.height = get_next_value(&line, fd);
	header.max_values = get_next_value(&line, fd);
    return (header);
}


