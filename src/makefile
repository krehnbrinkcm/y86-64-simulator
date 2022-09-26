#makefile to compile the .C files in this directory
#and write the .o output to the ../obj directory
CC = g++
INC = ../inc
BIN = ../bin
OBJD = ../obj
CFLAGS = -g -c -Wall -std=c++11 -I $(INC)

#rule to match .C with object in another directory
$(OBJD)/%.o: %.C create$(OBJD)
	$(CC) $(CFLAGS) $< -o $(OBJD)/$@

#1) need a macro for the .o files corresponding to the .C 
#   files in this directory (note they will be stored in the ../obj
#   directory
#2) need a target (with a name that doesn't match a file)
#   that is dependent upon the .o files 
#3) need a .o target for each .C
#4) need a clean target to delete the .o files in the ../obj directory



 
#This rule creates the ../obj directory if it doesn't exist
#This needs to be at the bottom of the makefile
create$(OBJD):
	mkdir -p $(OBJD)
