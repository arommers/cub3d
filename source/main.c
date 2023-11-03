/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 13:04:05 by arommers      #+#    #+#                 */
/*   Updated: 2023/11/02 22:14:52 by parisasadeq   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	game_loop(void	*param)
{
	t_player	*player;
	int			x;

	player = param;
	x = 0;
	while (x < WIDTH)
	{
		//calculate ray position and direction
		player->cameraX = 2 * x / (double)(WIDTH) - 1; //x-coordinate in camera space
		player->rayDirX = player->dirX + player->planeX * player->cameraX;
		player->rayDirY = player->dirY + player->planeY * player->cameraX;
		// the box of the map that we are in
		player->mapX = (int)(player->x);
		player->mapY = (int)(player->y);
		init_deltaDist(player);
		init_sideDist(player);
		till_hitting_wall(player);
		prev_fisheye(player);
		wall_color(player);
		draw_wall(player, x);
		x++;
	}
}

int main(int argc, char *argv[])
{
	mlx_t		*mlx;
	t_player	*player;
	
	player = input_player(player, argc, argv);
	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	player->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, player->img, 0, 0);
	mlx_loop_hook(mlx, &game_loop, player);
	mlx_key_hook(mlx, &control_keys, player);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
