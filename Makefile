# ############################################################################ #
#                                                                              #
#                                                             .                #
#    Makefile                                                / \               #
#                                                           /   \              #
#    By: charles <charles.cabergs@gmail.com>               /o  o \             #
#                                                         /  v    \            #
#    Created: 2020/06/27 13:12:43 by charles             /    _    \           #
#    Updated: 2020/06/27 13:12:48 by charles            '-----------'          #
#                                                                              #
# ############################################################################ #

RM = rm -f

INCDIR = inc
SRCDIR = src
OBJDIR = obj
OBJDIRS = $(shell find $(SRCDIR) -type d | sed 's/src/$(OBJDIR)/')

INC = $(shell find $(INCDIR) -name "*.h")
SRC = $(shell find $(SRCDIR) -name "*.c")
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

CC = gcc
CCFLAGS = -I$(INCDIR) -Wall -Wextra #-Werror
LDFLAGS = -lncurses

NAME = hanoi

all: prebuild $(NAME)

prebuild:
	@for subdir in $(OBJDIRS); do mkdir -vp $$subdir; done

$(NAME): $(OBJ)
	@echo "Linking: $@"
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC)
	@echo "Compiling: $@"
	@$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	@echo "Removing objects"
	@$(RM) -r $(OBJDIR)

fclean:
	@echo "Removing objects"
	@$(RM) -r $(OBJDIR)
	@echo "Removing exectable"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all prebuild clean fclean re
