/* 
 * Driver for the yess simulator
 * Usage: yess <file>.yo [-D]
 *
 * <file>.yo contains assembled y86-64 code.
 * If the -D option is provided then debug is set to 1.
 * The -D option can be used to turn on and turn off debugging print
 * statements.
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include "Memory.h"
#include "String.h"
#include "Loader.h"
#include "Debug.h"

int debug = 0;

int main(int argc, char * argv[])
{
   //check to see if the -D option was provided 
   if (argc >= 3 && (strcmp(argv[2], "-D") == 0)) debug = 1;

   if (debug) std::cout << "Debugging print statements displayed\n";

   Memory * mem = Memory::getInstance();
   Loader loadObj(argc, argv, mem);
   loadObj.load();
   if (mem != NULL) mem->dump();
   
   return 0;
}

