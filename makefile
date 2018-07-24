CC=gcc
SRCDIR=SRC
SRC=$(shell ls SRC/*.c)
OBJDIR=OBJ
OBJ=$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))
WARNINGS=-Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
         -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
         -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
         -Wuninitialized -Wconversion -Wstrict-prototypes
CFLAGS=-g -std=gnu11 $(WARNINGS)

all: shell

shell: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $^ $(CFLAGS)

