/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psadeghi <psadeghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:59:35 by arommers          #+#    #+#             */
/*   Updated: 2023/11/20 11:23:16 by psadeghi         ###   ########.fr       */
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
}

void	scroll(double xdelta, double ydelta, void *param)
{
	t_data		*data;
	double		rot;

	data = param;
	rot = 0.2;
	clear_frame(data);
	if (ydelta > 0)
		scroll_left(data, rot);
	if (ydelta < 0 && xdelta == 0)
		scroll_right(data, rot);
}

void	controls(mlx_key_data_t keydata, void *param)
{
	t_data		*data;
	t_player	*player;
	double		move;
	double		rot;

	data = param;
	player = data->player;
	move = 0.8;
	rot = 0.3;
	clear_frame(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	move_up_down(keydata, data, move);
	move_left_right(keydata, data, move);
	rot_left_right(keydata, data, rot);
}
