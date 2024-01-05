#include "syscall.h"

int main()
{
	
  int i, j;
  OpenFileId output = ConsoleOutput;
  char* name = "Raghunandan Bhat\n";
  char* date = "04/29/22\n";
  
  for (i = 0; i < 10; i++)
  {
    Write(name, 20, output);
    Write(date, 10, output);
    for (j = 0; j < 10000; j++);
  }
  Exit(0);
}
