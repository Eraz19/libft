NAME:=libft.a

CC:=CC
CC_FLAGS:=-Werror -Wextra -Wall

AR:=ar
AR_FLAGS:=-rc

HDR_DIR:=.
HDRS:=$(HDR_DIR)/libft.h

SRC_DIR:=.
SRCS_MANDATORY:=$(SRC_DIR)/ft_isalpha.c    \
				$(SRC_DIR)/ft_isdigit.c    \
				$(SRC_DIR)/ft_isalnum.c    \
				$(SRC_DIR)/ft_isascii.c    \
				$(SRC_DIR)/ft_isprint.c    \
				$(SRC_DIR)/ft_strlen.c     \
				$(SRC_DIR)/ft_memset.c     \
				$(SRC_DIR)/ft_bzero.c      \
				$(SRC_DIR)/ft_memcpy.c     \
				$(SRC_DIR)/ft_memmove.c    \
				$(SRC_DIR)/ft_strlcpy.c    \
				$(SRC_DIR)/ft_strlcat.c    \
				$(SRC_DIR)/ft_toupper.c    \
				$(SRC_DIR)/ft_tolower.c    \
				$(SRC_DIR)/ft_strchr.c     \
				$(SRC_DIR)/ft_strrchr.c    \
				$(SRC_DIR)/ft_strncmp.c    \
				$(SRC_DIR)/ft_memchr.c     \
				$(SRC_DIR)/ft_memcmp.c     \
				$(SRC_DIR)/ft_strnstr.c    \
				$(SRC_DIR)/ft_atoi.c       \
				$(SRC_DIR)/ft_calloc.c     \
				$(SRC_DIR)/ft_strdup.c     \
				$(SRC_DIR)/ft_substr.c     \
				$(SRC_DIR)/ft_strjoin.c    \
				$(SRC_DIR)/ft_strtrim.c    \
				$(SRC_DIR)/ft_split.c      \
				$(SRC_DIR)/ft_itoa.c       \
				$(SRC_DIR)/ft_strmapi.c    \
				$(SRC_DIR)/ft_striteri.c   \
				$(SRC_DIR)/ft_putchar_fd.c \
				$(SRC_DIR)/ft_putstr_fd.c  \
				$(SRC_DIR)/ft_putendl_fd.c \
				$(SRC_DIR)/ft_putnbr_fd.c
SRCS_BONUS:=$(SRC_DIR)/ft_lstnew_bonus.c       \
			$(SRC_DIR)/ft_lstadd_front_bonus.c \
			$(SRC_DIR)/ft_lstsize_bonus.c      \
			$(SRC_DIR)/ft_lstlast_bonus.c      \
			$(SRC_DIR)/ft_lstadd_back_bonus.c  \
			$(SRC_DIR)/ft_lstdelone_bonus.c    \
			$(SRC_DIR)/ft_lstclear_bonus.c     \
			$(SRC_DIR)/ft_lstiter_bonus.c      \
			$(SRC_DIR)/ft_lstmap_bonus.c

OBJ_DIR:=.
OBJS_MANDATORY=$(SRCS_MANDATORY:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS=$(SRCS_BONUS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

bonus: all $(OBJS_BONUS)
	$(AR) $(AR_FLAGS) $(NAME) $(OBJS_BONUS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	cc -Werror -Wextra -Wall -c $< -o $@

$(NAME) : $(OBJS_MANDATORY)
	$(AR) $(AR_FLAGS) $@ $(OBJS_MANDATORY)

clean:
	rm -f $(OBJ_DIR)/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all
