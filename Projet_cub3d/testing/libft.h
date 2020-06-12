/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:54:24 by ade-garr          #+#    #+#             */
/*   Updated: 2020/06/12 15:05:52 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <strings.h>
# include <unistd.h>
# include <stdlib.h>

void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strchr(const char *s, int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_isalnum(int c);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strnstr(const char *big, const char *little,
					size_t len);
int					ft_atoi(const char *nptr);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

////// POUR CUB3D ////////

# include <mlx.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

typedef struct	s_param
{
	void		*mlx;
	void		*win;
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		winX;
	double		winY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		wallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	int			color; // A VOIR SI NECESSAIRE A LA FIN
	void		*img; // POUR OPTI
	char		*imgadr; // POUR OPTI
	int			imgbpp;
	int			imglenght;
	int			endian;
	int			tab[7];
	char		*fn_tex1;// A ENLEVER
	char		*fn_texN;
    char		*fn_texS;
	char		*fn_texW;
	char		*fn_texE;
	char		*fn_tex_sprite;
	//t_tex1		*tex1;
	//t_tex_sprite	*tex_sprite;
	//t_sprite	*tab_sprite;
	int		nb_sprite;
	double		*tab_dist_wall;
	int		*sprite_order;
	double		*sprite_distance;
	int			floorR;
	int			floorG;
	int			floorB;
	int			cellR;
	int			cellG;
	int			cellB;
	int			mapWidth;
	int			mapHeight;
	char		**worldMap;
	
}				t_param;

int	ft_check_tab(int tab[8]);
int	ft_analyse_line_index2(char **spltline, int tab[8], int index);
int	ft_analyse_line_index(char **spltline, int tab[8]);
int	ft_find_long_spltline(char **spltline);
int	ft_check_nb(char *str1, char *str2);
void	ft_analyse_resolution_info(t_param *param, char **spltline, int index);
void	ft_param_texture_path(t_param *param, char *str, int index);
void	ft_analyse_texture_info(t_param *param, char **spltline, int index);
int	ft_check_valid_b(char *str, int index, t_param *param, int i);
int	ft_check_valid_g(char *str, int index, t_param *param, int i);
int	ft_check_valid_r(char *str, int index, t_param *param, int i);
void	ft_analyse_color_info(t_param *param, char **spltline, int index);
void	ft_analyse_line_info(t_param *param, char **spltline, int index);
void	ft_analyse_line(t_param *param, char *line, int	tab[8]);
void	ft_check_line(char *line);
char	*ft_parsing_empty_line(int fd);
void	ft_merge_lines(t_param *param, char *line, int height);
void	ft_parsing_map(t_param *param, int fd, char *line);
void	ft_parsing_get_info(t_param *param, int fd);
void	ft_check_NSWE(t_param *param);
int		ft_checking(char **check_map, int x, int y, int max);
void	ft_check_map(t_param *param);
void	ft_parsing(t_param *param, char *str);
char	**ft_free(char ***s1);
void	ft_exit(int nb);

int		ft_position(char *left);
int		ft_checkleft(char *left);
size_t	ft_strlen(const char *s);
char	*ft_join(char *line, char *left);
void	ft_moveleft(char *left, char *newleft);
int		ft_fill_line(int fd, char **line, char (*left)[BUFFER_SIZE + 1]);
int		ft_give_line(char **line, char *left);
int		get_next_line(int fd, char **line);
int		ft_free2(char **line);

#endif
