/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_texts.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/05 13:52:04 by adri          #+#    #+#                 */
/*   Updated: 2023/11/20 10:53:55 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*	- Use mlx_load_to png to intialize our walls array
	  with the texture paths from the scene description */

void	load_textures(t_data *data)
{
	t_input	*tmp;

	tmp = data->input;
	data->walls[NO].tex = mlx_load_png(tmp->no_texture);
	if (!data->walls[NO].tex)
		ft_error(data, "MLX42 Error");
	data->walls[EA].tex = mlx_load_png(tmp->ea_texture);
	if (!data->walls[EA].tex)
		ft_error(data, "MLX42 Error");
	data->walls[SO].tex = mlx_load_png(tmp->so_texture);
	if (!data->walls[SO].tex)
		ft_error(data, "MLX42 Error");
	data->walls[WE].tex = mlx_load_png(tmp->we_texture);
	if (!data->walls[WE].tex)
		ft_error(data, "MLX42 Error");
}

/*	- Determines which texture to retrieve the pixels from
	  based on the direction of the ray using the four quadrants
	  of a unit circle */

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
	else
		return (data->walls[NO].tex);
}
