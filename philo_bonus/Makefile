NAME = philo_bonus
INCDIR = ./includes/
SRCSDIR = ./srcs/
OBJDIR = ./objs/

SOURCES = $(wildcard $(SRCSDIR)*.c)
OBJECTS = $(addprefix $(OBJDIR), $(notdir $(SOURCES:.c=.o)))

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -g3

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJECTS)
	@echo "Linking $@"
	@$(CC) $(CFLAGS) -o $@ $(OBJECTS) -L -lft -lpthread -lrt
	@echo "$@ has been successfully built!"

$(OBJDIR)%.o: $(SRCSDIR)%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@echo "Cleaning objects"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "Cleaning $(NAME)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus