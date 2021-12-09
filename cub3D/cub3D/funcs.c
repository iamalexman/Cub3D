#include "cub3D.h"

int	ft_strcmp(char *str1, char *str2)
{
	int		i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi_rgb(char *str)
{
	int		res;
	int		i;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = ((res * 10) + (str[i] - '0'));
		if (res > 255 || res < 0)
			ft_error(MAP_ERROR);
		i++;
	}
	return (res);
}