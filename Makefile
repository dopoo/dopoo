
DEBUG       = -g -O0
RELEASE     = -O2 -DNDEBUG

CC          = gcc
LD          = gcc
RM          = rm -rf
RMDIR       = rmdir
AR          = ar

CFLAGS      := $(RELEASE) -MMD -MP
LDFLAGS     :=

LIBTARGET       = libdopoo.a
TARGET          = dopoo
SRCDIR          = src
INCDIR          = inc
TESTDIR         = test
OBJDIR          = build/obj/dopoo
BINDIR          = build/bin
LIBDIR          = build/lib
TESTFILE        = test/testMain.c

# Compiler Flags
ALL_CFLAGS      := $(CFLAGS) 
ALL_LDFLAGS     := $(LDFLAGS)
ALL_LDLIBS      := -lc -lm 
ALL_ARFLAGS     := rcs 


SRC         := $(shell find $(SRCDIR) -type f -name '*.c')
OBJ         := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRC:.c=.o))
TESTHEADER  := $(shell find $(TESTDIR) -type f -name '*.h')
DEP         := $(OBJ:.o=.d) 
DEP         += $(FLUIDOBJ:.o=.d)

BIN         := $(BINDIR)/$(TARGET)
LIB         := $(LIBDIR)/$(LIBTARGET)

-include $(DEP)

.DEFAULT_GOAL := all

all: $(BIN)

$(BIN):$(LIB) $(TESTFILE)  $(TESTHEADER)
	$(CC)  $(ALL_CFLAGS) $(TESTFILE) -L build/lib   -o  $@ -ldopoo


$(LIB): $(OBJ)
	$(AR) $(ALL_ARFLAGS)  $@ $^ 

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(ALL_CFLAGS) -c -x c -o $@ $<



.PHONY: clean
clean:
	rm -rf build/obj/dopoo/*
	rm -rf build/bin/*
	rm -rf build/lib/*


