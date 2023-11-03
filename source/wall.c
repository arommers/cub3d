#include "../include/cub3d.h"

void	wall_color(t_player *player)
{
	//choose wall color
	switch(worldMap[player->mapX][player->mapY])
	{
		case 1:  player->color = ft_pixel(255, 0, 0, 255);  break; //red
		case 2:  player->color = ft_pixel(0, 255, 0, 255);  break; //green
		case 3:  player->color = ft_pixel(0, 0, 255, 255);   break; //blue
		case 4:  player->color = ft_pixel(255, 105, 180, 255);   break; //white
		default: player->color = ft_pixel(255, 255, 0, 255); break; //yellow
	}
	//give x and y sides different brightness
	if (player->side == 1)
		player->color = player->color / 2;
}

void	draw_wall(t_player *player, int x)
{
	//Calculate height of line to draw on screen
	player->lineHeight = (int)(HEIGHT / player->perpWallDist);
	//calculate lowest and highest pixel to fill in current stripe
	player->drawStart = -player->lineHeight / 2 + HEIGHT / 2;
	if (player->drawStart < 0)
		player->drawStart = 0;
	player->drawEnd = player->lineHeight / 2 + HEIGHT / 2;
	if (player->drawEnd >= HEIGHT)
		player->drawEnd = HEIGHT - 1;
	//draw the pixels of the stripe as a vertical line
	while(player->drawStart < player->drawEnd)
	{
		mlx_put_pixel(player->img, x, player->drawStart, player->color);
		player->drawStart++;
	}
}


void	till_hitting_wall(t_player *player)
{
	player->hit = 0;
	while (player->hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (player->sideDistX < player->sideDistY)
		{
			player->sideDistX += player->deltaDistX;
			player->mapX += player->stepX;
			player->side = 0;
		}
		else
		{
			player->sideDistY += player->deltaDistY;
			player->mapY += player->stepY;
			player->side = 1;
		}
		//Check if ray has hit a wall
		if (worldMap[player->mapX][player->mapY] > 0)
			player->hit = 1;
	}
}
