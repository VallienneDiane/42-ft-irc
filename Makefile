# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/04 16:27:56 by dvallien          #+#    #+#              #
#    Updated: 2022/11/08 13:49:44 by dvallien         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98 #-fsanitize=address

PATH_SRCS		=	srcs
PATH_DEP		=	dep
PATH_OBJS		=	obj
PATH_INCLUDES	=	incs
PATH_BOTS		=	bots/bin
PATH_BOTS_SRCS	=	bots/srcs

LST_SRCS		=	main.cpp 				\
					iomanagement.cpp 		\
					Channel.cpp 			\
					User.cpp 				\
					signalManager.cpp 		\
					numericReply.cpp		\
					cmds/passHandler.cpp	\
					cmds/handleMsg.cpp 		\
					cmds/loginMsg.cpp		\
					cmds/pingPong.cpp		\
					cmds/join.cpp			\
					cmds/privmsg.cpp		\
					cmds/part.cpp			\
					cmds/invite.cpp			\
					cmds/names.cpp			\
					cmds/topic.cpp			\
					cmds/quit.cpp			\
					cmds/kick.cpp			\
					cmds/mode.cpp			\
					cmds/list.cpp			\

LST_BOTS_SRCS	=	fumier.cpp	\
					coolBot.cpp

LST_OBJS		=	${LST_SRCS:.cpp=.o}
LST_DEP			=	${LST_SRCS:.cpp=.d}
LST_BOTS		=	${LST_BOTS_SRCS:.cpp=.bot}

SUB_DIR	:= 	cmds	\

SRC =		$(addprefix ${PATH_SRCS}/,${LST_SRCS})
DEP =		$(addprefix ${PATH_DEP}/,${LST_DEP})
OBJS =		$(addprefix ${PATH_OBJS}/,${LST_OBJS})
BOTS_SRC =	$(addprefix ${PATH_BOT_SRCS}/,${LST_BOTS_SRCS})
BOTS	=	$(addprefix ${PATH_BOTS}/,${LST_BOTS})

all :				${NAME} Makefile

bot :				${BOTS}

${NAME} :			${OBJS}
					${CC} ${FLAGS} ${OBJS} -o $@

${PATH_DEP}/%.d :	${PATH_SRCS}/%.cpp Makefile
					mkdir -p $(PATH_DEP) $(addprefix $(PATH_DEP)/, $(SUB_DIR))
					${CC} ${FLAGS} -MM -MF $@ -MT "${PATH_OBJS}/$*.o $@" $<


${PATH_OBJS}/%.o:	${PATH_SRCS}/%.cpp Makefile
					mkdir -p $(PATH_OBJS) $(addprefix $(PATH_OBJS)/, $(SUB_DIR))
					${CC} ${FLAGS} -c $< -o $@ -I ${PATH_INCLUDES}

${PATH_BOTS}/%.bot:	${PATH_BOTS_SRCS}/%.cpp Makefile | ${PATH_BOTS}
					${CC} ${FLAGS} $< -o $@

${PATH_BOTS}:
					mkdir bots/bin

clean :
					rm -rf obj dep

bclean :
					rm -rf ${PATH_BOTS}

fclean :			clean bclean
					rm -f ${NAME}

re :				fclean all

-include ${DEP}

.PHONY: all re clean fclean
