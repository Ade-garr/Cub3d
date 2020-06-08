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

void	ft_check_index(int tab[8], int *ptr_index)
{
	int	i;

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
