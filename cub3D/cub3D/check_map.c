/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebalgruu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 13:40:45 by ebalgruu          #+#    #+#             */
/*   Updated: 2021/12/19 13:40:49 by ebalgruu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	*clear_tabs(char *str)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	i = -1;
	tmp = NULL;
	while (str[++i])
	{
		if (str[i] == '\t')
		{
			tmp = ft_substr(str, 0, i);
			tmp2 = ft_substr(str, i + 1, ft_strlen(str) - i);
			tmp3 = ft_strjoin(tmp, "    ");
			if (!tmp || !tmp2 || !tmp3)
				ft_error(MALLOC_ERROR);
			free(tmp);
			tmp = ft_strjoin(tmp3, tmp2);
			free(str);
			free(tmp2);
			free(tmp3);
			str = tmp;
		}
	}
	return (str);
}

void	get_char(char c, t_data *data, int i, int j)
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

char	*add_space(char *str, int max_len)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = malloc(sizeof(char) * (max_len + 1));
	while (i < (int)ft_strlen(str))
	{
		tmp[i] = str[i];
		i++;
	}
	while (i < max_len)
	{
		tmp[i] = ' ';
		i++;
	}
	tmp[i] = '\0';
	free (str);
	str = ft_strdup(tmp);
	free(tmp);
	return (str);
}

void	rot_map(char **map, int len, int size)
{
	char	**r_map;
	int		i;
	int		j;
	int		x;

	i = 0;
	j = len + 1;
	r_map = malloc(sizeof(char *) * (size));
	while (i < size)
	{
		if (map[--j])
		{
			x = 0;
			r_map[i] = malloc(sizeof(char) * (len));
			while (j >= 0)
				r_map[i][x++] = map[j--][i];
			r_map[i][x] = '\0';
			check_walls(r_map[i], 0);
			free(r_map[i]);
			j = len + 1;
			i++;
		}
	}
	free(r_map);
}

char	**check_map(char **map, t_data *data, int size, int len)
{
	int		i;

	i = -1;
	while (map[++i])
	{
		if (ft_strchr(map[i], '\t'))
			map[i] = clear_tabs(map[i]);
		check_walls(map[i], 0);
		if ((int)ft_strlen(map[i]) < len)
			map[i] = add_space(map[i], len);
		check_string(map[i], i, data);
	}
	rot_map(map, size, len);
	return (map);
}
