### OPERATING SYSTEM ###
OS=			$(shell uname -s)

### EXECUTABLE ###
NAME=		philo

### COMPILATION ###
CC=			gcc
CFLAGS=		-Wall -Werror -Wextra -pthread -g

### PATHS ###
INCL_PATH=		incl/
SRCS_PATH=		srcs/
OBJS_PATH=		objs/

### SOURCE FILES ###
SRC_NAME=		$(NAME).c
#SRC_BONUS=		$(NAME)_bonus.c
SRCS=			error_handling.c \
				actions.c \
				ft_atoi.c \
				ft_atoui.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_strncmp.c \
				ft_strlen.c
SRCS_NAME=		$(addprefix $(SRCS_PATH), $(SRC_NAME) $(SRCS))
#SRCS_BONUS=	$(addprefix $(SRCS_PATH), $(SRC_BONUS) $(SRCS))

### OBJECT FILES ###
OBJ_NAME=		$(SRC_NAME:.c=.o)
#OBJ_BONUS=		$(SRC_BONUS:.c=.o)
OBJS=			$(SRCS:.c=.o)
OBJS_NAME=		$(addprefix $(OBJS_PATH), $(OBJ_NAME) $(OBJS))
#OBJS_BONUS=	$(addprefix $(OBJS_PATH), $(OBJ_BONUS) $(OBJS))

### INCLUDES ###
INC=			-I $(INCL_PATH)

### COLOURS ###
ifeq ($(OS), Linux)
	ECHO=   echo "
else
	ECHO=   echo "
endif
GREEN=		$(addprefix $(ECHO), \033[1;32m)
RED=		$(addprefix $(ECHO), \033[1;31m)
DEFAULT=	\033[0m"

### IMPLICT RULES ###
%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

### ACTIVE RULES ###
all: $(NAME)

$(NAME): $(OBJS_PATH) $(OBJS_NAME)
	@$(CC) $(CFLAGS) $(OBJS_NAME) $(INC) -o $(NAME)
	@$(GREEN)$(NAME) Program created$(DEFAULT)

$(OBJS_PATH):
	@mkdir -p $@

clean:
	@rm -rf $(OBJS_PATH)
	@$(RED)Object files removed$(DEFAULT)

fclean: clean
	@rm -f $(NAME)
	@$(RED)$(NAME) Program removed$(DEFAULT)

re: fclean all

### NORMINETTE ###
norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS_PATH)
	@norminette -R CheckForbiddenSourceHeader $(INCL_PATH)
	@norminette -R CheckDefine $(SRCS_PATH)
	@norminette -R CheckDefine $(INCL_PATH)

### PHONY RULE ###
.PHONY: all bonus clean fclean re norm