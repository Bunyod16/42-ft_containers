NAME = span
SOURCES = main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -fsanitize=address -g3 -o $@ $^

%.o: %.cpp
	$(CC) -c $(CFLAGS) $<

clean:
	$(RM) $(OBJECTS)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all

lint:
	cpplint --filter=-legal/copyright $(SOURCES)

.PHONY: all clean fclean re lint