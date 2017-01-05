//
//  main.cpp
//  Lab 4 Pipes
//
//  Created by Brian Lykes on 11/14/16.
//  Copyright © 2016 Brian Lykes. All rights reserved.
//  -Wno-write-strings

//This program shows an example of interprocess commnucation between parent and child processes as well as forking. 
//There is no input for this program. 

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<iostream>
#define READ 0

#define WRITE 1

using namespace std;


char* phrase = "from parent to child";

char* phrase2= "from child to parent";

int main(){
    
    int fd[2][2],bytesRead[2];
    
    char message[2][100];
    
    pipe(fd[0]);
    
    pipe(fd[1]);
    
    if(fork()==0) //Child (in child fork() returns 0)
        {
        
        close(fd[0][READ]);
        
        close(fd[1][WRITE]);
        
        write(fd[0][WRITE],phrase,strlen(phrase)+1);
        
        close(fd[0][WRITE]);
        
        bytesRead[1]=read(fd[1][READ],message[1],100);
        
        printf("Read %d bytes: %s\n",bytesRead[1],message[1]);
        printf("ID=%d\n",getpid());
        printf("Parent ID=%d\n",getppid());
        close(fd[0][READ]);
        cout << "This is the end of the child\n";
    }
    
    else //parent (in parent fork() returned PID of the child)
        {
        
        close(fd[0][WRITE]);
        
        close(fd[1][READ]);
        
        bytesRead[0]=read(fd[0][READ],message[0],100);
        
        printf("Read %d bytes: %s\n",bytesRead[0],message[0]);
        printf("ID=%d\n",getpid());
        
        close(fd[0][READ]);
        
        write(fd[1][WRITE],phrase2,strlen(phrase2)+1);
        
        close(fd[1][WRITE]);
        cout << "This is the end of the parent\n";
    }
    
}
