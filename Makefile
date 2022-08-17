NAME := minishell

OBJDIR := objdir
LIBFTDIR := lib/libft
LIBFT := $(LIBFTDIR)/libft.a

CFLAGS += $(INCLUDE) -Wall -Wextra -Werror -g3
LDLIBS += -lreadline -lft
LDFLAGS += -L$(LIBFTDIR)
VALFLAGS = --suppressions=readline.supp --leak-check=full --show-leak-kinds=all
INCLUDE = -Iinclude -I$(LIBFTDIR)
CC = gcc

vpath %.c src \
	src/builtins \
	src/env \
	src/shell \
	src/pipes \
	src/parse \
	src/process \
	src/utils

OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

SRC = main.c prompt.c str_helpers.c ms_display_error.c \
	free_functions.c save_paths.c signal.c get_next_line.c \
	welcome.c free_functions2.c

SRC += import_env.c expand_env_var.c save_env_var.c

SRC += redirect.c redirect_in.c redirect_out.c

SRC += is_builtin.c exec_builtin.c ms_echo.c \
	   ms_cd.c ms_pwd.c ms_export.c \
	   ms_unset.c ms_env.c ms_exit.c

SRC += check_syntax.c convert_chars.c unpipe_and_alloc.c \
		parse.c remove_env_var.c remove_quotes.c syntax_message_errors.c

SRC += start_process.c check_exec.c heredoc.c heredoc_signal.c \
	   get_envp.c access_functions.c

$(OBJDIR)/%.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<

all: $(NAME)

options:
	@echo "$(NAME) build options:"
	@echo "CFLAGS        = $(CFLAGS)"
	@echo "LDFLAGS       = $(LDFLAGS)"
	@echo "LDLIBS        = $(LDLIBS)"
	@echo "CC            = $(CC)"

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

val: re
	valgrind $(VALFLAGS) ./$(NAME)

.PHONY: all clean
