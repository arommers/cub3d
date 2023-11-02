#include "../include/cub3d.h"

void	color_as_bg(t_player *player)
{
	int			x;
	int			y;
	uint32_t	color;

	color = ft_pixel(0x00, 0x00, 0x00, 0x00);
	x = 0;
	y = 0;
	while (y <= HEIGHT)
	{
		while (x <= WIDTH)
		{
			mlx_put_pixel(player->img, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
	return ;
}

void	control_keys(mlx_key_data_t keydata, void *param)
{
	t_player	*player;

	player = param;

	//timing for input and FPS counter
	color_as_bg(player);

	//speed modifiers
	double moveSpeed = 0.8; //the constant value is in squares/second
	double rotSpeed = 0.3; //the constant value is in radians/second
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		if (worldMap[(int)(player->x + player->dirX * moveSpeed)][(int)(player->y)] == 0)
			player->x += player->dirX * moveSpeed;
		if (worldMap[(int)(player->x)][(int)(player->y + player->dirY * moveSpeed)] == 0)
			player->y += player->dirY * moveSpeed;
		//game_loop(player);
	}
	//move backwards if no wall behind you
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		if (worldMap[(int)(player->x - player->dirX * moveSpeed)][(int)(player->y)] == 0)
			player->x -= player->dirX * moveSpeed;
		if (worldMap[(int)(player->x)][(int)(player->y - player->dirY * moveSpeed)] == 0)
			player->y -= player->dirY * moveSpeed;
	}
	//rotate to the right
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->dirX;
		player->dirX = player->dirX * cos(-rotSpeed) - player->dirY * sin(-rotSpeed);
		player->dirY = oldDirX * sin(-rotSpeed) + player->dirY * cos(-rotSpeed);
		double oldPlaneX =player->planeX;
		player->planeX =player->planeX * cos(-rotSpeed) - player->planeY * sin(-rotSpeed);
		player->planeY = oldPlaneX * sin(-rotSpeed) + player->planeY * cos(-rotSpeed);
	}
	//rotate to the left
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = player->dirX;
		player->dirX = player->dirX * cos(rotSpeed) - player->dirY * sin(rotSpeed);
		player->dirY = oldDirX * sin(rotSpeed) + player->dirY * cos(rotSpeed);
		double oldPlaneX =player->planeX;
		player->planeX =player->planeX * cos(rotSpeed) - player->planeY * sin(rotSpeed);
		player->planeY = oldPlaneX * sin(rotSpeed) + player->planeY * cos(rotSpeed);
	}
}
