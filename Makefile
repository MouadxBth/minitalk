# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbouthai <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/24 13:26:12 by mbouthai          #+#    #+#              #
#    Updated: 2022/07/24 14:29:48 by mbouthai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER	= server

CLIENT	= client

SERV_B	= server_bonus

CLIE_B	= client_bonus

CC	= gcc

CFLAGS	= -Wall -Werror -Wextra

HEADERS	= minitalk.h libft/libft.h ft_printf/ft_printf.h

INCS	= -Ilibft -Ift_printf

LIBFT	= libft.a

PRINTF	= libftprintf.a

LIBS	= -L./libft -L./ft_printf -lft -lftprintf

all: $(LIBFT) $(PRINTF) $(SERVER) $(CLIENT)

bonus: $(LIBFT) $(PRINTF) $(SERV_B) $(CLIE_B)

$(LIBFT):
	@make bonus -C libft

$(PRINTF):
	@make -C ft_printf

$(SERVER): server.o $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

$(CLIENT): client.o $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

$(SERV_B): server_bonus.o $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

$(CLIE_B): client_bonus.o $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

clean:
	@make clean -C libft
	@make clean -C ft_printf
	rm -f *.o

fclean: clean
	@make fclean -C libft
	@make fclean -C ft_printf
	rm -f $(SERVER) $(CLIENT)
	rm -f $(SERV_B) $(CLIE_B)

re: fclean all

.PHONY: all clean fclean re
