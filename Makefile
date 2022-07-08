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
	src/builtins \
	src/env \
	src/shell \
	src/pipes \
	src/parse \
	src/process \
	src/utils

OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

SRC = main.c prompt.c str_helpers.c ms_display_error.c free_functions.c #utils

SRC += import_env.c expand_env_var.c save_env_var.c #env

SRC += redirect.c redirect_in.c redirect_out.c #pipes

SRC += is_builtin.c exec_builtin.c ms_echo.c \
	   ms_cd.c ms_pwd.c ms_export.c \
	   ms_unset.c ms_env.c ms_exit.c #builtin

SRC += check_syntax.c convert_chars.c unpipe_and_alloc.c \
		parse.c remove_env_var.c remove_quotes.c    #parse

SRC += start_process.c #process

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
