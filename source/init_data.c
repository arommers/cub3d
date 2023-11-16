/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_data.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: psadeghi <psadeghi@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/03 09:18:11 by arommers      #+#    #+#                 */
/*   Updated: 2023/11/16 16:07:27 by arommers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_data(t_data *data, mlx_t *mlx, mlx_image_t *img)
{
	data->x = 0;
	data->map = NULL;
	data->input = malloc(sizeof(t_input));
	if (!data->input)
		ft_error(data, "Malloc Failed");
	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
		ft_error(data, "Malloc Failed");
	data->ray->line = NULL;
	data->walls = malloc(6 * sizeof(t_wall));
	if (!data->walls)
		ft_error(data, "Malloc Failed");
	data->walls[0].tex = NULL;
	data->walls[1].tex = NULL;
	data->walls[2].tex = NULL;
	data->walls[3].tex = NULL;
	data->walls[4].tex = NULL;
	data->walls[5].tex = NULL;
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		ft_error(data, "Malloc Failed");
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!data->mlx)
		ft_error(data, "MLX42 Error");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		ft_error(data, "MLX42 Error");
	data->floor = malloc(sizeof(t_floor));
	data->ceiling = malloc(sizeof(t_floor));
}

char	player_pos(t_data *data)
{
	int		x;
	int		y;
	char	**map;

	x = 0;
	y = 0;
	printf("data->input->map[0] = %s\n", data->input->map[0]);
	map = data->input->map;
	while (map[y] != NULL)
	{
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'E' || map[y][x] == 'W' || \
			map[y][x] == 'N' || map[y][x] == 'S')
			{
				data->player->x = (double)y + 0.5;
				printf("x = %d and y = %d\n", x, y);
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

void	player_direction(t_data *data, char dir)
{
	printf("Player direction %c\n", dir);
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

void	init_player(t_data *data)
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

void	init_line(t_line *line)
{
	line->line_height = 0;
	line->draw_start = 0;
	line->draw_end = 0;
}