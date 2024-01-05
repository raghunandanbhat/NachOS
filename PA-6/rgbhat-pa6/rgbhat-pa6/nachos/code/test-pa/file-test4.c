#include "syscall.h"
#include "stdbool.h"

int tostring(char str[], int num)
{
    int i, rem, len = 0, n;
    bool isNegative = false;

    if(num < 0){
	isNegative = true;
	len++;		
	num = (-1) * num;
    }
    if(num == 0){
	str[0] = 0 + '0';
	len++;
    }
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    
    if(isNegative){
    	for (i = 0; i < len-1; i++)
    	{
        	rem = num % 10;
        	num = num / 10;
        	str[len - (i + 1)] = rem + '0';
    	}
	str[0] = '-';
    }else{
 	for (i = 0; i < len; i++)
    	{
        	rem = num % 10;
        	num = num / 10;
        	str[len - (i + 1)] = rem + '0';
    	}
    }
	
    str[len] = '\0';
  return len+1;
}
 

int main(){
	
	int read_bytes = 0, length = 0;
	char* str = "Hello from test-file4\n";
	OpenFileId id, close_id, open_id;
	char buffer[100];
	char nofbytes[100];

	if(Create("file-test4.txt") < 0){
		Write("Error creating file\n", 21, ConsoleOutput);
		Exit(1);
	}

	id = Open("file-test4.txt");
	if(id < 0){
		Write("Error opening file\n", 20, ConsoleOutput);
		Exit(1);
	}else{
		Write(str, 22, id);
	}
	Close(id);
	
	open_id = Open("file-test4.txt");
	if(open_id > 0){
		read_bytes = Read(&buffer, 22, open_id);
		if(read_bytes > 0){
			Write("Read(): Successful: read ", 25, ConsoleOutput);
			length = tostring(&nofbytes, read_bytes);
			Write(&nofbytes, length, ConsoleOutput);
			Write(" bytes\n", 7, ConsoleOutput);
		}else{
			Write("Read(): Failed: returned ", 25, ConsoleOutput);
			length = tostring(&nofbytes, read_bytes);
			Write(&nofbytes, length, ConsoleOutput);
			Write("\n", 1, ConsoleOutput);
		}
	}
	
	close_id = Close(open_id);

	if(close_id < 0){
		Write("Close(): Failed: returned ", 26, ConsoleOutput);
		length = tostring(&nofbytes, close_id);
		Write(&nofbytes, length, ConsoleOutput);
		Write("\n", 1, ConsoleOutput);
	}else{
		Write("Close(): Successful: returned ", 30, ConsoleOutput);
		length = tostring(&nofbytes, close_id);
		Write(&nofbytes, length, ConsoleOutput);
		Write("\n", 1, ConsoleOutput);
	}
	
	read_bytes = Read(&buffer, 22, open_id);
	if(read_bytes > 0){
		Write("Read(): Successful: read ", 25, ConsoleOutput);
		length = tostring(&nofbytes, read_bytes);
		Write(&nofbytes, length, ConsoleOutput);
		Write(" bytes\n", 7, ConsoleOutput);
	}else{
		Write("Read(): Failed: returned ", 25, ConsoleOutput);
		length = tostring(&nofbytes, read_bytes);
		Write(&nofbytes, length, ConsoleOutput);
		Write("\n", 1, ConsoleOutput);
	}
	close_id = Close(open_id);

	if(close_id < 0){
		Write("Close(): Failed: returned ", 26, ConsoleOutput);
		length = tostring(&nofbytes, close_id);
		Write(&nofbytes, length, ConsoleOutput);
		Write("\n", 1, ConsoleOutput);
	}else{
		Write("Close(): Successful: returned ", 30, ConsoleOutput);
		length = tostring(&nofbytes, close_id);
		Write(&nofbytes, length, ConsoleOutput);
		Write("\n", 1, ConsoleOutput);
	}

Exit(0);
}
