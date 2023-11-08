#include "../include/cub3d.h"

void	check_wall_rightside(char var)
{
	if (var != '1')
	{
		printf("3 ERRROROROOROROROROOROR\n");
		exit (1);
	}
}
int	check_wall_spaces(char **map, int size_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i] != NULL)
	{
		while (map[i][j] != '\0')
		{
			if (map[i][j] == ' ')
			{
				if (i != size_map - 1 && !(map[i + 1][j] == ' ' || map[i + 1][j] == '1'))
				{
					printf("1 ERRROROROOROROROROOROR\n");
					exit (1);
				}
				if (i != 0 && !(map[i - 1][j] == ' ' || map[i - 1][j] == '1'))
				{
					printf("2 ERRROROROOROROROROOROR\n");
					exit (1);
				}
			}
			j++;
		}
		check_wall_rightside(map[i][j - 1]);
		j = 0;
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
			while(map[i][j] != '\0' && map[i][j] == ' ')
			{
				j++;
			}
			if (map[i][j] == '1')
				break;
			else
			{
				printf("4 ERRROROROOROROROROOROR\n");
				exit (1);
			}
		}
		j = 0;
		i++;
	}
	return (0);
}

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

int	check_map_char(t_input *input)
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
				printf("temp->map[i][j] = %c\n", temp->map[i][j]);
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	check_input(t_input *input, int size_map)
{
	if (check_colors(input) != 0)
	{
		printf("colors should be in the range of 0 to 255\n");
		exit(1);
	}
	if (check_map_char(input) != 0)
	{
		printf("invalid map\n");
		exit(1);
	}
	if (check_wall_spaces(input->map, size_map) != 0)
	{
		printf("!!oh no!!\n");
		exit (2);
	}
	if (check_wall_leftside(input->map) != 0)
	{
		printf("!!oh no!!\n");
		exit (2);
	}
	return (0);
}


void	check_args(int argc, char **argv)
{
	char	*cub_file;
	int		filename_size;

	filename_size = ft_strlen(argv[1]);
	if (argc > 2 || argc == 1)
	{
		printf("put the right amount of input\n");
		exit (1);
	}
	cub_file = ft_substr(argv[1], filename_size - 4, 4);
	if (ft_strncmp(cub_file, ".cub", 4) != 0)
	{
		printf("the file name is not valid!");
		free(cub_file);
		exit (1);
	}
	free(cub_file);
}
