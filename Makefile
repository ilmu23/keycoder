NAME	=	keycoder

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): main.c
	@printf "\e[32;1mKEYCODER >\e[m Compiling %s\n" $@
	@$(CC) $(CFLAGS) main.c -o $@
	@printf "\e[32;1mKEYCODER >\e[m \e[1mDone!\e[m\n"

clean:
	@rm -f $(NAME)

re: clean all

.PHONY: all clean re
