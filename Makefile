##################################################
# 1)	Define the compiler
##################################################
COMPILER?=g++

##################################################
# 2)	Define paths
##################################################
SRCDIR=./src
INCDIR=./include
BUILDDIR=./build
BINDIR=./bin

##################################################
# 3)	Define compiler flags
##################################################
MODE?=DEBUG
GCC_FLAGS_DEBUG=-g -O -ggdb -D_GCC -D_DEBUG
GCC_FLAGS_RELEASE=-O3 -D_GCC -D_RELEASE
ICC_FLAGS_DEBUG=-g -O -D_ICC -D_DEBUG
ICC_FLAGS_RELEASE=-O3 -xHost -ip -D_ICC -D_DEBUG

##################################################
# 4)	Define extra flags
##################################################
FLAGS=
-include make.inc


###################################################
#
#	DO NOT EDIT
#
###################################################
PROG=horsesgit
INCLUDE=-I$(INCDIR)

OBJS= main.o \
      gitcommand.o

BUILD_OBJS = $(addprefix $(BUILDDIR)/, $(OBJS))

# Get compiler 	-----------------------------------
ifeq ($(COMPILER),g++)
   CC=g++
else ifeq ($(COMPILER),GNU)
   CC=g++
else ifeq ($(COMPILER),gcc)
   CC=g++
endif

ifeq ($(COMPILER),icpc)
   CC=icpc
else ifeq ($(COMPILER),INTEL)
   CC=icpc
else ifeq ($(COMPILER),icc)
   CC=icpc
endif

# Choose the correct flags  ----------------------
ifeq ($(CC),g++)
    ifeq ($(MODE),DEBUG)
        CFLAGS=$(GCC_FLAGS_DEBUG)
    else ifeq ($(MODE),RELEASE)
        CFLAGS=$(GCC_FLAGS_RELEASE)
    endif

else ifeq ($(CC),icpc)
    ifeq ($(MODE),DEBUG)
        CFLAGS=$(ICC_FLAGS_DEBUG)
    else ifeq ($(MODE),RELEASE)
        CFLAGS=$(ICC_FLAGS_RELEASE)
    endif
endif



#	--------------
#	Default target
#	--------------
.DEFAULT_GOAL := all

all: mkdirs $(BINDIR)/$(PROG)

$(BINDIR)/$(PROG): $(BUILD_OBJS)
	@echo ""
	@echo "Building " $(PROG)
	$(CC) $(FLAGS) $(CFLAGS) $(INCLUDE) -o $(BINDIR)/$(PROG) $(BUILD_OBJS)

run: FORCE
	$(BINDIR)/$(PROG)

##########################################################
#	General compilation rule
##########################################################
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp 
	@echo ""
	@echo "Compiling " $<
	$(CC) $(FLAGS) $(CFLAGS) $(INCLUDE) -c $< -o $@

##########################################################
#	Additional rules
##########################################################
mkdirs: 
	@mkdir -p $(BINDIR) $(INCDIR) $(BUILDDIR)

clean: FORCE
	@echo "Cleaning *.o files in " $(BUILDDIR)
	@rm -f $(BUILDDIR)/*.o

allclean: FORCE clean
	@echo "Cleaning " $(BINDIR)/$(PROG)
	@rm -f $(BINDIR)/$(PROG)

# Dummy target to force a rule execution
FORCE:
