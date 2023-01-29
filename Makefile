NAME = ft_containers
SOURCES = main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++98

TESTDIR = test

VECTORTEST = vtest
MAPTEST = mtest

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -fsanitize=address -g3 -o $@ $^

$(VECTORTEST): $(TESTDIR)/vector.o
	$(CC) $(CFLAGS) -fsanitize=address $^ -g3 -o $@

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJECTS)
	
fclean: clean
	$(RM) $(NAME) $(VECTORTEST) $(MAPTEST)

re: fclean all

lint:
	cpplint --filter=-legal/copyright $(SOURCES)

.PHONY: all clean fclean re lint