NAME		= kdtree
INC_DIR		= INC/
MKFL		= Makefile
SRC_DIR		= SRC/
OBJ_DIR		= OBJ/


# -------------
CC = g++
RM = rm -rf
MP = mkdir -p
CFLAGS = -g -Wall -Wextra -Werror -fPIE
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
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) --no-print-directory

.PHONY: all clean fclean re
