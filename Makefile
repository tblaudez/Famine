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
ASFLAGS ?= -felf64
CFLAGS ?= -c -Wall -Wextra -I include/ -nostdlib -fPIC -nodefaultlibs -Wno-stack-protector -fno-builtin
LDFLAGS ?= -nostdlib -fPIC

C_SOURCES := $(shell find src/ -type f -name '*.c')
ASM_SOURCES := $(shell find src/ -type f -name '*.asm')
# payload.o and end.o MUST be linked respectively first and last
ALL_OBJECTS := src/asm/payload.o $(C_SOURCES:.c=.o) $(ASM_SOURCES:.asm=.o) src/asm/end.o
HEADERS := include/famine.h

all: $(TARGET)

$(TARGET): $(ALL_OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -vf $(ALL_OBJECTS)

fclean: clean
	@rm -vf $(TARGET)

re: fclean all

.PHONY: all clean fclean re