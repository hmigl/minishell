NAME := minishell

LIBFT_DIR := lib/libft
LIBFT := $(LIBFT_DIR)/libft.a

INCLUDE := -I include -I $(LIBFT_DIR)
LDLIBS += -lreadline -lft
LDFLAGS += -L$(LIBFT_DIR)
CFLAGS += -Wall -Wextra -Werror
DEBUG = -g3
CC := gcc -g3

vpath %.c	src \
			src/main \
			src/save_env_var \
			src/shell \
			src/pipes

SRC	=	main.c \
		save_local_env.c \
		prompt.c \
		redirect.c \
		redirect_in.c \
		str_helpers.c

OBJ_DIR := obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -o $@ $(LDLIBS) $(LDFLAGS)

$(LIBFT):
	@make -C $(LIBFT_DIR) --no-print-directory

$(OBJ_DIR)/%.o: %.c
	$(CC) $(INCLUDE) -c $< -o $@

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $@

clean:
	$(RM) $(OBJ)
	@make clean -C $(LIBFT_DIR) --no-print-directory

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR) --no-print-directory

re: fclean all

.PHONY: all clean
