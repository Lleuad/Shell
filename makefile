CC=gcc
JC=emcc

SRCDIR=SRC
SRC=$(shell ls SRC/*.c)
HDR=$(shell ls SRC/*.h)

OBJDIR=.OBJ
OBJ=$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

OBJSDIR=.OBJS
OBJS=$(patsubst $(SRCDIR)/%.c,$(OBJSDIR)/%.o,$(SRC))

OBJDIRS=$(OBJDIR) $(OBJSDIR)

WARNINGS=-Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
         -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
         -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
         -Wuninitialized -Wconversion -Wstrict-prototypes
CFLAGS=-g -std=gnu11 $(WARNINGS)
.PHONY: clean

all: shell shell.js

$(OBJDIRS):
	mkdir -p $@

shell: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h | $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS)

shell.js: $(OBJS)
	$(JC) -o $@ $^ $(CFLAGS)

$(OBJSDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/%.h | $(OBJSDIR)
	$(JC) -o $@ -c $< $(CFLAGS)

$(SRCDIR)/%.h:

clean:
	rm -r $(OBJDIRS)
	rm shell.was{m,t}
