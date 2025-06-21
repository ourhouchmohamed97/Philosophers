# ================= Colors =================
BLUE    = \033[0;34m
PURPLE  = \033[1;35m
YELLOW  = \033[0;33m
LIGHT_YELLOW = \033[1;33m
NOCOLOR = \033[0m
# ==========================================

NAME    = philo_bonus
CC      = cc
# CFLAGS  = -Wall -Wextra -Werror -g -fsanitize=thread
CFLAGS  = -Wall -Wextra -Werror
RM      = rm -rf

SRC     = philo_bonus.c \
          parse_bonus.c \
          exit_bonus.c \
          time_bonus.c \
          routine_bonus.c \
          end_bonus.c \
          life_bonus.c \
		  process_bonus.c \
		  utils_bonus.c \

OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) philo_bonus.h
	@echo "$(BLUE)Compiling philosopher...$(NOCOLOR)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo ""
	@echo "$(PURPLE)██████╗░██╗░░██╗██╗██╗░░░░░░█████╗░  ██████╗░░█████╗░███╗░░██╗██╗░░░██╗░██████╗$(NOCOLOR)"
	@echo "$(PURPLE)██╔══██╗██║░░██║██║██║░░░░░██╔══██╗  ██╔══██╗██╔══██╗████╗░██║██║░░░██║██╔════╝$(NOCOLOR)"
	@echo "$(PURPLE)██████╔╝███████║██║██║░░░░░██║░░██║  ██████╦╝██║░░██║██╔██╗██║██║░░░██║╚█████╗░$(NOCOLOR)"
	@echo "$(PURPLE)██╔═══╝░██╔══██║██║██║░░░░░██║░░██║  ██╔══██╗██║░░██║██║╚████║██║░░░██║░╚═══██╗$(NOCOLOR)"
	@echo "$(PURPLE)██║░░░░░██║░░██║██║███████╗╚█████╔╝  ██████╦╝╚█████╔╝██║░╚███║╚██████╔╝██████╔╝$(NOCOLOR)"
	@echo "$(PURPLE)╚═╝░░░░░╚═╝░░╚═╝╚═╝╚══════╝░╚════╝░  ╚═════╝░░╚════╝░╚═╝░░╚══╝░╚═════╝░╚═════╝░$(NOCOLOR)"
	@echo ""
	@echo "$(BLUE)Compilation finished!!$(NOCOLOR)"

%.o: %.c philo_bonus.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@echo "$(YELLOW)Object files removed.$(NOCOLOR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW)Executable removed.$(NOCOLOR)"

re: fclean all
