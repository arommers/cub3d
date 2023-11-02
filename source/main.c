/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 13:04:05 by arommers      #+#    #+#                 */
/*   Updated: 2023/11/02 16:19:48 by parisasadeq   ########   odam.nl         */
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

	player = param;
	int	x;

	x = 0;
	// while (1)
	// {
		while(x < WIDTH)
		{
			//calculate ray position and direction
			double	cameraX = 2 * x / (double)(WIDTH) - 1; //x-coordinate in camera space
			double	rayDirX = player->dirX + player->planeX * cameraX;
			double	rayDirY = player->dirY + player->planeY * cameraX;
			// the box of the map that we are in
			player->mapX = (int)(player->x);
			player->mapY = (int)(player->y);

			// length of the ray from current position to next x or y side
			double	sideDistX;
			double	sideDistY;

			//length of the ray from one x or y side to next x or y side
			double	deltaDistX;
			double	deltaDistY;
			if (rayDirX == 0)
				deltaDistX = 1e30;
			else
				deltaDistX = fabs(1.0 / rayDirX);
			if (rayDirY == 0)
				deltaDistY = 1e30;
			else
				deltaDistY = fabs(1.0 / rayDirY);
			double	perpWallDist;

			//what direction to step in x or y direction (+1 or -1)
			int	stepX;
			int	stepY;

			int	hit = 0; //was there a wall hit?
			int	side; //was a NS or a EW wall hit?

			//calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (player->x - player->mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (player->mapX + 1.0 - player->x) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (player->y - player->mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (player->mapY + 1.0 - player->y) * deltaDistY;
			}
			while (hit == 0)
			{
				//jump to next map square, either in x-direction, or in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					player->mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					player->mapY += stepY;
					side = 1;
				}
				//Check if ray has hit a wall
				if (worldMap[player->mapX][player->mapY] > 0)
					hit = 1;
			}
			//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
			if(side == 0)
				perpWallDist = (sideDistX - deltaDistX);
			else
				perpWallDist = (sideDistY - deltaDistY);
			//Calculate height of line to draw on screen
			int lineHeight = (int)(HEIGHT / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + HEIGHT / 2;
			if (drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + HEIGHT / 2;
			if (drawEnd >= HEIGHT)
				drawEnd = HEIGHT - 1;
			//choose wall color
			switch(worldMap[player->mapX][player->mapY])
			{
				case 1:  player->color = ft_pixel(255, 0, 0, 255);  break; //red
				case 2:  player->color = ft_pixel(0, 255, 0, 255);  break; //green
				case 3:  player->color = ft_pixel(0, 0, 255, 255);   break; //blue
				case 4:  player->color = ft_pixel(255, 255, 255, 255);   break; //white
				default: player->color = ft_pixel(255, 255, 0, 255); break; //yellow
			}
			//give x and y sides different brightness
			if (side == 1)
			{
				player->color = player->color / 2;
			}

			//draw the pixels of the stripe as a vertical line
			while(drawStart < drawEnd)
			{
				bresenhams_line_draw(x, drawStart, x, drawStart + 1, player);
				drawStart++;
			}
			x++;
		}
	}
	// mlx_key_hook(mlx, &control_keys, player);
// 	printf("after here?\n");
// }

int main(int argc, char *argv[])
{
	mlx_t		*mlx;
	t_player	*player;
	// t_data      data;
	
	player = malloc(sizeof(t_player));
	player->x = 22; //x of start position
	player->y = 12; //y of start position
	player->dirX = -1; //initial direction vector
	player->dirY = 0; //initial direction vector
	player->planeX = 0; //the 2d raycaster version of camera plane
	player->planeY = 0.66; //the 2d raycaster version of camera plane
	player->angle = 66; //not sure if we need this
	player->time = 0;
	player->oldTime = 0;
	player->mapX = player->x;
	player->mapY = player->y;
	
	printf("are we even getting here?\n");
	put_data(argc, argv);
	
	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	player->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, player->img, 0, 0);
	//game_loop(player);
	mlx_loop_hook(mlx, &game_loop, player);
	mlx_key_hook(mlx, &control_keys, player);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
