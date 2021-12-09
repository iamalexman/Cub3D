#include "cub3D.h"

void	ft_error(int key)
{
	write (1, "Error: ", 7);
	if (key == 100)
		write(1, "FILE_ERROR\n", 11);
	else if (key == 101)
		write (1, "MAP_ERROR\n", 10);
	else if (key == 102)
		write (1, "MALLOC_ERROR\n", 13);
	else if (key == 103)
		write (1, "READ_ERROR\n", 11);
	else
		write (1, "COMMON_ERROR\n", 13);
	exit(0);
}

void	init(t_data **data, t_texs **texs, t_colors **colors)
{
	*data = malloc(sizeof(t_data*));
	*texs = malloc(sizeof(t_texs*));
	*colors = malloc(sizeof(t_colors*));
	if (!data || !texs || !colors)
		ft_error(MALLOC_ERROR);
	(*data)->move = 0;
	(*data)->map = NULL;
	(*texs)->ea = NULL;
	(*texs)->no = NULL;
	(*texs)->so = NULL;
	(*texs)->we = NULL;
	(*data)->texs = *texs;
	(*colors)->cell = NULL;
	(*colors)->floor = NULL;
	(*data)->colors = *colors;
}

int	ft_close(t_data *data)
{
	mlx_clear_window(data->mlx, data->mlx_win);
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit (0);
}

void	ft_send_key(int key, t_data *data)
{
	if (key == W)
		data->move = W;
	else if (key == S)
		data->move = S;
	else if (key == A)
		data->move = A;
	else if (key == D)
		data->move = D;
	else if (key == ESC)
		ft_close(data);
}

void	ft_make_images(t_data *data)
{
	(void)data;
}

int	ft_action()
{

	return (0);
}

int	ft_press_buttons(int key, t_data *data)
{
	ft_send_key(key, data);
	printf("%d\n", key);
	return (key);
}

void	mlx_data_init(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WINDOW_X, WINDOW_Y, "Cub3D");
	data->move = 0;
	data->map = NULL;
}

void	run(t_data *data)
{
	mlx_data_init(data);
	mlx_loop_hook(data->mlx, ft_action, data);
	mlx_hook(data->mlx_win, 17, 0, ft_close, data);;
	mlx_hook(data->mlx_win, 02, (1L << 2), ft_press_buttons, data);
	ft_make_images(data);
	mlx_loop(data->mlx);
}

int	check(char *filename)
{
	int	len;

	len = (int)ft_strlen(filename);
	if ((filename[len - 4] != '.') || (filename[len - 3] != 'c')
		|| (filename[len - 2] != 'u') || (filename[len - 1] != 'b'))
		return (1);
	return (0);
}

t_rgb	*rgb_init(t_rgb *rgb)
{
	rgb = malloc(sizeof(t_rgb));
	if (!rgb)
		ft_error(MALLOC_ERROR);
	rgb->r = -1;
	rgb->g = -1;
	rgb->b = -1;
	return (rgb);
}

t_rgb	*make_colors(char *str, t_data *data, char flag)
{
	int		i;
	int		j;
	t_rgb	*rgb;

	i = 0;
	rgb = NULL;
	rgb = rgb_init(rgb);
	while(str[i])
	{
		if (ft_isdigit(str[i]))
		{
			j = i;
			while(ft_isdigit(str[j]))
				j++;
			if (rgb->r < 0)
				rgb->r = ft_atoi_rgb(ft_substr(str, i, j - i));
			else if (rgb->g < 0)
				rgb->g = ft_atoi_rgb(ft_substr(str, i, j - i));
			else if (rgb->b < 0)
				rgb->b = ft_atoi_rgb(ft_substr(str, i, j - i));
			else
				break ;
			i = j;
		}
		else if (str[i] == ',')
			i++;
		else
			ft_error(MAP_ERROR);
	}
	return (rgb);
}

void	get_colors(int i, char *line, t_data *data, char flag)
{
	int		j;
	int		dot;

	i++;
	dot = 1;
	while(line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (ft_isdigit(line[i]))
		{
			j = i;
			while (ft_isdigit(line[i]) || line[i] == ',')
			{
				if (line[i] == ',')
					dot++;
				i++;
			}
			if (flag == 'F')
				data->colors->floor = make_colors(ft_substr(line, j, i), data, flag);
			else if (flag == 'C')
				data->colors->cell = make_colors(ft_substr(line, j, i), data, flag);
			free(line);
			break ;
		}
		else
			ft_error(MAP_ERROR);
	}
}

char *get_str_texs(char *str, int i)
{
	int		j;
	int		len;

	j = i;
	len = (int)ft_strlen(str);
	while(str[++j])
		if (!ft_isalnum(str[j]) && str[j] != '_'
			&& str[j] != '/' && str[j] != '.')
			ft_error(MAP_ERROR);
	if (!ft_isalnum(str[len - 1]) && str[len - 1] != '/')
		ft_error(MAP_ERROR);
	return (ft_substr(str, i, len - i));
}

void	get_texts(int i , char *line, t_data *data, char *flag)
{
	int		j;

	j = i;
	while(line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '.' && line[i + 1] == '/')
		{
			while (line[j] && i != ' ')
				j++;
			if (!ft_strcmp(flag, "NO"))
				data->texs->no = get_str_texs(line, i);
			else if (!ft_strcmp(flag, "SO"))
				data->texs->so = get_str_texs(line, i);
			else if (!ft_strcmp(flag, "WE"))
				data->texs->we = get_str_texs(line, i);
			else if (!ft_strcmp(flag, "EA"))
				data->texs->ea = get_str_texs(line, i);
			break ;
		}
		else
			ft_error(MAP_ERROR);
	}
}

char	*clear_tabs(char *str)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
		{
			tmp = ft_substr(str, 0, i);
			tmp2 = ft_substr(str, i + 1, ft_strlen(str) - i);
			free(str);
			str = ft_strjoin(tmp, "    ");
			free(tmp);
			str = ft_strjoin(str, tmp2);
			free(tmp2);
		}
		i++;
	}
	return (str);
}

int		check_string (char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '1' || str[i] == '0' || str[i] == 'N' || str[i] == 'S'
			|| str[i] == 'E' || str[i] == 'W' || str[i] == 'C' || str[i] == 'X')
			i++;
		else if (str[i] == ' ' && str[i - 1] == '1')
		{
			while(str[i])
			{
				if (str[i] == '1')
					break ;
				else if (str[i] == ' ')
					i++;
				else
					ft_error(MAP_ERROR);
			}
		}
		else
			return (1);
	}
	return (0);
}

char	**check_map(char **map)
{
	int	i;
	int j;

	i = -1;
	while(map[++i])
	{
		j = 0;
		if (ft_strchr(map[i], '\t'))
			map[i] = clear_tabs(map[i]);
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				while (map[i][j] == ' ')
				j++;
			if (map[i][j] == '1' && map[i][ft_strlen(map[i]) - 1] == '1')
			{
				if (!check_string(map[i], ++j))
					break ;
			}
			else
				ft_error(MAP_ERROR);
		}
	}
	return (map);
}

void	check_r_map(char **map, int size, int len)
{
	int		i;

	i = -1;
	while (map[++i])
	{
		len = 0;
		while (map[i][len])
		{
			if (map[i][len] == ' ')
				while(map[i][len] == ' ')
					len++;
			if (map[i][len] == '1' && (map[i][ft_strlen(map[i]) - 1] == '1'
				|| map[i][ft_strlen(map[i]) - 1] == ' '))
			{
				if (!check_string(map[i], len))
					break ;
				else
					ft_error(MAP_ERROR);
			}
			else
				ft_error(MAP_ERROR);
		}
	}
}

void	free_map(char **map)
{
	int		i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map[i]);
}

void	rot_map(char **map, int len, int size)
{
	char	**r_map;
	int		i;
	int		j;
	int 	x;

	i = 0;
	j = len;
	r_map = (char **)malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		if (map[j])
		{
			x = 0;
			r_map[i] = malloc(sizeof(char) * (len + 1));
			while (j >= 0)
				r_map[i][x++] = map[j--][i];
			i++;
			j = len;
		}
		else
			j--;
	}
	r_map[i] = NULL;
	check_r_map(r_map, len, size);
	free_map(r_map);	 // переписать на стек или доделать фри с кучей
	free(r_map); 		// переписать на стек или доделать фри с кучей
}

void	rotate_map(char **map, int len, int size)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) < size)
		{
			j = (int)ft_strlen(map[i]);
			while (j < size)
			{
				map[i][j] = ' ';
				j++;
			}
		}
		else
			i++;
	}
	rot_map(map, len, size);
}

void	get_map(int i, char **file, t_data *data)
{
	char	**map;
	int		size;
	int		len;
	int		j;

	j = 0;
	size = 0;
	while (file[++i])
		size++;
	map = malloc(sizeof(char *) * (size + 1));
	i -= size;
	while (file[i])
		map[j++] = ft_strdup(file[i++]);
	map[j] = NULL;
	map = check_map(map);
	i = -1;
	j = 0;
	len = (int)ft_strlen(map[0]);
	while(map[++i])
	{
		j = (int)ft_strlen(map[i]);
		if (j > len)
			len = j;
	}
	rotate_map(map, size, len);
	data->map = map;/////////////////////////////////////////////check map
}

int	find_map(int i, char **file, t_data *data)
{
	int	j;

	while(file[++i])
	{
		j = 0;
		while (file[i][j])
		{
			if (file[i][j] == '1')
			{
				get_map(i - 1, file, data);
				break ;//сделать нормальный выход из цикла
			}
			else
				j++;
		}
		if (data->map)
			break ;
	}
	return (0);
}

void parse_line(t_data *data, char **file, int *i, int *j)
{
	while(file[++(*i)])
	{
		*j = 0;
		while(file[*i][*j])
		{
			if (file[*i][*j] == ' ')
				while(file[*i][*j] == ' ')
					(*j)++;
			if (file[*i][*j] == 'N' && file[*i][*j + 1] == 'O')
				get_texts(*j + 2, file[*i], data, "NO");
			else if (file[*i][*j] == 'S' && file[*i][*j + 1] == 'O')
				get_texts(*j + 2, file[*i], data, "SO");
			else if (file[*i][*j] == 'E' && file[*i][*j + 1] == 'A')
				get_texts(*j + 2, file[*i], data, "EA");
			else if (file[*i][*j] == 'W' && file[*i][*j + 1] == 'E')
				get_texts(*j + 2, file[*i], data, "WE");
			else if (file[*i][*j] == 'F') //добавить разрядность не более 3х
				get_colors(*j, file[*i], data, 'F');
			else if (file[*i][*j] == 'C') //добавить разрядность не более 3х
				get_colors(*j, file[*i], data, 'C');
			break ;//check this maybe need change to return/error
		}
		if (data->colors->floor && data->colors->cell && data->texs->no
			&& data->texs->ea && data->texs->so && data->texs->we)
		{
			find_map(*i, file, data);
			break ;
		}
//		else
//			ft_error(FILE_ERROR);
	}
}

void	check_params(t_data *data,  char **file)
{
	int		i;
	int		j;

	j = 0;
	i = -1;
	parse_line(data, file, &i, &j);
}

//void	check_map(t_data *data,  char **argv)
//{
//
//}

//void	get_map(t_data *data,  char **argv)
//{
//
//}

int	file_size(t_data *data, int out, char *argv)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(argv, O_RDONLY);
	while (out > 0)
	{
		out = get_next_line(fd, &line);
		if (out < 0)
			ft_error(READ_ERROR);
		free(line);
		i++;
	}
	line = NULL;
	close(fd);
	return (i);
}

void	parse(t_data *data, char *argv)
{
	int		i;
	int		fd;
	int		out;
	char	**file;

	i = 0;
	out = 1;
	file = malloc(sizeof(char *) * (file_size(data, out, argv) + 1));
	if (!file)
		ft_error(MALLOC_ERROR);
	fd = open(argv, O_RDONLY);
	while (out > 0)
	{
		out = get_next_line(fd, &file[i]);
		if (out < 0)
			ft_error(READ_ERROR);
		i++;
	}
	file[i] = NULL;
	check_params(data, file);
	close(fd);
}

int	main(int argc, char **argv)
{
	t_data		*data;
	t_texs		*texs;
	t_colors	*colors;

	data = NULL;
	texs = NULL;
	colors = NULL;
	init(&data, &texs, &colors);
	if (argc > 1)
	{
		if (check(argv[1]))
			ft_error(FILE_ERROR);
		parse(data, argv[1]);
		run(data);
	}
	else
		ft_error(FILE_ERROR);
	return (0);
}

//обработать невалидные пути к тестурам (напр ./...asd/asd   asd/... (после парсера)
//обработать невалидные координаты (например больше 2х запятых (в парсере)
