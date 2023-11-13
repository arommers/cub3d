/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psadeghi <psadeghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:18:48 by psadeghi          #+#    #+#             */
/*   Updated: 2023/11/13 17:19:30 by psadeghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_ws_horizontal(char **map, int i, int size_map)
{
	int	j;

	j = 0;
	while (map[i][j] != '\0')
	{
		if (map[i][j] == ' ')
		{
			if (i != size_map - 1 && \
			!(map[i + 1][j] == ' ' || map[i + 1][j] == '1'))
				return (1);
			if (i != 0 && !(map[i - 1][j] == ' ' || map[i - 1][j] == '1'))
				return (1);
		}
		j++;
	}
	if (map[i][j - 1] != '1')
		return (1);
	return (0);
}

int	check_wall_spaces(char **map, int size_map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		if (i < size_map && map[i][0] == '\0')
			return (1);
		if (check_ws_horizontal(map, i, size_map) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_wall_leftside(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		while (map[i][j] != '\0')
		{
			while (map[i][j] != '\0' && map[i][j] == ' ')
			{
				j++;
			}
			if (map[i][j] == '1')
				break ;
			else
				return (1);
		}
		j = 0;
		i++;
	}
	return (0);
}
