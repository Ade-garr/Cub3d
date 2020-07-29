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

int	ft_analyse_resolution_info(t_param *param, char **spltline)
{
	int	spltline_long;
	int	ret;

	spltline_long = ft_find_long_spltline(spltline);
	if (spltline_long != 3)
		return (-1);
	ret = ft_check_nb(*spltline[1], *spltline[2]);
	if (ret == -1)
		return (-1);
	param->winX = ft_atoi(*spltline[1]);
	param->winY = ft_atoi(*spltline[2]);
	return (1);
}

int	ft_analyse_texture_info(t_param *param, char **spltline)
{
	int	spltline_long;
	void	*ret;

	spltline_long = ft_find_long_spltline(spltline);
	if (spltline_long != 2)
		return (-1);
	ret = mlx_xpm_file_to_image(param->mlx, param->fn_tex_sprite, &param->tex_sprite->width,
	&param->tex_sprite->height);
	if (ret == NULL)
		return (-1);
	return (1);
}

int	ft_analyse_line_info(t_param *param, char **spltline, int index)
{
	int	ret;

	if (index == 0)
		ret = ft_analyse_resolution_info(param, spltline);
	if (index > 0 && index <= 5)
		ret = ft_analyse_texture_info(param, spltline);
	if (index > 5)
		ret = ft_analyse_color_info(param, spltline);
	if (ret == -1)
		return (-1);
	return (1);
}

int	ft_analyse_line(t_param *param, char *line, int	tab[8])
{
	char **spltline;
	int	index;
	int	ret;

	spltline = ft_split(line, ' ');
	if (spltline == NULL)
		return (ft_return(4));
	index = ft_analyse_line_index(spltline, tab);
	if (index >= 0 && index <= 7)
	{
		ret = ft_analyse_line_info(param, spltline, index);
		ft_free(&spltline);
		if (ret == -1)
			return (ft_return(index + 7));
		tab[index] = 1;
		return (1);
	}
	else
	{
		ft_free(&spltline);
		return (ft_return(6));
	}
}

int	ft_parsing_get_info(t_param *param, int fd)
{
	int	tab[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int	ret;
	char *line;

	while (ft_check_tab(tab) == 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (ft_return(4));
		if (ret == 0)
		{
			free(line);
			return (ft_return(5));
		}
		if (line[0] != '\0')
			ret = ft_analyse_line(param, line, tab);
		free(line);
		if (ret == -1)
			return (-1);
		}
	}
	return (1);
}

int ft_parsing(t_param *param, char *str)
{
    int 	fd;
    int 	ret;

	fd = open(str, O_RDONLY);
    if (fd == -1)
        return (ft_return(3));
	ret = ft_parsing_get_info(param, fd)
}
