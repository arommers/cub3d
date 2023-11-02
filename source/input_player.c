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
	player->dirX = -1; //initial direction vector
	player->dirY = 0; //initial direction vector
	player->planeX = 0; //the 2d raycaster version of camera plane
	player->planeY = 0.66; //the 2d raycaster version of camera plane
	player->angle = 66; //not sure if we need this
	player->time = 0;
	player->oldTime = 0;
	player->mapX = player->x;
	player->mapY = player->y;
	player->data = put_data(argc, argv);
	return (player);
}
