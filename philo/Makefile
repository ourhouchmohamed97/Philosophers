# ================= Colors =================
BLUE    = \033[0;34m
GREEN = \033[1;32m
YELLOW  = \033[0;33m
LIGHT_YELLOW = \033[1;33m
NOCOLOR = \033[0m
# ==========================================

NAME    = philo
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -fsanitize=thread 
# CFLAGS  = -Wall -Wextra -Werror
RM      = rm -rf

SRC     = philo.c \
          parse.c \
          exit.c \
          time.c \
          routine.c \
          end.c \
          life.c \

OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) philo.h
	@echo "$(BLUE)Compiling philosopher...$(NOCOLOR)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo ""
	@echo "$(GREEN)██████╗░██╗░░██╗██╗██╗░░░░░░█████╗░░██████╗░█████╗░██████╗░██╗░░██╗███████╗██████╗░░██████╗$(NOCOLOR)"
	@echo "$(GREEN)██╔══██╗██║░░██║██║██║░░░░░██╔══██╗██╔════╝██╔══██╗██╔══██╗██║░░██║██╔════╝██╔══██╗██╔════╝$(NOCOLOR)"
	@echo "$(GREEN)██████╔╝███████║██║██║░░░░░██║░░██║╚█████╗░██║░░██║██████╔╝███████║█████╗░░██████╔╝╚█████╗░$(NOCOLOR)"
	@echo "$(GREEN)██╔═══╝░██╔══██║██║██║░░░░░██║░░██║░╚═══██╗██║░░██║██╔═══╝░██╔══██║██╔══╝░░██╔══██╗░╚═══██╗$(NOCOLOR)"
	@echo "$(GREEN)██║░░░░░██║░░██║██║███████╗╚█████╔╝██████╔╝╚█████╔╝██║░░░░░██║░░██║███████╗██║░░██║██████╔╝$(NOCOLOR)"
	@echo "$(GREEN)╚═╝░░░░░╚═╝░░╚═╝╚═╝╚══════╝░╚════╝░╚═════╝░░╚════╝░╚═╝░░░░░╚═╝░░╚═╝╚══════╝╚═╝░░╚═╝╚═════╝░$(NOCOLOR)"
	@echo ""
	@echo "$(BLUE)Compilation finished!!$(NOCOLOR)"

%.o: %.c philo.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@echo "$(YELLOW)Object files removed.$(NOCOLOR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW)Executable removed.$(NOCOLOR)"

re: fclean all