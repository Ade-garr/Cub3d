/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:54:24 by ade-garr          #+#    #+#             */
/*   Updated: 2020/07/16 19:39:37 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <string.h>
# include <strings.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <limits.h>
# include <float.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	10
# endif

# ifndef M_PI
#  define M_PI	3.14159265358979323846264338
# endif

typedef struct		s_img
{
	int				file_size;
	short			reserved1;
	short			reserved2;
	unsigned int	offset_bits;
	unsigned int	size_header;
	unsigned int	width;
	unsigned int	height;
	short int		planes;
	short int		bbp;
	unsigned int	compression;
	unsigned int	image_size;
	unsigned int	ppm_x;
	unsigned int	ppm_y;
	unsigned int	clr_total;
	unsigned int	clr_important;
}					t_img;

typedef	struct		s_sprite
{
	double			x;
	double			y;
}					t_sprite;

typedef struct		s_tex
{
	int				width;
	int				height;
	unsigned int	*tab;
}					t_tex;

typedef	struct		s_spritecast
{
	int				i;
	double			spritex;
	double			spritey;
	double			invdet;
	double			transformx;
	double			transformy;
	int				sprite_screenx;
	int				sprite_height;
	int				sprite_width;
	int				draw_starty;
	int				draw_endy;
	int				draw_startx;
	int				draw_endx;
	int				x;
	int				y;
	int				texx;
	int				texy;
	char			*adr;
	int				d;
}					t_spritecast;

typedef	struct		s_raycast
{
	double			camerax;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			walldist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				lineheight;
	int				drawstart;
	int				drawend;
	int				x;
	char			*adr;
	double			wallx;
	int				texx;
	double			step;
	double			texpos;
	int				texy;
	int				xfloorcell;
}					t_raycast;

typedef struct		s_param
{
	void			*mlx;
	void			*win;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	double			winx;
	double			winy;
	void			*img;
	char			*imgadr;
	int				imgbpp;
	int				imglenght;
	int				endian;
	int				tab[7];
	char			*fn_tex_n;
	char			*fn_tex_s;
	char			*fn_tex_w;
	char			*fn_tex_e;
	char			*fn_tex_sprite;
	t_tex			*tex_n;
	t_tex			*tex_s;
	t_tex			*tex_w;
	t_tex			*tex_e;
	t_tex			*tex_sprite;
	t_sprite		*tab_sprite;
	int				nb_sprite;
	double			*tab_dist_wall;
	int				*sprite_order;
	double			*sprite_distance;
	int				local_endian;
	unsigned int	floorcolor;
	unsigned int	cellcolor;
	int				floorr;
	int				floorg;
	int				floorb;
	int				cellr;
	int				cellg;
	int				cellb;
	int				mapwidth;
	int				mapheight;
	char			**worldmap;
}					t_param;

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

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
char				*ft_strnstr(const char *big,
					const char *little, size_t len);
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
char				**ft_free(char ***s1);
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

int					ft_position(char *left);
int					ft_free_line(char **line);
int					ft_checkleft(char *left);
size_t				ft_strlen(const char *s);
char				*ft_join(char *line, char *left);
void				ft_moveleft(char *left, char *newleft);
int					ft_fill_line(int fd, char **line,
					char (*left)[BUFFER_SIZE + 1]);
int					ft_give_line(char **line, char *left);
int					get_next_line(int fd, char **line);

int					ft_checkcollision(t_param *param,
					double speed, double rectx, double recty);
int					ft_bodycollision4(t_param *param, double speed);
int					ft_bodycollision3(t_param *param, double speed);
int					ft_bodycollision2(t_param *param, double speed);
int					ft_bodycollision(t_param *param, double speed);

void				ft_set_tabs_tex(t_param *param);
void				ft_launch_cub3d(t_param *param, int argc);

void				ft_loop5(t_param *param, double rotspd);
void				ft_loop4(t_param *param, double speed);
void				ft_loop3(t_param *param, double speed);
void				ft_loop2(t_param *param, double speed);
int					ft_loop(t_param *param);

int					ft_exithook(t_param *param);
int					ft_keypress(int key, t_param *param);
int					ft_keyrelease(int key, t_param *param);

void				ft_define_ptr(t_param *param, t_img *ptr);
void				ft_tab_in_img(t_param *param, int fd);
void				ft_create_img(t_param *param);

void				ft_param_orient(t_param *param, char c);
void				ft_check_nswe(t_param *param);
int					ft_checking(char **check_map, int x, int y, int max);
void				ft_check_map(t_param *param);
void				ft_parsing(t_param *param, char *str);

int					ft_check_tab(int tab[8]);
int					ft_analyse_line_index2(char **spltline,
					int tab[8], int index);
int					ft_analyse_line_index(char **spltline, int tab[8]);
int					ft_find_long_spltline(char **spltline);
int					ft_check_nb(char *str1, char *str2);

void				ft_analyse_resolution_info(t_param *param, char **spltline,
					int index, char *line);
void				ft_param_texture_path(t_param *param, char **spltline,
					int index, char *line);
void				ft_analyse_texture_info(t_param *param, char **spltline,
					int index, char *line);
void				ft_check_valid_b(char **spltline, int index,
					t_param *param, char *line);
void				ft_check_valid_g(char **spltline, int index,
					t_param *param, char *line);

void				ft_check_valid_r(char **spltline, int index,
					t_param *param, char *line);
void				ft_analyse_color_info(t_param *param,
					char **spltline, int index, char *line);
void				ft_analyse_line_info(t_param *param,
					char **spltline, int index, char *line);
void				ft_analyse_line(t_param *param, char *line, int	tab[8]);
void				ft_check_line(t_param *param, char *line);

char				*ft_parsing_empty_line(t_param *param, int fd);
void				ft_merge_lines(t_param *param, char *line, int height);
void				ft_parsing_map(t_param *param, int fd, char *line);
void				ft_parsing_get_info(t_param *param, int fd);
void				ft_transform_map(t_param *param);

void				ft_get_mapwidth(t_param *param);
void				ft_fill_tmp_worldmap(t_param *param, char **tmp_worldmap);
void				ft_check_map_nobonus(t_param *param);

void				ft_raycasting5(t_param *param, t_raycast *raycast);
void				ft_raycasting4(t_param *param, t_raycast *raycast);
void				ft_raycasting3(t_param *param, t_raycast *raycast);
void				ft_raycasting2(t_param *param, t_raycast *raycast);
void				ft_raycasting(t_param *param);

void				ft_raycasting_west2(t_param *param, t_raycast *raycast);
void				ft_raycasting_west(t_param *param, t_raycast *raycast);
void				ft_raycasting_east2(t_param *param, t_raycast *raycast);
void				ft_raycasting_east(t_param *param, t_raycast *raycast);

void				ft_raycasting_south2(t_param *param, t_raycast *raycast);
void				ft_raycasting_south(t_param *param, t_raycast *raycast);
void				ft_raycasting_north2(t_param *param, t_raycast *raycast);
void				ft_raycasting_north(t_param *param, t_raycast *raycast);

void				ft_sort_sprites(t_param *param);
void				ft_find_nb_sprite(t_param *param);
void				ft_param_sprites(t_param *param);
void				ft_set_sprite(t_param *param);

void				ft_set_tex_sprite_tab_no_endian(t_param *param,
					char *adr, int bpp, int length);
void				ft_set_tex_sprite_tab_endian(t_param *param,
					char *adr, int bpp, int length);
void				ft_set_tex_sprite(t_param *param);
void				ft_set_tex_n_tab_no_endian(t_param *param,
					char *adr, int bpp, int length);
void				ft_set_tex_n_tab_endian(t_param *param,
					char *adr, int bpp, int length);

void				ft_set_tex_w_tab_endian(t_param *param,
					char *adr, int bpp, int length);
void				ft_set_tex_w(t_param *param);
void				ft_set_tex_e_tab_no_endian(t_param *param,
					char *adr, int bpp, int length);
void				ft_set_tex_e_tab_endian(t_param *param,
					char *adr, int bpp, int length);
void				ft_set_tex_e(t_param *param);

void				ft_set_tex_n(t_param *param);
void				ft_set_tex_s_tab_no_endian(t_param *param,
					char *adr, int bpp, int length);
void				ft_set_tex_s_tab_endian(t_param *param,
					char *adr, int bpp, int length);
void				ft_set_tex_s(t_param *param);
void				ft_set_tex_w_tab_no_endian(t_param *param,
					char *adr, int bpp, int length);

void				ft_spritecasting5(t_param *param, t_spritecast *spritecast);
void				ft_spritecasting4(t_param *param, t_spritecast *spritecast);
void				ft_spritecasting3(t_param *param, t_spritecast *spritecast);
void				ft_spritecasting2(t_param *param, t_spritecast *spritecast);
void				ft_spritecasting(t_param *param);

double				ft_max(double a, double b);
double				ft_min(double a, double b);
int					ft_check_arg(char *str);
void				ft_exit17(void);
void				ft_exit16(t_param *param);

void				ft_free_map(char **map, t_param *param);
void				ft_free_param2(t_param *param);
void				ft_free_param(t_param *param);
void				ft_set_local_endian(t_param *param);
void				ft_init(t_param *param);

void				ft_exit15(t_param *param);
void				ft_exit14(t_param *param, char **check_map);
void				ft_exit13(t_param *param, char **check_map);
void				ft_exit12(t_param *param);
void				ft_exit11(t_param *param, char **map, char *line);

void				ft_exit10(t_param *param);
void				ft_exit9(t_param *param, char **spltline, char *line);
void				ft_exit8(t_param *param, char **spltline, char *line);
void				ft_exit7(t_param *param, char **spltline,
					char *line, int nb);
void				ft_exit6(t_param *param, char *line);

void				ft_exit5(t_param *param, char *line);
void				ft_exit4(t_param *param, char *line);
void				ft_exit3(t_param *param);
void				ft_exit2(t_param *param);
void				ft_exit1(void);

int					ft_check_filename(char *str);
void				ft_param_orient2(t_param *param, char c);
int					ft_checking2(char **check_map, int x, int y, int max);

#endif
