#include "../include/cub3d.h"

t_player	*input_player(t_player *player, int argc, char **argv)
{
	player = malloc(sizeof(t_player));
	if (!player)
	{
		printf("Allocation failed!\n");
		exit (1);
	}
	player->x = 22; //x of start position
	player->y = 12; //y of start position
	player->dirX = 1; //initial direction vector
	player->dirY = 0; //initial direction vector
	player->planeX = 0; //the 2d raycaster version of camera plane
	player->planeY = 0.66; //the 2d raycaster version of camera plane
	player->mapX = player->x;
	player->mapY = player->y;
	player->data = put_data(argc, argv);
	return (player);
}

void	init_deltaDist(t_player *player)
{
	if (player->rayDirX == 0)
		player->deltaDistX = 1e30;
	else
		player->deltaDistX = fabs(1.0 / player->rayDirX);
	if (player->rayDirY == 0)
		player->deltaDistY = 1e30;
	else
		player->deltaDistY = fabs(1.0 / player->rayDirY);
}

void	init_sideDist(t_player *player)
{
	//calculate step and initial sideDist
	if (player->rayDirX < 0)
	{
		player->stepX = -1;
		player->sideDistX = (player->x - player->mapX) * player->deltaDistX;
	}
	else
	{
		player->stepX = 1;
		player->sideDistX = (player->mapX + 1.0 - player->x) * player->deltaDistX;
	}
	if (player->rayDirY < 0)
	{
		player->stepY = -1;
		player->sideDistY = (player->y - player->mapY) * player->deltaDistY;
	}
	else
	{
		player->stepY = 1;
		player->sideDistY = (player->mapY + 1.0 - player->y) * player->deltaDistY;
	}
}

void	prev_fisheye(t_player *player)
{
	//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
	if (player->side == 0)
		player->perpWallDist = (player->sideDistX - player->deltaDistX);
	else
		player->perpWallDist = (player->sideDistY - player->deltaDistY);
}
