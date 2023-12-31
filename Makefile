PROJECT = Cub3d
NAME 	= cub3d
CC 		= cc
CFLAGS 	= -lm -fsanitize=address -Wall -Wextra #-framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"
LIBFT	:= ./libft
HEADERS := -I $(LIBFT)/include -I include
LIB		:= $(LIBFT)/libft.a
SRC_DIR := source
OBJ_DIR := object
SRC 	=	main.c game_loop.c draw_walls.c	 moves.c init_data.c input_data.c input_data_utils.c check_input.c load_texts.c clean.c check_walls.c mini_map.c
SRC 	:= $(SRC:%=$(SRC_DIR)/%)
OBJ 	:= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DIR_DUP = mkdir -p $(@D)
RM 		:= rm -rf

#OBJ_DIR = obj
#OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

BLACK   := \033[30m
RED     := \033[31m
GREEN   := \033[32m
YELLOW  := \033[33m
BLUE 	:= \033[96m
MAGENTA := \033[38;5;206m
CYAN    := \033[36m
WHITE   := \033[37m
RESET   := \033[0m
BOLD    := \033[1m
DIM     := \033[2m
ITALIC  := \033[3m
UNDER   := \033[4m
BLINK   := \033[5m
REVERSE := \033[7m
HIDDEN  := \033[8m
PINK 	:= \033[35m

all: libft $(NAME)


libft:
	@$(MAKE) -C $(LIBFT)

$(NAME): $(OBJ)
	@echo "Compiled with $(GREEN)$(BOLD)$(CFLAGS)$(RESET)"
	@$(CC) $(OBJ) $(CFLAGS) $(LIB) $(HEADERS) ./MLX42/build/libmlx42.a -Iinclude -lglfw -o $(NAME)
	@echo "$(BLUE)$(BOLD)----------------------------------------"
	@echo "     $(PROJECT) = NOW READY FOR USE!"
	@echo "----------------------------------------$(RESET)"
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(DIR_DUP)
	@echo "Compiled ✅ $(BLUE) $(BOLD) $^ $(RESET)"
	@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $^
	
clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@echo "$(BLUE) $(BOLD)$(NAME) $(RESET) Cleansed ✅"

re: fclean all

.PHONY: all clean fclean re libft