/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/03 09:18:11 by arommers      #+#    #+#                 */
/*   Updated: 2023/11/20 12:05:48 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*	- Initializes a t_data struct
	- Sets initial values for its members
	- Allocating memory for nested struct */

void	init_data(t_data *data)
{
	data->x = 0;
	data->y = 0;
	data->map = NULL;
	data->input = malloc(sizeof(t_input));
	if (!data->input)
		ft_error(data, "Malloc Failed");
	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
		ft_error(data, "Malloc Failed");
	data->ray->line = NULL;
	data->walls = malloc(4 * sizeof(t_wall));
	if (!data->walls)
		ft_error(data, "Malloc Failed");
	init_walls(data->walls);
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		ft_error(data, "Malloc Failed");
}

/*	- Searches the input map for the player's initial position
	  denoted by 'E', 'W', 'N', or 'S'
	- Sets the player's coordinates (x and y)
	  and returns the corresponding cardinal direction */

char	player_pos(t_data *data)
{
	int		x;
	int		y;
	char	**map;

	x = 0;
	y = 0;
	map = data->input->map;
	while (map[y] != NULL)
	{
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'E' || map[y][x] == 'W' ||
			map[y][x] == 'N' || map[y][x] == 'S')
			{
				data->player->x = (double)y + 0.5;
				data->player->y = (double)x + 0.5;
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

/*	- Sets the player's direction vector (dirx and diry)
	  based on the provided cardinal direction */

void	player_direction(t_data *data, char dir)
{
	if (dir == 'E')
	{
		data->player->dirx = 0;
		data->player->diry = 1;
	}
	else if (dir == 'W')
	{
		data->player->dirx = 0;
		data->player->diry = -1;
	}
	else if (dir == 'N')
	{
		data->player->dirx = -1;
		data->player->diry = 0;
	}
	else if (dir == 'S')
	{
		data->player->dirx = 1;
		data->player->diry = 0;
	}
}

/*	- initializes the player's direction and camera plan vectors
	- It determines the player's initial direction using player_pos
	  and then calculates the perpendicular camera plane vectors (planex and planey)
	  based on the player's direction
	- The planeRatio is used to control the width of the view plane */

void	init_player(t_data *data)
{
	char	player_dir;
	double	planeratio;
	double	dirlength;

	player_dir = player_pos(data);
	player_direction(data, player_dir);
	planeratio = 0.66;
	dirlength = sqrt(data->player->dirx * data->player->dirx
			+ data->player->diry * data->player->diry);
	data->player->planex = data->player->diry / dirlength * planeratio;
	data->player->planey = -data->player->dirx / dirlength * planeratio;
}

/*	- Sets initial values for ray struct members*
	- Allocates memory for the nested line struct */

void	init_ray(t_data *data)
{
	t_ray	*tmp;

	tmp = data->ray;
	tmp->mapx = 0;
	tmp->mapy = 0;
	tmp->stepx = 0;
	tmp->stepy = 0;
	tmp->side = 0;
	tmp->wall = 0;
	tmp->camera_x = 0.0;
	tmp->dirx = 0.0;
	tmp->diry = 0.0;
	tmp->init_dist_x = 0.0;
	tmp->init_dist_y = 0.0;
	tmp->delta_dist_x = 0.0;
	tmp->delta_dist_y = 0.0;
	tmp->perp_wall_dist = 0.0;
	tmp->line = malloc(sizeof(t_line));
	if (!tmp->line)
		ft_error(data, "Malloc Failed");
	init_line(data->ray->line);
}
