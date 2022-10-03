#makefile to compile the .C files in this directory
#and write the .o output to the ../obj directory
#This makefile also creates the yess executable.
CC = g++
INC = ../inc
BIN = ../bin
OBJD = ../obj
CFLAGS = -g -c -Wall -Wno-unused-variable -std=c++11 -I $(INC)
OBJ = $(OBJD)/Tools.o $(OBJD)/Memory.o $(OBJD)/ConditionCodes.o \
      $(OBJD)/RegisterFile.o $(OBJD)/String.o $(OBJD)/yess.o \
      $(OBJD)/Loader.o

#rule to match .C with object in another directory
$(OBJD)/%.o: %.C 
	@mkdir -p $(OBJD)
	$(CC) $(CFLAGS) $< -o $@

$(BIN)/yess: $(OBJ)

#1) Need a .o target for the new .C files (String.C, yess.C, Loader.C)
#   Add those targets to the OBJ macro.
$(OBJD)/String.o: $(INC)/String.h

$(OBJD)/Loader.o: $(INC)/Loader.h $(INC)/Memory.h $(INC)/String.h

$(OBJD)/yess.o: $(INC)/Memory.h $(INC)/String.h $(INC)/Loader.h


#2) Need a ../bin/yess target that links together the .o files
#   to create a ../bin/yess executable (make the first target in
#   the makefile).  It actually doesn't need all of the .o files
#   yet, but it doesn't hurt to link them into the executable
#   Use the OBJ and BIN macros





#The rules below should match what you had in your old makefile
$(OBJD)/Memory.o: $(INC)/Tools.h $(INC)/Memory.h

$(OBJD)/Tools.o: $(INC)/Tools.h

$(OBJD)/RegisterFile.o: $(INC)/RegisterFile.h

$(OBJD)/ConditionCodes.o: $(INC)/ConditionCodes.h $(INC)/Tools.h

clean:
	rm -f $(OBJ)
