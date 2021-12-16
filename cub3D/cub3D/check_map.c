#include "cub3D.h"

static char	*clear_tabs(char *str)
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

static void	get_char(char c, t_data *data, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W' )
		data->params->pos++;
	else if (c == 'C')
		data->params->coin++;
	else if (c == 'X')
		data->params->enemy++;
	else if (c == '1' || c == '0')
		return ;
	if (data->params->pos)
	{
		data->params->x = i;
		data->params->y = j;
	}
	else if (data->params->coin)
	{
		data->params->coin_pos_x = i;
		data->params->coin_pos_y = j;
	}
}

int	check_string(char *str, int j, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1' || str[i] == '0' || str[i] == 'N' || str[i] == 'S'
			|| str[i] == 'E' || str[i] == 'W' || str[i] == 'C' || str[i] == 'X')
		{
			get_char(str[i], data, j, i);
			i++;
		}
		else if (str[i] == ' ') // && str[i - 1] == '1')
		{
			while (str[i])
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

void	check_r_map(char **map, int size, int j)
{
	int		i;

	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				while (map[i][j] == ' ')
					j++;
			if (map[i][j] == '1' && (map[i][ft_strlen(map[i]) - 1] == '1'
						|| map[i][ft_strlen(map[i]) - 1] == ' '))
			{
				if (!check_string(map[i], j, NULL))
					break ;
				else
					ft_error(MAP_ERROR);
			}
			else
				ft_error(MAP_ERROR);
		}
	}
}

void	add_space(char *str, int max_len)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = malloc(sizeof(char) * (max_len + 1));
	while (++i < ft_strlen(str))
	{
		tmp[i] = str[i];
		tmp[i + 1] = '\0';
	}
	while (i < max_len)
	{
		tmp[i] = ' ';
		tmp[i + 1] = '\0';
		i++;
	}
	free (str);
	str = ft_strdup(tmp);
	free(tmp);
}
//
//void	check_hole(char **map, int i, int j)
//{
//	int x;
//	int y;
//
//	x = i;
//	y = j;
//	while(map[x])
//	{
//		y = j;
//		while (map[x][y])
//		{
//
//		}
//	}
//}

int	check_left(char *str, int i)
{
	while (i)
	{
		if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i--;
			if (str[i] == '1' && i >= 0)
				break ;
			else
				return (1);
		}
		else
			break ;
	}
	return (0);
}

int	check_right(char *str, int i, int len)
{
	while (str[i])
	{
		if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i++;
			if (str[i] == '1' && i <= len)
				break ;
			else
				return (1);
		}
		else
			break ;
	}
	return (0);
}

int	check_walls(char *str, int i)
{
	int len;

	len = (int)ft_strlen(str) - 1;
	if (str[len] != '1')
		while (str[len] != '1')
			len--;
	if (check_left(str, i) || check_right(str, i, len))
		ft_error(MAP_ERROR);
	return (0);
}

//int	holes_count(char *str, int i)
//{
//	int	holes;
//
//	holes = 0;
//	while(str[i])
//	{
//		j = 0;
//	}
//
//	return (holes);
//}
//
//int	is_hole(char **map, int size, int len, int flag)
//{
//	int		i;
//	int		j;
//
//	i = 0;
//	j = 0;
//	while (map[i])
//	{
//		j = 0;
//		while (map[i][j])
//		{
//			holes_count(map[i], i);
//			if (map[i][j] == ' ')
//				check_walls(map[i], j);
//			j++;
//		}
//		i++;
//	}
//	return (0);
//}

char 	**tmp_map(char **map, int size)
{
	int		i;
	int		j;
	char	**tmp;

	tmp = malloc(sizeof(char *) * (size + 1));
	i = -1;
	j =  0;
	while (map[++i])
	{
		j = 0;
		while(j <= ft_strlen(map[i]))
		{
			if(map[i][j] == '\0')
			{
				tmp[i] = ft_strdup(map[i]);
				break ;
			}
			if (map[i][j] != ' ')
				j++;
			else
			{
				tmp[i] = ft_substr(map[i], 0, j);
				break ;
			}
		}
	}
	tmp[i] = NULL;
	return (tmp);
}

//void	check_hole (char **map, int i, int j)
//{
//	int	x;
//	int	y;
//	int	flag;
//
//	flag = 0;
//	x = i;
//	y = j;
//	if (!flag)
//	{
//		while(map[x][y])
//		{
//			if (map[x + 1][y] == ' ')
//				x++;
//			else
//			{
//				while(map[x][y - 1] != '1' && y)
//					y--;
//				if (!y)
//					ft_error(MAP_ERROR);
//				else
//					flag = 1;
//			}
//
//		}
//	}
//	else
//
//}

//void	hole(char **map)
//{
//	int i;
//	int j;
//
//	i = 0;
//	j = 0;
//	while(map[i])
//	{
//		while(map[i][j])
//		{
//			if (map[i][j] == ' ')
//				check_hole(map, i, j);
//			j++;
//		}
//		i++;
//	}
//}

char	**check_map(char **map, t_data *data, int size, int len)
{
	int		i;
//	int		j;
//	char	**tmp;
	int		flag;

	i = -1;
	flag = 1;
	while (map[++i])
	{
		if (ft_strchr(map[i], '\t'))
			map[i] = clear_tabs(map[i]);
//		if (ft_strlen(map[i]) < len)
//			add_space(map[i], len);
	}
//	tmp = tmp_map(map, size);
//	hole(map);
//	i = -1;
//	while(++i < size)
//	{
//		printf("%s \t \t\t\t......... \t \t%s\n", tmp[i], map[i]);
//		if (ft_strlen(tmp[i]) == ft_strlen(map[i]))
//		{
//			flag = 0;
//			break ;
//		}
//	}



//	i = -1;
//	while (map[++i])
//		printf("%s\n", map[i]);
//	is_hole(map, size, len);

//	while (map[i][j])
//	{
//		if (map[i][j] == ' ' && j != ft_strlen(map[i]))
//		{
//			if ()
//
//			else
//
//		}
//		j++;
//			if (map[i][j] == ' ')
//			{
//				while (map[i][j] == ' ')
//					j++;
//				trim_start = ft_substr(map[i], 0, j);
//				j = (int)ft_strlen(map[i]);
//				if (map[i][j - 1] == ' ')
//				{
//					j--;
//					while (map[i][j] == ' ')
//						j--;
//				}
//				trim_end = ft_substr(map[i], j + 1, ft_strlen(map[i]));
//				map[i] = ft_strtrim(map[i], trim_start);
//				free (trim_start);
//				map[i] = ft_strtrim(map[i], trim_end);
//				free(trim_end);
//			}
//			if (map[i][0] == '1' && map[i][ft_strlen(map[i]) - 1] == '1')
//			{
//				if (!check_string(map[i], ++j, data))
//					break ;
//			}
//			else
//				ft_error(MAP_ERROR);
//	}

	i = -1;
	while (map[++i])
		check_string(map[i], i, data);
	return (map);
}
