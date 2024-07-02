CC = cc
CFLAGS = -Werror -Wextra -Wall
RM = rm -rf

SRC_SRVR = server.c
SRC_CLNT = client.c 

CLNT_NAME = client
SRVR_NAME = server

OBJ_SRVR = $(SRC_SRVR:.c=.o)
OBJ_CLNT = $(SRC_CLNT:.c=.o)

all : $(CLNT_NAME) $(SRVR_NAME)

$(CLNT_NAME) : $(OBJ_CLNT) minitalk.h
	$(CC) $(CFLAGS) $(OBJ_CLNT) -o $(CLNT_NAME)

$(SRVR_NAME) : $(OBJ_SRVR) minitalk.h
	$(CC) $(CFLAGS) $(OBJ_SRVR) -o $(SRVR_NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ_CLNT) $(OBJ_SRVR)

fclean : clean
	$(RM) $(CLNT_NAME) $(SRVR_NAME)

re : fclean all