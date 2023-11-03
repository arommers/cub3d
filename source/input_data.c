#include "../include/cub3d.h"

t_data	*texture_data(t_data *data, char *line)
{
	char	**path_data;
	char	*texture_path;

	path_data = ft_split(line, ' ');
	texture_path = path_data[1];
	if (line[0] == 'N' && line[1] == 'O')
	{
		printf("texture_path = %s\n", texture_path);
		data->no_texture = texture_path;
	}
	else if (line[0] == 'S' && line[1] == 'O')
	{
		printf("texture_path = %s\n", texture_path);
		data->so_texture = texture_path;
	}
	else if (line[0] == 'W' && line[1] == 'E')
	{
		printf("texture_path = %s\n", texture_path);
		data->we_texture = texture_path;
	}
	else if (line[0] == 'E' && line[1] == 'A')
	{
		printf("texture_path = %s\n", texture_path);
		data->ea_texture = texture_path;
	}
	free(path_data[0]);
	free(path_data[1]);
	free(path_data);
	return (data);
}

t_data	*f_c_colors(t_data *data, char *line)
{
	char	*before_split;
	char	**colors;

	before_split = ft_substr(line, 2, ft_strlen(line) - 2);
	colors = ft_split(before_split, ',');
	if (line[0] == 'F')
	{
		data->f_r = ft_atoi(colors[0]);
		data->f_g = ft_atoi(colors[1]);
		data->f_b = ft_atoi(colors[2]);
	}
	if (line[0] == 'C')
	{
		data->c_r = ft_atoi(colors[0]);
		data->c_g = ft_atoi(colors[1]);
		data->c_b = ft_atoi(colors[2]);
	}
	free(colors[0]);
	free(colors[1]);
	free(colors[2]);
	free(colors);
	free(before_split);
	return (data);
}

t_data	*texture_color_init(t_data *data, char *with_nl)
{
	char	*line;

	line = ft_strtrim(with_nl, "\n");
	//printf("after remove = %s", line);
	//free(with_nl);
	if (line[0] == 'F' || line[0] == 'C')
	{
		data = f_c_colors(data, line);
	}
	else
	{
		data = texture_data(data, line);
	}
	return (data);
}

t_data	*map_init(t_data *data, char *with_nl, int fd, int size_map)
{
	int		i;
	char	*line;

	i = 1;
	data->map = malloc(sizeof(char *) * (size_map + 1));
	line = ft_strtrim(with_nl, "\n");
	free(with_nl);
	data->map[0] = line;
	while (i < size_map)
	{
		with_nl = get_next_line(fd);
		line = ft_strtrim(with_nl, "\n");
		free(with_nl);
		data->map[i] = line;
		i++;
	}
	data->map[i] = NULL;
	i = 0;
	while (data->map[i] != NULL)
	{
		printf("data->map[%d] = %s\n", i, data->map[i]);
		i++;
	}
	return (data);
}

t_data	*put_data(int argc, char **argv)
{
	t_data	*data;
	int		fd;
	char	*line;
	int		count_line;
	int		file_lines;
	int		lines_left;

	count_line = 0;
	if (argc > 2 || argc == 1)
	{
		printf("put the right amount of input\n");
		return(NULL) ;
	}
	file_lines = line_counter(argv[1]);
	data = initialize_data_struct(data);
	fd = open(argv[1], O_RDONLY);
	while(1)
	{
		line = get_next_line(fd);
		//printf("line = %s\n", line);
		if (!line)
			return(NULL) ;
		if (strcmp(line, "\n") == 0)
		{
			count_line++;
			free(line);
			continue;
		}
		if ((line[0] >= 'C' && line[0] <= 'W'))
		{
			count_line++;
			data = texture_color_init(data, line);
		}
		else
			break;
		free(line);
	}
	lines_left = file_lines - count_line;
	data = map_init(data, line, fd, lines_left);
	if (check_data(data) != 0)
		return(NULL) ;
	return (data);
}
