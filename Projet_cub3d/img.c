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

int	ft_analyse_line(t_param *param, char *line)
{
	
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
		{
			ret = ft_analyse_line(param, line);
			if (ret == -1)
				return (-1);
		}
		free(line);
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