NAME		= kdtree
INC_DIR		= inc/
MKFL		= Makefile
SRC_DIR		= src/
OBJ_DIR		= obj/


# -------------
CC = g++
RM = rm -rf
MP = mkdir -p
CFLAGS = -g -Wall -Wextra -Werror -fPIE
# =============

SRC_L	=	main.cc kdtree.cc node.cc CSVcreator.cc


SRC = $(addprefix $(SRC_DIR), $(SRC_L))

# -------------
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.cc=.o))
DEP = $(addsuffix .d, $(basename $(OBJ)))
# =============

$(OBJ_DIR)%.o: %.cc $(MKFL)
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
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) --no-print-directory

.PHONY: all clean fclean re
