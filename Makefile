#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/07 17:38:00 by angagnie          #+#    #+#              #
#    Updated: 2016/03/03 17:05:55 by angagnie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# ==== Editable ====
NAME:=fdf
MODEL_PATH:=model/
MODEL:=calculus quaternion conversion system_tree
FILES=main view controller parser
# ==================

# ==== Standard ====
CC:=clang
CCHPATH:=cache/
SRCPATH:=src/
HDRPATH:=include/
IFLAGS=-I $(HDRPATH) -I Libft/include/
DEFLAG=
LFLAGS=-L Libft/ -lft
DEP=Libft/libft.a
CFLAGS=-Wall -Wextra $(IFLAGS) $(DEFLAG)
# ==================

# === Colors ===
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
YELLOW:="\033[1;33m"
BLUE:="\033[1;34m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0m"
# ==============

# ====== Auto ======
FILES+=$(addprefix $(MODEL_PATH),$(MODEL))
SRC=$(addprefix $(SRCPATH),$(addsuffix .c,$(FILES)))
OBJ=$(addprefix $(CCHPATH),$(addsuffix .o,$(FILES)))
# ==================
CCHF:=.cache_exists

usage:
	@echo "Usage : make    osx | x11    [all | re | clean | fclean | test]"

all: $(NAME)

$(NAME): $(OBJ) $(DEP)
	@echo $(GREEN) " - Compiling $@" $(EOC)
	@$(CC) $(OBJ) -o $@ $(IFLAGS) $(LFLAGS)

$(CCHPATH)%.o: $(SRCPATH)%.c $(CCHF)
	@echo $(PURPLE) " - Compiling $< into $@" $(EOC)
	@$(CC) $(CFLAGS) -c $< -o $@

%.c:
	@echo $(RED) "Missing file : $@" $(EOC)

$(CCHF):
	@mkdir $(CCHPATH)
	@mkdir $(CCHPATH)$(MODEL_PATH)
	@touch $(CCHF)

clean:
	@echo $(YELLOW) "Deleting cache" $(EOC)
	@rm -rf $(CCHPATH)
	@rm -f $(CCHF)

fclean: clean
	@echo $(YELLOW) "Deleting binairie" $(EOC)
	@rm -f $(NAME)

re: fclean all

test:
	@echo $(YELLOW)"Files :\n\033[0;33m"$(FILES)
	@echo $(BLUE)"Objects :\n\033[0;34m"$(OBJ)
	@echo $(CYAN)"Sources :\n\033[0;36m"$(SRC)

norme:
	@echo $(RED)
	@norminette $(SRC) $(HDRPATH) | grep -v  Norme -B1 || true
	@echo $(END)

Libft/libft.a:
	@echo $(BLUE) "Making $@" $(EOC)
	@make -C Libft/
	@make -C Libft clean

miniLibX_OSX/libmlx.a:
	@echo $(BLUE) "Making $@" $(EOC)
	@make -C miniLibX_OSX/

def_x11:
#	$(eval FILES+=main_x11)
	$(eval DEFLAG=-DX11)
	$(eval LFLAGS+=-lX11)

x11: def_x11

def_osx:
#	$(eval FILES+=main_osx)
	$(eval IFLAGS+=-I miniLibX_OSX/)
	$(eval LFLAGS+=-lmlx -framework OpenGL -framework AppKit)
	$(eval DEP+=miniLibX_OSX/libmlx.a)

osx: def_osx

.PHONY: all clean fclean re test norme x11 def_x11 osx def_osx usage
