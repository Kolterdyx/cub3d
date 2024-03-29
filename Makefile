
NAME = cub3D

CC = gcc

CFLAGS = -Wall -Wextra -Werror -MD -g

SRC_PATH = src
SRC_FILES = main.c \
			hooks.c \
			utils/vector_functions_1.c \
			utils/vector_functions_2.c \
			utils/vector_functions_3.c \
			utils/edges.c \
			utils/bit_stuff.c \
			utils/utils.c \
			utils/array_utils.c \
			setup.c \
			render/render.c \
			render/minimap.c \
			render/lines.c \
			render/rays.c \
			render/casts.c \
			render/texture_utils.c \
			render/animation.c \
			level/level.c \
			level/level_elements.c \
			level/collisions.c \
			parser/parser_utils.c \
			parser/parser_utils2.c \
			parser/parser_utils3.c \
			parser/map_info_check.c \
			parser/map_content_check.c \
			parser/map_filler.c \
			parser/parser.c \

SRC = $(addprefix $(SRC_PATH)/, $(SRC_FILES))

OBJ_PATH = obj
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_FILES))

-include $(OBJ:.o=.d)

LIB_PATH = libs
INCLUDES = -I./includes -I./$(LIB_PATH)/libft -I./$(LIB_PATH)/MLX42/include/MLX42
LIB_SRCS = $(LIB_PATH)/MLX42 $(LIB_PATH)/libft
LIB_FILES = $(LIB_PATH)/MLX42/libmlx42.a $(LIB_PATH)/libft/libft.a

ifeq ($(shell uname), Linux)
	# Must be installed: build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev
	LIBS = -Wl,--no-as-needed -lpthread -ldl -lglfw -lm -lft $(foreach lib, $(LIB_FILES), -L$(dir $(lib)))
else
	LIBS = -framework OpenGL -framework AppKit -lglfw -lft -L "/Users/$(USER)/.brew/opt/glfw/lib/" -lm $(foreach lib, $(LIB_FILES), -L./$(dir $(lib)))
endif

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiling $<"

$(NAME): $(LIB_SRCS) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) $(LIBS) -o $(NAME) $(LIB_FILES)
	@echo "Compiling $(NAME)"

$(LIB_SRCS):
	@for dir in $(LIB_SRCS); do \
        make --no-print-directory -C $$dir; \
    done

all: $(NAME)

clean:
	@rm -rf $(OBJ_PATH)
	@echo "Cleaning $(OBJ_PATH)"

cclean:
	@rm -rf $(OBJ_PATH)
	@echo "Cleaning $(OBJ_PATH)"
	@rm -f $(NAME)
	@echo "Cleaning $(NAME)"

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaning $(NAME)"
	@for dir in $(LIB_SRCS); do \
        make --no-print-directory -C $$dir fclean; \
    done

re: fclean all

rre: cclean all

.PHONY: all clean fclean re $(LIB_SRCS)
