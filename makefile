#general
CC    		:= gcc
CLC			:= openclc
RM			:= rm -rf
MKDIR 		:= mkdir -p
MAKE		:= make

#Flags
wFlags 		:= -Wall -O0
Archs 		:= -arch x86_64
Frameworks 	:= -framework OpenCL
Libs		:= -lSDL
CFlags		:= $(wFlags) $(Archs)

#Paths
srcPath		:= src
clPath		:= cl
incPath		:= inc
objPath		:= obj
binPath		:= bin

#Project Name
Project		:= matlib
buildFlags  := -D BUILD

#Debug
dbgFlags	:= -g -D DEBUG
debugPath	:= debug

# dbg_verbose options: alloc, op&data, context, memory, all
ifeq ($(dbg_verbose), alloc)
dbgFlags += -D DEBUG_MALLOC
dbgFlags += -D DEBUG_FREE
dbgFlags += -D DEBUG_CONTEXT
dbgFlags += -D DEBUG_INLINE
endif

ifeq ($(dbg_verbose), op&data)
dbgFlags += -D DEBUG_INIT
dbgFlags += -D DEBUG_OPERATION
dbgFlags += -D DEBUG_CONTEXT
dbgFlags += -D DEBUG_INLINE
endif

ifeq ($(dbg_verbose), context)
dbgFlags += -D DEBUG_CONTEXT
dbgFlags += -D DEBUG_INLINE
endif

ifeq ($(dbg_verbose), memory)
dbgFlags += -D DEBUG_MEMORY
endif

ifeq ($(dbg_verbose), all)
dbgFlags += -D DEBUG_CONTEXT
dbgFlags += -D DEBUG_INLINE
dbgFlags += -D DEBUG_MEMORY
dbgFlags += -D DEBUG_MALLOC
dbgFlags += -D DEBUG_FREE
dbgFlags += -D DEBUG_INIT
dbgFlags += -D DEBUG_OPERATION
dbgFlags += -D DEBUG_PRINT
endif

#Colors
BLACK	:= \033[0;30m
GRAY	:= \033[1;30m
RED		:= \033[0;31m
LRED	:= \033[1;31m
GREEN	:= \033[0;32m
LGREEN	:= \033[1;32m
BROWN	:= \033[0;33m
YELLOW	:= \033[1;33m
BLUE	:= \033[0;34m
LBLUE	:= \033[1;34m
PURPLE	:= \033[0;35m
LPURPLE	:= \033[1;35m
CYAN	:= \033[0;36m
LCYAN	:= \033[1;36m
LGRAY	:= \033[0;37m
WHITE	:= \033[1;37m
NOCOLOR := \033[0m

#common
inc 	:= $(shell find $(incPath) -name '*.h')
src  	:= $(shell find $(srcPath) -name '*.c')
kernels	:= $(shell find $(clPath) -name '*.cl')

obj		:= $(src:$(srcPath)/%c=$(objPath)/%o)
dobj	:= $(src:$(srcPath)/%c=$(debugPath)/%o)

all: mrproper dbuild build

help:
	@echo "the project is in developement"
	@echo "usage: make ./$(debugPath)/srcfile.dbg objects=\"object.o files.o dependencies.o if_there_is_any.o\""
	@echo "NB: srcfile.c should have a main function in the DEBUG macro space"
	@echo "ie: ./$(debugPath)/structures/vectors.dbg objects=\"structures/real.o structures/complexe.o structures/entity.o\""

build: $(obj)
	@$(MAKE) directory path=$(binPath)/Release
	@$(MAKE) compile OBJ='no' Flags="$(CFlags) $(buildFlags)" out=$(binPath)/Release/$(Project) objects="$^"

dbuild: $(dobj)
	@$(MAKE) directory path=$(binPath)/Debug
	@$(MAKE) compile OBJ='no' Flags="$(CFlags) $(buildFlags) $(dbgFlags)" out=$(binPath)/Debug/$(Project) objects="$^"


$(objPath)/%.o: $(srcPath)/%.c
	@$(MAKE) directory path=$(dir $@)
	@$(MAKE) compile OBJ='yes' Flags="$(CFlags) $(buildFlags)" out=$@ in=$<

#debug
$(debugPath)/%.o: $(srcPath)/%.c
	@$(MAKE) directory path=$(dir $@)
	@$(MAKE) compile OBJ='yes' Flags="$(CFlags) $(dbgFlags)" out=$@ in=$< 2> $(basename $@).err


directory:
	@[ -d $(path) ] || echo "$(LRED)Creating $(LPURPLE)Path:$(GREEN) $(path)$(NOCOLOR)"; $(MKDIR) $(path)

compile:
	@if [ $(OBJ) = 'yes' ]; then \
		echo "$(LRED)Generating $(LPURPLE)Object $(LRED)file:$(GREEN) $(out)$(NOCOLOR)"; \
		$(CC) -I $(incPath) $(Flags) -c -o $(out) $(in); \
	else \
		echo "$(LRED)Generating $(LPURPLE)Binary $(LRED)file:$(GREEN) $(out)$(NOCOLOR)"; \
		$(CC) -I $(incPath) $(Flags) -o $(out) $(objects); \
	fi

mrproper:
	@echo "$(LRED)Cleaning...$(NOCOLOR)"
	@[ ! -d $(binPath)   ] || $(RM) $(binPath)/*
	@[ ! -d $(objPath)   ] || $(RM) $(objPath)/*
	@[ ! -d $(debugPath) ] || $(RM) $(debugPath)/*

clean:
	@[ ! -d $(binPath)   ] || $(RM) $(binPath)
	@[ ! -d $(objPath)   ] || $(RM) $(objPath)
	@[ ! -d $(debugPath) ] || $(RM) $(debugPath)
