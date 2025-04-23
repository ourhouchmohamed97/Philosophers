# ================= Colors =================
BLUE    = \033[0;34m
PURPLE  = \033[1;35m
YELLOW  = \033[0;33m
LIGHT_YELLOW = \033[1;33m
NOCOLOR = \033[0m
# ==========================================

NAME    = philo
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -pthread
RM      = rm -rf

SRC     = philo.c \
          parse.c \
          exit.c \
          time.c \
          routine.c \
          end.c \
          life.c \

OBJ     = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) philo.h
	@echo "$(BLUE)Compiling philosopher...$(NOCOLOR)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo ""
	@echo "$(PURPLE).______    __    __   __   __        ______        _______.  ______   .______    __    __   _______ .______      $(NOCOLOR)"
	@echo "$(PURPLE)|   _  \  |  |  |  | |  | |  |      /  __  \      /       | /  __  \  |   _  \  |  |  |  | |   ____||   _  \     $(NOCOLOR)"
	@echo "$(PURPLE)|  |_)  | |  |__|  | |  | |  |     |  |  |  |    |   (----\`|  |  |  | |  |_)  | |  |__|  | |  |__   |  |_)  |    $(NOCOLOR)"
	@echo "$(PURPLE)|   ___/  |   __   | |  | |  |     |  |  |  |     \   \    |  |  |  | |   ___/  |   __   | |   __|  |      /     $(NOCOLOR)"
	@echo "$(PURPLE)|  |      |  |  |  | |  | |  \`----.|  \`--'  | .----)   |   |  \`--'  | |  |      |  |  |  | |  |____ |  |\  \----.$(NOCOLOR)"
	@echo "$(PURPLE)| _|      |__|  |__| |__| |_______| \______/  |_______/     \______/  | _|      |__|  |__| |_______|| _| \`._____|$(NOCOLOR)"
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