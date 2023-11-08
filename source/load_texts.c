/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_texts.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/05 13:52:04 by adri          #+#    #+#                 */
/*   Updated: 2023/11/08 11:31:29 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	load_textures(t_data *data)
{
	// int	i;
	
	// i = 0;
	// while (i < 4)
	// {
		data->walls->path = "./textures/eagle.png";
		data->walls->tex = mlx_load_png(data->walls->path);
		// data->walls[i].tex = mlx_load_png(data->walls[i].path);
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


mlx_texture_t *check_side(t_data *data)
{
	t_player 	*p;
	t_ray		*r
}