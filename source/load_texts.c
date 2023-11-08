/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_texts.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/05 13:52:04 by adri          #+#    #+#                 */
/*   Updated: 2023/11/08 12:06:05 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	load_textures(t_data *data)
{
	// int	i;
	
	// i = 0;
	// while (i < 4)
	// {
	data->walls[NO].path = "./textures/eagle.png";
	data->walls[NO].tex = mlx_load_png(data->walls[NO].path);
	data->walls[EA].path = "./textures/bluestone.png";
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

void	clean_textures(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < 4)
		mlx_delete_texture(data->walls[i++].tex);
}


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