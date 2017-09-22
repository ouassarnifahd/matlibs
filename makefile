#general
CC    		:= gcc
RM			:= rm -rf
MKDIR 		:= mkdir -p
wFlag 		:= -Wall
srcPath		:= src
incPath		:= inc
objPath		:= obj
binPath		:= bin
debugPath	:= debug
Project		:= time_sort

#Debug
dbgFlags	:= $(wFlag) -D DEBUG

#Colors
RED			:= \033[0;31m
GREEN		:= \033[0;32m
BLUE		:= \033[0;34m
PURPLE		:= \033[0;35m
NOCOLOR		:= \033[0m

#common
src  		:= $(wildcard $(srcPath)/*.c)
obj  		:= $(src:$(srcPath)/%c=%o)

all: mrproper build

$(debugPath)/%.dbg: $(srcPath)/%.c $(inc)
	@$(MAKE) directory path=$(dir $@)
	@if [ '$(objects)' != '' ]; then \
		$(MAKE) $(addprefix $(debugPath)/,$(objects)) Flags="$(Flags)"; \
		$(MAKE) compile OBJ=no CFlags="$(dbgFlags) $(Flags)" out=$@ objects="$(addprefix $(debugPath)/,$(objects)) $<" 2> $(basename $@).err; \
	else \
		$(MAKE) compile OBJ=yes CFlags="$(dbgFlags) $(Flags)" out=$@ in=$< 2> $(basename $@).err; \
	fi;

$(debugPath)/%.o: $(srcPath)/%.c
	@$(MAKE) directory path=$(dir $@)
	@$(MAKE) compile OBJ='yes' CFlags="$(Flags)" out=$@ in=$<

$(objPath)/$(type)/%.o: $(srcPath)/%.c
	@$(MAKE) directory path=$(dir $@)
	@$(MAKE) compile OBJ='yes' CFlags="$(Flags)" out=$@ in=$<

$(binPath)/$(Project)_$(type): $(objPath)/$(type)/$(Project).o
	@$(MAKE) directory path=$(dir $@)
	@$(MAKE) compile OBJ='no' CFlags=$(wFlag) out=$@ objects="$(wildcard $(objPath)/*.o) $(staticOBJ) $<";

$(objPath)/$(type)/$(Project).o: $(srcPath)/main.c
	@$(MAKE) directory path=$(dir $@)
	@$(MAKE) compile OBJ='yes' CFlags="$(Flags)" out=$@ in=$<

$(objPath)/%.o: $(srcPath)/%.c
	@$(MAKE) directory path=$(dir $@)
	@$(MAKE) compile OBJ='yes' CFlags="$(Flags)" out=$@ in=$<

directory:
	@[ -d $(path) ] || $(MKDIR) $(path)

compile:
	@if [ $(OBJ) == yes ]; then $(CC) -I $(incPath) $(CFlags) -c -o $(out) $(in); else $(CC) -I $(incPath) $(CFlags) -o $(out) $(objects); fi

mrproper:
	@[ ! -d $(binPath)   ] || $(RM) $(binPath)/*
	@[ ! -d $(objPath)   ] || $(RM) $(objPath)/*
	@[ ! -d $(debugPath) ] || $(RM) $(debugPath)/*

clean:
	@$(RM) $(binPath) $(objPath) $(docPath) $(debugPath)
