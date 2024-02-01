
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBRARY = libminitalk.a
SRC = server.c client.c
#SRCB = server_bonus.c client_bonus.c
OBJ = $(SRC:.c=.o)
#OBJB = $(SRCB:.c=.o)
AR = ar rcs

all: server client

server: server.c $(LIBRARY)
	$(CC) $(CFLAGS) -o server server.c -L. -lminitalk -Lprintf -lftprintf

client: client.c $(LIBRARY)
	$(CC) $(CFLAGS) -o client client.c -L. -lminitalk -Lprintf -lftprintf
 
$(LIBRARY): $(OBJ)
	@cd printf && $(MAKE)
	$(AR) $(LIBRARY) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f server client server_bonus client_bonus $(OBJ) $(OBJB)
	@cd printf && $(MAKE) clean

fclean: clean
	rm -f $(LIBRARY)
	@cd printf && $(MAKE) fclean

re: fclean all

NAME: all