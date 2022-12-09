SRCS =  ft_atoi.c		\
		ft_bzero.c		\
		ft_calloc.c		\
		ft_isalnum.c	\
		ft_isalpha.c 	\
		ft_isascii.c	\
		ft_isdigit.c	\
		ft_isprint.c	\
		ft_itoa.c		\
		ft_memchr.c		\
		ft_memcmp.c		\
		ft_memcpy.c		\
		ft_memmove.c 	\
		ft_memset.c		\
		ft_putchar_fd.c	\
		ft_putendl_fd.c \
		ft_putnbr_fd.c	\
		ft_putstr_fd.c	\
		ft_split.c		\
		ft_strchr.c		\
		ft_strdup.c		\
		ft_striteri.c	\
		ft_strjoin.c 	\
		ft_strlcat.c	\
		ft_strlcpy.c	\
		ft_strlen.c		\
		ft_strmapi.c	\
		ft_strcmp.c		\
		ft_strncmp.c	\
		ft_strnstr.c	\
		ft_strrchr.c	\
		ft_strtrim.c	\
		ft_substr.c		\
		ft_tolower.c	\
		ft_toupper.c    \
		ft_printf.c     \
		ft_printf_utils.c \
		ft_puthex.c     \
		get_next_line_bonus.c \
		get_next_line_utils_bonus.c \
		ft_arradd_back.c

SRCSB =	ft_lstnew.c			\
		ft_lstadd_front.c	\
		ft_lstsize.c		\
		ft_lstlast.c		\
		ft_lstadd_back.c	\
		ft_lstclear.c		\
		ft_lstdelone.c		\
		ft_lstiter.c		\
		ft_lstmap.c			\
		ft_lstprint.c		\
		$(SRCS)

NAME = libft.a

OBJS = $(SRCS:.c=.o)

OBJSB = $(SRCSB:.c=.o)

CC = gcc

CC_FLAGS = -Wall -Wextra -Werror -g

%.o		:	%.c
	@echo "Compiling $<"
	@$(CC) -c $(CC_FLAGS) -o $@ $<

$(NAME): $(OBJS) $(SRCS) $(OBJSB) $(SRCSB)
	@echo "Creating $(NAME)"
	@ar src $(NAME) $(OBJS) $(OBJSB)

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus:
	@$(CC) -c $(CC_FLAGS) $(SRCSB)
	@ar src $(NAME) $(OBJSB)

.PHONY: all, clean, fclean, re
