/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/03 09:18:11 by arommers      #+#    #+#                 */
/*   Updated: 2023/11/10 12:24:15 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_data(t_data *data, mlx_t *mlx, mlx_image_t * img)
{
	data->input = NULL;
	data->map = NULL;
	data->ray = malloc(sizeof(t_ray));
	data->walls = malloc(4 * sizeof(t_wall));
	data->player = malloc(sizeof(t_player));
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
}

char	player_pos(t_data *data)
{
	int	x;
	int	y;
	char	**map;

	x = 0;
	y = 0;
	if (data->input == NULL)
		printf("i am empty\n");
	printf("data->input->map[0] = %s\n", data->input->map[0]);
	map = data->input->map;
	while (map[y] != NULL)
	{
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'E' || map[y][x] == 'W' || \
			map[y][x] == 'N' || map[y][x] == 'S')
			{
				data->player->x = x;
				printf("x = %d and y = %d\n", x, y);
				data->player->y = y;
				return (map[y][x]);
			}
			else
				x++;
		}
		x = 0;
		y++;
	}
	return (map[y][x]);
}


void	player_direction(t_data *data, char dir)
{
	printf("%c\n", dir);
	if (dir == 'N')
	{
		data->player->dirx = 0;
		data->player->diry = 1;
	}
	else if (dir == 'S')
	{
		data->player->dirx = 0;
		data->player->diry = -1;
	}
	else if (dir == 'W')
	{
		data->player->dirx = -1;
		data->player->diry = 0;
	}
	else if (dir == 'E')
	{
		data->player->dirx = 1;
		data->player->diry = 0;
	}
}

void init_player(t_data *data)
{
	char	player_dir;
	double	planeRatio;
	double	dirLength;

	player_dir = player_pos(data);
	player_direction(data, player_dir);
	planeRatio = 0.66; // specified length ratio
	// Calculate the length of the direction vector
	dirLength = sqrt(data->player->dirx * data->player->dirx \
	+ data->player->diry * data->player->diry);
	// Calculate the new planeX and planeY based on the ratio
	data->player->planex = data->player->diry / dirLength * planeRatio;
	data->player->planey = -data->player->dirx / dirLength * planeRatio;
}

void init_ray(t_ray *ray)
{
	ray->mapx = 0;
	ray->mapy = 0;
	ray->stepx = 0;
	ray->stepy = 0;
	ray->side = 0;
	ray->wall = 0;
	ray->camera_x = 0.0;
	ray->dirx = 0.0;
	ray->diry = 0.0;
	ray->init_dist_x= 0.0;
	ray->init_dist_y = 0.0;
	ray->delta_dist_x = 0.0;
	ray->delta_dist_y = 0.0;
	ray->perp_wall_dist = 0.0;
	ray ->line = malloc(sizeof(t_line));
	init_line(ray->line);
}

void init_line(t_line *line)
{
	line->line_height = 0;
	line->draw_start = 0;
	line->draw_end = 0;
}