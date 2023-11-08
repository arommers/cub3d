#include "../include/cub3d.h"

t_input	*texture_data(t_input *input, char *line)
{
	char	**path_data;
	char	*texture_path;

	path_data = ft_split(line, ' ');
	texture_path = path_data[1];
	if (line[0] == 'N' && line[1] == 'O')
	{
		printf("texture_path = %s\n", texture_path);
		input->no_texture = texture_path;
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		printf("texture_path = %s\n", texture_path);
		input->so_texture = texture_path;
	}
	else if (line[0] == 'W' && line[1] == 'E')
	{
		printf("texture_path = %s\n", texture_path);
		input->we_texture = texture_path;
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		printf("texture_path = %s\n", texture_path);
		input->ea_texture = texture_path;
	}
	free(path_data[0]);
	free(path_data[1]);
	free(path_data);
	return (input);
}

t_input	*f_c_colors(t_input *input, char *line)
{
	char	*before_split;
	char	**colors;

	before_split = ft_substr(line, 2, ft_strlen(line) - 2);
	colors = ft_split(before_split, ',');
	if (line[0] == 'F')
	{
		input->floor_color = true;
		input->f_r = ft_atoi(colors[0]);
		input->f_g = ft_atoi(colors[1]);
		input->f_b = ft_atoi(colors[2]);
	}
	if (line[0] == 'C')
	{
		input->ceiling_color = true;
		input->c_r = ft_atoi(colors[0]);
		input->c_g = ft_atoi(colors[1]);
		input->c_b = ft_atoi(colors[2]);
	}
	free(colors[0]);
	free(colors[1]);
	free(colors[2]);
	free(colors);
	free(before_split);
	return (input);
}

t_input	*texture_color_init(t_input *input, char *with_nl)
{
	char	*line;

	line = ft_strtrim(with_nl, "\n");
	if (line[0] == 'F' || line[0] == 'C')
	{
		input = f_c_colors(input, line);
	}
	else
	{
		input = texture_data(input, line);
	}
	return (input);
}

t_input	*map_init(t_input *input, char *with_nl, int fd, int size_map)
{
	int		i;
	char	*line;
	t_input	*temp;

	i = 1;
	if (!with_nl)
	{
		printf("there is no map!\n");
		exit (1);
	}
	input->map = malloc(sizeof(char *) * (size_map + 1));
	temp = input;
	line = ft_strtrim(with_nl, "\n");
	free(with_nl);
	temp->map[0] = line;
	printf("temp->map[0] = %s\n", temp->map[0]);
	while (i < size_map)
	{
		with_nl = get_next_line(fd);
		line = ft_strtrim(with_nl, "\n");
		free(with_nl);
		temp->map[i] = line;
		i++;
	}
	temp->map[i] = NULL;
	i = 0;
	while (temp->map[i] != NULL)
	{
		printf("temp->map[%d] = %s\n", i, temp->map[i]);
		i++;
	}
	return (input);
}

t_input	*input_data(int argc, char **argv, t_input *input, t_data *data)
{
	int		fd;
	char	*line;
	int		count_line;
	int		file_lines;
	int		lines_left;

	input = malloc(sizeof(t_input));
	count_line = 0;
	file_lines = line_counter(argv[1]);
	input = initialize_data_struct(input);
	fd = open(argv[1], O_RDONLY);
	while(1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (strcmp(line, "\n") == 0)
		{
			count_line++;
			free(line);
			continue;
		}
		if ((line[0] >= 'C' && line[0] <= 'W'))
		{
			count_line++;
			input = texture_color_init(input, line);
			printf("1 are we getting here? line = %s\n", line);
		}
		else
			break;
		free(line);
	}
	lines_left = file_lines - count_line;
	if (!line)
	{
		if (lines_left == 0)
			printf("invalid map\n");
		else
			printf("allocation failed!\n");
		exit (1);
	}
	if (input->no_texture == NULL || input->so_texture == NULL || input->ea_texture == NULL || input->we_texture == NULL || input->ceiling_color == false || input->floor_color == false)
	{
		printf("Invalid map!\n");
		exit (1);
	}
	input = map_init(input, line, fd, lines_left);
	if (check_input(input, lines_left) != 0)
		return(NULL) ;
	data->input = input;
	return (input);
}
