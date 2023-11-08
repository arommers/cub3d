/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 13:04:05 by arommers      #+#    #+#                 */
/*   Updated: 2023/11/08 14:48:53 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int main(int argc, char *argv[])
{
	t_data		data;
	t_player	player;
	t_ray		ray;
	t_line		line;
	t_input		input;
	mlx_t		*mlx;
	mlx_image_t	*game_window;
	
	check_args(argc, argv);
	init_data(&data, &player, &ray);
	data.mlx = mlx;
	data.img = game_window;
	data.walls = ft_calloc(4, sizeof(t_wall));
	input_data(argc, argv, &input, &data);
	printf("are we after in mian\n");
	init_player(&data);
	init_ray(&ray, &line);
	init_line(&line);
	load_textures(&data);
	data.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	mlx_loop_hook(data.mlx, &game_loop, &data);
	mlx_key_hook(data.mlx, &moves, &data);
	mlx_scroll_hook(data.mlx, &scroll, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
