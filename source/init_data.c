/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: arommers <arommers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/03 09:18:11 by arommers      #+#    #+#                 */
/*   Updated: 2023/11/03 14:15:06 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void init_data(t_data *data, t_player *player, t_ray *ray)
{
	data->player = player;
	data->ray = ray;
}

void	player_pos(t_data *data)
{
	int	x;
	int	y;
	char	**map;

	x = 0;
	y = 0;
	map = data->input->map;
	while (map[y] != NULL)
	{
		printf("here\n");
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'E' || map[y][x] == 'W' || \
			map[y][x] == 'N' || map[y][x] == 'S')
			{
				data->player->x = x;
				data->player->y = y;
				//write a function for giving the directions
				return ;
			}
			else
				x++;
		}
		x = 0;
		y++;
	}
}

void init_player(t_data *data)
{
	player_pos(data);
	// data->player->x = 22;
	// data->player->y = 12; 
	data->player->dirx = -1;
	data->player->diry = 0;
	data->player->planex = 0;
	data->player->planey = 0.66;
	data->player->angle = 66;
}

void init_ray(t_ray *ray, t_line *line)
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
	ray ->line = line;
}

void init_line(t_line *line)
{
	line->line_height = 0;
	line->draw_start = 0;
	line->draw_end = 0;
}