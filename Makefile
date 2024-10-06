# Makefile for philo project

# Compiler
CC = cc

# Compiler flags
CFLAGS =  -g3 -fsanitize=thread 
# CFLAGS = -Wall -Wextra -Werror


# Name of the executable
NAME = philo

# Source files
SRCS = main.c \
       parsing.c \
       routine_utils.c \
       init.c \
       utils.c \
	   eat.c \
	   routine.c \
	   simulation.c

# Object files
OBJS = $(SRCS:.c=.o)

# Build the executable
all: $(NAME)

# Rule to create the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

# Rule to compile .c files to .o files
%.o: %.c Philo.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Clean object files and the executable
fclean: clean
	rm -f $(NAME)

# Rebuild the project
re: fclean all

.PHONY: all clean fclean re
