# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 00:35:07 by jsebasti          #+#    #+#              #
#    Updated: 2023/09/29 00:40:45 by baltes-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= kdtree
INC_DIR		= INC/
MKFL		= Makefile
SRC_DIR		= SRC/
OBJ_DIR		= OBJ/


# -------------
CC = g++
RM = rm -rf
MP = mkdir -p
CFLAGS = -g -Wall -Wextra -Werror
# =============

SRC_L	=	main.cpp kdtree.cpp node.cpp


SRC = $(addprefix $(SRC_DIR), $(SRC_L))

# -------------
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))
DEP = $(addsuffix .d, $(basename $(OBJ)))
# =============

$(OBJ_DIR)%.o: %.cpp $(MKFL)
	@$(MP) $(dir $@)
	@$(CC) $(CFLAGS) -MMD -I $(INC_DIR) -c $< -o $@

all:
	@$(MAKE) $(NAME) --no-print-directory

$(NAME):: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(NAME)::
	@echo "Hello, kdtree already compiled"

-include $(DEP)

clean:
	@$(MAKE) clean -C $(LIB_M) --no-print-directory
	$(RM) $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIB_M) --no-print-directory
	$(RM) $(NAME)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) --no-print-directory

.PHONY: all clean fclean re
