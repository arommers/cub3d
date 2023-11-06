#include "../include/cub3d.h"

int	check_colors(t_input *input)
{
	t_input	*temp;

	temp = input;
	if (temp->f_r > 255 || temp->f_r < 0)
		return (1);
	if (temp->f_g > 255 || temp->f_g < 0)
		return (1);
	if (temp->f_b > 255 || temp->f_b < 0)
		return (1);
	if (temp->c_r > 255 || temp->c_r < 0)
		return (1);
	if (temp->c_g > 255 || temp->c_g < 0)
		return (1);
	if (temp->c_b > 255 || temp->c_b < 0)
		return (1);
	return (0);
}

int	check_map(t_input *input)
{
	t_input	*temp;
	int		i;
	int		j;

	temp = input;
	i = 0;
	j = 0;
	while (temp->map[i] != NULL)
	{
		while (temp->map[i][j] != '\0')
		{
			if (!(temp->map[i][j] == '0' || \
			temp->map[i][j] == '1' || temp->map[i][j] == ' ' \
			|| temp->map[i][j] == 'N' || temp->map[i][j] == 'S' || \
			temp->map[i][j] == 'W' || temp->map[i][j] == 'E'))
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

int	check_input(t_input *input)
{
	if (check_colors(input) != 0)
	{
		printf("colors should be in the range of 0 to 255\n");
		return (1);
	}
	if (check_map(input) != 0)
	{
		printf("map should only contain 0 or 1\n");
		return (1);
	}
	return (0);
}
