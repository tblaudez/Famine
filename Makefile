# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tblaudez <tblaudez@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/03/31 15:06:14 by tblaudez      #+#    #+#                  #
#    Updated: 2021/05/12 10:06:26 by tblaudez      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

TARGET := Famine


AS := nasm
ASFLAGS ?= -felf64 -I include/
LDFLAGS ?=

SOURCES := src/famine.asm
HEADERS := include/famine.inc
OBJECTS := $(SOURCES:.asm=.o)

ifdef DEBUG
	ASFLAGS += -g -Fdwarf
endif

all: $(TARGET)

$(TARGET): $(OBJECTS) $(HEADERS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	@rm -vf $(OBJECTS)

fclean: clean
	@rm -vf $(TARGET)

re: fclean all

.PHONY: all clean fclean re