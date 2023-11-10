/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/10 12:31:21 by arommers      #+#    #+#                 */
/*   Updated: 2023/11/10 16:11:08 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// Clean up the saved mlx_texture_t textures

void	clean_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->walls[i].tex)
			mlx_delete_texture(data->walls[i].tex);
		i++;
	}
}

void	ft_clean(t_data *data)
{
	if (data->ray)
	{
		if (data->ray->line)
			free(data->ray->line);
		free(data->ray);
	}
	if (data->player)
		free(data->player);
	if (data->walls)
	{
		clean_textures(data);
		free(data->walls);
	}
}

void	ft_error(t_data *data, char *msg)
{
	perror(msg);
	ft_clean(data);
	exit(EXIT_FAILURE);
}
