#include "../include/cub3d.h"

int	check_colors(t_data *data)
{
	if (data->f_r > 255 || data->f_r < 0)
		return (1);
	if (data->f_g > 255 || data->f_g < 0)
		return (1);
	if (data->f_b > 255 || data->f_b < 0)
		return (1);
	if (data->c_r > 255 || data->c_r < 0)
		return (1);
	if (data->c_g > 255 || data->c_g < 0)
		return (1);
	if (data->c_b > 255 || data->c_b < 0)
		return (1);
	return (0);
}

int	check_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i] != NULL)
	{
		while(data->map[i][j] != '\0')
		{
			if (!(data->map[i][j] == '0' || data->map[i][j] == '1' || data->map[i][j] == ' ' \
			|| data->map[i][j] == 'N' || data->map[i][j] == 'S' || \
			data->map[i][j] == 'W' || data->map[i][j] == 'E'))
			{
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	check_data(t_data *data)
{
	if (check_colors(data) != 0)
	{
		printf("colors should be in the range of 0 to 255\n");
		return (1);
	}
	if (check_map(data) != 0)
	{
		printf("map should only contain 0 or 1\n");
		return (1);
	}
	return (0);
}
