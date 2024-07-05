#########################
######    NAME    #######
#########################

NAME 		= philo

#########################
######   SOURCES  #######
#########################

SRC_DIR		=	src

SRC			=	main.c \

FILES		=	${addprefix ${SRC_DIR}/,${SRC}}

########################
######  OBJECTS  #######
########################

OBJ_DIR		=	objs

OBJETS		=	${FILES:${SRC_DIR}/%.c=${OBJ_DIR}/%.o}

#########################
######  INCLUDES  #######
#########################

INC_DIR		=	./inc

LIB_DIR		=	./lib

LIBFT_DIR	=	$(LIB_DIR)/libft

LIBFT		=	libft.a

###########################
######  COMPILATION  ######
###########################

CFLAGS		=	-Wall -Wextra -Werror

###########################
######     RULES     ######
###########################

all : $(NAME)

$(NAME): $(LIBFT_DIR)/$(LIBFT) $(OBJETS)
	cc $(OBJETS) $(LIBFT_DIR)/$(LIBFT) -o $(NAME) $(CFLAGS) -pthread

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c $(INC_DIR)/philosopher.h
	@mkdir -p ${dir $@}
	cc $(CFLAGS) -c -o $@ $< -g

$(LIBFT_DIR)/$(LIBFT): $(LIBFT_DIR)/libft.h
	make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C lib/libft/ fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re
