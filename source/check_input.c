#include "../include/cub3d.h"

int	check_colors(t_input *input)
{
	if (input->f_r > 255 || input->f_r < 0)
		return (1);
	if (input->f_g > 255 || input->f_g < 0)
		return (1);
	if (input->f_b > 255 || input->f_b < 0)
		return (1);
	if (input->c_r > 255 || input->c_r < 0)
		return (1);
	if (input->c_g > 255 || input->c_g < 0)
		return (1);
	if (input->c_b > 255 || input->c_b < 0)
		return (1);
	return (0);
}

int	check_map(t_input *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input->map[i] != NULL)
	{
		while (input->map[i][j] != '\0')
		{
			if (!(input->map[i][j] == '0' || \
			input->map[i][j] == '1' || input->map[i][j] == ' ' \
			|| input->map[i][j] == 'N' || input->map[i][j] == 'S' || \
			input->map[i][j] == 'W' || input->map[i][j] == 'E'))
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
