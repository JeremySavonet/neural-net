SRC_DIR =src/*
SRC_DIR += main.cpp
HEADERS_DIR = include/

CC		= g++
CFLAGS	= -c -Wall
LDFLAGS	= -I$(HEADERS_DIR) 
EXEC	= neural-net
SRC		= $(wildcard $(SRC_DIR) .cpp)
OBJ		= $(SRC:.cpp=.o)
RM      = rm -f

neural-net: libs.o
	$(CC) -o $(EXEC) *.o
libs.o:
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC_DIR)
		
clean:
	$(RM) *.o	
dist-clean: clean
	$(RM) $(EXEC)
run: 
	./$(EXEC)
