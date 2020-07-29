# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 15:12:32 by ade-garr          #+#    #+#              #
#    Updated: 2020/07/23 21:12:37 by ade-garr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS += ./srcs/ft_atoi.c
SRCS += ./srcs/ft_split.c
SRCS += ./srcs/ft_strdup.c
SRCS += ./srcs/ft_strlen.c
SRCS += ./srcs/ft_substr.c
SRCS += ./srcs/collision.c
SRCS += ./srcs/cub3d.c
SRCS += ./srcs/get_next_line.c
SRCS += ./srcs/get_next_line_utils.c
SRCS += ./srcs/hook.c
SRCS += ./srcs/hook2.c
SRCS += ./srcs/img.c
SRCS += ./srcs/parsing.c
SRCS += ./srcs/parsing2.c
SRCS += ./srcs/parsing3.c
SRCS += ./srcs/parsing4.c
SRCS += ./srcs/parsing5.c
SRCS += ./srcs/parsing6.c
SRCS += ./srcs/raycasting.c
SRCS += ./srcs/raycasting2.c
SRCS += ./srcs/raycasting3.c
SRCS += ./srcs/set_sprite.c
SRCS += ./srcs/set_tex.c
SRCS += ./srcs/set_tex2.c
SRCS += ./srcs/set_tex3.c
SRCS += ./srcs/spritecasting.c
SRCS += ./srcs/utils.c
SRCS += ./srcs/utils2.c
SRCS += ./srcs/utils3.c
SRCS += ./srcs/utils4.c
SRCS += ./srcs/utils5.c
SRCS += ./srcs/utils6.c

SRCS2 += ./srcs_bonus/ft_atoi.c
SRCS2 += ./srcs_bonus/ft_split.c
SRCS2 += ./srcs_bonus/ft_strdup.c
SRCS2 += ./srcs_bonus/ft_strlen.c
SRCS2 += ./srcs_bonus/ft_substr.c
SRCS2 += ./srcs_bonus/collision.c
SRCS2 += ./srcs_bonus/cub3d.c
SRCS2 += ./srcs_bonus/get_next_line.c
SRCS2 += ./srcs_bonus/get_next_line_utils.c
SRCS2 += ./srcs_bonus/hook.c
SRCS2 += ./srcs_bonus/hook2.c
SRCS2 += ./srcs_bonus/hud.c
SRCS2 += ./srcs_bonus/img.c
SRCS2 += ./srcs_bonus/parsing.c
SRCS2 += ./srcs_bonus/parsing2.c
SRCS2 += ./srcs_bonus/parsing3.c
SRCS2 += ./srcs_bonus/parsing4.c
SRCS2 += ./srcs_bonus/parsing5.c
SRCS2 += ./srcs_bonus/raycasting.c
SRCS2 += ./srcs_bonus/raycasting2.c
SRCS2 += ./srcs_bonus/raycasting3.c
SRCS2 += ./srcs_bonus/set_sprite.c
SRCS2 += ./srcs_bonus/set_tex.c
SRCS2 += ./srcs_bonus/set_tex2.c
SRCS2 += ./srcs_bonus/set_tex3.c
SRCS2 += ./srcs_bonus/spritecasting.c
SRCS2 += ./srcs_bonus/utils.c
SRCS2 += ./srcs_bonus/utils2.c
SRCS2 += ./srcs_bonus/utils3.c
SRCS2 += ./srcs_bonus/utils4.c
SRCS2 += ./srcs_bonus/utils5.c
SRCS2 += ./srcs_bonus/utils6.c

OBJS	= ${SRCS:.c=.o}

OBJS2	= ${SRCS2:.c=.o}

NAME	= Cub3D

INCLUDES = ./includes/

INCLUDES2 = ./includes_bonus/

CC		= clang

CFLAGS	+= -Wall
CFLAGS	+= -Wextra
CFLAGS	+= -Werror

HEADER = ${INCLUDES}libft.h

HEADER2 = ${INCLUDES2}libft.h

all:		${NAME}

${NAME}:	${OBJS}
			rm -f ${OBJS2} ${NAME}
			${CC} ${CFLAGS} -I ${INCLUDES} ${OBJS} -lmlx -lXext -lX11 -lm -lbsd -o ${NAME}
			printf "\033[32m$@ is ready ! \n\033[0m"

bonus:		${OBJS2}
			rm -f ${OBJS} ${NAME}
			${CC} ${CFLAGS} -I ${INCLUDES2} ${OBJS2} -lmlx -lXext -lX11 -lm -lbsd -o ${NAME}
			printf "\033[32m${NAME} bonus is ready ! \n\033[0m"

${OBJS}: %.o: %.c ${HEADER}
			${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o $@
	
${OBJS2}: %.o: %.c ${HEADER2}
			${CC} ${CFLAGS} -I ${INCLUDES2} -c $< -o $@
			
clean:
			${RM} ${OBJS} ${OBJS2}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
.SILENT:
