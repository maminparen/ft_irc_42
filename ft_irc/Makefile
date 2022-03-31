NAME		=	IrcServ

CC			=	c++ -std=c++98
CFLAGS		=	-Wall -Werror -Wextra

HEADER_DIR	=	./include
SRC_DIR		=	./src
OBJ_DIR		=	./obj

HEADER		=	Chanel.hpp Commands.hpp Ping.hpp Server.hpp ServerException.hpp User.hpp Utils.hpp

SRC			=	Chanel.cpp Commands.cpp main.cpp Server.cpp User.cpp Utils.cpp

OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

BOTFOLDER	=	bonus/

RM_DIR		=	rm -rf
RM_FILE		=	rm -f

#COLORS
C_NO		=	"\033[00m"
C_OK		=	"\033[32m"
C_GOOD		=	"\033[32m"

#DEBUG
SUCCESS		=	$(C_GOOD)SUCCESS$(C_NO)
OK			=	$(C_OK)OK$(C_NO)

all			:	$(NAME) bonus

bonus		:
	@$(MAKE) -C $(BOTFOLDER) all

$(OBJ)		: 	| $(OBJ_DIR)	

$(OBJ_DIR)	:
				@mkdir -p $(OBJ_DIR)
			
$(OBJ_DIR)/%.o	:	$(SRC_DIR)/%.cpp ${HEADER_DIR}/*.hpp Makefile
					$(CC) $(CFLAG) -c $< -o $@

$(NAME)		:	$(OBJ)
				$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
				@echo "\tCompiling...\t" [ $(NAME) ] $(SUCCESS)

clean		:
				@$(RM_DIR) $(OBJ_DIR) 
				@$(MAKE) -C $(BOTFOLDER) clean
				@echo "\tCleaning...\t" [ $(OBJ_DIR) ] $(OK)

fclean		:	clean
				@$(RM_FILE) $(NAME)
				@$(MAKE) -C $(BOTFOLDER) fclean
				@echo "\tDeleting...\t" [ $(NAME) ] $(OK)

re			:	fclean all

.PHONY		:	all, clean, fclean, re, test, bonus