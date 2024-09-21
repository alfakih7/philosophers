# Makefile for philo project

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -pthread

# Name of the executable
NAME = philo

# Source files
SRCS = main.c \
       philo.h \
       parsing.c \
       routine.c \
       init.c \
       utils.c

# Object files
OBJS = $(SRCS:.c=.o)

# Build the executable
all: $(NAME)

# Rule to create the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Rule to compile .c files to .o files
%.o: %.c
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
