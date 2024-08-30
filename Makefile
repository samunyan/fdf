# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samunyan <samunyan@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/08 18:05:22 by samunyan          #+#    #+#              #
#    Updated: 2022/11/26 13:51:31 by samunyan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable
NAME		=	fdf
NAME_BONUS	=	fdf_bonus

#Libs
LIBS_DIR		=	./libs
LIBFT_DIR		=	$(LIBS_DIR)/libft
LIBFT			= 	libft.a
ifeq ($(shell uname), Linux)
	MLX_DIR		=	$(LIBS_DIR)/libmlx/minilibx-linux
	LIBS		=	ft mlx m X11 Xext bsd
else
	MLX_DIR		=	$(LIBS_DIR)/libmlx/minilibx_mms_20200219
	LIBS		=	ft m mlx
endif
MLX				=	libmlx.dylib
LIB_PATHS		=	$(LIBFT_DIR) $(MLX_DIR)

#Directories
OBJ_DIR			= 	./objs
SRC_DIR			=	./srcs
HEAD_DIRS		=	./include $(LIBFT_DIR)/include $(MLX_DIR)

#Files
FILES		=	main.c \
				init.c \
				init_utils.c \
				get_map_data.c \
				get_map_data_utils.c \
				vector.c \
				matrix_1.c \
				matrix_2.c \
				transform.c \
				transform_utils.c \
				project.c \
				draw.c \
				draw_utils.c \
				hooks.c \
				error.c
B_FILES 	=	color_bonus.c \
				error_bonus.c \
				get_map_data_utils_bonus.c \
				init_bonus.c \
				main_bonus.c \
				project_bonus.c \
                draw_bonus.c \
				draw_utils_bonus.c \
                get_map_data_bonus.c    \
                hooks_bonus.c  \
				hooks_utils_bonus.c \
                init_utils_bonus.c\
                matrix_1_bonus.c   \
				matrix_2_bonus.c   \
                transform_bonus.c  \
                transform_utils_bonus.c \
                vector_bonus.c
ifeq ($(shell uname), Darwin)
	FILES += utils_apple.c
	B_FILES += utils_apple_bonus.c
else
	FILES += utils_linux.c
	B_FILES += utils_linux_bonus.c
endif
SRCS	= 	$(addprefix $(SRC_DIR)/, $(FILES))
B_SRCS	=  	$(addprefix $(SRC_DIR)/, $(B_FILES))
OBJS	=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
B_OBJS	= 	$(addprefix $(OBJ_DIR)/, $(B_FILES:.c=.o))

#Compiler
SYSTEM		 := $(shell uname)
ifeq ($(SYSTEM),Linux)
CC			=	clang
else
CC			= 	gcc
endif
CFLAGS	=	-Wall -Werror -Wextra $(HEAD_DIRS:%=-I %)
LDFLAGS	=	$(foreach lib_path, $(LIB_PATHS), -L$(lib_path)) $(foreach lib, $(LIBS), -l$(lib))
ifeq ($(SANITIZER), 1)
		CFLAGS	+=	-g -fsanitize=address
		LDFLAGS	+=	-g -fsanitize=address
endif
ifeq ($(DEBUG), 1)
		CFLAGS	+=	-g
		LDFLAGS	+=	-g
endif


.PHONY:		all bonus FORCE clean fclean re sanitizer debug

all:	$(NAME)

$(NAME):	$(LIBFT) $(MLX) $(OBJS)
			@$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $(NAME)
			@test -z '$(filter %.o,$?)' || (echo ✅ $(BBlue) [$(NAME)]"\t"$(BGreen)Compilation done. \
				Usage: ./$(NAME) \<filename\>.fdf  && \
				echo $(White)"\t\t\t"Compiler flags: $(CFLAGS)$(Color_Off))

$(NAME_BONUS): $(LIBFT) $(MLX) $(B_OBJS)
			@$(CC) $(CFLAGS) $(B_SRCS) $(LDFLAGS) -o $(NAME_BONUS)
			@test -z '$(filter %.o,$?)' || (echo ✅ $(BBlue) [$(NAME)]"\t"$(BGreen)Compilation done. \
				Usage: ./$(NAME) \<filename\>.fdf  && \
				echo $(White)"\t\t\t"Compiler flags: $(CFLAGS)$(Color_Off))

bonus:		$(NAME_BONUS)
			@cp $(NAME_BONUS) $(NAME)
			@rm $(NAME_BONUS)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
			@mkdir -p $(dir $@)
			@echo ⌛ $(BBlue)[$(NAME)]"\t"$(Yellow)Compiling $<$(Color_Off)
			@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): FORCE
			@make -C $(LIBFT_DIR)

$(MLX):	FORCE
			@if ! find $(MLX_DIR) -name "*.o" | grep -q .; then \
  					echo ⌛ $(BBlue)[$(MLX)]$(Yellow)Compiling library... $(Color_Off); \
  					make -s -C $(MLX_DIR); \
  					echo ✅ $(BBlue) [$(MLX)]$(BGreen)Compilation done.$(Color_Off); \
			fi
ifeq ($(shell uname), Darwin)
	@cp $(MLX_DIR)/$(MLX) $(MLX)
endif

FORCE:

clean:
			@if [ -d $(OBJ_DIR) ]; then \
  					rm -rf $(OBJ_DIR); \
  					echo 🗑$(BBlue)[$(NAME)]"\t"$(BGreen)Object files removed.$(Color_Off); \
  			fi
			@make -C $(LIBFT_DIR) clean
			@if find $(MLX_DIR) -name "*.o" | grep -q .; then \
  					make -s -C $(MLX_DIR) clean; \
  					rm -rf $(MLX); \
  					echo 🗑$(BBlue)[$(MLX)]$(BGreen)Object files removed.$(Color_Off); \
  					echo 🗑$(BBlue)[$(MLX)]$(BGreen)Library removed.$(Color_Off); \
  					rm -rf $(MLX_DIR)/*.swiftsourceinfo; \
  			fi

fclean:		clean
			@if [ -f $(NAME) ]; then \
					rm -rf $(NAME); \
					rm -rf *.dSYM; \
					echo 🗑$(BBlue)[$(NAME)]"\t"$(BGreen)Executable removed.$(Color_Off); \
			fi
			@make -C $(LIBFT_DIR) fclean

re:			fclean all

sanitizer:
			@SANITIZER=1 make re

debug:
			@DEBUG=1 make re


bonus_sanitizer: fclean
			@SANITIZER=1 make bonus

bonus_debug: fclean
			@DEBUG=1 make bonus

# Colors
## Reset
Color_Off='\033[0m'       # Text Reset
## Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White
## Bold
BBlack='\033[1;30m'       # Black
BRed='\033[1;31m'         # Red
BGreen='\033[1;32m'       # Green
BYellow='\033[1;33m'      # Yellow
BBlue='\033[1;34m'        # Blue
BPurple='\033[1;35m'      # Purple
BCyan='\033[1;36m'        # Cyan
BWhite='\033[1;37m'       # White
## Underline
UBlack='\033[4;30m'       # Black
URed='\033[4;31m'         # Red
UGreen='\033[4;32m'       # Green
UYellow='\033[4;33m'      # Yellow
UBlue='\033[4;34m'        # Blue
UPurple='\033[4;35m'      # Purple
UCyan='\033[4;36m'        # Cyan
UWhite='\033[4;37m'       # White
## Background
On_Black='\033[40m'       # Black
On_Red='\033[41m'         # Red
On_Green='\033[42m'       # Green
On_Yellow='\033[43m'      # Yellow
On_Blue='\033[44m'        # Blue
On_Purple='\033[45m'      # Purple
On_Cyan='\033[46m'        # Cyan
On_White='\033[47m'       # White
## Bold High Intensity
BIBlack='\033[1;90m'      # Black
BIRed='\033[1;91m'        # Red
BIGreen='\033[1;92m'      # Green
BIYellow='\033[1;93m'     # Yellow
BIBlue='\033[1;94m'       # Blue
