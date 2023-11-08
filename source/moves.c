/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   moves.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/03 12:59:35 by arommers      #+#    #+#                 */
/*   Updated: 2023/11/08 11:14:35 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clear_frame(t_data *data)
{
	int			x;
	int			y;
	uint32_t	color;

	color = ft_pixel(0x00, 0x00, 0x00, 0x00);
	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			mlx_put_pixel(data->img, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
	return ;
}


void	scroll(double xdelta, double ydelta, void *param)
{
	t_data		*data;
	t_player	*player;
	double		rotSpeed;

	data = param;
	player = data->player; 
	rotSpeed = 0.3; //the constant value is in radians/second
	clear_frame(data);
	//rotate to the right
	if (ydelta > 0)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->dirx;
		player->dirx = player->dirx * cos(-rotSpeed) - player->diry * sin(-rotSpeed);
		player->diry = oldDirX * sin(-rotSpeed) + player->diry * cos(-rotSpeed);
		double oldPlaneX =player->planex;
		player->planex =player->planex * cos(-rotSpeed) - player->planey * sin(-rotSpeed);
		player->planey = oldPlaneX * sin(-rotSpeed) + player->planey * cos(-rotSpeed);
	}
	//rotate to the left
	if (ydelta < 0 && xdelta == 0)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->dirx;
		player->dirx = player->dirx * cos(rotSpeed) - player->diry * sin(rotSpeed);
		player->diry = oldDirX * sin(rotSpeed) + player->diry * cos(rotSpeed);
		double oldPlaneX =player->planex;
		player->planex =player->planex * cos(rotSpeed) - player->planey * sin(rotSpeed);
		player->planey = oldPlaneX * sin(rotSpeed) + player->planey * cos(rotSpeed);
	}
}

void	moves(mlx_key_data_t keydata, void *param)
{
	t_data		*data;
	t_player	*player;

	data = param;
	player = data->player; 

	clear_frame(data);

	//speed modifiers
	double moveSpeed = 0.8; //the constant value is in squares/second
	double rotSpeed = 0.3; //the constant value is in radians/second
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
	{
		if (data->input->map[(int)(player->x + player->dirx * moveSpeed)][(int)(player->y)] == '0')
			player->x += player->dirx * moveSpeed;
		if (data->input->map[(int)(player->x)][(int)(player->y + player->diry * moveSpeed)] == '0')
			player->y += player->diry * moveSpeed;
	}
	//move backwards if no wall behind you
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	{
		if (data->input->map[(int)(player->x - player->dirx * moveSpeed)][(int)(player->y)] == '0')
			player->x -= player->dirx * moveSpeed;
		if (data->input->map[(int)(player->x)][(int)(player->y - player->diry * moveSpeed)] == '0')
			player->y -= player->diry * moveSpeed;
	}
	// strave left
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	{
		if (data->input->map[(int)(player->x - player->diry * moveSpeed)][(int)(player->y)] == '0')
			player->x -= player->diry * moveSpeed;
		if (data->input->map[(int)(player->x)][(int)(player->y + player->dirx * moveSpeed)] == '0')
			player->y += player->dirx * moveSpeed;
	}
	// strave right
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	{
		if (data->input->map[(int)(player->x + player->diry * moveSpeed)][(int)(player->y)] == '0')
			player->x += player->diry * moveSpeed;
		if (data->input->map[(int)(player->x)][(int)(player->y - player->dirx * moveSpeed)] == '0')
			player->y -= player->dirx * moveSpeed;
	}
	//rotate to the right
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->dirx;
		player->dirx = player->dirx * cos(-rotSpeed) - player->diry * sin(-rotSpeed);
		player->diry = oldDirX * sin(-rotSpeed) + player->diry * cos(-rotSpeed);
		double oldPlaneX =player->planex;
		player->planex =player->planex * cos(-rotSpeed) - player->planey * sin(-rotSpeed);
		player->planey = oldPlaneX * sin(-rotSpeed) + player->planey * cos(-rotSpeed);
	}
	//rotate to the left
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->dirx;
		player->dirx = player->dirx * cos(rotSpeed) - player->diry * sin(rotSpeed);
		player->diry = oldDirX * sin(rotSpeed) + player->diry * cos(rotSpeed);
		double oldPlaneX =player->planex;
		player->planex =player->planex * cos(rotSpeed) - player->planey * sin(rotSpeed);
		player->planey = oldPlaneX * sin(rotSpeed) + player->planey * cos(rotSpeed);
	}
}