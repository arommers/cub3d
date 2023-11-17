/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_texts.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: adri <adri@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/05 13:52:04 by adri          #+#    #+#                 */
/*   Updated: 2023/11/17 11:26:37 by arommers      ########   odam.nl         */
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
	data->walls[C].path = "./textures/sky.png";
	data->walls[C].tex = mlx_load_png(data->walls[C].path);
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

void	draw_ceiling(t_data *data)
{
	t_floor		*f;
	t_player	*p;
	int			y;

	f = data->floor;
	p = data->player;
	y = 0;
	while (y < HEIGHT / 2)
	{
		f->ray_xl = p->dirx - p->planex;
		f->ray_yl = p->diry - p->planey;
		f->ray_xr = p->dirx + p->planex;
		f->ray_yr = p->diry + p->planey;
		f->p = y - 0.5 * HEIGHT;
		f->z = 0.5 * HEIGHT;
		f->row_dis = f->z / f->p;
		f->x = p->x + f->row_dis * f->ray_xl;
		f->y = p->y + f->row_dis * f->ray_yl;
		f->step_x = f->row_dis * (f->ray_xr - f->ray_xl) / WIDTH;
		f->step_y = f->row_dis * (f->ray_yr - f->ray_yl) / WIDTH;
		draw_horo_line(data, f, HEIGHT / 2 - y - 1, 0);
		y++;
	}
}

void	draw_floor(t_data *data)
{
	t_floor		*f;
	t_player	*p;
	int			y;

	f = data->floor;
	p = data->player;
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		f->ray_xl = p->dirx - p->planex;
		f->ray_yl = p->diry - p->planey;
		f->ray_xr = p->dirx + p->planex;
		f->ray_yr = p->diry + p->planey;
		f->p = y - 0.5 * HEIGHT;
		f->z = 0.5 * HEIGHT;
		f->row_dis = f->z / f->p;
		f->x = p->x + f->row_dis * f->ray_xl;
		f->y = p->y + f->row_dis * f->ray_yl;
		f->step_x = f->row_dis * (f->ray_xr - f->ray_xl) / WIDTH;
		f->step_y = f->row_dis * (f->ray_yr - f->ray_yl) / WIDTH;
		draw_horo_line(data, f, y, 1);
		y++;
	}
}

void	draw_horo_line(t_data *data, t_floor *f, int y, int half)
{
	int		x;
	int32_t	color;

	x = 0;
	while (x < WIDTH)
	{
		f->cell_x = (int)f->x;
		f->cell_y = (int)f->y;
		f->tex_x = (int)(TEXW * (f->x - f->cell_x)) & (TEXW - 1);
		f->tex_y = (int)(TEXH * (f->y - f->cell_y)) & (TEXH - 1);
		f->x += f->step_x;
		f->y += f->step_y;
		if (half == 0)
			color = get_pixel(data->walls[C].tex, f->tex_x, f->tex_y);
		else
			color = get_pixel(data->walls[F].tex, f->tex_x, f->tex_y);
		mlx_put_pixel(data->img, x, y, color);
		x++;
	}
}

// void	draw_background(t_data *data, int half)
// {
// 	t_floor		*f;
// 	t_player	*p;
// 	int			y;
// 	int			end;

// 	f = data->floor;
// 	p = data->player;
// 	end = check_half(half, &y);
// 	while (y < end)
// 	{
// 		f->ray_xl = p->dirx - p->planex;
// 		f->ray_yl = p->diry - p->planey;
// 		f->ray_xr = p->dirx + p->planex;
// 		f->ray_yr = p->diry + p->planey;
// 		f->p = y - 0.5 * HEIGHT;
// 		f->z = 0.5 * HEIGHT;
// 		f->row_dis = f->z / f->p;
// 		f->x = p->x + f->row_dis * f->ray_xl;
// 		f->y = p->y + f->row_dis * f->ray_yl;
// 		f->step_x = f->row_dis * (f->ray_xr - f->ray_xl) / WIDTH;
// 		f->step_y = f->row_dis * (f->ray_yr - f->ray_yl) / WIDTH;
// 		draw_horo_line(data, f, y, half);
// 		y++;
// 	}
// }

// void	draw_horo_line(t_data *data, t_floor *f, int y, int half)
// {
// 	int		x;
// 	int32_t	color;

// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		f->cell_x = (int)f->x;
// 		f->cell_y = (int)f->y;

// 		f->tex_x = (int)(TEXW * (f->x - f->cell_x)) & (TEXW - 1);
// 		f->tex_y = (int)(TEXH * (f->y - f->cell_y)) & (TEXH - 1);

// 		f->x += f->step_x;
// 		f->y += f->step_y;
// 		if (half == 0)
// 			color = get_pixel(data->walls[C].tex, f->tex_x, f->tex_y);
// 		else
// 			color = get_pixel(data->walls[F].tex, f->tex_x, f->tex_y);
// 		mlx_put_pixel(data->img, x, y, color);
// 		x++;
// 	}
// }