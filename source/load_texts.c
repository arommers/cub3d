/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_texts.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/05 13:52:04 by adri          #+#    #+#                 */
/*   Updated: 2023/11/08 15:03:30 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// Use mlx_load_to png to intialize our walls array with the texture paths from the scene description

void	load_textures(t_data *data)
{
	// int	i;
	
	// i = 0;
	// while (i < 4)
	// {
	data->walls[NO].path = "./textures/colorstone.png";
	data->walls[NO].tex = mlx_load_png(data->walls[NO].path);
	data->walls[EA].path = "./textures/colorstone.png";
	data->walls[EA].tex = mlx_load_png(data->walls[EA].path);
	data->walls[SO].path = "./textures/colorstone.png";
	data->walls[SO].tex = mlx_load_png(data->walls[SO].path);
	data->walls[WE].path = "./textures/mossy.png";
	data->walls[WE].tex = mlx_load_png(data->walls[WE].path);

	// 	// if (!data->walls[i].tex)
	// 		// error handling
	// 	i++;
	// }
}

// Clean up the saved mlx_texture_t textures

void	clean_textures(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < 4)
		mlx_delete_texture(data->walls[i++].tex);
}


/*	Determines which texture to retrieve the pixels from based on the direction of the ray
	Using the four quadrants of a unit circle */

mlx_texture_t	*check_side(t_data *data)
{
	t_ray		*r;

	r = data->ray;
	if (r->dirx >= 0 && r->diry <= 0 && r->side == 0)
		return (data->walls[WE].tex);
	else if (r->dirx >= 0 && r->diry <= 0 && r->side == 1)
		return (data->walls[SO].tex);
	if ((r->dirx <= 0 && r->diry <= 0 && r->side == 0))
		return (data->walls[EA].tex);
	else if ((r->dirx <= 0 && r->diry <= 0 && r->side == 1))
		return (data->walls[SO].tex);
	if (r->dirx <= 0 && r->diry >= 0 && r->side == 0)
		return (data->walls[EA].tex);
	else if (r->dirx <= 0 && r->diry >= 0 && r->side == 1)
		return (data->walls[NO].tex);
	if (r->dirx >= 0 && r->diry >= 0 && r->side == 0)
		return (data->walls[WE].tex);
	else if (r->dirx >= 0 && r->diry >= 0 && r->side == 1)
		return (data->walls[NO].tex);
	else
		return (NULL);
}