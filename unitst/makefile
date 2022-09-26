#lab4 makefile (complete)
CC = g++
INC = ../inc
BIN = ../bin
OBJD = ../obj
CFLAGS = -g -c -Wall -std=c++11 -I $(INC)
OBJ = $(OBJD)/lab4.o $(OBJD)/MemoryTester.o $(OBJD)/Memory.o $(OBJD)/Tools.o \
$(OBJD)/RegisterFile.o $(OBJD)/RegisterFileTester.o $(OBJD)/ConditionCodes.o \
$(OBJD)/ConditionCodesTester.o

$(OBJD)/%.o: %.C create$(OBJD)
	$(CC) $(CFLAGS) $< -o $(OBJD)/$@

run:
	make compile
	../bin/lab4

compile:
	(cd ../src && make)
	make $(BIN)/lab4

$(BIN)/lab4: $(OBJ)
	$(CC) $(OBJ) -o $(BIN)/lab4

objects: $(OBJ)

$(OBJD)/lab4.o: $(INC)/MemoryTester.h $(INC)/Memory.h

$(OBJD)/MemoryTester.o: $(INC)/MemoryTester.h $(INC)/Memory.h

$(OBJD)/RegisterFileTester.o: $(INC)/RegisterFile.h $(INC)/RegisterFileTester.h

$(OBJD)/ConditionCodesTester.o: $(INC)/ConditionCodes.h $(INC)/ConditionCodesTester.h

clean:
	rm ../bin/lab4
	rm $(OBJ)

create$(OBJD):
	mkdir -p $(OBJD)
