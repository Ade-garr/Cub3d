int	ft_check_tab(int tab[8])
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (tab[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_analyse_line_index2(char **spltline, int tab[8], int index)
{
	if (ft_strlen(spltline[0]) == 2)
	{
		if (spltline[0][0] == 'N' && spltline[0][1] == 'O')
			index = 1;
		if (spltline[0][0] == 'S' && spltline[0][1] == 'O')
			index = 2;
		if (spltline[0][0] == 'W' && spltline[0][1] == 'E')
			index = 3;
		if (spltline[0][0] == 'E' && spltline[0][1] == 'A')
			index = 4;
	}
	if (index >= 0 && index <= 7)
	{
		if (tab[index] == 1)
			index = -1;
	}
	return (index);
}

int	ft_analyse_line_index(char **spltline, int tab[8])
{
	int	index;

	index = -1;
	if (spltline[0] == NULL)
		return (-1);
	if (ft_strlen(spltline[0]) == 1)
	{
		if (spltline[0][0] == 'R')
			index = 0;
		if (spltline[0][0] == 'S')
			index = 5;
		if (spltline[0][0] == 'F')
			index = 6;
		if (spltline[0][0] == 'C')
			index = 7;
	}
	return (ft_analyse_line_index2(spltline, tab, index))
}

int	ft_find_long_spltline(char **spltline)
{
	int	i;

	i = 0;
	while (*spltline[i] != NULL)
		i++;
	return (i);
}

int	ft_check_nb(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0')
	{
		if (str1[i] < 48 || str1[i] > 57)
			return (-1);
		i++;
	}
	i = 0;
	while (str2[i] != '\0')
	{
		if (str2[i] < 48 || str2[i] > 57)
			return (-1);
		i++;
	}
	return (1);
}

void	ft_analyse_resolution_info(t_param *param, char **spltline, int index)
{
	int	spltline_long;
	int	ret;
	int	screenX_max;
	int	screenY_max;

	spltline_long = ft_find_long_spltline(spltline);
	if (spltline_long != 3)
		ft_exit(index + 7);
	ret = ft_check_nb(*spltline[1], *spltline[2]);
	if (ret == -1)
		ft_exit(index + 7);
	param->winX = ft_atoi(*spltline[1]);
	param->winY = ft_atoi(*spltline[2]);
	mlx_get_screen_size(param->mlx, &screenX_max, &screenY_max);
	if (param->winX <= 0 || param->winY <= 0)
		ft_exit(15);
	if (param->winX > screenX_max)
		param->winX = screenX_max;
	if (param->winY > screenY_max)
		param->winY = screenY_max;
}

void	ft_param_texture_path(t_param *param, char *str, int index)
{
	if (index == 1)
		param->fn_texN = ft_strdup(str);
	if (index == 2)
		param->fn_texS = ft_strdup(str);
	if (index == 3)
		param->fn_texW = ft_strdup(str);
	if (index == 4)
		param->fn_texE = ft_strdup(str);
	if (index == 5)
		param->fn_tex_sprite = ft_strdup(str);
}

void	ft_analyse_texture_info(t_param *param, char **spltline, int index)
{
	int	spltline_long;
	void	*ret;
	int	i1;
	int	i2;

	spltline_long = ft_find_long_spltline(spltline);
	if (spltline_long != 2)
		ft_exit(index + 7);
	ret = mlx_xpm_file_to_image(param->mlx, *spltline[1], &i1, &i2);
	if (ret == NULL)
		ft_exit(index + 7);
	ft_param_texture_path(param, *spltline[1], index);
	mlx_destroy_image(param->mlx, ret);
	
}

int	ft_check_valid_b(char *str, int index, t_param *param, int i)
{
	int	B;

	B = -1;
	while (str[i] >= 48 || str[i] <= 57)
	{
		if (B = -1)
			B = str[i] - 48;
		else
			B = B * 10 + str[i] - 48;
		i++;
	}
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0')
		ft_exit(index + 7);
	if ((B < 0 || B > 255))
		ft_exit(index + 7);
	if (index == 6)
		param->floorB = B;
	if (index == 7)
		param->cellB = B;
	return (i);
}

int	ft_check_valid_g(char *str, int index, t_param *param, int i)
{
	int	G;

	G = -1;
	while (str[i] >= 48 || str[i] <= 57)
	{
		if (G = -1)
			G = str[i] - 48;
		else
			G = G * 10 + str[i] - 48;
		i++;
	}
	if (str[i] != ',')
		ft_exit(index + 7);
	i++;
	if ((G < 0 || G > 255))
		ft_exit(index + 7);
	if (index == 6)
		param->floorG = G;
	if (index == 7)
		param->cellG = G;
	return (i);
}

int	ft_check_valid_r(char *str, int index, t_param *param, int i)
{
	int	R;

	R = -1;
	while (str[i] >= 48 || str[i] <= 57)
	{
		if (R = -1)
			R = str[i] - 48;
		else
			R = R * 10 + str[i] - 48;
		i++;
	}
	if (str[i] != ',')
		ft_exit(index + 7);
	i++;
	if ((R < 0 || R > 255))
		ft_exit(index + 7);
	if (index == 6)
		param->floorR = R;
	if (index == 7)
		param->cellR = R;
	return (i);
}

void	ft_analyse_color_info(t_param *param, char **spltline, int index)
{
	int	spltline_long;
	int	i;

	i = 0;
	spltline_long = ft_find_long_spltline(spltline);
	if (spltline_long != 2)
		ft_exit(index + 7);
	i = ft_check_valid_r(*spltline[1], index, param, i);
	i = ft_check_valid_g(*spltline[1], index, param, i);
	i = ft_check_valid_b(*spltline[1], index, param, i);
}

void	ft_analyse_line_info(t_param *param, char **spltline, int index)
{
	if (index == 0)
		ft_analyse_resolution_info(param, spltline, index);
	if (index > 0 && index <= 5)
		ft_analyse_texture_info(param, spltline, index);
	if (index > 5)
		ft_analyse_color_info(param, spltline, index);
}

void	ft_analyse_line(t_param *param, char *line, int	tab[8])
{
	char **spltline;
	int	index;

	spltline = ft_split(line, ' ');
	if (spltline == NULL)
		ft_exit(4);
	index = ft_analyse_line_index(spltline, tab);
	if (index >= 0 && index <= 7)
	{
		ft_analyse_line_info(param, spltline, index);
		ft_free(&spltline);
		tab[index] = 1;
	}
	else
		ft_exit(6);
}

void	ft_check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '2' && line[i] != 'N' 
		&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
			ft_exit(16);
		i++;
	}
}

char	*ft_parsing_empty_line(t_param *param, int fd)
{
	char	*line;
	int		ret;

	ret = get_next_line(fd, &line);
	while (ret == 1 && line[0] == '\0')
	{
		free(line);
		ret = get_next_line(fd, &line);	
	}
	if (ret == -1 || ret == 0)
		ft_exit(4);
	ft_check_line(line);
	return (line);
}

void	ft_merge_lines(t_param *param, char *line, int height)
{
	int	i;
	char	**tmp_worldMap;

	i = 0;
	tmp_worldMap = param->worldMap;
	param->worldMap = malloc(sizeof(char *) * param->mapHeight);
	if (param->worldMap == NULL)
		ft_exit(4);
	while (i < height - 1)
	{
		param->worldMap[i] = tmp_worldMap[i];
		i++;
	}
	param->worldMap[i] = line;
	free(tmp_worldMap);
}

void	ft_parsing_map(t_param *param, int fd, char *line)
{
	int		ret;

	ret = 1;
	param->mapHeight = 1;
	param->worldMap = malloc(sizeof(char *) * param->mapHeight);
	if (param->worldMap == NULL)
		ft_exit(4);
	param->worldMap[0] = line;
	while (ret == 1)
	{	
		ret = get_next_line(fd, &line);
		if (ret >= 0)
		{
			ft_check_line(line);
			param->mapHeight++;
			ft_merge_lines(param, line, param->mapHeight);
		}
	}
	if (ret == -1)
		ft_exit(4);
}

void	ft_parsing_get_info(t_param *param, int fd)
{
	int	tab[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int	ret;
	char *line;

	while (ft_check_tab(tab) == 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			ft_exit(4);
		if (ret == 0)
			ft_exit(5);
		if (line[0] != '\0')
			ft_analyse_line(param, line, tab);
		free(line);
	}
}

void	ft_check_NSWE(t_param *param)
{
	int	compteur;
	int	i;
	int	j;

	i = 0;
	compteur = 0;
	while (i < param->mapHeight)
	{
		j = 0;
		while (param->worldMap[i][j] != '\0')
		{
			if (param->worldMap[i][j] == 'N' || param->worldMap[i][j] == 'S'
			|| param->worldMap[i][j] == 'E' || param->worldMap[i][j] == 'W')
			{
				compteur++;
				param->posX = j + 0.5;
				param->posY = i + 0.5;
			}
			j++;
		}
		i++;
	}
	if (compteur != 1)
		ft_exit(16);
}

void	ft_parsing(t_param *param, char *str)
{
    int 	fd;
	char	*line;

	fd = open(str, O_RDONLY);
    if (fd == -1)
        ft_exit(3);
	ft_parsing_get_info(param, fd);
	line = ft_parsing_empty_line(param, fd);
	ft_parsing_map(param, fd, line);
	ft_check_NSWE(param);
	ft_check_map(param);
	if (close(fd) == -1)
		ft_exit(4);
}
