/**************************************************************
 *
 * userprog/ksyscall.h
 *
 * Kernel interface for systemcalls 
 *
 * by Marcus Voelp  (c) Universitaet Karlsruhe
 *
 **************************************************************/

#ifndef __USERPROG_KSYSCALL_H__ 
#define __USERPROG_KSYSCALL_H__ 

#include "kernel.h"
#include<unistd.h>

//----------------------------------------------------------------------
//get_parameter
//given the start address of the parameter, extract the name of the
//parameter/filename

int get_parameter(char *filename, int start_addr){
	int ch, i = 0;
	if(kernel->machine->ReadMem(start_addr, 1, &ch)){
		while((char(ch) != '\0')){
			filename[i] = (char)ch;
			i++;
			start_addr++;
			kernel->machine->ReadMem(start_addr, 1, &ch);	
		}
		filename[i] = '\0';
		return i;
	}else{
		return -1;
	}
	return -1;
}

//---------------------------------------------------------------------
//SysHalt()

void SysHalt()
{
  kernel->interrupt->Halt();
}


int SysAdd(int op1, int op2)
{
  return op1 + op2;
}

//-------------------------------------------------------------
// Write System call
// Read 'size' amount of bytes from 'buf_addrs' and
//write it to 'dest_addrs' and return the number of
//bytes actually written to 'dest_buf'

int SysWrite(int buf_addrs, int size, int dest_addr){
	int i = -1;
	char* content = (char*)malloc((size+2) * sizeof(char));
	
	int len = get_parameter(content, buf_addrs);
	if(dest_addr == ConsoleOutput){
		if(len < 0){
			return -1;
		}else{
			cout << content;
			return len;
		}
	}else{
		int byte_count = write(dest_addr, content, size);
		if(byte_count < 0){
			return -1;
		}else{
			return byte_count;
		}
	}
	free(content);
	return i;
}


#endif /* ! __USERPROG_KSYSCALL_H__ */
