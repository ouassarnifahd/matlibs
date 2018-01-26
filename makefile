#general
CC    		:= gcc
CLC			:= openclc
RM			:= rm -rf
MKDIR 		:= mkdir -p
MAKE		:= make

#Paths
srcPath		:= src
clPath		:= cl
libPath		:= lib
incPath		:= inc
objPath		:= obj
binPath		:= bin

#Flags
wFlags 		:= -Wall -O0
Archs 		:= -arch x86_64
Frameworks 	:= -framework OpenCL -framework OpenGL
Libs		:= -I$(libPath)
CFlags		:= $(wFlags) $(Archs) $(Libs)
LFlags 		:= $(Frameworks) -lglfw -lglew

#Project Name
Project		:= matlib
buildName	?=
buildPath	:= $(srcPath)/$(buildName)
buildPath	:= $(buildPath:%/=%)
buildFlags  := -D __BUILD__

#Debug
dbgFlags	:= -g -D __DEBUG__
debugPath	:= debug
verbose		?= context

#verbose options: alloc, op&data, context, memory, print, graphics, all
ifeq ($(verbose), all)
  verbose += alloc op&data context memory print graphics
endif

ifneq (,$(findstring alloc , $(verbose)))
  dbgFlags += -D __DEBUG__MALLOC__
  dbgFlags += -D __DEBUG__FREE__
endif

ifneq (,$(findstring context , $(verbose)))
  dbgFlags += -D __DEBUG__CONTEXT__
  dbgFlags += -D __DEBUG__INLINE__
endif

ifneq (,$(findstring op&data , $(verbose)))
  dbgFlags += -D __DEBUG__INIT__
  dbgFlags += -D __DEBUG__OPERATION__
endif

ifneq (,$(findstring memory , $(verbose)))
  dbgFlags += -D __DEBUG__MEMORY__
endif

ifeq ($(verbose), graphics)
  dbgFlags += -D __DEBUG__OpenGL__
  dbgFlags += -D __DEBUG__GCONTEXT__
endif

ifneq (,$(findstring print , $(verbose)))
  dbgFlags += -D __DEBUG__PRINT__
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
src  	:= $(shell find $(buildPath) -name '*.c')
kernels	:= $(shell find $(clPath) -name '*.cl')

obj		:= $(src:$(srcPath)/%c=$(objPath)/%o)
dobj	:= $(src:$(srcPath)/%c=$(debugPath)/%o)

all: mrproper dbg$(Project) $(Project)

help:
	@echo "the project is in developement"
	@echo "usage: make ./$(debugPath)/srcfile.dbg objects=\"object.o files.o dependencies.o if_there_is_any.o\""
	@echo "NB: srcfile.c should have a main function in the DEBUG macro space"
	@echo "ie: ./$(debugPath)/structures/vectors.dbg objects=\"structures/real.o structures/complexe.o structures/entity.o\""

$(Project): $(obj)
	@$(MAKE) directory path=$(binPath)/Release
	@$(MAKE) compile OBJ='no' Flags="$(buildFlags)" out=$(binPath)/Release/$(Project) objects="$^"

dbg$(Project): $(dobj)
	@$(MAKE) directory path=$(binPath)/Debug
	@$(MAKE) compile OBJ='no' Flags="$(buildFlags) $(dbgFlags)" out=$(binPath)/Debug/$(Project) objects="$^"

$(objPath)/%.o: $(srcPath)/%.c
	@$(MAKE) directory path=$(dir $@)
	@$(MAKE) compile OBJ='yes' Flags="$(buildFlags)" out=$@ in=$<

#debug
$(debugPath)/%.o: $(srcPath)/%.c
	@$(MAKE) directory path=$(dir $@)
	@$(MAKE) compile OBJ='yes' Flags="$(dbgFlags)" out=$@ in=$< 2> $(basename $@).err


directory:
	@[ -d $(path) ] || echo "$(LRED)Creating $(LPURPLE)Path:$(GREEN) $(path)$(NOCOLOR)"; $(MKDIR) $(path)

compile:
	@if [ $(OBJ) = 'yes' ]; then \
		echo "$(LRED)Generating $(LPURPLE)Object $(LRED)file:$(GREEN) $(out)$(NOCOLOR)"; \
		$(CC) -I $(incPath) $(CFlags) $(Flags) -c -o $(out) $(in); \
	else \
		echo "$(LRED)Generating $(LPURPLE)Binary $(LRED)file:$(GREEN) $(out)$(NOCOLOR)"; \
		$(CC) -I $(incPath) $(LFlags) $(CFlags) $(Flags) -o $(out) $(objects); \
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
