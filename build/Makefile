
DEBUG		= -g -O0
RELEASE     = -O2 -DNDEBUG

CC			= clang
LD			= clang
RM			= rm -rf
RMDIR		= rmdir
AR          = llvm-ar
#AR          = /Library/Developer/CommandLineTools/usr/bin/libtool

CFLAGS		:= $(DEBUG) -MMD -MP
CPPFLAGS	:=
LDFLAGS		:=
PREFIX		:= /usr/local
TARGET_ARCH :=

LIBTARGET		= libcvoxel.a
FLUIDLIBTARGET		= libfluid.a
EXTERNLIBTARGET = libextern.a
UNITTESTLIBTARGET = libunittest.a
INTEGRATIONTESTLIBTARGET = libintegrationtest.a
TARGET		    = testRayTrace
INTEGRATIONTESTTARGET		    = testRayTrace
UNITTESTTARGET  = testGrid
SRCDIR		    = ../src
INCDIR		    = ../inc
FLUIDSRCDIR		    = ../fluid/src
FLUIDINCDIR		    = ../fluid/inc
EXTERNSRCDIR    = ../extern
OBJDIR		    = obj/cvoxel
FLUIDOBJDIR		    = obj/fluid
EXTERNOBJDIR    = obj/extern
UNITTESTOBJDIR    = obj/unittest
INTEGRATIONTESTOBJDIR    = obj/integrationtest
BINDIR		    = bin
LIBDIR          = lib
INTEGRATIONTESTSRCDIR = ../integrationtest
UNITTESTSRCDIR = ../unittest
INTEGRATIONTESTTARGETDIR = integrationtest
UNITTESTTARGETDIR = unittest

# Compiler Flags
ALL_CFLAGS		:= $(CFLAGS) -arch x86_64

# Preprocessor Flags
ALL_CPPFLAGS	:= $(CPPFLAGS)

ALL_LDFLAGS		:= $(LDFLAGS)
ALL_LDLIBS		:= -lc -lm
 
ALL_ARFLAGS     := rcs 
#ALL_ARFLAGS     :=-static 


SRC			:= $(shell find $(SRCDIR) -type f -name '*.c')
FLUIDSRC	:= $(shell find $(FLUIDSRCDIR) -type f -name '*.c')
EXTERNSRC   := $(shell find $(EXTERNSRCDIR) -type f -name '*.h')
UNITTESTSRC	:= $(shell find $(UNITTESTSRCDIR) -type f -name '*.h')
INTEGRATIONTESTSRC	:= $(shell find $(INTEGRATIONTESTSRCDIR) -type f -name '*.h')
OBJ			:= $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRC:.c=.o))
FLUIDOBJ	:= $(patsubst $(FLUIDSRCDIR)/%,$(FLUIDOBJDIR)/%,$(FLUIDSRC:.c=.o))
EXTERNOBJ   := $(patsubst $(EXTERNSRCDIR)/%,$(EXTERNOBJDIR)/%,$(EXTERNSRC:.h=.o))
UNITTESTOBJ	:= $(patsubst $(UNITTESTSRCDIR)/%,$(UNITTESTOBJDIR)/%,$(UNITTESTSRC:.h=.o))
INTEGRATIONTESTOBJ	:= $(patsubst $(INTEGRATIONTESTSRCDIR)/%,$(INTEGRATIONTESTOBJDIR)/%,$(INTEGRATIONTESTSRC:.h=.o))
DEP			:= $(OBJ:.o=.d) 
DEP         += $(FLUIDOBJ:.o=.d)

BIN         := $(BINDIR)/$(TARGET)
LIB			:= $(LIBDIR)/$(LIBTARGET)
FLUIDLIB	:= $(LIBDIR)/$(FLUIDLIBTARGET)
EXTERNLIB   := $(LIBDIR)/$(EXTERNLIBTARGET)
UNITTESTLIB   := $(LIBDIR)/$(UNITTESTLIBTARGET)
INTEGRATIONTESTLIB   := $(LIBDIR)/$(INTEGRATIONTESTLIBTARGET)
INTEGRATIONTEST := $(INTEGRATIONTESTTARGETDIR)/$(INTEGRATIONTESTTARGET)
UNITTEST := $(UNITTESTTARGETDIR)/$(UNITTESTTARGET)

UNITTESTFILE := CVLTestGrid.c
UNITTESTFULLPATH := $(UNITTESTSRCDIR)/$(UNITTESTFILE)

INTEGRATIONTESTFILE := CVLTestRayTrace.c
INTEGRATIONTESTFULLPATH := $(INTEGRATIONTESTSRCDIR)/$(INTEGRATIONTESTFILE)

-include $(DEP)

.DEFAULT_GOAL := all

all: $(INTEGRATIONTEST) $(UNITTEST)

$(UNITTEST):$(LIB) $(UNITTESTLIB) $(UNITTESTFULLPATH)
	$(CC) $(ALL_CFLAGS) $(UNITTESTFULLPATH) -L./lib   -o  $@ -lcvoxel 


$(INTEGRATIONTEST):$(LIB) $(FLUIDLIB) $(EXTERNLIB) $(INTEGRATIONTESTLIB) $(INTEGRATIONTESTFULLPATH)
	$(CC)  $(ALL_CFLAGS) $(INTEGRATIONTESTFULLPATH) -L./lib   -o  $@ -lcvoxel -lextern -lfluid


$(LIB): $(OBJ)
	$(AR) $(ALL_ARFLAGS)  $@ $^ 

$(FLUIDLIB): $(FLUIDOBJ)
	$(AR) $(ALL_ARFLAGS)  $@ $^ 

$(EXTERNLIB): $(EXTERNOBJ)
	$(AR) $(ALL_ARFLAGS) $@ $^ 

$(UNITTESTLIB): $(UNITTESTOBJ)
	$(AR) $(ALL_ARFLAGS)  $@ $^ 

$(INTEGRATIONTESTLIB): $(INTEGRATIONTESTOBJ)
	$(AR) $(ALL_ARFLAGS)  $@ $^ 

$(EXTERNOBJDIR)/%.o: $(EXTERNSRCDIR)/%.h
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) -c -x c -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) -c -x c -o $@ $<

$(FLUIDOBJDIR)/%.o: $(FLUIDSRCDIR)/%.c
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) -c -x c -o $@ $<

$(UNITTESTOBJDIR)/%.o: $(UNITTESTSRCDIR)/%.h
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) -c -x c -o $@ $<

$(INTEGRATIONTESTOBJDIR)/%.o: $(INTEGRATIONTESTSRCDIR)/%.h
	$(CC) $(ALL_CFLAGS) $(ALL_CPPFLAGS) -c -x c -o $@ $<

.PHONY: clean
clean:
	rm -rf obj/cvoxel/*
	rm -rf obj/extern/*
	rm -rf obj/unittest/*
	rm -rf obj/integrationtest/*
	rm -rf obj/fluid/*
	rm -rf bin/*
	rm -rf lib/*
	rm -rf output/*
	rm -rf unittest/*
	rm -rf integrationtest/*


