#general
CC    		:= gcc
CLC			:= openclc
RM			:= rm -rf
MKDIR 		:= mkdir -p
wFlags 		:= -Wall -O0
Archs 		:= -arch x86_64
Frameworks 	:= -framework OpenCL
srcPath	    := src
clPath		:= cl
incPath		:= inc
objPath		:= obj
binPath		:= bin
debugPath	:= debug
Project		:= matlib

#Debug
dbgFlags	:= $(wFlag) -g -D DEBUG

ifeq ($(dbg_verbose), yes)
dbgFlags	+= -D DEBUG_CONTEXT
dbgFlags	+= -D DEBUG_MALLOC
dbgFlags	+= -D DEBUG_FREE
dbgFlags	+= -D DEBUG_INIT
dbgFlags	+= -D DEBUG_OPERATION
endif

ifeq ($(dbg_verbose), alloc)
dbgFlags	+= -D DEBUG_MALLOC
dbgFlags	+= -D DEBUG_FREE
endif

ifeq ($(dbg_verbose), op&data)
dbgFlags	+= -D DEBUG_INIT
dbgFlags	+= -D DEBUG_OPERATION
endif

ifeq ($(dbg_verbose), context)
dbgFlags	+= -D DEBUG_CONTEXT
endif

ifeq ($(dbg_verbose), all)
dbgFlags	+= -D DEBUG_CONTEXT
dbgFlags	+= -D DEBUG_MALLOC
dbgFlags	+= -D DEBUG_FREE
dbgFlags	+= -D DEBUG_INIT
dbgFlags	+= -D DEBUG_OPERATION
dbgFlags	+= -D DEBUG_PRINT
endif

#Colors
RED			:= \033[0;31m
GREEN		:= \033[0;32m
BLUE		:= \033[0;34m
PURPLE		:= \033[0;35m
NOCOLOR		:= \033[0m

#common
rec_wildcard = $(foreach dir, $(wildcard $1*), $(call rec_wildcard, $dir/, $2) $(filter $(subst *,%,$2), $dir))

inc 		:= $(call rec_wildcard $(incPath)/, *.h)
src  		:= $(call rec_wildcard $(srcPath)/, *.c)
kernels		:= $(call rec_wildcard $(clPath)/, *.cl)

obj  		:= $(src:$(srcPath)/%c=%o)

# all: mrproper build

help:
	@echo "the project is in developement"
	@echo "make ./$(debugPath)/srcfile.dbg objects=\"object.o files.o dependencies.o if_there_is_any.o\""
	@echo "NB: srcfile.c should have a main function in the DEBUG macro space"
	@echo "ie: ./$(debugPath)/vectors.dbg objects=\"real.o complexe.o entity.o\""

$(debugPath)/%.dbg: $(srcPath)/%.c $(inc)
	@$(MAKE) directory path=$(dir $@)
	@if [ '$(objects)' != '' ]; then \
		$(MAKE) $(addprefix $(debugPath)/,$(objects)) Flags="$(Flags)"; \
		$(MAKE) compile OBJ='no' CFlags="$(dbgFlags) $(Flags)" out=$@ objects="$(addprefix $(debugPath)/,$(objects)) $<" 2> $(basename $@).err; \
	else \
		$(MAKE) compile OBJ='no' CFlags="$(dbgFlags) $(Flags)" out=$@ objects=$< 2> $(basename $@).err; \
	fi;

$(debugPath)/%.o: $(srcPath)/%.c
	@$(MAKE) directory path=$(dir $@)
	@$(MAKE) compile OBJ='yes' CFlags="$(dbgFlags) $(Flags)" out=$@ in=$< 2> $(basename $@).err

$(objPath)/%.o: $(srcPath)/%.c
	@$(MAKE) directory path=$(dir $@)
	@$(MAKE) compile OBJ='yes' CFlags="$(wFlag) $(Flags)" out=$@ in=$<

$(objPath)/%.o: $(srcPath)/%.c
	@$(MAKE) directory path=$(dir $@)
	@$(MAKE) compile OBJ='yes' CFlags="$(wFlag) $(Flags)" out=$@ in=$<

directory:
	@[ -d $(path) ] || $(MKDIR) $(path)

compile:
	@if [ $(OBJ) = 'yes' ]; then \
		$(CC) -I $(incPath) $(CFlags) -c -o $(out) $(in); \
	else \
		$(CC) -I $(incPath) $(CFlags) -o $(out) $(objects); \
	fi

mrproper:
	@[ ! -d $(binPath)   ] || $(RM) $(binPath)/*
	@[ ! -d $(objPath)   ] || $(RM) $(objPath)/*
	@[ ! -d $(debugPath) ] || $(RM) $(debugPath)/*

clean:
	@$(RM) $(binPath) $(objPath) $(docPath) $(debugPath)
