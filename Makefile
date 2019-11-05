COMPILER = g++
COPTIONS = -Wall -std=c++11
LOPTIONS =
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

EXEC = myGame

PROJECT = $(shell pwd)
SRCDIR = $(PROJECT)/src
OBJDIR = $(PROJECT)/obj

EXEDIR = $(PROJECT)

SRC = $(wildcard $(SRCDIR)/*.cpp)

NAME = $(basename $(notdir $(SRC)))
OBJ = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(NAME)))

build: makedirs $(OBJ)
	$(COMPILER) $(INC) -o $(EXEDIR)/$(EXEC) $(OBJ) $(LOPTIONS) $(LIBS)

# Object compilation, with header file.
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.hpp
	$(COMPILER) $(INC) -c $(COPTIONS) -o $@ $< $(LOPTIONS)

# Object compilation, if no header file.
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(COMPILER) $(INC) -c $(COPTIONS) -o $@ $< $(LOPTIONS)

# Installation
install: build
	cp $(EXEDIR)/$(EXECUTABLE1)

makedirs:
	mkdir -p $(OBJDIR)
	mkdir -p $(EXEDIR)

# --------------------------------------------------------------------------
#  Cleaning rules
# --------------------------------------------------------------------------

# Removing the object and temp files.
clean:
	rm -rf $(OBJDIR)
	rm -rf *~

# Removing the object and temp files and the executable.
mrproper: clean
	rm -rf $(EXEDIR)

help:
	echo
	echo "-------------------------------------------------------------"
	echo " Disponible rules                                            "
	echo
	echo " build     : compile the source files (default)              "
	echo " install   : install the executable in /usr/bin (sudo needed)"
	echo " clean     : remove the object files                         "
	echo " mrproper  : remove the object files and the executable      "
	echo " help      : print this help                                 "
	echo "-------------------------------------------------------------"
	echo