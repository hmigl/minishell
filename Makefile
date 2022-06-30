NAME := minishell

OBJDIR := objdir
LIBFTDIR := lib/libft
LIBFT := $(LIBFTDIR)/libft.a

CFLAGS += -Wall -Wextra -Werror
LDLIBS += -lreadline -lft
LDFLAGS += -L$(LIBFTDIR)
INCLUDE = -Iinclude -I$(LIBFTDIR)
CC := gcc -g3

vpath %.c src \
	src/main \
	src/builtins \
	src/env \
	src/shell \
	src/pipes

OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

SRC = main.c save_local_env.c prompt.c str_helpers.c ms_display_error.c

SRC += redirect.c redirect_in.c redirect_out.c

SRC += is_builtin.c exec_builtin.c echo.c \
	   pwd.c env.c unset.c exit_ms.c

$(OBJDIR)/%.o: %.c
	$(CC) $(INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -o $@ $(LDLIBS) $(LDFLAGS)

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR) --no-print-directory

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $@

clean:
	@$(MAKE) clean -C $(LIBFTDIR) --no-print-directory
	$(RM) $(OBJS)

fclean: clean
	@$(MAKE) fclean -C $(LIBFTDIR) --no-print-directory
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean
