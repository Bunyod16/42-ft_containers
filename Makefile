NAME = ft_containers
SOURCES = main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++98

TESTDIR = test

VECTORTEST = v
MAPTEST = m

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -fsanitize=address -g3 -o $@ $^

$(VECTORTEST)ft: clean
	$(CC) -c $(CFLAGS) $(TESTDIR)/vector.cpp -DNAME_SPACE=ft 
	$(CC) $(CFLAGS) -fsanitize=address -DNAME_SPACE=ft $(TESTDIR)/vector.cpp -g3 -o $@ 

$(VECTORTEST)std: clean
	$(CC) -c $(CFLAGS) $(TESTDIR)/vector.cpp -DNAME_SPACE=std
	$(CC) $(CFLAGS) -fsanitize=address -DNAME_SPACE=std $(TESTDIR)/vector.cpp -g3 -o $@

$(MAPTEST)ft: clean
	$(CC) -c $(CFLAGS) $(TESTDIR)/map.cpp -DNAME_SPACE=ft 
	$(CC) $(CFLAGS) -fsanitize=address -DNAME_SPACE=ft $(TESTDIR)/map.cpp -g3 -o $@ 

$(MAPTEST)std: clean
	$(CC) -c $(CFLAGS) $(TESTDIR)/map.cpp -DNAME_SPACE=std
	$(CC) $(CFLAGS) -fsanitize=address -DNAME_SPACE=std $(TESTDIR)/map.cpp -g3 -o $@ 

%.o: %.cpp
	

clean:
	$(RM) $(VECTORTEST)ft
	$(RM) $(VECTORTEST)std
	$(RM) $(OBJECTS)
	
fclean: clean
	$(RM) $(NAME) $(VECTORTEST) $(MAPTEST)

re: fclean all

lint:
	cpplint --filter=-legal/copyright $(SOURCES)

.PHONY: all clean fclean re lint