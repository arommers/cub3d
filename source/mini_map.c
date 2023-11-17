/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/17 12:17:22 by arommers      #+#    #+#                 */
/*   Updated: 2023/11/17 14:42:23 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	make_mm_img(t_data *data)
{

	data->m_map = mlx_new_image(data->mlx, MMS * WIDTH, MMS * HEIGHT);
	if (!data->m_map)
		ft_error(data, "MLX42 Error");
	// data->tile = mlx_new_image(data->mlx, MMS * 64, MMS * 64);
	// if (!data->tile)
	// 	ft_error(data, "MLX42 Error");
	// data->dot = mlx_new_image(data->mlx, 14, 14);
	// if (!data->dot)
	// 	ft_error(data, "MLX42 Error");
}

void	make_map(mlx_image_t *m_map)
{
	int32_t	color;
	int		x;
	int		y;

	color = ft_pixel(0, 0, 0, 255);
	y = 0;
	while (y < MMS * HEIGHT - 1)
	{
		x = 0;
		while (x < MMS * WIDTH - 1)
		{
			mlx_put_pixel(m_map, x, y, color);
			x++;
		}
		y++;
	}
}

// void	make_tile(mlx_image_t *tile)
// {
// 	int32_t	color;
// 	int		x;
// 	int		y;

// 	color = ft_pixel(255, 255, 255, 255);
// 	y = 0;
// 	while (y < MMS * 64 - 1)
// 	{
// 		x = 0;
// 		while (x < MMS * 64 - 1)
// 		{
// 			mlx_put_pixel(tile, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }


void	draw_mm(t_data *data)
{
	// int		x;
	// int		y;

	// y = 0;
	make_map(data->m_map);
	// make_tile(data->tile);
	mlx_image_to_window(data->mlx, data->m_map, 0, 0);
	// while (y < MMS * HEIGHT - 1)
	// {
	// 	x = 0;
	// 	while (x < MMS * WIDTH -1)
	// 	{
	// 		printf("test\n");
	// 		if (data->input->map[x][y] == '1')
	// 		{
	// 			mlx_image_to_window(data->mlx, data->tile,
	// 				x * MMS, y * MMS);
	// 		}
	// 		x++;
	// 	}
	// 	y++;
	// }
}

