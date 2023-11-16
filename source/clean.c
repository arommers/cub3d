/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/10 12:31:21 by arommers      #+#    #+#                 */
/*   Updated: 2023/11/16 10:02:22 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// Clean up the saved mlx_texture_t textures

void	clean_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (data->walls && data->walls[i].tex)
			mlx_delete_texture(data->walls[i].tex);
		i++;
	}
}
void	free_2darray(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	clean_input(t_input *input)
{
	free_2darray(input->map);
	free(input->no_texture);
	free(input->so_texture);
	free(input->ea_texture);
	free(input->we_texture);
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
	if (data->input)
	{
		clean_input(data->input);
		free(data->input);
	}
}

void	ft_error(t_data *data, char *msg)
{
	perror(msg);
	ft_clean(data);
	exit(EXIT_FAILURE);
}
