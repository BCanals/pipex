# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bizcru <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 17:30:42 by bizcru            #+#    #+#              #
#    Updated: 2024/12/07 16:20:45 by bizcru           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BNS_NAME = pipex

SRCS = pipex.c
#main.c utils_list_1.c utils_list_2.c utils_param.c utils_rotate.c \
			 utils_r_rotate.c utils_swap.c utils_sort_1.c utils_sort_2.c
#SRCS = $(addprefix src/, $(SRCS_NAMES))
OBJS = $(SRCS:.c=.o)
BNS_SRCS_NAMES = main_bonus.c utils_misc_bonus.c utils_param_bonus.c \
				 utils_ops_bonus.c utils_sort_bonus.c
BNS_SRCS = $(addprefix bonus/, $(BNS_SRCS_NAMES))
BNS_OBJS = $(BNS_SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDE = src/push_swap.h
BNS_INCLUDE = bonus/push_swap_bonus.h
CFLAGS = -Wall -Wextra -Werror

END = \033[m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PURPLE = \033[35m
CIAN = \033[36m
MAKEFLAGS += --no-print-directory

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo -n "\n$(YELLOW) ---> BUILDING $(NAME)...$(END)"
	@gcc $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(GREEN) DONE!$(END)"
	@echo "$(GREEN)   === BUILDING COMPLETE : ) ===$(END)\n"

bonus: $(BNS_OBJS) $(LIBFT)
	@echo -n "\n$(YELLOW) ---> BUILDING $(BNS_NAME)...$(END)"
	@gcc $(CFLAGS) $(BNS_OBJS) -L$(LIBFT_DIR) -lft -o $(BNS_NAME)
	@echo "$(GREEN) DONE!$(END)"
	@echo "$(GREEN)   === BUILDING COMPLETE : ) ===$(END)\n"
	

$(LIBFT):
	@echo "\n $(YELLOW) ---> Compiling libft... === $(END)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)   === libft.a is compiled :) ===$(END)"

%.o: %.c $(INCLUDE)
	@gcc $(CFLAGS) -I. -c $< -o $@
	@echo -n "\n $(BLUE) ---> Building objects... --- $(END)"
	@echo " $(CIAN) DONE! :) $(END)"

clean:
	@echo -n "$(RED) --> Deleting object files... $(END)"
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJS) $(BNS_OBJS)
	@echo "$(GREEN) DONE! $(END)"

fclean: clean
	@echo -n "$(RED) --> Deleting executables... $(END)"
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME) $(BNS_NAME)
	@echo "$(GREEN) DONE! $(END)"

re: fclean all

.PHONY: all clean fclean bonus re $(LIBFT)
