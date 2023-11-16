/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_texts.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/05 13:52:04 by adri          #+#    #+#                 */
/*   Updated: 2023/11/16 11:37:27 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// Use mlx_load_to png to intialize our walls array with the texture paths from the scene description

void	load_textures(t_data *data)
{
	t_input	*tmp;

	tmp = data->input;
	data->walls[NO].tex = mlx_load_png(tmp->no_texture);
	data->walls[EA].tex = mlx_load_png(tmp->ea_texture);
	data->walls[SO].tex = mlx_load_png(tmp->so_texture);
	data->walls[WE].tex = mlx_load_png(tmp->we_texture);
	data->walls[F].path = "./textures/grass.png";
	data->walls[F].tex = mlx_load_png(data->walls[F].path);
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
	else
		return (data->walls[NO].tex);
}

void	draw_background(t_data *data)
{
	t_player	*tmp = data->player;
	int		y;
	int		x;
	int32_t	color;


	float	raydirxl;
	float	raydiryl;
	float	raydirxr;
	float	raydiryr;

	y = 0;
	while (y < HEIGHT)
	{
		raydirxl = tmp->dirx - tmp->planex;
		raydiryl = tmp->diry - tmp->planey;
		raydirxr = tmp->dirx + tmp->planex;
		raydiryr = tmp->diry + tmp->planey;

		int p = y - 0.5 * HEIGHT;
		float pos_z = 0.5 * HEIGHT;

		float row_dist = pos_z / p;
		
		float floor_step_x = row_dist * (raydirxr - raydirxl) / WIDTH;
		float floor_step_y = row_dist * (raydiryr - raydiryl) / WIDTH;

		float floor_x = tmp->x + row_dist * raydirxl;
		float floor_y = tmp->y + row_dist * raydiryl;

		x = 0;
		while (x < WIDTH)
		{
			int cell_x = (int)floor_x;
			int cell_y = (int)floor_y;
			
			int tex_x = (int)(TEXW * (floor_x - cell_x)) & (TEXW - 1);
			int tex_y = (int)(TEXH * (floor_y - cell_y)) & (TEXH - 1);

			floor_x += floor_step_x;
			floor_y += floor_step_y;
			color = get_pixel(data->walls[F].tex, tex_x, tex_y);
			mlx_put_pixel(data->img, x, y, color);
			x++;
		}
		y++;
	}
}
