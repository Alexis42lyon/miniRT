/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuncker <mjuncker@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:48:28 by mjuncker          #+#    #+#             */
/*   Updated: 2025/04/15 11:49:44 by mjuncker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

int parse_texture(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (-1);
    return (0);
}
